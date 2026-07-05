# Selected Parts

This file explains the parts I picked for the Stardance/Outpost funding request.

## Main Idea

```text
Raspberry Pi 5 = camera, mapping, path planning, and bigger robot decisions
ESP32-S3 = encoders, motor control, PID, safety stop, and debug data
DRV8833 = motor driver for the two small motors
N20 encoder motors = wheels plus movement feedback
MPU6050 = turning/orientation sensor after safety checks
USB camera = camera input for SLAM tests
```

## Funding Items

| Item | Why I picked it |
| --- | --- |
| MECCANIXITY 100RPM N20 6V encoder motors | These are slow enough for indoor testing, and the encoders help the robot know how far the wheels moved. |
| KOOBOOK DRV8833 motor driver | This is a small motor driver that fits the N20 motors better than an L298N. |
| MECCANIXITY N20 brackets | These help attach the motors to the printed chassis. |
| ESP32-S3-DevKitC-1-N16R8 | This board will handle the motor side of the robot. |
| 4-channel logic-level shifters | These help protect the ESP32-S3 pins if a signal is 5V. |
| 4xAA battery holder + AA cells | This gives the motors their own power source. |
| Brass standoff/screw kit | These are for mounting the boards and parts neatly. |
| N20 D-hole wheels | These should fit the 3mm D-shaft N20 motors. |
| Raspberry Pi 5 UPS/battery parts | These let the Pi run while the robot moves around, instead of needing a wall cable. |

## Items I Am Not Asking For

| Item | Reason |
| --- | --- |
| Acrylic sheet | I am 3D printing the chassis instead. |
| Ball caster | I am 3D printing the front skid/support instead. |
| Raspberry Pi 5 | I already own it. |
| USB camera | I already own it. |
| MPU6050 | I already have one, but I still need to check that it is safe to wire. |
| Raspberry Pi AI HAT+ | I already own it, and it is only for later YOLO work. |
| Arduino Uno | I already own it, and it is only a backup if the ESP32-S3 setup has problems. |

Estimated funding subtotal: **$151.59**.
