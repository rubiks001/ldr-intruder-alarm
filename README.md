# ldr-intruder-alarm

An Arduino-based intruder detection system that monitors a laser beam using an LDR. When the beam is broken, an RGB LED turns red and the buzzer plays Für Elise as an alarm. The system self-calibrates on startup and the alarm plays the full melody before resetting.

---

## Features

- Auto-calibrates laser beam baseline on startup (averages 20 readings over 1 second)
- Detects beam interruption using a configurable threshold (±200 analog units)
- Plays Für Elise melody on a passive buzzer when triggered
- RGB LED shows green for safe state and red for alarm state
- Alarm plays the full melody before resetting — beam restoration mid-song does not cancel it
- Lightweight and easy to extend

---

## Hardware Requirements

| Component | Quantity |
|---|---|
| Arduino Uno (or compatible) | 1 |
| LDR (Light Dependent Resistor) | 1 |
| Laser module (5V) | 1 |
| Passive Buzzer | 1 |
| RGB LED | 1 |
| 10kΩ Resistor (LDR pull-down) | 1 |
| 220Ω Resistors (RGB LED legs) | 3 |
| Breadboard + jumper wires | — |

---

## Wiring

| Component | Arduino Pin |
|---|---|
| LDR (voltage divider) | A0 |
| Passive Buzzer | D8 |
| RGB LED — Red | D7 |
| RGB LED — Green | D5 |
| RGB LED — Blue | D6 |
| Laser module | 5V / GND |

> **LDR wiring:** Point the laser directly at the LDR. Connect one leg of the LDR to 5V and the other to A0. Place a 10kΩ pull-down resistor between A0 and GND.

---

## How It Works

1. **Startup calibration** — On power-up, the Arduino samples the LDR 20 times over 1 second with the laser beam hitting it directly, and averages the readings to establish `baselineLight`. The RGB LED blinks green twice to confirm calibration is complete.

2. **Beam monitoring** — In the main loop, the LDR is read continuously. If the reading drops more than 200 units below the baseline (laser beam broken), the alarm triggers.

3. **Alarm state** — The RGB LED turns red and `playFurElise()` begins cycling through the full melody.

4. **Reset** — Once the full melody finishes, the buzzer stops, the LED returns to green, and the system goes back to monitoring the beam.

---

## Pin Configuration

```cpp
const int ldrPin    = A0;
const int buzzerPin = 8;
const int redPin    = 7;
const int greenPin  = 5;
const int bluePin   = 6;
```

Change these constants at the top of proxi_gate.ino to match your wiring.

---

## LED Colour States

| Colour | Meaning |
|---|---|
| Green (blinking) | Startup calibration complete |
| Green (solid) | Beam intact — safe state |
| Red (solid) | Beam broken — alarm active |

---

## Sensitivity Adjustment

The detection threshold is set at 200 analog units below baseline. To adjust:

```cpp
if (lightVal < baselineLight - 200)  // increase 200 to reduce sensitivity
```

- Higher value (e.g. 400) → less sensitive, fewer false triggers
- Lower value (e.g. 100) → more sensitive, triggers on smaller light changes

> Tip: Since a laser produces a tight focused beam, the LDR reading drops sharply when interrupted — a higher threshold like 400 works well for reliable detection.

---

## Getting Started

1. Clone the repo:
   git clone https://github.com/rubiks001/ldr-intruder-alarm.git

2. Open proxi_gate.ino in the Arduino IDE.

3. Wire up the components as described in the wiring table above.

4. Aim the laser module directly at the LDR.

5. Upload the sketch to your Arduino Uno.

6. On startup, wait for the RGB LED to blink green twice — calibration is done.

7. Break the laser beam to trigger the alarm.

---

## File Structure

ldr-intruder-alarm/
└── proxi_gate.ino    # Main sketch (setup, loop, melody, alarm logic)

---

## Built With

- Arduino Uno
- Arduino IDE
- C++ (Arduino framework)

---

## Author

Olatunde David Durojaiye
- GitHub: https://github.com/rubiks001
- LinkedIn: https://linkedin.com/in/olatunde-david-durojaiye-bb5985207

---

## License

This project is open source and available under the MIT License.
---

## Hardware Requirements

| Component | Quantity |
|---|---|
| Arduino Uno (or compatible) | 1 |
| LDR (Light Dependent Resistor) | 1 |
| Laser module (5V) | 1 |
| Passive Buzzer | 1 |
| Red LED | 1 |
| Green LED | 1 |
| 10kΩ Resistor (LDR pull-down) | 1 |
| 220Ω Resistors (LEDs) | 2 |
| Breadboard + jumper wires | — |

---

## Wiring

| Component | Arduino Pin |
|---|---|
| LDR (voltage divider) | A0 |
| Passive Buzzer | D8 |
| Red LED | D7 |
| Green LED | D6 |
| Laser module | 5V / GND |

> **LDR wiring:** Point the laser directly at the LDR. Connect one leg of the LDR to 5V and the other to A0. Place a 10kΩ pull-down resistor between A0 and GND.

---

## How It Works

1. **Startup calibration** — On power-up, the Arduino samples the LDR 20 times over 1 second with the laser beam hitting it directly, and averages the readings to establish `baselineLight`. The green LED blinks twice to confirm calibration is complete.

2. **Beam monitoring** — In the main loop, the LDR is read continuously. If the reading drops more than 200 units below the baseline (laser beam broken), the alarm triggers.

3. **Alarm state** — The red LED turns on, the green LED turns off, and `playFurElise()` begins cycling through the melody.

4. **Auto-cancel** — On every note, the LDR is re-checked. If the laser beam is restored mid-song, the buzzer stops immediately and the system returns to safe state without finishing the melody.

---

## Pin Configuration

const int ldrPin      = A0;
const int buzzerPin   = 8;
const int redLedPin   = 7;
const int greenLedPin = 6;

Change these constants at the top of proxi_gate.ino to match your wiring.

---

## Sensitivity Adjustment

The detection threshold is set at 200 analog units below baseline. To adjust:

if (lightVal < baselineLight - 200)  // increase 200 to reduce sensitivity

- Higher value (e.g. 300) → less sensitive, fewer false triggers
- Lower value (e.g. 100) → more sensitive, triggers on smaller light changes

> Tip: Since a laser produces a tight focused beam, the LDR reading drops sharply when interrupted — you can safely use a higher threshold (e.g. 400) for more reliable detection.

---

## Getting Started

1. Clone the repo:
   git clone https://github.com/rubiks001/ldr-intruder-alarm.git

2. Open proxi_gate.ino in the Arduino IDE.

3. Wire up the components as described in the wiring table above.

4. Aim the laser module directly at the LDR.

5. Upload the sketch to your Arduino Uno.

6. On startup, wait for the green LED to blink twice — calibration is done.

7. Break the laser beam to trigger the alarm.

---

## File Structure

ldr-intruder-alarm/
└── proxi_gate.ino    # Main sketch (setup, loop, melody, alarm logic)

---

## Built With

- Arduino Uno
- Arduino IDE
- C++ (Arduino framework)

---

## Author

Olatunde David Durojaiye
- GitHub: https://github.com/rubiks001
- LinkedIn: https://linkedin.com/in/olatunde-david-durojaiye-bb5985207

---

## License

This project is open source and available under the MIT License.
