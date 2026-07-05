# Stardance Submission Summary

## Status

This folder is ready to upload for the Stardance/Outpost hardware funding review.

## Included

- `README.md` with the project idea, diagrams, build plan, and demo plan
- `BOM.csv` with the parts, links, costs, and reasons
- `assets/system-diagram.png`
- `assets/wiring-diagram.png`
- `assets/chassis-sketch.png`
- `assets/demo-plan.md`
- `cad/` with the 3D-print files
- `firmware/` with the ESP32-S3 motor-control skeleton
- `software/` with the Raspberry Pi software plan
- `pcb/README.md` explaining why I do not need a custom PCB

## Funding Description

Car Vault is an indoor robot I am building so it can map a room and drive toward a goal. It uses a Raspberry Pi 5, ESP32-S3, USB camera, MPU6050 IMU, and N20 encoder motors.

The Raspberry Pi 5 handles the camera, SLAM tests, mapping, and A* path planning. The ESP32-S3 handles the wheel encoders, motor control, PID, safety stop behavior, and telemetry.

I am asking for funding for the parts I still need: the drivetrain, low-level controller, motor driver, level shifters, power parts, wheels, and mounting hardware. I will 3D print the chassis/base and front support myself, so I am not asking for acrylic sheet or a ball caster.

Estimated requested funding subtotal: **$151.59**.

## Final Human Action Required

Upload this folder to a GitHub repository and paste the funding description into the Stardance/Outpost funding form.
