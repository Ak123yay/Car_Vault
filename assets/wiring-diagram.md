# Wiring Diagram

## Main Connections

```text
Raspberry Pi 5
  |-- USB port ------ USB Camera
  |-- USB port ------ ESP32-S3 DevKitC-1
  |-- I2C SDA/SCL --- MPU6050 only if confirmed 3.3V-safe
  `-- USB-C power --- Stable Pi 5 power supply

ESP32-S3
  |-- GPIO pins ---------- Logic-level shifter outputs from encoders
  |-- PWM/direction GPIO - DRV8833 motor driver input pins
  |-- GND ---------------- DRV8833 GND + motor battery negative reference
  `-- USB ---------------- Raspberry Pi 5 serial communication

Logic-Level Shifter
  |-- High-voltage side -- Possible 5V encoder A/B signals
  |-- Low-voltage side --- ESP32-S3 3.3V GPIO signals
  `-- GND --------------- Shared signal ground

DRV8833 Motor Driver
  |-- VM / motor power --- 4xAA motor battery positive
  |-- GND --------------- ESP32-S3 GND + motor battery negative
  |-- A outputs ---------- Left N20 motor
  `-- B outputs ---------- Right N20 motor
```

## Power Rules

```text
Pi 5 power rail:
  The Pi 5 gets its own stable 5V USB-C power source.

Motor power rail:
  The motors get separate 6V-class power through the DRV8833.

Common reference:
  ESP32-S3 GND, motor driver GND, and motor battery negative connect together.

Do not connect:
  Motor battery positive must never connect to Raspberry Pi 5V or ESP32-S3 3.3V.
```

## Encoder Signal Rule

Because the ESP32-S3 uses 3.3V GPIO, encoder signals must go through a logic-level shifter unless they are measured and confirmed 3.3V-safe.

## Motor Driver Rule

```text
Preferred: DRV8833
Acceptable fallback: TB6612FNG
Avoid: L298N for the final robot
```
