# Current Build And Materials

## Purpose

Keep one clean source of truth for the current robot build, owned parts, remaining purchases, and immediate assembly plan.

## Current Architecture

```text
USB camera -> Raspberry Pi 5 -> ORB-SLAM3 / Hailo YOLO / A*
MPU6050 -> Raspberry Pi 5 I2C preferred, Arduino Uno fallback -> orientation data
Wheel encoders -> Arduino Uno -> odometry ticks -> Raspberry Pi 5
Raspberry Pi 5 -> USB serial -> Arduino Uno -> DRV8833 -> motors
```

Power split:

```text
Pi rail: official Raspberry Pi 27W USB-C PSU, or mobile 5V 5A Pi-compatible battery/UPS that works with the AI HAT+ stack -> Raspberry Pi 5
Motor rail: 4xAA holder plus 4 fresh alkaline AA cells -> DRV8833 VM -> N20 motors
Control: Pi 5 USB -> Arduino Uno
Required ground reference: Arduino GND <-> DRV8833 GND <-> motor battery negative
Pi ground path: Pi shares ground with Arduino through USB; add a direct Pi-to-driver ground only if needed and record it
```

## Owned Parts

These should not be bought again.

| Part | Status | Notes |
| --- | --- | --- |
| Raspberry Pi 5 | Owned | Main compute for vision, SLAM, planning, and Hailo inference |
| Raspberry Pi AI HAT+ 26 TOPS | Owned | Hailo-8 accelerator for future YOLO/object detection |
| Arduino Uno | Owned | V1 low-level encoder/PID/motor controller |
| USB camera | Owned | Camera source for SLAM and YOLO |
| MPU6050 module | Owned | Verify module label, 3.3V I2C safety, and I2C address before calibration |
| 3 wheels | Owned | Use 2 as powered wheels if they fit N20 3mm D-shafts; keep third as spare/reference |
| Starter kit wiring/sensors | Owned | Jumpers, breadboard items, ultrasonic/IR sensors, LEDs/buttons, etc. |

## Purchase Rules

- First cart excludes owned parts: Pi 5, AI HAT+, Arduino Uno, USB camera, provided MPU6050, starter-kit wiring/sensors, and the 3 existing wheels.
- Buy only the required drivetrain, power, and mounting parts needed for Phase 1 bench bring-up.
- Do not buy conditional parts until the listed condition is true.
- Treat Amazon search strings as ordering targets, not live stock or price guarantees. Verify the product page before buying.
- Do not replace the Arduino Uno with ESP32-S3 for Phase 1.

## Buy Or Prepare Now

Buy or prepare these before drivetrain bring-up.

| Priority | Item | Quantity | Exact/current recommendation | Why |
| --- | --- | ---: | --- | --- |
| 1 | Pi 5 bench power source | 1 if not already owned | Official Raspberry Pi 27W USB-C PSU | Powers Pi 5, USB camera, AI HAT+, and Arduino-over-USB during bench tests |
| 2 | Encoder motors | 1 pack | MECCANIXITY 2pcs 100RPM Micro Gear Motor with Encoder, N20 DC6V, 1:150, 0.15A | Provides 2 powered drive motors with encoders |
| 3 | Motor driver | 1 | DRV8833 dual motor driver module; TB6612FNG acceptable if DRV8833 is unavailable | Drives both 6V motors from Arduino PWM/direction signals |
| 4 | Motor brackets | 2 or 1 pack | N20 motor mounting brackets with screws | Secure motors to chassis |
| 5 | Motor battery holder | 1 | 4xAA holder with switch/leads | Powers motors separately from Pi/Arduino |
| 6 | Motor battery cells | 4 fresh cells | Alkaline AA cells for Phase 1 low-speed motor tests | Simple 6V-class first motor source |
| 7 | Chassis/base material | 1 | CAD/printed plate, acrylic, plywood, or foam board | Holds Pi, Arduino, motors, battery, and camera |
| 8 | Fasteners/standoffs | 1 kit if not already available | M2/M3 screws, nuts, standoffs, zip ties, double-sided tape | Mounts electronics and drivetrain |

## First Amazon Cart

Use this as the current first cart, excluding parts already owned.

