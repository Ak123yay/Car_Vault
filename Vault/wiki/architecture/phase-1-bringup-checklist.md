# Phase 1 Bring-Up Checklist

## Purpose

Turn the current materials list and wiring plan into a safe first build procedure.

This checklist ends when the robot can power on, spin both motors at low speed, report encoder ticks, read the MPU6050, capture USB camera frames, and record the required physical measurements. It does not include SLAM, A*, PID tuning, or YOLO.

## Source Docs

Use these docs while executing this checklist:

| Need | Source |
| --- | --- |
| Owned parts and purchase list | `wiki/architecture/current-build-and-materials.md` |
| Wiring and pin assignments | `wiki/architecture/wiring-and-pin-plan.md` |
| Measurements | `wiki/architecture/hardware-design.md` |
| Recording worksheet | `wiki/architecture/phase-1-measurement-worksheet.md` |
| Encoder/IMU/camera calibration requirements | `wiki/architecture/sensor-calibration.md` |
| Validation targets | `wiki/testing/test-strategy.md` |

## Stage 0 - Do Not Start Until

- Pi 5 boots from a known-good power source.
- Arduino Uno can connect to a computer over USB.
- Motor driver board is identified as DRV8833 or TB6612FNG.
- Selected motors are 6V N20 motors with encoders.
- Wheels are removed or lifted for first motor tests.
- The rectangular 9V battery is not used.

## Stage 1 - Purchase And Prepare

| Item | Required action | Pass condition |
| --- | --- | --- |
| N20 encoder motors | Order selected 6V encoder motor pair | Product page confirms 2 motors, 6V, 100RPM target, encoder, N20/GA12-N20 style, and 3mm shaft |
| Motor driver | Order DRV8833 first choice, TB6612FNG acceptable | Product page confirms dual DC motor driver, 6V motor supply compatibility, and clear VM/GND/input/output pin labels |
| N20 brackets | Order or prepare mounting brackets | Motors can mount without flexing |
| Pi 5 bench power | Use official Raspberry Pi 27W USB-C PSU | Pi boots without undervoltage warning |
| Motor power | Prepare 4xAA holder plus 4 fresh alkaline AA cells | Motor voltage can be measured before connection; record battery chemistry |
| Chassis | Prepare base material | Pi, Arduino, motors, battery, and camera fit without strain |
| Fasteners | Prepare M2/M3 screws/standoffs/zip ties/tape | Electronics and motors can be secured |
| Front support plan | Follow `front-support-and-chassis-plan.md` | Center skid design has height, mounting, and test criteria |
| Encoder logic path | Keep Phase 1 encoder A/B on Arduino Uno | No encoder output is wired directly into Pi GPIO |
| First-cart boundary | Exclude owned and conditional-later parts | No extra IMU, ESP32-S3 replacement controller, mobile UPS, or N20 wheels unless their condition is documented |

Conditional:

- Buy N20 3mm D-hole wheels only if the existing wheels do not fit the selected motor shafts.
- Buy mobile Pi power only after bench bring-up works and only if it supports Pi 5-class 5V 5A output without blocking the AI HAT+ stack.
- Buy an I2C logic-level shifter only if the MPU6050 cannot safely use Pi 3.3V I2C and Arduino fallback is not chosen.
- Buy extra jumper wires only if the starter-kit wiring is missing, damaged, or too short.

Before checkout:

- Compare every listing against `wiki/architecture/current-build-and-materials.md#product-page-acceptance-checklist`.
- Reject search results that are only close matches but fail voltage, RPM, encoder, shaft, or driver-chip requirements.
- Save the final product page title or screenshot so received parts can be checked against the order.

## Stage 2 - Bench Wiring With Motor Power Off

Complete this before connecting the motor battery.

| Check | Pass condition |
| --- | --- |
| Pi 5 powered by USB-C supply | Pi boots normally |
| Arduino connected to Pi over USB | Serial device appears on Pi |
| Serial protocol smoke test | `PING`/`PONG` works and `STATUS` reports stopped before motor power is connected |
| DRV8833 logic inputs wired to Arduino | Pins match `wiring-and-pin-plan.md` or changes are recorded |
| Arduino/driver ground connected | Arduino GND, DRV8833 GND, and motor battery negative are common; Pi ground is through USB unless a direct ground jumper is recorded |
| Motor battery disconnected | No motor power reaches the driver yet |
| USB camera plugged into Pi | Camera appears as a USB video device |
| Hailo HAT physically mounted | No cable or power conflict with Pi power path |

Stop if any wire gets warm, Pi shows undervoltage, or the Arduino disconnects repeatedly.

## Stage 3 - Motor Power And Low-PWM Test

Keep the robot lifted so wheels cannot drive the chassis off the table.

