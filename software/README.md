# Raspberry Pi Software Plan

This folder has the Raspberry Pi 5 high-level software plan for the Car Vault SLAM robot.

## Raspberry Pi 5 Jobs

The Raspberry Pi 5 will handle:

- USB camera capture
- SLAM experiments
- IMU reading if the MPU6050 is verified safe for direct Pi I2C
- Odometry processing from ESP32-S3 encoder telemetry
- Occupancy grid generation
- A* path planning
- High-level navigation commands
- Serial communication with the ESP32-S3
- Future YOLO object detection using the Raspberry Pi AI HAT+ 26 TOPS / Hailo-8

## Planned Software Modules

```text
camera/        USB camera capture and camera settings
sensors/       IMU and encoder telemetry interfaces
slam/          ORB-SLAM3 tests and pose estimation
mapping/       Occupancy grid representation
planning/      A* path planning and waypoint output
control/       High-level movement commands to ESP32-S3
robot_config/  Measured robot constants after hardware bring-up
```

## Important Rule

Final calibration and control values should not be guessed. Values like wheel diameter, wheelbase, encoder ticks per revolution, camera FPS, IMU orientation, and PID constants must be measured or tested first.
