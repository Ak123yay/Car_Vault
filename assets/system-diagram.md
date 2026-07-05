# System Diagram

```text
USB Camera + MPU6050 IMU + Wheel Encoders
                    |
                    v
              Raspberry Pi 5
        SLAM / Mapping / A* / Navigation
                    |
                    v
              USB serial
                    |
                    v
                ESP32-S3
       Encoders / PID / PWM / Safety Stop
                    |
                    v
            DRV8833 Motor Driver
                    |
                    v
        Left and Right N20 Encoder Motors
```

## Data Flow

1. The USB camera sends frames to the Raspberry Pi 5.
2. The MPU6050 gives orientation data after voltage and I2C checks.
3. Wheel encoders send A/B signals through level shifting if needed.
4. The ESP32-S3 reads encoders and controls motor PWM.
5. The Raspberry Pi 5 estimates pose and builds a map.
6. The path planner uses A* to choose waypoints.
7. The Raspberry Pi sends movement commands to the ESP32-S3.
8. The ESP32-S3 runs low-level PID and safety-stop logic.
9. The DRV8833 powers the two N20 motors.
