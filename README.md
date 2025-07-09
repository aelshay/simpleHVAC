# Arduino HVAC Fan Control System (Work in Progress)

A custom-built HVAC-style fan controller using Arduino, designed to read temperature and humidity, control a fan through a transistor switch, sweep a servo for directional air movement, and allow interaction via an LCD menu, buttons, and a potentiometer.

> **⚠️ Note:** This project is a work in progress, being actively developed and refined for real-world testing and demonstration. Final images and wiring diagram will be added when hardware is finalized.

---

## Features

* DHT11 for temperature and humidity sensing
* 16x2 LCD menu interface (non-I2C)
* Button + potentiometer menu navigation
* Adjustable temperature setpoint
* Toggle AC mode (fan reacts to room temp)
* Fan speed level (low, mid, high)
* Servo-controlled fan motion (optional sweep mode)
* PWM fan control using transistor switching

---

## Components Used

| Component          | Model/Type              |
| ------------------ | ----------------------- |
| Microcontroller    | Arduino Uno R3          |
| Temperature Sensor | DHT11                   |
| Servo Motor        | SG90 or similar         |
| DC Fan             | 5V kit fan              |
| Transistor         | 2N2222A / S8050         |
| LCD Display        | 16x2 Parallel (non-I2C) |
| Potentiometer      | 10k                     |
| Push Buttons       | Tactile x2              |
| Breadboard PSU     | 5V module               |
| Resistors          | 330Ω (transistor base)  |

---

## Wiring Table

| Component             | Arduino Pin |
| --------------------- | ----------- |
| DHT11 (signal)        | D2          |
| Servo                 | D3          |
| Button Left           | D4          |
| Button Right          | D5          |
| LCD RS                | D12         |
| LCD E                 | D11         |
| LCD D4                | D10         |
| LCD D5                | D9          |
| LCD D6                | D8          |
| LCD D7                | D7          |
| Fan Transistor Base   | D13         |
| Potentiometer (wiper) | A0          |

> GND and 5V lines shared among components; fan powered via breadboard PSU. Arduino GND tied to PSU GND.

---

## Menu System

Use **Left** and **Right** buttons to cycle through menu items. Use the **potentiometer** to adjust each selected setting.

### Menu Items:

1. **Temp/Humidity** – View current sensor readings
2. **Set Temp** – Adjust setpoint (15–35°C)
3. **Fan Motion** – Toggle servo sweep mode
4. **AC Control** – Enable/disable fan automation
5. **Fan Power** – Select fan power level (Low / Mid / High)

---

## How It Works

* When **AC mode is ON** and **room temperature > setpoint**, fan turns on.
* Fan power level determines PWM strength.
* If **Fan Motion** is ON, the servo slowly sweeps to direct airflow.
* LCD displays system status and user adjustments.

---

## Status

✅ Core features functional (servo, LCD, DHT, buttons, potentiometer)

⚠️ Fan transistor circuit under final testing — fan control code is included but physical behavior may vary.

📸 Images and final schematic to be uploaded when hardware layout is finalized.

---


## 📜 License

MIT License — open for learning and non-commercial modification.
