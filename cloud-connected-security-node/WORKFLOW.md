# Project Workflow

```text
HC-SR04 Ultrasonic Sensor
          |
          | Echo pulse / distance
          v
ESP32 Microcontroller
          |
          | Connect to local Wi-Fi
          v
MQTT Client (PubSubClient)
          |
          | Publish numeric telemetry
          v
Adafruit IO MQTT Broker
          |
          v
security-distance Feed
          |
          v
Cloud Dashboard (Gauge / Line Chart)
```

## Data cycle

1. Trigger the ultrasonic sensor.
2. Measure the Echo pulse duration.
3. Convert pulse duration to distance in centimeters.
4. Connect/reconnect to Wi-Fi and MQTT as needed.
5. Publish the distance value every five seconds.
6. View incoming values on the Adafruit IO dashboard.
