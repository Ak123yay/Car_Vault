# TASKS.md - Car Vault Work State

This file is the source of truth for current robotics work.

---

## Done

- [x] Replace prior vault context with Tier 3 robotics planning scope.
- [x] Compile raw planning input into engineering wiki documents.
- [x] Define the minimum planning document set: system architecture, hardware design, navigation, and control.
- [x] Define the advanced planning document set: SLAM configuration, sensor calibration, software architecture, testing, and failure handling.
- [x] Select drivetrain architecture: 2 powered encoder wheels plus CAD/printed passive front support.
- [x] Select compute architecture: Raspberry Pi 5 for vision/SLAM/navigation and Arduino Uno for v1 encoder/PID/motor control.
- [x] Select wheel usage plan: use 2 existing wheels as powered drive wheels and CAD/print front passive support instead of buying front drive hardware.
- [x] Add owned AI accelerator: Raspberry Pi AI HAT+ 26 TOPS with Hailo-8 for future YOLO/object detection.
- [x] Select camera interface: USB camera on Raspberry Pi 5.
- [x] Select IMU: use provided MPU6050 module.
- [x] Add explicit Amazon-order checklist, Pi power answer, and split motor/Pi power plan to active hardware docs.
- [x] Add deprecated-legacy routing so old Onara/SaaS wiki files are not treated as active robot docs.
- [x] Add first-pass wiring and pin plan for Pi 5, Arduino Uno, DRV8833, MPU6050, encoders, and split power.
- [x] Add Phase 1 bring-up checklist for purchase confirmation, bench wiring, motor tests, encoder checks, IMU checks, camera checks, and measurement capture.
- [x] Add Phase 1 measurement worksheet for received parts, wiring, measurements, and bring-up pass/fail results.
- [x] Add log routing so old Onara/SaaS logs are marked legacy and cannot override active robotics docs.
- [x] Lock selected Phase 1 hardware choices in root context files to prevent future regressions.
- [x] Mark `Onara_Design/` as deprecated legacy material and create a locked `project-code/` placeholder.
- [x] Run secret-pattern audit, sanitize scanner-triggering private-key/token placeholders, and redact legacy credential inventory text.
- [x] Run wiki routing integrity audit and confirm all wiki Markdown files are active or explicitly deprecated.
- [x] Align `PROJECT_CONTEXT.md` with locked Phase 1 hardware choices and remove stale generic hardware wording.
- [x] Tighten Phase 1 power and ground rules across active hardware docs.
- [x] Run implementation-boundary audit and add guard READMEs for legacy design and output directories.
- [x] Add explicit MPU6050 identity, voltage-safety, and Pi I2C fallback verification gates.
- [x] Add explicit encoder/controller logic-level verification gates and lock Arduino Uno as the Phase 1 encoder/PID controller.
- [x] Split Phase 1 materials into already-owned, first-cart, conditional-later, and do-not-buy categories.
- [x] Add product-page acceptance criteria for first-cart hardware purchases.
- [x] Add front support and chassis mechanical design specification.
- [x] Add Pi-to-Arduino serial protocol and motor safety specification.
- [x] Select 4 alkaline AA cells as the Phase 1 motor test battery source.

---

## Active

Current phase: Phase 1 - Fill in real hardware measurements and part choices.

Execution rule:

1. Work on the first unchecked task in the active or backlog sections.
2. Do not write production robot code until the relevant wiki document and `_code-map.md` mapping exist.
3. Keep implementation inside `project-code/` only.

---

## Backlog

### Phase 1 - Hardware Measurements

