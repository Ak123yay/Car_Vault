# Testing & Validation Plan

## Purpose

Define how to prove the robot works before adding more complex behavior.

## Test Order

1. Hardware smoke tests.
2. Sensor calibration tests.
3. Odometry tests.
4. SLAM tests.
5. Mapping tests.
6. Planning tests.
7. Control tests.
8. Full navigation test.

Phase 1 bring-up uses `wiki/architecture/phase-1-bringup-checklist.md` before formal calibration starts. Record the actual part confirmations, measurements, and pass/fail results in `wiki/architecture/phase-1-measurement-worksheet.md`.

## Hardware Smoke Tests

| Test | Pass condition |
| --- | --- |
| Front support contact | Chassis sits level with both powered wheels and passive front support touching floor |
| Front support drag | Robot can be rotated by hand and by low-PWM turn without the support digging in |
| Motor direction | Positive command moves expected wheel forward |
| Encoder identity and voltage | Encoder `VCC`, `GND`, `A`, `B`, supply voltage, and output voltage are identified before signal wiring |
| Encoder readout | Ticks increase/decrease consistently with wheel motion |
| IMU readout | Stable samples while stationary |
| Camera readout | Stable frames at target resolution/FPS |

## Encoder Tests

| Test | Method | Target |
| --- | --- | --- |
| Encoder controller path | Inspect wiring against the worksheet | Encoder A/B signals terminate at Arduino Uno, not Pi GPIO |
| Encoder voltage safety | Confirm supply and A/B output voltage | Safe for Arduino Uno inputs; 3.3V controllers require verified compatibility or level shifting |
| Wheel tick count | Rotate wheel one full revolution | Matches expected ticks per revolution |
| Straight line | Drive 2 meters | Within +/- 2 cm after calibration |
| Left/right mismatch | Drive straight and compare tick deltas | Difference recorded and corrected if repeatable |

## IMU Tests

| Test | Method | Target |
| --- | --- | --- |
| Identity check | Inspect board label and detect I2C address | `MPU6050` or `GY-521`, address `0x68` or `0x69` |
| Voltage safety check | Confirm direct Pi I2C safety or choose fallback path | No 5V I2C signal connected to Pi GPIO |
| Bias test | 10 seconds stationary | Bias recorded |
| 90-degree turn | Rotate against physical reference | Within +/- 3 degrees |
| Drift test | Sit still for 5 minutes | Drift rate recorded |

## Camera And SLAM Tests

| Test | Method | Target |
| --- | --- | --- |
| Camera FPS | Log frame intervals | Stable near configured FPS |
| Feature tracking | Move in textured indoor area | Tracking remains active |
| SLAM drift | Repeat a known loop | Drift measured and documented |
| Relocalization | Brief tracking loss in controlled test | Behavior recorded |

## Mapping Tests

| Test | Method | Target |
| --- | --- | --- |
| Static room map | Drive slow loop in room | Major obstacles represented |
| Grid consistency | Compare map to visible layout | No obvious occupied/free inversion |
| Unknown handling | Plan near unmapped area | Unknown cells follow configured cost |

## Planning Tests

| Test | Method | Target |
| --- | --- | --- |
| Empty grid A* | Start to goal without obstacles | Short valid path |
| Obstacle grid A* | Known blocked cells | Path avoids obstacles |
| No path case | Goal fully blocked | Planner returns failure |

## Control Tests

| Test | Method | Target |
| --- | --- | --- |
| Serial ping | Send `PING` over USB serial | Matching `PONG` received |
| Serial stop | Send low motor command, then `STOP` | Both motors stop immediately |
| Serial watchdog | Stop sending commands while low motor command is active | Arduino stops motors on watchdog expiry |
| Command clamp | Send command above first safe limit | Arduino clamps or rejects and reports `FAULT LIMIT` |
| In-place turn | Command 90-degree turn | Within configured heading tolerance |
| Straight motion | Command fixed distance | Within configured distance tolerance |
| Waypoint approach | Drive to one waypoint | Stops within tolerance |
| Speed clamp | Command above max | Output stays bounded |

## Full Navigation Test

Scenario:

```text
Robot starts at point A.
Robot builds or receives map.
Goal point B is selected.
A* generates path.
PID follows waypoints.
Robot stops at goal.
```

Initial pass condition:

- Robot reaches goal without collision.
- Pose remains valid or fallback behavior is triggered safely.
- Final position error is measured and recorded.

## Test Artifacts

Each test run should record:

- Date.
- Hardware configuration.
- Calibration values.
- Software version or commit.
- Test environment.
- Result.
- Observed failure or drift.
