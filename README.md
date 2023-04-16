# Arduino Ghostbusters Tripod Trap

Arduino-based sketch to run a replica Ghostbusters 2 Tripod Trap
(aka 'Polarity Rectification Tripod')

## References
* [Tripod Trap 3D Files](https://github.com/OfficerSkidmark/Tripod-Trap-V4)
* [Build Thread on GBFans Forum](https://www.gbfans.com/forum/viewtopic.php?t=50774)

## Features
* Animated LED bargraph
* Animated Analog Gauge
* Startup animation sequence
* Flashing Antenna LEDs
* Flashing Wing Lamps
* (TODO) Adjustable Potentiometer
* (TODO) 3-Position Switch (OFF, ON, BAT. TEST)
* (TODO) External Multi-Unit Control Panel/Synchronization

## Components
* Arduino Nano
* HT16K33 LED Matrix Controller
* White LEDs (for Antenna and Wing Lamps)
* Warm-White 5V LED Strips for Center Light Column
* Wires & Resistors
* Analog Gauge (eg 5V Analog Voltmeter)
* 3-position Toggle Switch
* Blue Micro-Potentometer

## Pin Assignments
| Pin    | Assignment               | Constant Name      |
|--------|--------------------------|--------------------|
| 3      | Switch Upper (ON)        | N/A (unused)       |
| 4      | Switch Lower (BAT. TEST) | N/A (unused)       |
| 5      | Analog Gauge/Meter       | `ANALOG_METER_PIN` |
| 6      | Wing Lamp 1              | `FLASHER_PIN_0`    |
| 7      | Wing Lamp 2              | `FLASHER_PIN_1`    |
| 8,9,10 | Antenna Pins             | `ANTENNA_PINS`     |
| A0     | Potentiometer            | N/A (unused)       |
| A4,A5  | I2C SDA/SCL (HT16K33)    | N/A                |

