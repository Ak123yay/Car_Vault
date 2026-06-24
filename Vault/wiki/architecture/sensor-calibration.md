# Sensor Calibration

## Purpose

Define how raw camera, IMU, and encoder readings become usable measurements.

## Encoder Calibration

V1 encoder capture owner: Arduino Uno. Use USB serial to stream tick counts to the Pi 5.

Phase 1 controller boundary:

- Arduino Uno is the selected encoder/PID/motor controller.
- Do not connect encoder outputs directly to Pi GPIO.
- Do not replace Uno with ESP32-S3 or another 3.3V controller unless `TASKS.md` changes the controller and the encoder output voltage is verified safe or level shifted.

Initial Uno wiring approach:

- Left encoder channel A -> Arduino Uno interrupt pin `D2`.
- Right encoder channel A -> Arduino Uno interrupt pin `D3`.
- Left/right encoder channel B -> normal digital pins for direction sensing.
- Motor driver PWM/direction pins -> normal Arduino output pins.

Exact first-pass pin assignments are defined in `wiki/architecture/wiring-and-pin-plan.md`.

This is good enough for first odometry and PID. Full 4x quadrature decoding can be revisited if the tick rate or accuracy becomes a problem.

Before wiring encoders:

1. Identify motor power wires separately from encoder wires.
2. Identify encoder `VCC`, `GND`, `A`, and `B`.
3. Confirm encoder supply voltage.
4. Confirm encoder output voltage.
5. Route encoder A/B to Arduino Uno only for Phase 1.

Required values:

| Value | Description |
| --- | --- |
| `encoder_supply_voltage` | Voltage used to power the encoder electronics |
| `encoder_output_voltage` | Measured or confirmed A/B signal voltage |
| `ticks_per_revolution` | Encoder counts per full wheel revolution |
| `wheel_diameter_cm` | Measured wheel diameter |
| `wheel_circumference_cm` | `pi * wheel_diameter_cm` |
| `cm_per_tick` | `wheel_circumference_cm / ticks_per_revolution` |

Formula:

```text
cm_per_tick = (pi * wheel_diameter_cm) / ticks_per_revolution
```

Per-wheel distance:

```text
left_distance_cm = left_ticks * cm_per_tick
right_distance_cm = right_ticks * cm_per_tick
```

Differential-drive odometry:

```text
distance_cm = (left_distance_cm + right_distance_cm) / 2
delta_theta_rad = (right_distance_cm - left_distance_cm) / wheelbase_cm
```

Validation:

- Command 1 meter forward.
- Measure actual travel distance.
- Repeat at least 3 times.
- Record average error and direction of drift.

## IMU Calibration

Selected IMU: provided MPU6050 module.

### MPU6050 Verification Before Wiring

Do not connect the module to Pi GPIO until this gate is complete.

Physical checks:

- Board label should say `MPU6050` or `GY-521`.
- Main sensor package should be an MPU6050-class 6-axis IMU.
- Pin labels should include `VCC`, `GND`, `SCL`, and `SDA`.
- Optional pins such as `XDA`, `XCL`, `AD0`, and `INT` are not required for the first bring-up.

Electrical checks:

- Prefer powering the module from Pi `3V3` if connecting directly to Pi I2C.
- Direct Pi I2C is allowed only if the module works from 3.3V and does not pull `SDA`/`SCL` up to 5V.
- If the module only works from 5V, has I2C pullups to 5V, or the pullup voltage is unknown, do not connect `SDA`/`SCL` directly to Pi GPIO.
- Use a logic-level shifter or read the module from Arduino Uno and stream timestamped samples over USB when 3.3V safety is not confirmed.

Identity checks:

- Detect I2C address as `0x68` or `0x69`.
- If no address appears, stop and check power, ground, `SDA`, `SCL`, and `AD0` state before continuing.
- Record the final connection path in `wiki/architecture/phase-1-measurement-worksheet.md`.

Before calibration:

- Confirm the board is actually labeled MPU6050 or GY-521.
- Confirm I2C address, usually `0x68` or `0x69`.
- Prefer Raspberry Pi 5 I2C for IMU reads only if the MPU6050 module works from 3.3V and does not pull `SDA`/`SCL` up to 5V.
- If the MPU6050 module requires 5V or has 5V I2C pullups, use a logic-level shifter or read it from Arduino Uno and stream samples over USB.
- Mount it firmly so it cannot vibrate or rotate separately from the chassis.
- Record which sensor axis points forward, left, and up.

Required process:

1. Place robot still on a flat surface.
2. Collect gyro samples for at least 10 seconds.
3. Average gyro readings to estimate bias.
4. Subtract bias from future gyro readings.
5. Re-test 90-degree turns against a physical reference.

Required values:

| Value | Description |
| --- | --- |
| Connection path | Pi I2C, level shifter, or Arduino fallback |
| Direct Pi I2C safety | Confirmed yes/no and reason |
| Gyro bias X/Y/Z | Average stationary gyro offset |
| Accelerometer bias | Optional, measured while stationary |
| Mounting orientation | Axis mapping relative to robot frame |
| Drift rate | Observed heading drift over time |

## Camera Calibration

Required values:

| Value | Description |
| --- | --- |
| Resolution | Width x height |
| FPS | Target capture rate |
| Intrinsics | `fx`, `fy`, `cx`, `cy` |
| Distortion | Lens distortion coefficients |
| Camera height | Floor to optical center |
| Camera tilt | Degrees from horizontal |

Camera calibration should happen before ORB-SLAM3 tuning. Lens distortion must be handled by the camera model used in the SLAM config.

## Sync Requirements

- Camera frames need timestamps.
- IMU samples need timestamps.
- Encoder samples need timestamps.
- SLAM and odometry comparisons are invalid without aligned time references.

## Acceptance Targets

Initial targets before autonomous navigation:

| Test | Target |
| --- | --- |
| Straight-line encoder test | 2 meters within +/- 2 cm after calibration |
| 90-degree IMU turn | Within +/- 3 degrees |
| Stationary IMU drift | Recorded and corrected |
| Camera FPS | Stable near target FPS |
