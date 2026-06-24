# Software Architecture

## Purpose

Define the module layout, loop ownership, timing targets, and communication boundaries for future robot code.

Implementation must follow `wiki/_code-map.md`.

## Module Layout

```text
project-code/car_vault/
  sensors/
  slam/
  mapping/
  planning/
  control/
  motors/
  operations/
  perception/
  config/
```

## Module Responsibilities

| Module | Responsibility |
| --- | --- |
| `sensors/camera.py` | Capture frames and attach timestamps |
| `sensors/imu.py` | Read IMU data and apply bias correction |
| `sensors/encoders.py` | Convert ticks into wheel distance estimates |
| `slam/orbslam3_bridge.py` | Connect sensor streams to ORB-SLAM3 |
| `slam/pose_fusion.py` | Select or combine pose sources based on confidence |
| `mapping/occupancy_grid.py` | Store free, occupied, and unknown cells |
| `planning/astar.py` | Compute a path through the grid |
| `planning/waypoints.py` | Convert path cells into driveable waypoints |
| `control/pid.py` | PID primitive for wheel speed and heading control |
| `control/differential_drive.py` | Convert desired motion into left/right motor commands |
| `motors/motor_driver.py` | Send bounded commands to motor hardware |
| `operations/failure_manager.py` | Stop, fallback, or replan on system faults |
| `perception/hailo_yolo.py` | Future Hailo-8 inference integration |
| `perception/yolo_detector.py` | Future object detection, disabled until base navigation works |

## Timing Targets

| Loop | Target | Notes |
| --- | ---: | --- |
| Camera | 30 FPS | Match ORB-SLAM3 camera config |
| IMU | 200 Hz | Exact rate depends on sensor and bus stability |
| Encoders | 50-200 Hz | Prefer Arduino Uno interrupt capture, streamed to Pi 5 |
| SLAM | Camera frame rate or ORB-SLAM3 output rate | Must preserve timestamps |
| Occupancy grid update | 5-30 Hz | Depends on map source |
| A* planning | 1-5 Hz or event-driven | Replan on blocked path or new goal |
| PID control | 50-100 Hz | Prefer Arduino Uno for steady motor timing |

## Compute Split

Current hardware split:

| Board | Owns | Notes |
| --- | --- | --- |
| Raspberry Pi 5 | Camera, vision, SLAM, mapping, A*, high-level commands, preferred MPU6050 readout | Main compute board |
| Arduino Uno | Encoder interrupts, wheel PID, PWM/direction output, motor stop | Selected v1 low-level controller |

Pi 5 should send bounded targets to Arduino Uno over USB serial. Arduino Uno should return encoder counts, estimated wheel speeds, and fault/status flags.

Serial message names, units, command limits, watchdog behavior, and fault codes are defined in `wiki/architecture/serial-protocol-and-safety.md`.

First-pass wiring and pin assignments are defined in `wiki/architecture/wiring-and-pin-plan.md`.

Arduino firmware belongs in:

```text
project-code/firmware/arduino_uno/motor_controller.ino
```

## Data Contracts

### Pose

```text
pose = {
  x_m,
  y_m,
  theta_rad,
  timestamp_s,
  source,
  confidence
}
```

### Encoder Delta

```text
encoder_delta = {
  left_ticks,
  right_ticks,
  left_distance_m,
  right_distance_m,
  timestamp_s
}
```

### Occupancy Cell

```text
cell = {
  x_index,
  y_index,
  cost,
  state
}
```

Allowed states:

- `free`
- `occupied`
- `unknown`

### Motor Command

```text
motor_command = {
  left_speed,
  right_speed,
  duration_s,
  safety_limited,
  sequence_id
}
```

## Communication Rules

- Sensor modules publish timestamped readings only.
- SLAM and odometry modules own pose estimates.
- Planning consumes maps and poses, not raw motor state.
- Pi-side control consumes target waypoints and current pose.
- Arduino-side motor control receives bounded speed targets and owns PWM output.
- Arduino-side firmware owns final command clamping, duration expiry, and watchdog stop.
- Failure manager can override control output with stop commands.

## Threading Model

The first implementation can use separate loops for:

- Camera capture
- IMU/encoder readout
- SLAM update
- Planner
- Control

Shared data must include timestamps and should use queues or immutable snapshots once implementation begins.
