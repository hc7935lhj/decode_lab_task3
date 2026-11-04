# Wiring Guide — ESP32 + HC-SR04

| HC-SR04 pin | Connection |
|---|---|
| VCC | 5V / VIN (check your ESP32 board) |
| GND | ESP32 GND |
| TRIG | ESP32 GPIO 5 |
| ECHO | ESP32 GPIO 18 through a resistor voltage divider |

## Echo voltage divider (required)

HC-SR04 Echo is typically a 5V signal, while ESP32 GPIO pins are 3.3V logic and are not 5V tolerant.

Use:
- 1 kΩ resistor between HC-SR04 ECHO and the GPIO 18 junction.
- 2 kΩ resistor between the GPIO 18 junction and GND.
- Connect GPIO 18 to the junction of the two resistors.

The divider reduces a 5V Echo signal to about 3.3V. Connect all grounds together.

Do not connect ECHO directly to ESP32. Verify the exact sensor module and board specifications before powering the circuit.
