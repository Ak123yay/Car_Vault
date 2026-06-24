# Hardware Design

## Purpose

Define the physical robot setup so SLAM, odometry, planning, and control can use real measurements.

## Required Hardware Blocks

| Block | Current status | Required details |
| --- | --- | --- |
| Chassis | 2WD layout with passive front support selected | Dimensions, weight, mounting points |
| Motors | 2 powered motors selected as architecture | Final Amazon SKU, voltage, gear ratio |
| Encoders | Required on powered wheels only | Type, ticks per revolution, mounting |
| Wheels | 2 powered + CAD/printed passive front support | Diameter, tread material, front support height |
| IMU | Provided MPU6050 selected | Confirm module label, I2C address, placement, axis orientation |
| Camera | USB camera selected | Model, height, tilt, resolution, FPS |
| Compute board | Raspberry Pi 5 selected | OS, camera interface, power supply, storage |
| AI accelerator | Raspberry Pi AI HAT+ 26 TOPS owned | Hailo-8 inference for YOLO/object detection |
| Motor-control coprocessor | Arduino Uno selected for v1 | Use for encoder interrupts, PWM, wheel PID, and motor stop |
| Motor driver | Low-power dual driver required | DRV8833 or TB6612FNG preferred; avoid L298N |
| Pi power | Required | Official Raspberry Pi 27W USB-C PSU for bench, or mobile 5V 5A Pi-compatible battery/UPS that works with the AI HAT+ stack |
| Motor battery | Pending | Separate 6V motor rail, voltage under load, capacity, regulator layout |

## Drivetrain Decision

Use a chassis with only 2 powered wheels and passive front support:

```text
Front center support: CAD/printed skid or ball-caster-style support
Back left wheel: powered motor + encoder
Back right wheel: powered motor + encoder
```

The control model is 2WD differential drive. A front skid/caster is simpler than trying to make extra powered wheels and keeps the robot low power.

Why this is the current architecture:

- Lower power draw.
- Less wiring.
- One dual motor driver is enough.
- Easier PID tuning.
- Cleaner odometry because only left and right drive wheels are measured.
- Less wheel fighting during turns.
- Lets the project use the existing 3-wheel inventory without buying unnecessary front drive hardware.

Current Amazon-orderable recommendation:

- Primary motors: 1x MECCANIXITY 2pcs 100RPM Micro Gear Motor with Encoder, N20 DC6V, 1:150 reduction ratio, 0.15A.
- Backup motors: 2x uxcell GA12-N20 6V 100RPM DC Gear Motor with Encoder.
- Driver: DRV8833 or TB6612FNG dual motor driver.
- Avoid: L298N, because it wastes power and is a poor fit for a low-power 6V robot.
- Do not rely on: DFRobot TT Motor with Encoder, 6V 160RPM, 120:1, because the Amazon listing is currently unavailable.

Do not order from search results alone. The product page must pass the acceptance checklist in `wiki/architecture/current-build-and-materials.md`.

## Compute And Control Boards

Current compute plan:

- Raspberry Pi 5 runs vision, camera capture, ORB-SLAM3 experiments, mapping, planning, and high-level navigation.
- Arduino Uno runs v1 real-time motor tasks: encoder interrupts, wheel-speed PID, and PWM output to the motor driver.
- Pi 5 and Arduino Uno should communicate over USB serial.
- Powered wheel encoder A/B signals go to Arduino Uno for Phase 1, not Pi GPIO.
- ESP32-S3 is not the selected Phase 1 motor controller. It can be reconsidered only after `TASKS.md` changes the controller and encoder output voltage or level shifting is verified.

Why split control this way:

- Pi 5 is strong for camera/vision but Linux is not ideal for precise encoder interrupt timing.
- Arduino Uno is simpler for deterministic motor timing.
- USB serial avoids unsafe direct 5V Arduino UART wiring into Pi GPIO.

Power rule:

- Do not power motors from the Pi 5 or Arduino Uno.
- For Phase 1, do not power the Pi 5 from the motor battery rail. A future shared battery system would need its own documented 5V 5A-class regulator/UPS design.
- Pi 5 power must be its own stable 5V 5A-class USB-C source.
- Use a separate motor battery rail for the driver and motors.
- Tie Arduino GND, motor driver GND, and motor battery negative together when control signals cross boards. Pi ground is normally shared through the Pi-to-Arduino USB cable; add a direct Pi-to-driver ground only if needed and record it.

## Power Architecture

Use two power rails:

