# Adafruit IO Cloud Setup

1. Sign up or log in at https://io.adafruit.com/.
2. Open **Feeds** and create a feed named `security-distance`.
3. Open **Dashboards** and create `Security Node`.
4. Add a Line Chart or Gauge block.
5. Select the `security-distance` feed as the block's data source.
6. Find your Adafruit IO username and active AIO key in account settings.
7. Enter them into the local sketch, along with your Wi-Fi credentials.
8. Upload the sketch to the ESP32 and check that the feed receives numeric distance values.

The MQTT topic used by the sketch is:

`YOUR_ADAFRUIT_IO_USERNAME/feeds/security-distance`

The sketch uses `io.adafruit.com` on MQTT TCP port `1883` for a simple training example. Do not expose real credentials in a public repository. For production, use encrypted transport (TLS), secure secret storage and access controls.
