# Phase 1 Measurement Worksheet

## Purpose

Record the real parts, wiring choices, measurements, and first bring-up results for the robot.

Do not replace values in this worksheet with guesses. Leave unknown values as `TBD` until measured or confirmed from the received part.

## Build Snapshot

| Field | Value |
| --- | --- |
| Date recorded | TBD |
| Recorder | TBD |
| Robot revision/name | TBD |
| Chassis/base material | TBD |
| Notes | TBD |

## Received Parts Confirmation

| Part | Expected | Actual received | Pass |
| --- | --- | --- | --- |
| Left drive motor | 6V N20 encoder motor, 100RPM target, 3mm shaft | TBD | TBD |
| Right drive motor | 6V N20 encoder motor, 100RPM target, 3mm shaft | TBD | TBD |
| Motor driver | DRV8833 preferred, TB6612FNG acceptable | TBD | TBD |
| Motor brackets | N20-compatible brackets | TBD | TBD |
| Pi 5 power | Official 27W USB-C PSU for bench | TBD | TBD |
| Motor power holder/source | 4xAA holder plus 4 fresh alkaline AA cells | TBD | TBD |
| Existing wheels | Fit 3mm D-shaft or require replacement | TBD | TBD |
| Front support | CAD/printed skid or caster-style support | TBD | TBD |
| MPU6050 module | Labeled `MPU6050` or `GY-521` | TBD | TBD |
| USB camera | Detected by Pi 5 | TBD | TBD |

## Product Page Verification

Fill this before checkout or immediately after ordering.

| Item | Product page/listing title | Required checks passed? | Notes |
| --- | --- | --- | --- |
| N20 encoder motor pair | TBD | TBD | Must confirm 2 motors, 6V, 100RPM target, encoder, N20/GA12-N20 style, and 3mm D-shaft |
| DRV8833/TB6612FNG motor driver | TBD | TBD | Must confirm dual DC motor driver, 6V motor supply compatibility, and clear VM/GND/input/output labels |
| N20 brackets | TBD | TBD | Must confirm N20/GA12-N20/12mm micro metal gearmotor compatibility |
| Pi 5 bench power | TBD | TBD | Must confirm official Raspberry Pi 27W USB-C PSU or 5.1V/5A Pi 5-compatible output |
| Motor battery holder/source | TBD | TBD | Must confirm 4xAA holder with leads/switch |
| Alkaline AA cells | TBD | TBD | Must use 4 fresh matching cells for Phase 1 low-speed motor tests |
| Chassis/base | TBD | TBD | Must be rigid enough for motor/camera mounting |
| Fasteners/standoffs | TBD | TBD | Required only if not already owned |

## Power Measurements

| Measurement | Value | Notes |
| --- | --- | --- |
| Pi power source model | TBD | Must be stable 5V 5A-class for Pi 5 |
| Pi undervoltage warning seen? | TBD | Yes/no |
| Motor rail source | TBD | 4xAA holder |
| Motor rail battery chemistry | Alkaline | Use 4 fresh matching AA cells for Phase 1 |
| Motor rail voltage no load | TBD | Measure before connecting motors |
| Motor rail voltage low-PWM load | TBD | Measure while motors spin slowly |
| Grounds connected | TBD | Arduino GND, driver GND, motor battery negative |
| Pi ground path | TBD | Pi-to-Arduino USB only, or direct Pi ground jumper if used |
| Shared-ground notes | TBD | Record any direct ground jumper changes |

## Wiring Record

Record final wiring even if it differs from `wiki/architecture/wiring-and-pin-plan.md`.

| Signal | Planned pin/connection | Actual pin/connection | Notes |
| --- | --- | --- | --- |
| Pi 5 to Arduino | USB serial | TBD | Avoid direct 5V UART into Pi GPIO |
| USB camera | Pi USB | TBD | TBD |
| Hailo AI HAT+ | Pi PCIe/GPIO stack | TBD | TBD |
| Left motor input 1 | Arduino `D5` PWM -> driver left input 1 | TBD | TBD |
| Left motor input 2 | Arduino `D6` PWM -> driver left input 2 | TBD | TBD |
| Right motor input 1 | Arduino `D9` PWM -> driver right input 1 | TBD | TBD |
| Right motor input 2 | Arduino `D10` PWM -> driver right input 2 | TBD | TBD |
| Left encoder A | Arduino `D2` interrupt | TBD | TBD |
| Left encoder B | Arduino `D4` | TBD | TBD |
| Right encoder A | Arduino `D3` interrupt | TBD | TBD |
| Right encoder B | Arduino `D7` | TBD | TBD |
| Encoder controller path | Arduino Uno for Phase 1 | TBD | Do not wire encoder outputs directly to Pi GPIO |
| Encoder VCC | Confirm from product page/label before wiring | TBD | Record voltage |
| Encoder GND | Arduino/motor-control ground reference | TBD | Must share reference with Uno |
| Encoder output voltage | Confirm before wiring A/B | TBD | ESP32-S3 or other 3.3V controller would need verification or level shifting |
| Driver VM | Motor rail positive | TBD | TBD |
| Driver GND | Motor rail negative + Arduino GND | TBD | TBD |
| MPU6050 VCC | Pi `3V3` only if direct-Pi-I2C safety gate passes; otherwise level shifter/Arduino fallback | TBD | TBD |
| MPU6050 GND | Ground | TBD | TBD |
| MPU6050 SDA | Pi `GPIO2/SDA1` only if no 5V I2C pullup risk | TBD | TBD |
| MPU6050 SCL | Pi `GPIO3/SCL1` only if no 5V I2C pullup risk | TBD | TBD |

