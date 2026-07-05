# Raspberry Pi Software Plan

This folder has the Raspberry Pi 5 software plan for Car Vault.

## Raspberry Pi 5 Jobs

The Raspberry Pi 5 will:

- Get USB camera frames
- Run SLAM tests
- Read the IMU if the MPU6050 is safe for direct Pi I2C
- Use encoder data from the ESP32-S3
- Build an occupancy grid map
- Run A* path planning
- Send movement commands to the ESP32-S3
- Add YOLO later using the Raspberry Pi AI HAT+ 26 TOPS / Hailo-8

## Planned Software Modules

```text
camera/        camera frames and settings
sensors/       IMU and encoder data
slam/          SLAM tests and position estimates
mapping/       map grid
planning/      A* path planning
control/       movement commands to ESP32-S3
robot_config/  real measurements after hardware bring-up
```

## Important Rule

I should not guess final robot values. Wheel diameter, wheelbase, encoder ticks, camera FPS, IMU direction, and PID values need to be measured or tested first.