```text
Pi rail:
official Raspberry Pi 27W USB-C PSU
or mobile 5V 5A Pi-compatible battery/UPS that does not block the AI HAT+ stack
-> Raspberry Pi 5
-> USB camera + AI HAT + Arduino over USB

Motor rail:
4xAA holder plus 4 fresh alkaline AA cells
-> DRV8833 VM
-> N20 motors

Shared reference:
Arduino GND <-> DRV8833 GND <-> motor battery negative
Pi GND shared through USB to Arduino unless a direct ground jumper is needed and recorded
```

The rectangular 9V battery is not acceptable for the Pi or the motors.

Direct answer: the Pi is powered by the official 27W USB-C PSU while building, or by a Pi 5-compatible 5V 5A mobile battery/UPS later. The motor battery is separate and only powers the motor driver/motors.

Motor source note: Phase 1 uses 4 fresh alkaline AA cells in a 4xAA holder. This is near 6V when fresh and matches the selected low-power 6V motor plan. NiMH rechargeables remain an optional later upgrade for repeated testing. Do not use a higher-voltage pack directly unless the motor driver, motors, and regulator layout are explicitly verified.

## Remaining Hardware Needed

Canonical current inventory and purchase list:

- See `wiki/architecture/current-build-and-materials.md`.
- See `wiki/architecture/front-support-and-chassis-plan.md` for passive front support and chassis mechanical constraints.
- See `wiki/architecture/wiring-and-pin-plan.md` for first-pass safe wiring and pin assignments.
- Record final measured values in `wiki/architecture/phase-1-measurement-worksheet.md`.

Owned:

- Raspberry Pi 5 for main compute.
- Raspberry Pi AI HAT+ 26 TOPS / Hailo-8 for future object detection.
- Arduino Uno for encoder/PID/motor control.
- USB camera for Pi 5 vision/SLAM input.
- Provided MPU6050 module for gyro + accelerometer readings.
- Starter kit basic sensors for early tests.
- 3 wheels available; use 2 as powered wheels and keep the third as spare or test-fit reference.

Still needed to buy or prepare for the first cart:

| Item | Why it is needed | Current recommendation |
| --- | --- | --- |
| Encoder motors | Provides 2 powered motors with encoders | 1x MECCANIXITY 2pcs 100RPM Micro Gear Motor with Encoder, N20 DC6V |
| Dual motor driver | Drives 2 DC motors from Arduino PWM/direction signals | DRV8833 first choice; TB6612FNG also acceptable |
| N20 motor mounts | Secure the metal gearmotors to the chassis | N20 mounting brackets with screws |
| Pi 5 bench power source | Powers Pi 5, USB camera, AI HAT+, and Arduino-over-USB during bench tests | Official Raspberry Pi 27W USB-C PSU if not already owned |
| Front support | Keeps chassis level without adding drive complexity | CAD/print 1 center skid or ball-caster-style support; use 2 passive front wheels only if needed |
| Motor battery holder | Powers the 6V motors separately from compute | 4xAA holder with switch/leads |
| Motor battery cells | Provides first low-speed motor test power | 4 fresh alkaline AA cells |
| Chassis/base material | Holds drivetrain, Pi, Arduino, battery, and camera | 3D printed plate, acrylic, plywood, or foam board |
| Fasteners/standoffs | Mount electronics and drivetrain | M2/M3 hardware, standoffs, zip ties, tape |

Conditional:

| Item | Buy if | Current recommendation |
| --- | --- | --- |
| N20 wheels | Existing wheels do not fit the selected motors' 3mm D-shafts | N20 3mm D-hole rubber wheels |
| Pi 5 storage | Missing or unstable | microSD/SSD suitable for Pi 5 |
| Pi 5 mobile power | Untethered tests are needed after bench bring-up passes | Pi 5-compatible 5V 5A UPS/battery that does not block the AI HAT+ stack |
| I2C logic-level shifter | MPU6050 cannot be safely used on Pi 3.3V I2C and Arduino fallback is not chosen | 4-channel bidirectional logic-level shifter |
| Extra jumper wires | Starter-kit jumper wires are unavailable or too short | Dupont jumper wire set |
| AA NiMH rechargeable cells and charger | Alkaline cells drain too quickly during repeated testing | 4 to 8 AA NiMH cells plus compatible charger |

Do not include conditional parts in the first cart unless their condition is already true.

## AI Vision Accelerator

Owned accelerator:

- Raspberry Pi AI HAT+ 26 TOPS.
- Accelerator chip: Hailo-8.
- Intended use: YOLO/object detection on the Pi 5 camera stream.

