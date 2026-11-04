# Cloud-Connected Security Node (IoT Telemetry)

**Internship Project 3 — DecodeLabs Industrial Training Kit**

An ESP32-based IoT telemetry demo. An HC-SR04 ultrasonic sensor measures distance, the ESP32 connects to Wi-Fi, and MQTT publishes the readings to an Adafruit IO feed for a live cloud dashboard.

> **Demo limitation:** This is an educational proximity-monitoring prototype, not a certified security or intruder-detection system. Distance readings alone cannot identify a person or guarantee security.

## 1. Project requirements

- Connect the ESP32 to a local Wi-Fi network.
- Read sensor data (example: ultrasonic distance).
- Publish telemetry using MQTT.
- Visualize live readings on a cloud dashboard (Adafruit IO).

## 2. Hardware

- ESP32 development board
- HC-SR04 ultrasonic distance sensor
- 1 kΩ resistor and 2 kΩ resistor for the Echo voltage divider
- Breadboard and jumper wires
- USB cable and suitable power source

## 3. Wiring

| HC-SR04 | ESP32 / supply |
|---|---|
| VCC | 5V / VIN (check your board) |
| GND | GND |
| TRIG | GPIO 5 |
| ECHO | GPIO 18 through a voltage divider |

**Important: HC-SR04 Echo is typically 5V. ESP32 GPIO pins are not 5V tolerant. Do not connect Echo directly to ESP32.**

Voltage divider:
- HC-SR04 ECHO → 1 kΩ resistor → GPIO 18 node.
- GPIO 18 node → 2 kΩ resistor → GND.
- ESP32 and sensor grounds must be connected together.

This reduces the Echo signal to approximately 3.3V. Confirm your sensor's specifications before wiring.

## 4. Cloud setup (Adafruit IO)

1. Create an account at https://io.adafruit.com/.
2. Open **Feeds** and create a feed named `security-distance`.
3. Open **Dashboards** and create a dashboard named `Security Node`.
4. Add a **Line Chart** or **Gauge** block and select the `security-distance` feed.
5. In your Adafruit IO account settings, locate your username and active AIO key.
6. Put your Wi-Fi name, Wi-Fi password, Adafruit IO username, and AIO key into the placeholders in the sketch.
7. Keep credentials private. Never commit real Wi-Fi passwords or AIO keys to a public GitHub repository.

## 5. Arduino IDE setup

1. Install Arduino IDE and the ESP32 board package.
2. In Library Manager, install **PubSubClient** by Nick O'Leary.
3. Open `CloudConnectedSecurityNode.ino`.
4. Enter your credentials locally in the sketch.
5. Select your ESP32 board and port, then upload.
6. Open Serial Monitor at **115200 baud**.
7. Check the Adafruit IO feed and dashboard.

This starter uses MQTT over TCP on port 1883 for a simple learning demonstration. For a production deployment, use TLS and appropriate credential management.

## 6. Expected output

Serial Monitor (example only):

```text
Connecting to Wi-Fi...
Wi-Fi connected
Connecting to Adafruit IO MQTT...
MQTT connected
Distance: 84.2 cm | MQTT publish: success
Distance: 32.7 cm | MQTT publish: success
Distance: 12.4 cm | MQTT publish: success
```

Your measurements and timing will vary.

## 7. Repository files

- `CloudConnectedSecurityNode.ino` — ESP32 + ultrasonic + Wi-Fi + MQTT firmware
- `WIRING.md` — wiring and voltage-level notes
- `CLOUD_SETUP.md` — Adafruit IO feed/dashboard instructions
- `WORKFLOW.md` — data flow
- `.gitignore` — common files to exclude

## 8. Before submitting

- Test the sensor locally before configuring MQTT.
- Verify Wi-Fi connection.
- Verify the MQTT connection and feed updates.
- Check the dashboard displays incoming data.
- Add your own circuit and dashboard screenshots after testing.
- Remove credentials before uploading code to a public repository.
- Do not claim that the system is physically tested unless you have tested it.
