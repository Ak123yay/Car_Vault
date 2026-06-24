# _coding-rules.md - Car Vault Coding Rules

These rules apply to future robot code in `project-code/`.

---

## Architecture Rules

- Keep hardware access in `sensors/` and `motors/`.
- Keep SLAM, mapping, planning, and control as separate modules.
- Do not let the A* planner depend on motor-driver details.
- Do not let motor-control code read raw camera frames directly.
- Keep YOLO optional until the base navigation stack passes validation.
- Do not add ROS, ROS 2, or another framework unless `TASKS.md` explicitly adds that task.

## Measurement Rules

- Do not hardcode guessed dimensions.
- Store measured wheel diameter, wheelbase, encoder ticks, camera height, camera tilt, and IMU orientation in configuration.
- PID values, camera intrinsics, and IMU noise values must be labeled as placeholders until tested.
- Any calibration change must include the test result that justified it.

## Safety Rules

- Motor commands must be clamped before reaching the motor driver.
- Invalid pose must trigger stop or fallback behavior.
- Lost SLAM tracking must not allow blind full-speed motion.
- Encoder mismatch, stale IMU data, stale encoder data, or planner failure must be visible to the failure manager.
- Autonomous navigation tests must have an operator stop method.

## Code Style

- Use Python with type hints for robot modules unless a task explicitly chooses another language.
- Keep shared data structures small and explicit.
- Prefer simple dataclasses or typed models for pose, encoder deltas, grid cells, waypoints, and motor commands.
- Keep loop rates configurable.
- Add focused tests for odometry math, A*, PID, and safety limit behavior.

## File Rules

- No new implementation file without a matching path in `wiki/_code-map.md`.
- No new subsystem without a wiki entry explaining ownership and behavior.
- No production code in `wiki/`.
- No large refactors during calibration or hardware bring-up unless required for safety.

## Logging Rules

Future robot runtime logs should include:

- Timestamp.
- Active mode.
- Pose source.
- SLAM tracking state.
- Encoder freshness.
- IMU freshness.
- Planner status.
- Motor command limit status.
- Failure manager state.
