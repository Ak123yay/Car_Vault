# Selected Parts

This file explains the parts I picked for the Stardance/Outpost funding request.

## Final Plan

```text
Raspberry Pi 5 = SLAM, mapping, A*, camera work, and high-level navigation
ESP32-S3 = encoders, PID motor control, PWM, safety stop, and telemetry
DRV8833 = small dual motor driver
N20 encoder motors = drivetrain and wheel feedback
MPU6050 = IMU heading/orientation support after voltage-safety checks
USB camera = visual SLAM input
```

## Funding Items

| Item | Why I picked it |
| --- | --- |
| MECCANIXITY 100RPM N20 6V encoder motors | These are slow enough to control indoors, and the encoders help with odometry and PID. |
| KOOBOOK DRV8833 motor driver | This can drive the two small N20 motors and is a better fit than an L298N for this robot. |
| MECCANIXITY N20 brackets | These make it easier to mount the motors cleanly to the printed chassis. |
| ESP32-S3-DevKitC-1-N16R8 | This is the low-level controller for encoders, motor PWM, PID, safety stop, and telemetry. |
| 4-channel logic-level shifters | These protect the ESP32-S3 3.3V pins if an encoder or sensor signal is 5V. |
| 4xAA battery holder + AA cells | This gives the motors their own 6V-class power rail. |
| Brass standoff/screw kit | These help mount the boards and parts neatly to the chassis. |
| N20 D-hole wheels | These fit the 3mm D-shaft N20 motors. |
| Raspberry Pi 5 UPS/battery parts | These let the Pi run untethered later, instead of needing a wall power cable during movement tests. |

## Items Not Requested

| Item | Reason |
| --- | --- |
| Acrylic sheet | I am 3D printing the chassis/base instead. |
| Ball caster | I am 3D printing the front skid/support instead. |
| Raspberry Pi 5 | I already own it. |
| USB camera | I already own it. |
| MPU6050 | I already have one, but I still need to verify it is safe to wire. |
| Raspberry Pi AI HAT+ | I already own it, and it is only for future YOLO work. |
| Arduino Uno | I already own it, and it is only a backup if the ESP32-S3 path has problems. |

Estimated funding subtotal: **$151.59**.