| Cart status | Buy/prep | Quantity | Search or example listing | Notes |
| --- | --- | ---: | --- | --- |
| Buy now | N20 encoder motor pair | 1 pack | `MECCANIXITY 2pcs 100RPM Micro Gear Motor with Encoder N20 DC6V 1:150` | Current motor pick. Must be 6V, 100RPM target, N20/GA12-N20 style, 3mm D-shaft, and include encoder. |
| Buy now | DRV8833 dual motor driver | 1 module | `DRV8833 dual motor driver module 3V-10V` | Must drive two DC motors. TB6612FNG is acceptable if DRV8833 is unavailable. Do not buy L298N. |
| Buy now | N20 motor brackets | 2 brackets or 1 pack | `N20 motor mounting bracket 12mm with screws` | Needed because N20 motors are small and hard to mount cleanly without brackets. |
| Buy if not owned | Pi 5 bench power | 1 | `Official Raspberry Pi 27W USB-C Power Supply` | Bench power for Pi 5, USB camera, AI HAT+, and Arduino-over-USB. |
| Buy/prep | Motor battery holder | 1 | `4 AA battery holder with switch leads` | This powers only the motor rail, not the Pi. |
| Buy/prep | Alkaline AA cells | 4 fresh cells | `AA alkaline batteries` | Phase 1 motor test cells. Measure motor rail voltage under load. |
| Prepare or buy | Chassis/base | 1 | CAD/print, acrylic sheet, plywood, or foam board | CAD/printed plate is preferred if available. |
| Buy if not owned | M2/M3 fasteners | 1 kit | `M2 M3 screw nut standoff kit` | Needed for motors, Pi/Arduino mounting, and cable strain relief. |

## Product Page Acceptance Checklist

Before checkout, open each product page and verify the listing details. Do not rely on the search-result title alone.

| Item | Buy only if the product page confirms | Reject if |
| --- | --- | --- |
| N20 encoder motor pair | 2 motors included; `DC6V` or 6V; 100RPM target; N20/GA12-N20 micro metal gearmotor; 3mm D-shaft; encoder included; encoder cable or pin labels shown | 12V version, 300RPM/1000RPM version, no encoder, unknown shaft, single motor when expecting pair |
| DRV8833 motor driver | DRV8833 chip/module; dual H-bridge or dual DC motor driver; motor supply range includes 6V; logic inputs can be driven by Arduino Uno; pins expose motor A/B outputs, VM, GND, and input pins | L298N, single-channel driver, motor voltage range excludes 6V, no clear VM/GND/input labels |
| TB6612FNG backup driver | TB6612FNG chip/module; dual DC motor driver; motor/load supply range includes 6V; logic supply/input compatible with Arduino Uno; `STBY`/standby pin is documented | L298N, single-channel driver, no standby/input labeling, motor voltage range excludes 6V |
| N20 brackets | Bracket says N20, GA12-N20, or 12mm micro metal gearmotor compatible; includes or fits small screws | Generic bracket with no N20/12mm compatibility |
| Pi 5 bench power | Official Raspberry Pi 27W USB-C PSU or clearly states 5.1V/5A output for Pi 5 | Phone charger, rectangular 9V battery, USB-A charger, unknown current rating |
| Motor battery holder | 4xAA holder with switch/leads; output wires are accessible for driver VM/GND | 8xAA holder wired as 8 cells in series, rectangular 9V clip as motor source, holder with no usable leads, higher-voltage pack without regulation plan |
| Alkaline AA cells | 4 fresh alkaline AA cells for Phase 1 low-speed motor tests | Mixing old/new cells, mixing battery chemistries, rechargeable pack without measuring under load |
| Chassis/base | Rigid enough to hold Pi, Arduino, motor battery, motor brackets, and camera without bending into wheels | Flexible base that lets motors twist or camera wobble |
| Fasteners/standoffs | M2/M3 screws, nuts, standoffs, zip ties, or tape suitable for Pi/Arduino/motor mounting and cable strain relief | No mounting hardware for the selected base |

Reference specs to check against:

- Raspberry Pi 27W USB-C Power Supply: official output is 5.1V, 5.0A, USB-C. Reference: https://www.raspberrypi.com/products/27w-power-supply/
- DRV8833: official motor supply range is 2.7V to 10.8V and it is a dual H-bridge driver. Reference: https://www.ti.com/lit/gpn/DRV8833
- TB6612FNG: motor/load supply range includes 6V; official/authorized listings show dual DC motor use and about 1.2A average output current. References: https://toshiba.semicon-storage.com/us/semiconductor/product/motor-driver-ics/brushed-dc-motor-driver-ics/detail.TB6612FNG.html and https://www.digikey.com/en/products/detail/toshiba-semiconductor-and-storage/TB6612FNG-C-8-EL/1730070

If a product page is unclear, do not treat it as confirmed. Pick a clearer listing or leave the item as pending.

## Pi Power Answer

The Pi is powered from its own USB-C rail, not from the motor battery.

Bench/testing setup:

```text
Wall outlet -> official Raspberry Pi 27W USB-C PSU -> Raspberry Pi 5
```

Mobile setup:

