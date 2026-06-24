# _code-map.md - Car Vault Code Structure

This file maps robotics concepts to future implementation paths. Do not write code outside this structure unless this file is updated first.

---

## Repository Layout

```text
Car_Vault/
  raw/                         <- source notes and unprocessed input
  wiki/                        <- engineering documentation only
  project-code/                <- robot implementation goes here
    car_vault/
      main.py                  <- runtime entrypoint
      config/
        robot.yaml             <- measured hardware and runtime settings
        slam_orbslam3.yaml     <- ORB-SLAM3 camera/IMU configuration
      sensors/
        camera.py              <- camera capture and frame timestamps
        imu.py                 <- IMU readout, bias correction, timestamps
        encoders.py            <- encoder tick capture and odometry deltas
      slam/
        orbslam3_bridge.py     <- ORB-SLAM3 integration boundary
        pose_fusion.py         <- pose selection/fusion policy
      mapping/
        occupancy_grid.py      <- grid representation and obstacle costs
      planning/
        astar.py               <- A* path planner
        waypoints.py           <- path-to-waypoint conversion
      control/
        pid.py                 <- PID controller primitive
        differential_drive.py  <- left/right motor mixing
      motors/
        motor_driver.py        <- motor driver interface
      operations/
        failure_manager.py     <- fallback and stop behavior
      perception/
        hailo_yolo.py          <- Hailo-8 YOLO inference integration
        yolo_detector.py       <- object detection wrapper used by navigation
    firmware/
      arduino_uno/
        motor_controller.ino   <- encoder interrupts, wheel PID, motor driver PWM
    tests/
      test_odometry.py
      test_astar.py
      test_pid.py
```

---

## Concept Mapping

| Concept | Wiki source | Code path |
| --- | --- | --- |
| System architecture | `wiki/architecture/system-design.md` | `project-code/car_vault/main.py` |
| Software modules | `wiki/architecture/modules.md` | `project-code/car_vault/*` |
| Hardware measurements | `wiki/architecture/hardware-design.md`, `wiki/architecture/front-support-and-chassis-plan.md`, and `wiki/architecture/phase-1-measurement-worksheet.md` | `project-code/car_vault/config/robot.yaml` |
| Wiring and pin assignments | `wiki/architecture/wiring-and-pin-plan.md` | `project-code/firmware/arduino_uno/motor_controller.ino` and `project-code/car_vault/config/robot.yaml` |
| Pi-to-Arduino serial protocol | `wiki/architecture/serial-protocol-and-safety.md` | `project-code/firmware/arduino_uno/motor_controller.ino` and Pi-side serial integration under `project-code/car_vault/` |
| Encoder calibration | `wiki/architecture/sensor-calibration.md` | `project-code/car_vault/sensors/encoders.py` |
| IMU calibration | `wiki/architecture/sensor-calibration.md` | `project-code/car_vault/sensors/imu.py` |
| Camera calibration | `wiki/architecture/sensor-calibration.md` | `project-code/car_vault/sensors/camera.py` |
| ORB-SLAM3 config | `wiki/architecture/slam-configuration.md` | `project-code/car_vault/config/slam_orbslam3.yaml` |
| SLAM bridge | `wiki/architecture/slam-configuration.md` | `project-code/car_vault/slam/orbslam3_bridge.py` |
| Occupancy grid | `wiki/features/navigation-planning.md` | `project-code/car_vault/mapping/occupancy_grid.py` |
| A* planner | `wiki/features/navigation-planning.md` | `project-code/car_vault/planning/astar.py` |
| Waypoint output | `wiki/features/navigation-planning.md` | `project-code/car_vault/planning/waypoints.py` |
| PID controller | `wiki/features/control-system.md` | `project-code/car_vault/control/pid.py` |
| Motor mixing | `wiki/features/control-system.md` | `project-code/car_vault/control/differential_drive.py` |
| Motor driver | `wiki/architecture/hardware-design.md` | `project-code/car_vault/motors/motor_driver.py` |
| Arduino Uno firmware | `wiki/architecture/hardware-design.md` | `project-code/firmware/arduino_uno/motor_controller.ino` |
| Failure handling | `wiki/operations/failure-handling.md` | `project-code/car_vault/operations/failure_manager.py` |
| Hailo YOLO inference | `wiki/ai_agents/perception-yolo.md` | `project-code/car_vault/perception/hailo_yolo.py` |
| YOLO future layer | `wiki/ai_agents/perception-yolo.md` | `project-code/car_vault/perception/yolo_detector.py` |
| Validation tests | `wiki/testing/test-strategy.md` | `project-code/tests/*` |

---

## Timing Targets

| Loop | Target rate | Owner |
| --- | ---: | --- |
| Camera capture | 30 FPS | `sensors/camera.py` |
| Hailo YOLO inference | Camera-dependent | `perception/hailo_yolo.py` on Raspberry Pi AI HAT+ 26 TOPS |
| IMU readout | 200 Hz | `sensors/imu.py` |
| Encoder readout | 50-200 Hz, hardware-dependent | `firmware/arduino_uno/motor_controller.ino` streams ticks to `sensors/encoders.py` |
| SLAM update | Camera frame rate or ORB-SLAM3 output rate | `slam/orbslam3_bridge.py` |
| Planner | 1-5 Hz or on map/goal changes | `planning/astar.py` |
| Control | 50-100 Hz | `control/differential_drive.py` |

---

## Implementation Rules

- Use measured values from `hardware-design.md` and `sensor-calibration.md`.
- Keep hardware access isolated in `sensors/` and `motors/`.
- Keep low-level Arduino firmware in `project-code/firmware/arduino_uno/`.
- Keep planning independent from motor control.
- Keep YOLO optional until base navigation passes validation.
- Add tests before changing shared math such as odometry, A*, or PID.