Architecture boundary:

- Hailo-8 does not replace ORB-SLAM3.
- Hailo-8 does not control motors.
- Hailo-8 runs neural-network inference and sends detections to the navigation/failure-handling layer.

First useful integration:

```text
USB camera frame -> Hailo-8 YOLO inference -> object detections -> stop/replan signal
```

Keep this after baseline driving, encoder odometry, and PID tests.

## Measurement Table

Fill these before calibration or control tuning.

| Measurement | Value | Notes |
| --- | --- | --- |
| Wheel diameter | TBD | Measure in centimeters |
| Wheelbase | TBD | Distance between left and right wheel contact centers |
| Front support height | TBD | Tune from powered wheel radius so chassis sits level without lifting drive wheels |
| Front support type | TBD | Center skid first; caster/passive wheels only if skid fails testing |
| Front support low-PWM turn test | TBD | Must pass before Phase 1 mechanical exit |
| Encoder ticks per revolution | TBD | From powered motor encoder specs or measured count |
| Encoder supply voltage | TBD | Confirm before powering encoder electronics |
| Encoder output voltage | TBD | Confirm A/B signal voltage before wiring |
| Encoder controller path | Arduino Uno | Phase 1 path; do not route encoder outputs to Pi GPIO |
| Camera height | TBD | Floor to camera optical center |
| Camera tilt | TBD | Degrees from horizontal |
| MPU6050 position | TBD | Prefer center of chassis |
| MPU6050 orientation | TBD | Record axis direction relative to robot frame |
| MPU6050 I2C address | TBD | Usually `0x68` or `0x69`; verify on the Pi 5 or Arduino |
| MPU6050 connection path | TBD | Pi I2C only if direct-Pi-I2C safety gate passes; otherwise level shifter or Arduino fallback |
| MPU6050 direct Pi I2C safety | TBD | Confirm no 5V I2C pullups before connecting to Pi GPIO |
| Pi power source | TBD | Record PSU/battery model and current rating; target stable 5V 5A-class source |
| Motor battery voltage | TBD | Motor rail expected around 6V; measure under load |

Use `wiki/architecture/phase-1-measurement-worksheet.md` as the fill-in record for actual values.

## Example Values

These are examples only and must not be treated as measured values.

```text
Wheel diameter: 6.5 cm
Wheelbase: 14 cm
Camera tilt: 15 degrees
IMU mounted center of chassis
```

## Coordinate Frame

Use this robot frame unless later changed deliberately:

- `+x`: forward
- `+y`: left
- `+theta`: counterclockwise rotation
- Origin: center point between the two drive wheels

## Wiring Plan

Minimum wiring diagram to create before implementation:

```text
Official 27W USB-C PSU or AI HAT+-compatible 5V 5A battery/UPS -> Raspberry Pi 5
Pi 5 PCIe/GPIO stack -> Raspberry Pi AI HAT+ 26 TOPS
Pi 5 USB -> Arduino Uno serial
Motor battery -> motor driver VM
Motor driver -> left/right powered motors
Left/right powered wheel encoders -> Arduino Uno interrupt-capable pins
Arduino Uno PWM/direction pins -> motor driver control inputs
MPU6050 -> Pi 5 I2C, or Arduino Uno I2C if using Arduino for low-level state
USB camera -> Pi 5 USB port
```

First-pass pin assignments are defined in `wiki/architecture/wiring-and-pin-plan.md`.

## Safety Requirements

- Motor power and compute power should be regulated appropriately.
- Pi 5 power and motor power must be separate rails unless a properly rated shared power system is designed.
- Motor battery positive must never connect to Pi 5V or Arduino 5V.
- A Pi 5 mobile power board must be checked for physical compatibility with the Raspberry Pi AI HAT+ before ordering.
- MPU6050 `SDA` and `SCL` must not connect directly to Pi GPIO unless the module is confirmed safe for 3.3V I2C.
- Encoder outputs must not connect directly to Pi GPIO during Phase 1.
- ESP32-S3 or another 3.3V controller must not replace Arduino Uno until encoder logic voltage compatibility or level shifting is verified and `TASKS.md` records the controller change.
- Do not buy a mobile Pi UPS, replacement N20 wheels, extra IMU, or ESP32-S3 controller as part of the first cart unless the matching condition is documented.
- Motor commands must have a software stop path.
- Wiring should prevent loose encoder or IMU connections during motion.
- Battery current capacity must support motor stall risk.
