# Failure Handling

## Purpose

Define what the robot does when sensors, localization, planning, or control become unreliable.

## Failure Policy

Default rule:

```text
When confidence is low, slow down or stop before trying to recover.
```

## Lost SLAM Tracking

Condition:

- ORB-SLAM3 reports `lost`.
- Pose confidence drops below threshold.
- Pose output stops updating.

Response:

1. Stop or reduce speed immediately.
2. Switch to IMU + encoder dead reckoning only for short controlled movement.
3. Attempt relocalization.
4. Replan after valid pose returns.
5. If pose remains invalid, stop and require operator intervention.

Example rule:

```text
If SLAM tracking is lost, switch to IMU + encoder dead reckoning.
```

## Encoder Mismatch

Condition:

- Left and right encoder deltas differ more than expected during a straight command.
- Encoder ticks stop while motor command is active.
- Encoder count jumps unexpectedly.

Response:

1. Reduce speed.
2. Compare IMU heading change against expected motion.
3. Stop if mismatch persists.
4. Flag calibration, wheel slip, wiring, or motor fault.

## IMU Drift

Condition:

- Heading changes while robot is stationary.
- IMU heading disagrees with encoder/SLAM estimate beyond threshold.
- Bias correction no longer holds.

Response:

1. Re-estimate gyro bias while stationary if safe.
2. Prefer SLAM heading if tracking confidence is high.
3. Stop autonomous navigation if heading uncertainty is too high.

## Sudden Obstacle

Condition:

- Occupancy grid updates a cell on the current path to occupied.
- Future YOLO layer detects a stop-relevant object.
- Any proximity sensor added later reports immediate blockage.

Response:

1. Stop.
2. Mark blocked area in occupancy grid.
3. Replan using A*.
4. Continue only if a safe path exists.

## Planner Failure

Condition:

- A* cannot find a valid path.
- Goal is inside an occupied or unreachable area.

Response:

1. Stop.
2. Report no-path state.
3. Wait for new goal, updated map, or operator action.

## Motor Control Fault

Condition:

- Command exceeds configured speed limit.
- Motor output saturates for too long.
- Robot does not move as expected.
- Pi-to-Arduino serial watchdog expires.
- Arduino reports `FAULT`.
- Command acknowledgment is missing or mismatched.

Response:

1. Clamp command.
2. Stop if saturation persists.
3. Send `STOP` if serial link is still available.
4. Log commanded speed, measured encoder deltas, serial state, and pose response.

## Serial Link Fault

Condition:

- `PING`/`PONG` fails.
- `ACK` does not match the latest command sequence.
- Arduino reports `WATCHDOG`, `PARSE`, `LIMIT`, or `UNKNOWN_CMD`.
- Status messages stop while motors are active.

Response:

1. Treat motor state as unsafe.
2. Send `STOP` if possible.
3. Require Arduino watchdog to stop motors if serial is stale.
4. Do not resume motion until `STATUS` reports `STOPPED` and `PING`/`PONG` works.

## Required Health Signals

Future implementation should expose:

- SLAM tracking state.
- Pose confidence.
- Encoder tick freshness.
- IMU sample freshness.
- Motor command limit status.
- Serial link state and watchdog status.
- Planner status.
- Obstacle stop status.
