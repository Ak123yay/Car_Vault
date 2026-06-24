# _decision-log.md - Car Vault Decisions

## 2026-06-18 - Tier 3 Robotics Documentation Reset

Decision: Replace the prior non-robotics active vault context with a Tier 3 autonomous robot planning stack.

Active stack:

- Camera for visual features.
- IMU for orientation correction.
- Wheel encoders for odometry and scale.
- ORB-SLAM3 for pose and map estimation.
- Occupancy grid for planning.
- A* for path planning.
- PID for motor control.
- YOLO as future perception after base navigation works.

Rationale:

- The user requested a full raw compile and replacement around robotics engineering planning documents.
- The old active vault context conflicted with the Car Vault project name and current robotics scope.
- A documentation-first structure is necessary before writing robot code because hardware measurements and calibration values are still unknown.

Impact:

- `TASKS.md`, `PROJECT_CONTEXT.md`, root context files, and active wiki indexes now describe the robotics system.
- Old legacy wiki files are deprecated unless explicitly reactivated.
- Future implementation must use `project-code/` paths from `_code-map.md`.

---

## 2026-06-19 - Legacy Wiki Routing Quarantine

Decision: Keep old Onara/SaaS files in place for recoverability, but mark them as deprecated and route all current work through the robotics source of truth.

Active routing:

- `TASKS.md` remains the highest-priority work tracker.
- `wiki/_master-index.md` remains the active robotics navigation map.
- `wiki/_legacy-deprecated.md` identifies old files and folders that must not be used for robot work.
- Section indexes now separate active robotics files from deprecated legacy files.

Rationale:

- The vault still contained many old Onara/SaaS files, including business, legal, integrations, data, dashboard, billing, and pipeline docs.
- Deleting them could remove recoverable history, but leaving them unmarked could cause incorrect hardware/software decisions.
- Explicit deprecation preserves history while preventing accidental use.

Impact:

- Active robotics work should ignore deprecated folders unless the user explicitly reactivates a file.
- Search results may still find old text, but the folder indexes and `_legacy-deprecated.md` identify it as inactive.
- New robot implementation must still follow `project-code/` paths from `_code-map.md`.

---

## 2026-06-19 - Phase 1 Purchase Triage

Decision: Split Phase 1 materials into already-owned parts, first-cart buys/prep, conditional-later buys, and do-not-buy items.

First-cart buys/prep:

- Official Raspberry Pi 27W USB-C PSU if not already owned.
- 1 pack of 2x 6V N20 encoder motors.
- DRV8833 dual motor driver, with TB6612FNG acceptable if DRV8833 is unavailable.
- N20 motor brackets.
- 4xAA motor battery holder or regulated 6V motor source.
- AA NiMH cells and charger if not already owned.
- Chassis/base material and basic fasteners/standoffs if not already available.

Conditional-later:

- N20 wheels only if existing wheels do not fit the 3mm D-shaft.
- Mobile Pi 5 UPS/battery only after bench bring-up proves untethered testing is needed.
- I2C logic-level shifter only if MPU6050 direct Pi 3.3V I2C is unsafe and Arduino fallback is not chosen.
- Extra jumper wires only if starter-kit wiring is missing, damaged, or too short.

Rationale:

- The user already owns Pi 5, AI HAT+, Arduino Uno, USB camera, MPU6050 module, starter-kit wiring/sensors, and 3 wheels.
- Mixing required buys with conditional buys caused unnecessary-order risk.
- The low-power Phase 1 build should minimize purchases and validate real fit/electrical details before expanding hardware.

Impact:

- `wiki/architecture/current-build-and-materials.md` is the canonical first-cart source.
- `wiki/architecture/hardware-design.md` and `wiki/architecture/phase-1-bringup-checklist.md` must keep conditional purchases separate from the first cart.
