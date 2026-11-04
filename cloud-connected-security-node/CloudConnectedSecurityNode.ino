/*
  Project 3: Cloud-Connected Security Node (IoT Telemetry)
  Board: ESP32
  Sensor: HC-SR04 ultrasonic distance sensor
  Cloud: Adafruit IO via MQTT (PubSubClient)

  EDUCATIONAL PROTOTYPE ONLY — not a certified security system.

  IMPORTANT:
  HC-SR04 Echo is typically 5V. Use the resistor voltage divider
  described in WIRING.md before connecting Echo to the ESP32.
*/

#include <WiFi.h>
#include <PubSubClient.h>

// ---------- Fill these in on your local copy only ----------
const char* WIFI_SSID     = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

const char* AIO_USERNAME  = "YOUR_ADAFRUIT_IO_USERNAME";
const char* AIO_KEY       = "YOUR_ADAFRUIT_IO_KEY";

// ---------- Adafruit IO MQTT ----------
const char* MQTT_SERVER = "io.adafruit.com";
const int MQTT_PORT = 1883;

// Adafruit IO MQTT topic format: username/feeds/feed-key
char mqttTopic[128];

// ---------- Hardware pins ----------
const int TRIG_PIN = 5;
const int ECHO_PIN = 18; // Must receive <= 3.3V through a divider.

// ---------- Timing ----------
const unsigned long PUBLISH_INTERVAL_MS = 5000;
unsigned long lastPublishTime = 0;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void connectWiFi() {
  if (WiFi.status() == WL_CONNECTED) return;

  Serial.print("Connecting to Wi-Fi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void connectMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Connecting to Adafruit IO MQTT...");

    // Client ID should be unique for each connected device.
    String clientId = "ESP32-SecurityNode-";
    clientId += String((uint32_t)ESP.getEfuseMac(), HEX);

    if (mqttClient.connect(clientId.c_str(), AIO_USERNAME, AIO_KEY)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, state=");
      Serial.print(mqttClient.state());
      Serial.println(" — retrying in 3 seconds");
      delay(3000);
    }
  }
}

float readDistanceCm() {
  // Ensure a clean trigger pulse.
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(3);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Timeout prevents waiting indefinitely. HC-SR04 range is limited.
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);

  if (duration == 0) {
    return -1.0; // No valid echo within timeout.
  }

  return (duration * 0.0343f) / 2.0f;
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  snprintf(mqttTopic, sizeof(mqttTopic), "%s/feeds/security-distance",
           AIO_USERNAME);

  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);

  connectWiFi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  if (!mqttClient.connected()) {
    connectMQTT();
  }

  mqttClient.loop();

  unsigned long now = millis();
  if (now - lastPublishTime >= PUBLISH_INTERVAL_MS) {
    lastPublishTime = now;

    float distanceCm = readDistanceCm();

    if (distanceCm < 0) {
      Serial.println("No valid ultrasonic echo; skipping publish.");
      return;
    }

    char payload[16];
    snprintf(payload, sizeof(payload), "%.1f", distanceCm);

    bool published = mqttClient.publish(mqttTopic, payload);

    Serial.print("Distance: ");
    Serial.print(distanceCm, 1);
    Serial.print(" cm | MQTT publish: ");
    Serial.println(published ? "success" : "failed");
  }
}
