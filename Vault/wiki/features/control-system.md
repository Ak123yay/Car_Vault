# Control System

## Purpose

Define how planned waypoints become physical robot movement.

## Control Stack

```text
Pi 5 waypoint control -> serial target speeds -> Arduino Uno PID -> motor driver -> motors
```

## PID Controllers

Use separate control loops for:

- Heading control.
- Forward speed control.
- Optional wheel-speed balancing.

Example values only:

```text
Kp = 1.2
Ki = 0.01
Kd = 0.3
```

Do not treat these as final constants. Tune after encoder and IMU calibration.

Recommended ownership:

- Pi 5: high-level waypoint, heading, and navigation decisions.
- Arduino Uno: encoder counting, wheel-speed PID, PWM, direction pins, and emergency motor stop.

Do not wire Arduino Uno TX directly into Pi GPIO RX because Uno logic is 5V and Pi GPIO is 3.3V. Use USB serial between them.

Do not wire encoder outputs directly into Pi GPIO for Phase 1. Encoder A/B signals go to Arduino Uno. ESP32-S3 or another 3.3V controller is not a drop-in replacement for the Uno unless `TASKS.md` changes the controller and encoder output voltage or level shifting is verified.

Use `wiki/architecture/wiring-and-pin-plan.md` for first-pass Arduino, DRV8833, encoder, and power wiring.

Use `wiki/architecture/serial-protocol-and-safety.md` for Pi-to-Arduino message names, command units, watchdog timeout, `STOP` behavior, and fault reporting.

## Differential-Drive Mixing

The robot uses left and right powered wheels only. The front support should be passive: a CAD/printed skid, ball-caster-style support, or passive wheel pair if the chassis needs four contact points.

The front support must pass `wiki/architecture/front-support-and-chassis-plan.md` before PID tuning. If it lifts a drive wheel or drags during turns, encoder odometry and PID tuning will be misleading.

Inputs:

- Desired forward speed.
- Desired turn rate.

Output:

- Left motor speed.
- Right motor speed.

Basic relationship:

```text
left_speed = forward_speed - turn_rate
right_speed = forward_speed + turn_rate
```

Final implementation must clamp both outputs to safe limits.

The Arduino must clamp again even if the Pi already clamped the command. Pi-side limits are not a substitute for Arduino-side motor safety.

## Wheel Layout

Current layout:

```text
Passive front support

Powered left wheel  Powered right wheel
with encoder        with encoder
```

Only the powered wheels participate in PID, motor mixing, and encoder odometry. Passive support should slide or roll freely and should not be mechanically linked to the powered wheels.

## Speed Limits

Required limits:

| Limit | Purpose |
| --- | --- |
| Maximum forward speed | Prevent unstable tracking and unsafe motion |
| Maximum reverse speed | Prevent uncontrolled backing |
| Maximum turn rate | Reduce wheel slip and heading overshoot |
| Acceleration limit | Avoid sudden motor jumps |
| Minimum command threshold | Overcome motor deadband if needed |

## Turning Behavior

Initial turn behavior:

1. Stop forward motion.
2. Rotate toward waypoint heading.
3. Move forward once heading error is below threshold.
4. Slow down near target.

This is simpler and easier to debug than smooth pursuit. Smooth pursuit can be added after baseline navigation passes validation.

## Safety Behavior

Control must output stop commands when:

- Pose is invalid.
- SLAM is lost and fallback is unavailable.
- Obstacle stop is active.
- Encoder mismatch exceeds threshold.
- Motor command exceeds configured limits.
- Serial command acknowledgment or watchdog health is invalid.

## Tuning Order

1. Confirm motor direction and command range.
2. Tune wheel speed response.
3. Tune straight-line movement with encoders.
4. Tune in-place 90-degree turns with IMU.
5. Tune waypoint following.
6. Tune full path following.
