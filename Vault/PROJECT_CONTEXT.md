# PROJECT_CONTEXT.md - Car Vault

## What This Vault Builds

Car Vault documents and guides a Tier 3 autonomous indoor robotics platform.

The robot uses camera-based SLAM, an IMU, wheel encoders, A* path planning, and PID motor control. A Raspberry Pi AI HAT+ 26 TOPS with Hailo-8 is available for YOLO object detection after the base navigation stack is stable.

Core system:

```text
Camera + IMU + Encoders -> ORB-SLAM3 / Odometry -> Occupancy Map -> A* -> PID -> Motors
```

## Current Stage

Phase 1 hardware bring-up preparation. The planning documents, current hardware direction, wiring plan, bring-up checklist, and measurement worksheet exist. No production robot code should be written until the remaining hardware is received, real measurements are recorded, and calibration requirements are updated in the wiki and tracked in `TASKS.md`.

## Target Robot Capability

- Build a usable indoor map.
- Estimate pose as `(x, y, theta)`.
- Fuse camera, IMU, and encoder information for more stable odometry.
- Plan a path to a goal point using A*.
- Drive a differential-drive chassis using PID control.
- Handle common failures such as SLAM tracking loss, encoder mismatch, IMU drift, and sudden obstacles.

## Locked Phase 1 Hardware Direction

- Differential-drive chassis with two powered wheels and a passive CAD/printed front support.
- Raspberry Pi 5 as main compute for camera capture, ORB-SLAM3 experiments, mapping, planning, and high-level navigation.
- Arduino Uno as v1 low-level controller for encoder interrupts, wheel PID, PWM, and motor stop.
- Encoder A/B signals route to Arduino Uno for Phase 1, not Pi GPIO.
- ESP32-S3 is not the selected Phase 1 controller. Switching to it requires a `TASKS.md` controller change and encoder logic-level verification.
- Forward-facing USB camera on Raspberry Pi 5; do not switch to a CSI ribbon camera unless `TASKS.md` changes the camera plan.
- Raspberry Pi AI HAT+ 26 TOPS / Hailo-8 for local YOLO inference after base navigation is stable.
- Provided MPU6050 module if confirmed by board label and I2C detection.
- Two 6V N20 encoder motors; current order target is MECCANIXITY 2pcs 100RPM Micro Gear Motor with Encoder, N20 DC6V, 1:150, 0.15A.
- Low-power dual motor driver; DRV8833 is first choice and TB6612FNG is acceptable. Avoid L298N for the final robot.
- Split power: Pi 5 uses its own stable 5V 5A-class USB-C rail; motors use a separate 6V-class motor rail. Arduino GND, motor driver GND, and motor battery negative share the motor-control reference; Pi ground normally reaches that reference through the Pi-to-Arduino USB cable.

Final received board labels, wheel fit, encoder details, dimensions, and electrical measurements are pending until parts arrive and are recorded.

## Software Stack Assumptions

- ORB-SLAM3 for visual-inertial SLAM.
- Encoder odometry for distance and scale correction.
- IMU integration for heading/orientation stability.
- Occupancy grid for planning.
- A* for global path planning.
- PID for low-level wheel and heading control.
- YOLO added later for object-aware perception using the Hailo-8 accelerator after navigation works.

## Engineering Priorities

1. Document architecture before implementation.
2. Record real robot measurements before calibration.
3. Validate sensors individually before fusing them.
4. Prove motion control before autonomous navigation.
5. Add Hailo-accelerated YOLO only after SLAM, planning, and control are reliable.

## What This Project Is Not Yet

- Not a ROS migration plan unless explicitly added to `TASKS.md`.
- Not a YOLO-first object detection project.
- Not ready for production code until hardware measurements are filled in.
- Not a place for unrelated non-robotics documentation.
