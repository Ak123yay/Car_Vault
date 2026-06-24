# System Architecture

## Purpose

Define how the Tier 3 robot connects sensors, processing, mapping, planning, control, and motors.

Core flow:

```text
Sensors -> Processing -> Mapping -> Planning -> Control -> Motors
```

Expanded flow:

```text
Camera ----\
IMU --------> ORB-SLAM3 / Odometry -> Pose (x, y, theta) -> Occupancy Map -> A* -> Waypoints -> PID -> Motors
Encoders --/
```

## Hardware Blocks

| Block | Role | Notes |
| --- | --- | --- |
| USB camera | Visual feature input for SLAM and Hailo YOLO | Requires intrinsics, FPS, mounting, and distortion calibration |
| IMU | Orientation and acceleration input | MPU6050-class sensor is acceptable but drift must be measured |
| Wheel encoders | Wheel movement and odometry | Required for distance scale and slip/mismatch detection |
| Raspberry Pi 5 | Runs vision, camera capture, SLAM experiments, mapping, and planning | Selected main compute board |
| Raspberry Pi AI HAT+ 26 TOPS | Runs local AI inference | Owned Hailo-8 accelerator for YOLO/object detection |
| Arduino Uno | Low-level motor controller for v1 | Selected for encoder interrupts, PWM, wheel PID, and motor stop |
| Motor driver | Converts control output into motor power | Must support left/right motor commands |
| DC motors | 2WD differential-drive movement | 2 powered encoder motors selected; exact Amazon order pending |
| Passive front support | Physical support only | CAD/printed skid/caster-style support; optional passive wheels if needed |
| Pi power source | Powers Pi 5, USB camera, AI HAT, and Arduino over USB | Official 27W USB-C PSU for bench, or mobile 5V 5A Pi-compatible battery/UPS that works with the AI HAT+ stack |
| Motor battery/regulator | Powers motor driver and motors only | Separate 6V-class motor rail; Arduino GND, driver GND, and motor battery negative share reference; Pi ground normally reaches this through USB to Arduino |

## Software Blocks

| Block | Input | Output |
| --- | --- | --- |
| USB camera capture | Camera frames | Timestamped image frames |
| IMU reader | Raw accel/gyro | Bias-corrected IMU samples |
| Encoder reader | Left/right ticks from Arduino Uno over USB serial | Wheel deltas and odometry estimates |
| ORB-SLAM3 bridge | Frames, IMU samples, calibration | Pose estimate and map data |
| Hailo YOLO inference | Camera frames | Object detections for stop/replan or future semantic mapping |
| Occupancy grid | Map/obstacle data | Grid cells with traversal costs |
| A* planner | Grid, start pose, goal pose | Path or waypoint list |
| PID control | Target waypoint, current pose | Left/right motor commands |
| Failure manager | Health signals | Stop, fallback, or replan command |

## Data Flow

1. Camera produces timestamped frames at the target camera rate.
2. IMU produces timestamped orientation/acceleration samples at the target IMU rate.
3. The two powered wheel encoders produce left/right tick deltas captured by Arduino Uno and streamed to Pi 5 over USB serial.
4. ORB-SLAM3 consumes camera and IMU data to estimate pose and map structure.
5. Hailo-8 can run YOLO inference on camera frames after baseline navigation is stable.
6. Encoder odometry is used to validate motion scale and support fallback behavior.
7. Mapping converts pose and obstacle knowledge into an occupancy grid.
8. A* plans from current pose to goal across the occupancy grid.
9. PID converts waypoint error into motor commands.
10. Failure handling can stop, replan, or fall back to dead reckoning when confidence drops.

## Decision Flow

```text
Has valid pose?
  yes -> update map -> plan/replan if needed -> follow waypoint
  no  -> stop or switch to encoder + IMU dead reckoning

Is path blocked?
  yes -> stop -> update grid -> replan
  no  -> continue PID control

Are encoder/IMU readings inconsistent?
  yes -> slow down or stop -> flag calibration/fault
  no  -> continue
```

## Open Values

These must not be treated as final until measured:

| Value | Status |
| --- | --- |
| Wheel diameter | Pending |
| Wheelbase | Pending |
| Encoder ticks per revolution | Pending |
| Final Amazon motor SKU | MECCANIXITY N20 DC6V selected; confirm exact received listing after delivery |
| Low-level control owner | Arduino Uno selected for v1 encoder/PID/motor control |
| AI inference accelerator | Raspberry Pi AI HAT+ 26 TOPS / Hailo-8 owned |
| Camera height | Pending |
| Camera tilt | Pending |
| Camera intrinsics | Pending |
| IMU noise parameters | Pending |
| PID constants | Pending |
| Pi power source | Official 27W USB-C PSU selected for bench; mobile source pending only if untethered testing is needed |
| Motor battery voltage under load | Pending |
