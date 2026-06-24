# CONTEXT_LOCK.md - Car Vault Structural Rules

These boundaries apply to all future work in this vault.

---

## Architecture Boundaries

- The base robot is a differential-drive indoor robot.
- Core navigation stack is camera + IMU + encoders + ORB-SLAM3 + occupancy grid + A* + PID.
- YOLO is future work and must not replace the base navigation stack.
- Do not introduce ROS, ROS 2, or a new robotics framework unless `TASKS.md` explicitly adds that migration.
- Do not write production code until the relevant wiki document and `_code-map.md` mapping exist.

## Documentation Boundaries

- `TASKS.md` controls current work order.
- `wiki/_master-index.md` controls active wiki navigation.
- `wiki/_code-map.md` controls implementation paths.
- `wiki/_legacy-deprecated.md` identifies old non-robotics wiki files that must not be used for current decisions.
- `logs/_index.md` identifies active logs and deprecated legacy logs.
- `raw/` is unprocessed source input and is lower priority than the compiled wiki.
- Older legacy documents are deprecated unless explicitly reactivated.
- Log entries before the 2026-06-18 robotics reset are historical only and must not override current robotics docs.
- `Onara_Design/` is old Onara/SaaS frontend prototype material and must not be used for current robotics work unless explicitly reactivated.

## Hardware Boundaries

- Current main compute is Raspberry Pi 5.
- Current camera source is USB camera, not CSI ribbon camera.
- Current AI accelerator is Raspberry Pi AI HAT+ 26 TOPS / Hailo-8 for future YOLO only.
- Current low-level controller is Arduino Uno for v1 encoder interrupts, wheel PID, PWM, and motor stop.
- Do not replace Arduino Uno with ESP32, ESP32-S3, or another 3.3V controller for Phase 1 unless `TASKS.md` explicitly changes the low-level controller.
- Current IMU is the provided MPU6050 module if label and I2C detection confirm it.
- Current drivetrain is two powered 6V N20 encoder motors plus passive CAD/printed front support.
- Do not switch to 12V motors for this low-power build unless `TASKS.md` explicitly changes the motor architecture.
- Do not add extra front drive motors unless `TASKS.md` explicitly changes the drivetrain architecture.
- Do not buy another IMU unless the provided module fails identity or electrical verification.
- Phase 1 encoder A/B outputs go to Arduino Uno, not Pi GPIO.
- If a future controller uses 3.3V logic, verify encoder output voltage and add level shifting before wiring encoder outputs.
- Do not connect MPU6050 SDA/SCL directly to Pi GPIO unless the module is confirmed safe for 3.3V I2C.
- If MPU6050 voltage safety is unknown, use a logic-level shifter or Arduino Uno fallback until verified.
- Use DRV8833 first choice, TB6612FNG acceptable, and avoid L298N for the final robot.
- Pi 5 power and motor power are separate rails: Pi 5 uses a stable 5V 5A-class USB-C source; motors use a separate 6V-class motor rail.
- Common ground is required when control signals cross between Arduino, motor driver, and motor battery.
- Pi ground normally reaches the motor-control reference through the Pi-to-Arduino USB cable; add a direct Pi-to-driver ground only if needed and record it.
- Motor battery positive must never connect to Pi 5V or Arduino 5V.
- Do not invent final dimensions, encoder ticks, PID values, IMU noise values, or camera intrinsics.
- Placeholder values are allowed only when labeled as examples.
- Measurements must be recorded before calibration or control tuning is treated as complete.

## Control and Safety Boundaries

- Motor commands must eventually include speed limits.
- Arduino motor firmware must stop motors on stale serial commands, explicit `STOP`, and configured duration expiry.
- Autonomous motion must include a stop condition for invalid pose, lost tracking, or obstacle detection.
- Failure handling must be defined before unattended navigation tests.

## Scope Lock

Out of scope until the core stack is stable:

- YOLO-based semantic navigation.
- Outdoor navigation.
- Multi-floor mapping.
- Swarm or multi-robot coordination.
- Cloud robotics.
