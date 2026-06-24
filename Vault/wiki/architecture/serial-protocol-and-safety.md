# Serial Protocol And Motor Safety

## Purpose

Define the Pi 5 to Arduino Uno serial boundary for Phase 1 motor bring-up.

This is an interface specification for future firmware and Pi-side code. It does not mean production code is ready to write. Hardware measurements, wiring checks, and Phase 1 bring-up still come first.

## Ownership

| Board | Owns |
| --- | --- |
| Raspberry Pi 5 | High-level commands, target speeds, stop requests, logging |
| Arduino Uno | Encoder interrupts, PWM output, wheel PID later, command clamping, watchdog stop |

Use USB serial between Pi 5 and Arduino Uno. Do not use direct Pi GPIO UART with Arduino Uno 5V logic.

## Protocol Style

Use newline-terminated ASCII messages for first bring-up.

Rules:

- One command per line.
- Fields are separated by single spaces.
- Unknown commands are ignored and reported as `FAULT`.
- Malformed commands are ignored and reported as `FAULT`.
- `STOP` always has priority over motion commands.
- Arduino must clamp every motor command before output.
- Arduino must stop motors if the serial watchdog expires.

## Phase 1 Command Set

Pi 5 to Arduino Uno:

| Command | Meaning | Notes |
| --- | --- | --- |
| `PING seq host_ms` | Link check | Arduino returns `PONG` with same `seq` |
| `STOP seq reason` | Immediate motor stop | Must clear active PWM/speed target |
| `SET_PWM seq left_pwm right_pwm duration_ms` | Open-loop low-PWM bench command | First motor tests only |
| `SET_SPEED_TPS seq left_ticks_per_s right_ticks_per_s duration_ms` | Closed-loop wheel-speed target | Use only after encoder direction and ticks are verified |
| `STATUS seq` | Request current Arduino state | Returns `STATE` and latest tick data |

Arduino Uno to Pi 5:

| Message | Meaning | Notes |
| --- | --- | --- |
| `PONG seq arduino_ms` | Reply to `PING` | Confirms link and Arduino timebase |
| `ACK seq command` | Accepted command | Does not mean motion succeeded |
| `TICKS left_ticks right_ticks left_rate_tps right_rate_tps arduino_ms` | Encoder status | Ticks are signed cumulative counts |
| `STATE mode left_pwm right_pwm watchdog_ms arduino_ms` | Current motor state | `mode` examples: `STOPPED`, `OPEN_PWM`, `SPEED_PID`, `FAULT` |
| `FAULT code detail arduino_ms` | Rejected command or safety fault | `detail` should not contain spaces in first-pass firmware |

## Units And Limits

Initial safe limits:

| Field | Unit | Initial rule |
| --- | --- | --- |
| `left_pwm`, `right_pwm` | signed PWM command | Accept `-255..255`, clamp first tests to `-60..60` until motor direction is verified |
| `duration_ms` | milliseconds | Reject or clamp above `1000` for first bring-up |
| `watchdog_ms` | milliseconds | Stop motors if no valid command or `PING` arrives for `500` ms while motors are active |
| `left_ticks_per_s`, `right_ticks_per_s` | encoder ticks per second | Use only after ticks per revolution and direction are known |
| `seq` | integer | Pi increments each command; Arduino echoes in `ACK`/`PONG` |

Do not use meters per second for Phase 1 serial commands until wheel diameter and ticks per revolution are measured.

## Safety State Machine

```text
BOOT -> STOPPED
STOPPED + SET_PWM valid -> OPEN_PWM
STOPPED + SET_SPEED_TPS valid -> SPEED_PID
OPEN_PWM + duration expired -> STOPPED
SPEED_PID + duration expired -> STOPPED
ANY + STOP -> STOPPED
ANY + watchdog expired -> FAULT_STOP
ANY + parse/limit fault -> FAULT or STOPPED depending on severity
FAULT_STOP + STOP -> STOPPED
```

Rules:

- Arduino boots with motors stopped.
- Arduino must not output motor PWM until a valid command is received.
- Duration expiry stops motors even if serial is still connected.
- Watchdog expiry stops motors if commands stop arriving.
- `STOP` must work even if the previous command was malformed.
- Fault state must keep motors stopped until an explicit `STOP` or reset clears it.

## Fault Codes

Use simple stable codes:

| Code | Meaning |
| --- | --- |
| `PARSE` | Command could not be parsed |
| `UNKNOWN_CMD` | Command name not recognized |
| `LIMIT` | Command exceeded configured safe limits |
| `WATCHDOG` | Serial watchdog expired while motors were active |
| `ENCODER_STALE` | Motor command active but encoder ticks stopped unexpectedly |
| `DRIVER_DISABLED` | Motor driver enable/sleep pin not ready |
| `DIRECTION_MISMATCH` | Encoder direction disagrees with commanded direction |

## Bring-Up Sequence

1. Upload firmware with motor outputs disabled or clamped to zero.
2. Connect Arduino Uno to Pi 5 over USB.
3. Confirm serial device appears on Pi.
4. Send `PING 1 host_ms` and require matching `PONG 1 arduino_ms`.
5. Send `STATUS 2` and require `STATE STOPPED`.
6. With wheels lifted, send a low command such as `SET_PWM 3 30 0 250`.
7. Confirm left motor turns briefly and stops after duration.
8. Send `STOP 4 bench`.
9. Repeat for right motor.
10. Unplug or pause serial while a low command is active and confirm watchdog stop.

## Implementation Boundaries

- `wiki/architecture/wiring-and-pin-plan.md` owns physical pin assignments.
- `wiki/features/control-system.md` owns PID and motor mixing behavior.
- This document owns serial message names, units, watchdog behavior, and command safety rules.
- Future firmware belongs in `project-code/firmware/arduino_uno/motor_controller.ino`.
- Future Pi-side serial code belongs under `project-code/car_vault/`.

## Phase 1 Exit Criteria

Before PID tuning:

- `PING`/`PONG` works.
- `STOP` stops both motors.
- Low `SET_PWM` commands stop after `duration_ms`.
- Watchdog stop works.
- `TICKS` reports signed encoder counts.
- Fault messages are visible on the Pi.
- Worksheet records baud rate, watchdog timeout, command limit, and pass/fail results.
