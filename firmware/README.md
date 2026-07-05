# Firmware Plan

This folder has the ESP32-S3 motor-control plan.

## ESP32-S3 Jobs

The ESP32-S3 will:

- Read the left and right motor encoders
- Send PWM to the motors
- Control motor direction
- Run wheel-speed PID
- Stop the motors if commands get stale
- Handle stop commands
- Send debug data back
- Talk to the Raspberry Pi 5 over USB serial

## Safety Requirements

The firmware must stop the motors if:

- It gets a `STOP` command.
- Serial commands stop coming in.
- A command runs out of time.
- A motor fault is detected.
- A speed command is too high.

## Logic-Level Requirement

The ESP32-S3 uses 3.3V GPIO. If an encoder signal is 5V, it needs to go through a logic-level shifter before connecting to the ESP32-S3.

## Included Source

`esp32_s3_motor_controller/main.cpp` is only a starter file. Final pin numbers, PID values, and speed limits need to be filled in after the real wiring and measurements are done.
