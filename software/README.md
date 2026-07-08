# This folder is meant to have all software running on the RPI 5

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

