# Firmware Plan

This folder has the ESP32-S3 low-level control plan.

## ESP32-S3 Jobs

The ESP32-S3 will handle:

- Left and right motor encoder reading
- Motor PWM output
- Motor direction output
- Wheel-speed PID control
- Watchdog stop if commands get stale
- Stop command handling
- Telemetry/debug output
- USB serial communication with the Raspberry Pi 5

## Safety Requirements

The firmware must stop the motors if:

- A `STOP` command is received.
- Serial commands stop arriving.
- A command duration expires.
- A motor fault is detected.
- A command is above the safe speed limit.

## Logic-Level Requirement

The ESP32-S3 uses 3.3V GPIO. Encoder signals must be verified as 3.3V-safe or routed through a logic-level shifter before connecting to ESP32-S3 pins.

## Included Source

`esp32_s3_motor_controller/main.cpp` is only a bring-up skeleton. Final pin assignments, PID constants, and speed limits must be filled in after the real wiring and measurements are done.