```text
Pi 5-compatible 5V 5A battery/UPS -> Raspberry Pi 5
```

Motor setup:

```text
4xAA holder with 4 fresh alkaline AA cells -> DRV8833 VM -> N20 motors
```

The motor rail and control rail must share a reference only where control signals cross:

```text
Arduino GND <-> DRV8833 GND <-> motor battery negative
Pi GND is normally shared through the Pi-to-Arduino USB cable.
```

Do not power the Pi from the 4xAA motor pack, the Arduino 5V pin, the motor driver, a weak phone charger, or a rectangular 9V battery. Do not connect motor battery positive to Pi 5V or Arduino 5V.

## Conditional Buys - Wait

Only buy these if the condition is true.

| Item | Buy if | Recommendation |
| --- | --- | --- |
| N20 wheels | Existing wheels do not fit 3mm D-shaft N20 motors | N20 3mm D-hole rubber wheels |
| Extra front support hardware | Printed skid does not slide/turn well | Small ball caster or passive wheel hardware |
| Pi 5 mobile power | Untethered testing is needed now after bench bring-up works | Pi 5-compatible 5V 5A battery/UPS that does not block the AI HAT+ stack |
| I2C logic-level shifter | MPU6050 cannot be safely connected to Pi 3.3V I2C and Arduino fallback is not chosen | 4-channel bidirectional logic-level shifter |
| Extra jumper wires | Starter-kit jumpers are missing, damaged, or too short | Dupont female-to-female and male-to-female jumper set |
| AA NiMH rechargeable cells and charger | Alkaline cells drain too quickly during repeated testing | 4 to 8 AA NiMH cells plus compatible charger |

## Do Not Buy

- Another IMU unless the provided module is not actually MPU6050/GY-521.
- ESP32-S3 or another replacement controller for Phase 1.
- L298N motor driver.
- 12V motors.
- Motors without encoders.
- Pi camera ribbon cable, because the current camera is USB.
- Extra front drive motors.
- N20 wheels before checking whether the existing wheels fit.
- Mobile Pi UPS before bench bring-up proves the robot needs untethered tests.
- 8xAA holder unless it has a documented way to use exactly 4 cells as one 4-cell series bank.
- A weak phone charger or rectangular 9V battery for the Pi 5.

## Front Support Plan

Use a CAD/printed passive front support instead of buying front drive hardware.

Detailed mechanical requirements are in `wiki/architecture/front-support-and-chassis-plan.md`.

Preferred first part:

```text
single rounded front skid
height = tuned from powered wheel radius so chassis sits level
bottom = smooth rounded contact
mount = 2 screw holes into chassis
```

If the skid drags too much, revise to a ball-caster-style holder or buy a small caster.

Do not buy caster or passive wheel hardware until the printed skid fails the tests in `wiki/architecture/front-support-and-chassis-plan.md`.

## First Assembly Order

1. Mount the two N20 encoder motors with brackets.
2. Fit the two existing wheels if they match the 3mm D-shaft.
3. Print and mount the front skid using the height rules in `front-support-and-chassis-plan.md`.
4. Power Pi 5 from official 27W USB-C PSU first; use a verified 5V 5A mobile source only after checking AI HAT+ stack compatibility.
5. Measure motor rail, then wire motor battery -> DRV8833 -> motors.
6. Tie Arduino GND to DRV8833 GND and motor battery negative; rely on Pi-to-Arduino USB for Pi ground unless a direct Pi ground jumper is needed and recorded.
7. Complete the encoder verification gate, then wire encoders -> Arduino Uno.
8. Connect Arduino Uno -> Pi 5 over USB serial.
9. Verify motor direction and encoder ticks before adding autonomous behavior.

Detailed wiring and pin assignments are in `wiki/architecture/wiring-and-pin-plan.md`.

Use `wiki/architecture/phase-1-bringup-checklist.md` as the ordered execution checklist for purchase confirmation, bench wiring, low-PWM motor tests, encoder checks, IMU checks, camera checks, and measurement capture.

Record received part details and measured values in `wiki/architecture/phase-1-measurement-worksheet.md`.

## Immediate Measurements

Record these as soon as parts are mounted:

| Measurement | Why |
| --- | --- |
| Wheel diameter | Needed for cm-per-tick odometry |
| Wheelbase | Needed for differential-drive turning math |
| Front support height | Keeps chassis level |
| Encoder ticks per wheel revolution | Needed for odometry and PID |
| USB camera height/tilt | Needed for SLAM/camera calibration |
| MPU6050 axis orientation | Needed for heading correction |
| Pi 5 supply voltage/current rating | Needed to avoid brownouts under USB camera/Hailo load |
| Motor battery voltage under load | Needed to tune motor speed consistently |
