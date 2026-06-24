# Wiring And Pin Plan

## Purpose

Define the first-pass safe wiring plan for the Pi 5, Arduino Uno, MPU6050, DRV8833, N20 encoder motors, USB camera, and split power rails.

This is a build plan, not measured calibration data. Update it after the exact motor driver board and encoder wire colors are confirmed.

## Power Rails

Use separate compute and motor rails.

```text
Pi rail:
official Raspberry Pi 27W USB-C PSU
or AI HAT+-compatible 5V 5A mobile battery/UPS
-> Raspberry Pi 5
-> USB camera
-> Raspberry Pi AI HAT+ 26 TOPS
-> Arduino Uno over USB

Motor rail:
4xAA holder plus 4 fresh alkaline AA cells
-> DRV8833 VM
-> N20 motors

Shared reference:
Arduino GND <-> DRV8833 GND <-> motor battery negative
Pi GND is shared through USB to Arduino; add a direct Pi/Arduino-to-driver ground only if needed for a stable signal reference.
```

4 fresh alkaline AA cells are near 6V and are the selected Phase 1 motor test source. NiMH rechargeables are optional later if repeated testing drains disposable cells too quickly.

Do not power the Pi from the motor pack, the Arduino 5V pin, the DRV8833, a phone charger, or a rectangular 9V battery. Do not connect motor battery positive to Pi 5V or Arduino 5V.

## Pi 5 Connections

| Device | Connection | Notes |
| --- | --- | --- |
| USB camera | Pi 5 USB port | Current selected camera source for SLAM and YOLO |
| Arduino Uno | Pi 5 USB port | Serial command/status link; avoids unsafe direct 5V UART into Pi GPIO |
| Raspberry Pi AI HAT+ 26 TOPS | Pi 5 PCIe/GPIO stack | Used later for Hailo YOLO inference |
| MPU6050 preferred path | Pi 5 I2C | Use only if the module works from 3.3V and does not pull I2C to 5V |

Preferred Pi I2C pins for MPU6050:

| MPU6050 pin | Pi 5 pin | Notes |
| --- | --- | --- |
| `VCC` | `3V3` physical pin 1 | Prefer 3.3V when connected directly to Pi I2C |
| `GND` | `GND` physical pin 6 | Common ground |
| `SDA` | `GPIO2 / SDA1` physical pin 3 | I2C data |
| `SCL` | `GPIO3 / SCL1` physical pin 5 | I2C clock |

First-pass MPU6050 gate:

1. Inspect the module label. It must say `MPU6050` or `GY-521`.
2. Confirm pin labels before wiring: `VCC`, `GND`, `SDA`, and `SCL`.
3. Direct Pi wiring uses Pi `3V3`, not Pi `5V`.
4. Run direct Pi I2C only if the module works from 3.3V and does not pull `SDA`/`SCL` up to 5V.
5. If voltage safety is unknown, use a logic-level shifter or read it from Arduino Uno over USB first.
6. Record detected address `0x68` or `0x69` and the final connection path.

If the MPU6050 board only works at 5V or has pullups to 5V, do not connect it directly to Pi I2C. Use a logic-level shifter or read it from the Arduino Uno and stream timestamped samples over USB.

## Arduino Uno To DRV8833

First-pass DRV8833 control uses two input pins per motor. PWM can be applied to one input while the other input controls direction.

| Function | Arduino Uno pin | DRV8833 pin label example |
| --- | --- | --- |
| Left motor input 1 | `D5` PWM | `AIN1` or `IN1` |
| Left motor input 2 | `D6` PWM | `AIN2` or `IN2` |
| Right motor input 1 | `D9` PWM | `BIN1` or `IN3` |
| Right motor input 2 | `D10` PWM | `BIN2` or `IN4` |
| Driver sleep/enable | Tie high or Arduino output if present | `nSLEEP`, `STBY`, or `EN` depending on board |
| Driver logic ground | Arduino `GND` | Must share ground with motor rail |

Different DRV8833 breakout boards use different labels. Match by function, not by exact label text.

## Motor And Encoder Wiring

| Function | Arduino Uno pin | Notes |
| --- | --- | --- |
| Left encoder channel A | `D2` interrupt | Primary tick count |
| Right encoder channel A | `D3` interrupt | Primary tick count |
| Left encoder channel B | `D4` | Direction sensing |
| Right encoder channel B | `D7` | Direction sensing |
| Left motor wires | DRV8833 left output pair | Swap pair if forward command spins backward |
| Right motor wires | DRV8833 right output pair | Swap pair if forward command spins backward |

Encoder power depends on the motor board. Confirm the encoder voltage from the product page or label before wiring. If encoder outputs are 5V, feed them to Arduino Uno only, not directly to Pi GPIO.

Encoder verification gate:

1. Identify the two motor power wires separately from the encoder wires.
2. Confirm encoder pin labels or wire colors from the product page, board label, or continuity check.
3. Identify encoder `VCC`, `GND`, `A`, and `B` before applying power.
4. Confirm encoder supply voltage and output voltage before connecting signal wires.
5. Phase 1 encoder A/B outputs go to Arduino Uno only, not Pi GPIO.
6. 5V encoder outputs are acceptable for Arduino Uno digital inputs, but not for Pi GPIO.
7. ESP32-S3 or another 3.3V controller is future-only unless `TASKS.md` changes the controller and level shifting or 3.3V-compatible encoder output is verified.

## Serial Contract

Detailed protocol rules, message units, watchdog behavior, and fault handling are defined in `wiki/architecture/serial-protocol-and-safety.md`.

First-pass message shape:

```text
SET_PWM seq left_pwm right_pwm duration_ms
STOP seq reason
PING seq host_ms
```

Arduino Uno returns status:

```text
TICKS left_ticks right_ticks left_rate_tps right_rate_tps arduino_ms
FAULT code detail arduino_ms
PONG seq arduino_ms
```

Future firmware must implement the protocol from `wiki/architecture/serial-protocol-and-safety.md`; do not invent a separate message format in code.

## Bring-Up Order

1. Power the Pi 5 from the official 27W USB-C PSU.
2. Connect Arduino Uno to Pi 5 over USB and confirm serial visibility.
3. Wire DRV8833 logic inputs to Arduino with motor power disconnected.
4. Wire common ground between Arduino, DRV8833, and motor battery negative.
5. Connect motor battery to DRV8833 VM.
6. Test one motor at low PWM.
7. Test both motors at low PWM.
8. Wire encoder channels and verify tick direction.
9. Connect MPU6050 on Pi I2C only after the direct-Pi-I2C safety gate passes; otherwise use a logic-level shifter or Arduino Uno fallback.
10. Record final wire colors, board labels, and any pin changes in this document.

## Safety Checks

- Pi and motor power rails are separate.
- No motor power passes through the Pi or Arduino.
- Motor battery positive never connects to Pi 5V or Arduino 5V.
- No Arduino 5V UART wire goes into Pi GPIO.
- No 5V I2C signal goes into Pi GPIO.
- No encoder output wire goes directly into Pi GPIO during Phase 1.
- Arduino Uno remains the Phase 1 encoder/PID/motor controller; ESP32-S3 is not a drop-in replacement without voltage verification and a `TASKS.md` controller change.
- DRV8833 ground, Arduino ground, and motor battery negative share reference.
- Pi ground normally reaches the motor-control reference through the Pi-to-Arduino USB cable; any direct Pi ground jumper must be recorded.
- Motor outputs are tested at low PWM before mounting the robot on the floor.
- Wheels are lifted during first motor tests.