- [ ] Order 1x MECCANIXITY 2pcs 100RPM Micro Gear Motor with Encoder, N20 DC6V, 1:150 reduction ratio, 0.15A.
- [ ] Order 1x low-power dual motor driver, current recommendation: DRV8833 or TB6612FNG instead of L298N.
- [ ] Order N20 motor mounting brackets for the powered motors.
- [ ] Buy or confirm Raspberry Pi 5 bench power: official Raspberry Pi 27W USB-C PSU.
- [ ] Verify first-cart product pages against `wiki/architecture/current-build-and-materials.md#product-page-acceptance-checklist` before checkout.
- [ ] Buy mobile Pi 5 battery/UPS only if untethered testing is needed now; verify stable 5V 5A output and physical compatibility with the Raspberry Pi AI HAT+ stack before ordering.
- [ ] Buy or prepare motor battery holder: 4xAA holder with switch/leads.
- [ ] Buy or prepare 4 fresh alkaline AA cells for Phase 1 low-speed motor tests.
- [ ] Prepare chassis/base material: 3D printed plate, acrylic, plywood, or foam board.
- [ ] Prepare fasteners/standoffs: M2/M3 screws, nuts, standoffs, zip ties, or double-sided tape.
- [ ] Check whether existing wheels fit 3mm D-shaft N20 motors; order N20 3mm D-hole wheels only if they do not fit.
- [ ] CAD/print front passive support: preferred 1 center skid/ball-caster-style support; fallback 2 passive front wheels if the chassis needs 4 contact points.
- [ ] Verify provided MPU6050 module label, I2C wiring, and detected I2C address.
- [ ] Confirm final motor model and encoder type after order arrives.
- [ ] Confirm encoder supply voltage, output voltage, `VCC`, `GND`, `A`, and `B` wiring before connecting signal wires.
- [ ] Verify Arduino Uno encoder interrupt wiring and USB serial communication with Pi 5.
- [ ] Verify serial `PING`/`PONG`, `STOP`, watchdog stop, command clamp, and fault visibility before PID tuning.
- [ ] Confirm final DRV8833 board pin labels against `wiki/architecture/wiring-and-pin-plan.md`.
- [ ] Confirm MPU6050 can be safely wired to Pi 5 I2C at 3.3V, or route it through level shifting/Arduino fallback.
- [ ] Buy an I2C logic-level shifter only if MPU6050 direct Pi I2C is unsafe and Arduino fallback is not chosen.
- [ ] Record encoder ticks per revolution.
- [ ] Measure wheel diameter.
- [ ] Measure wheelbase.
- [ ] Record front support type, CAD/version, contact height, and low-PWM turn test result.
- [ ] Record USB camera model, resolution, FPS, mounting height, and tilt.
- [ ] Record MPU6050 mounting position and orientation.
- [ ] Document Pi 5 power source, motor battery voltage, shared-ground plan, regulator layout, and motor driver wiring.
- [ ] Fill in `wiki/architecture/phase-1-measurement-worksheet.md` as parts arrive and tests pass.
- [ ] Complete Phase 1 gate in `wiki/architecture/phase-1-bringup-checklist.md` before starting Phase 2 calibration.

### Phase 2 - Sensor Calibration

- [ ] Calculate centimeters per encoder tick.
- [ ] Run straight-line encoder distance test.
- [ ] Measure IMU gyro bias at rest.
- [ ] Define IMU drift correction process.
- [ ] Calibrate camera intrinsics.
- [ ] Record camera resolution and FPS.

### Phase 3 - SLAM Configuration

- [ ] Create ORB-SLAM3 camera configuration.
- [ ] Add IMU noise parameter estimates.
- [ ] Define camera and IMU timestamp synchronization.
- [ ] Validate SLAM pose output in a simple indoor path.

### Phase 4 - Navigation

- [ ] Define occupancy grid resolution and cost values.
- [ ] Implement or select A* planner after the grid format is fixed.
- [ ] Define waypoint output format.
- [ ] Test path planning on a static sample map.

### Phase 5 - Control

- [ ] Define differential-drive motor mixing.
- [ ] Tune wheel-speed PID.
- [ ] Tune heading PID.
- [ ] Add speed limits and turn-rate limits.
- [ ] Test 90-degree turn and 2-meter straight-line movement.

### Phase 6 - Failure Handling

- [ ] Define SLAM lost-tracking fallback.
- [ ] Define encoder mismatch handling.
- [ ] Define IMU drift threshold.
- [ ] Define sudden obstacle stop/replan behavior.

### Phase 7 - Future Perception

- [ ] Install and verify Raspberry Pi AI HAT+ 26 TOPS / Hailo-8 software on Pi 5.
- [ ] Run a Hailo YOLO object-detection demo on the Pi 5 camera stream.
- [ ] Add YOLO only after base navigation is stable.
- [ ] Define object classes that affect navigation.
- [ ] Decide whether YOLO outputs should modify the occupancy grid or act as a separate stop/replan signal.

---

## Notes

- Exact PID constants, camera intrinsics, IMU noise values, and dimensions are placeholders until measured.
- The current priority is engineering documentation and calibration readiness, not feature expansion.