| Step | Action | Pass condition |
| --- | --- | --- |
| 1 | Measure motor rail before connection | Voltage is expected for 4 fresh alkaline AA cells and within motor/driver limits |
| 2 | Connect motor rail to driver VM/GND | Driver powers without heat or reset |
| 3 | Run left motor at low PWM | Left motor spins smoothly |
| 4 | Run right motor at low PWM | Right motor spins smoothly |
| 5 | Command forward direction | Both powered wheels rotate in expected forward direction |
| 6 | Fix direction if needed | Swap motor output pair or invert firmware direction flag |
| 7 | Test serial `STOP` | Both motors stop immediately |
| 8 | Test serial watchdog at low PWM | Motors stop when command stream is stale |

Do not tune PID here. This stage only proves wiring and motor direction.

## Stage 4 - Encoder Tick Test

Complete this before powering encoder signal wires from an unknown board.

| Step | Action | Pass condition |
| --- | --- | --- |
| 1 | Identify encoder `VCC`, `GND`, `A`, and `B` | Wire colors or board labels are recorded |
| 2 | Confirm encoder supply and output voltage | Voltage is safe for Arduino Uno inputs; no Pi GPIO connection is used |
| 3 | Rotate left wheel by hand | Left tick count changes |
| 4 | Rotate right wheel by hand | Right tick count changes |
| 5 | Rotate each wheel forward | Tick direction is consistent |
| 6 | Rotate one full wheel revolution | Ticks per wheel revolution are recorded |
| 7 | Run low-PWM motor command | Ticks increase while the commanded motor spins |

Record:

```text
left_ticks_per_wheel_rev =
right_ticks_per_wheel_rev =
encoder_supply_voltage =
encoder_output_voltage =
encoder_wire_colors =
encoder_controller = Arduino Uno
```

## Stage 5 - MPU6050 Check

| Check | Pass condition |
| --- | --- |
| Board label | Module says `MPU6050` or `GY-521` |
| Pin labels | `VCC`, `GND`, `SDA`, and `SCL` are identified before wiring |
| Voltage safety | Direct Pi I2C only if module works from 3.3V and does not pull I2C to 5V |
| I2C address | `0x68` or `0x69` detected |
| Connection path | Pi I2C, level shifter, or Arduino fallback recorded |
| Stationary readings | Accelerometer and gyro values are stable at rest |
| Axis orientation | Forward, left, and up axes are recorded |

If the module requires 5V, has 5V pullups, or voltage safety is unknown, do not connect it directly to Pi I2C. Use level shifting or read it through Arduino Uno.

## Stage 6 - USB Camera Check

| Check | Pass condition |
| --- | --- |
| Camera detected | Pi sees the USB camera |
| Frame capture | Frames can be captured consistently |
| Resolution recorded | Width and height recorded |
| FPS recorded | Stable frame rate recorded |
| Mount position | Height and tilt recorded after mounting |

Do not start ORB-SLAM3 tuning until camera FPS and mounting are stable.

## Stage 7 - Mechanical Measurements

Record these before calibration:

| Measurement | How to measure |
| --- | --- |
| Wheel diameter | Diameter of powered wheel in centimeters |
| Wheelbase | Distance between left and right wheel contact centers |
| Front support height | Height from floor to support contact point |
| Front support type | Center skid, caster-style support, passive wheel, or other |
| Front support test result | Three-point contact, traction, push, hand-rotation, and low-PWM turn checks |
| Camera height | Floor to camera optical center |
| Camera tilt | Degrees from horizontal |
| MPU6050 position | Location relative to robot center |
| Motor rail voltage under load | Voltage while motors spin at low PWM |
| Pi power source | PSU or battery model and output rating |

Record the final values in `wiki/architecture/phase-1-measurement-worksheet.md`.

## Stage 8 - Ready For Phase 2 Gate

Phase 1 is ready to close when these are true:

- Both motors spin in the intended direction.
- Serial `PING`/`PONG`, `STOP`, and watchdog tests pass.
- Both encoders report ticks.
- Encoder supply/output voltage and controller path are recorded.
- Wheel diameter and wheelbase are recorded.
- Front support type, height, and low-PWM turn result are recorded.
- MPU6050 identity, address, and orientation are recorded.
- MPU6050 connection path and direct-Pi-I2C safety decision are recorded.
- USB camera resolution/FPS and mount geometry are recorded.
- Pi rail and motor rail are documented.
- Shared-ground layout is documented.
- Any direct Pi-to-driver ground jumper is documented, or the worksheet states that Pi ground is through USB only.
- No production robot code has been written outside `project-code/`.
- `wiki/architecture/phase-1-measurement-worksheet.md` is filled in for all available values, with unknowns left as `TBD`.

After this gate, continue with sensor calibration in `wiki/architecture/sensor-calibration.md`.