## Serial Protocol And Safety Results

| Check | Value | Notes |
| --- | --- | --- |
| Serial device path on Pi | TBD | Example: `/dev/ttyACM0`; record actual |
| Baud rate | TBD | Record firmware setting |
| `PING`/`PONG` passed? | TBD | Yes/no |
| `STATUS` reports stopped before motor power? | TBD | Yes/no |
| First safe PWM limit | TBD | Example limit only after firmware defines it |
| Command duration limit ms | TBD | Record final firmware limit |
| Watchdog timeout ms | TBD | Record final firmware limit |
| `STOP` test passed? | TBD | Yes/no |
| Watchdog stop test passed? | TBD | Yes/no |
| Fault messages visible on Pi? | TBD | Yes/no |

## Mechanical Measurements

| Measurement | Value | Method/notes |
| --- | --- | --- |
| Left wheel diameter cm | TBD | Measure actual powered wheel |
| Right wheel diameter cm | TBD | Measure actual powered wheel |
| Average wheel diameter cm | TBD | Use for initial odometry |
| Wheelbase cm | TBD | Distance between left/right wheel contact centers |
| Front support height cm | TBD | Tuned from powered wheel radius so chassis sits level without lifting drive wheels |
| Front support type | TBD | Center skid first; caster/passive wheel only if skid fails tests |
| Front support CAD/version | TBD | File name, sketch name, or revision note |
| Front support low-PWM turn passed? | TBD | Yes/no and notes |
| Chassis length cm | TBD | Useful for collision clearance |
| Chassis width cm | TBD | Useful for collision clearance |
| Camera height cm | TBD | Floor to optical center |
| Camera tilt degrees | TBD | Degrees from horizontal |
| MPU6050 position | TBD | Prefer near chassis center |
| MPU6050 orientation | TBD | Axis mapping relative to robot frame |

## Encoder Measurements

| Measurement | Value | Notes |
| --- | --- | --- |
| Encoder supply voltage | TBD | Confirm before applying encoder power |
| Encoder output voltage | TBD | Encoder A/B route to Arduino Uno for Phase 1, not Pi GPIO |
| Encoder controller path | Arduino Uno | Change only if `TASKS.md` changes the controller and voltage safety is verified |
| Left ticks per wheel revolution | TBD | Rotate one wheel revolution |
| Right ticks per wheel revolution | TBD | Rotate one wheel revolution |
| Average ticks per wheel revolution | TBD | Use for first odometry calculation |
| Left tick direction correct? | TBD | Yes/no |
| Right tick direction correct? | TBD | Yes/no |
| Encoder wire colors | TBD | Record left/right color mapping |

## IMU Measurements

| Measurement | Value | Notes |
| --- | --- | --- |
| Board label | TBD | `MPU6050` or `GY-521` expected |
| Required pins identified? | TBD | `VCC`, `GND`, `SDA`, `SCL` |
| Optional pins present | TBD | `XDA`, `XCL`, `AD0`, `INT`, or other |
| I2C address | TBD | Usually `0x68` or `0x69` |
| Direct Pi I2C safe? | TBD | Yes/no/unknown |
| Direct Pi I2C safety reason | TBD | Works from 3.3V and no 5V I2C pullups, or fallback required |
| Connection path used | TBD | Pi I2C, level shifter, or Arduino fallback |
| Forward axis | TBD | Sensor axis pointing robot forward |
| Left axis | TBD | Sensor axis pointing robot left |
| Up axis | TBD | Sensor axis pointing up |
| Stationary gyro stable? | TBD | Yes/no |

## Camera Measurements

| Measurement | Value | Notes |
| --- | --- | --- |
| USB camera model | TBD | Record exact name if known |
| Resolution | TBD | Width x height |
| FPS | TBD | Measured stable FPS |
| Exposure/auto settings | TBD | Record if changed |
| Mount rigidity | TBD | Camera should not wobble |
| Lens distortion calibration needed? | TBD | Yes until calibrated |

## Phase 1 Bring-Up Results

| Gate | Result | Notes |
| --- | --- | --- |
| Pi boots from correct power | TBD | TBD |
| Arduino serial visible from Pi | TBD | TBD |
| Serial protocol safety smoke test passed | TBD | PING/PONG, STOP, watchdog, and fault visibility |
| Driver logic wiring checked with motor power off | TBD | TBD |
| Motor rail measured before connection | TBD | TBD |
| Left motor low-PWM test passed | TBD | TBD |
| Right motor low-PWM test passed | TBD | TBD |
| Both motors forward direction correct | TBD | TBD |
| Left encoder tick test passed | TBD | TBD |
| Right encoder tick test passed | TBD | TBD |
| MPU6050 detection/readout passed | TBD | TBD |
| USB camera frame capture passed | TBD | TBD |
| Required mechanical measurements recorded | TBD | TBD |
| Shared-ground layout documented | TBD | TBD |

## Phase 1 Exit Decision

| Decision | Value |
| --- | --- |
| Ready for Phase 2 calibration? | TBD |
| Blocking issue, if any | TBD |
| Next required action | TBD |

Phase 2 may start only after the Phase 1 gate in `wiki/architecture/phase-1-bringup-checklist.md` passes.
