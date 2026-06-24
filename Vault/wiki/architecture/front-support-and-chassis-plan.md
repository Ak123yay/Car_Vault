# Front Support And Chassis Plan

## Purpose

Define the mechanical plan for the passive front support and chassis layout.

This document does not replace CAD. It defines what the CAD/printed part must satisfy before the robot is treated as mechanically ready for Phase 1 driving tests.

## Selected Layout

Use a three-contact-point layout for the first build:

```text
Front center: passive skid or ball-caster-style support

Rear left: powered N20 motor + wheel + encoder
Rear right: powered N20 motor + wheel + encoder
```

The two rear wheels provide all drive, turning, PID feedback, and encoder odometry. The front support is passive only.

Do not add front drive motors. Do not mechanically link the front support to the drive wheels.

## Required Measurements Before CAD

Record these in `phase-1-measurement-worksheet.md` before finalizing the part.

| Measurement | Why it matters |
| --- | --- |
| Powered wheel diameter | Defines wheel radius and target chassis height |
| Wheel radius | Starting target for support contact height |
| Chassis/base thickness | Needed for screw length and support mount height |
| Drive axle position | Defines wheelbase and support placement |
| Front support mounting area | Defines screw spacing and available footprint |
| Ground clearance target | Prevents chassis scraping during turns |
| Camera mount height/tilt | Front support height changes camera pitch |

Do not guess these values. Use placeholders only until the actual wheels, motors, brackets, and chassis material are available.

## Preferred Front Skid

Preferred first CAD part:

```text
shape: single rounded center skid
location: centered on robot centerline
height: tuned so chassis sits level with both powered wheels firmly on floor
bottom: smooth rounded contact patch
mount: 2 screw holes or zip-tie slots into chassis
material: low-friction printed plastic or smooth taped/contact surface
```

The skid should be narrow enough to turn without large drag, but wide enough that it does not dig into carpet or catch on small floor gaps.

## CAD Parameters

Use parameter names like these in CAD or design notes:

| Parameter | Initial value |
| --- | --- |
| `wheel_diameter_mm` | TBD |
| `wheel_radius_mm` | `wheel_diameter_mm / 2` |
| `chassis_plate_thickness_mm` | TBD |
| `drive_axle_to_front_support_mm` | TBD |
| `support_contact_height_mm` | TBD after wheel/bracket mounting |
| `support_mount_hole_spacing_mm` | TBD |
| `support_mount_screw_size` | TBD |
| `skid_contact_radius_mm` | TBD |
| `skid_contact_width_mm` | TBD |

`support_contact_height_mm` is not automatically equal to wheel radius. It must be adjusted for chassis thickness, motor bracket geometry, and where the support mounts.

## Fit Rules

- The chassis must sit level when the powered wheels and front support touch the floor.
- Both powered wheels must stay firmly on the floor.
- The front support must not lift either powered wheel.
- The support must not drag hard enough to prevent in-place turns.
- The support must not wobble enough to shake the camera or MPU6050.
- Wires must not run under the skid contact area.
- The support must not block motor wires, encoder wires, battery access, USB cable, or camera view.

## Height Tuning

Start with the support slightly too short, then shim upward if needed.

Failure signs:

| Symptom | Likely issue | Fix |
| --- | --- | --- |
| One or both drive wheels lose traction | Front support too tall or chassis twisted | Lower support or shim motor side |
| Chassis nose points down | Front support too short | Shim support upward or revise CAD height |
| Robot turns poorly in place | Skid contact too wide or too rough | Round/polish contact patch or switch to caster |
| Camera image bounces | Support mount flexes or catches floor | Stiffen mount and smooth contact |
| Robot rocks diagonally | Chassis/base flex or uneven mount | Stiffen base or adjust bracket/support height |

## Fallback Options

Use these only if the simple center skid fails testing.

| Fallback | Use if | Tradeoff |
| --- | --- | --- |
| Small ball caster | Skid drag is too high | Adds part cost and height constraints |
| Single passive front wheel | Skid catches on surface | Tracks straight better but can resist sideways turns |
| Two passive front wheels | Chassis needs four contact points | More alignment risk and more turn friction |

Do not buy fallback hardware until the printed skid fails a bench test.

## Mechanical Tests

Run these before motor PID or navigation tests.

| Test | Pass condition |
| --- | --- |
| Three-point contact test | Both powered wheels and front support touch floor without rocking |
| Drive-wheel traction test | Each powered wheel resists light finger spin while robot rests on floor |
| Push test | Robot rolls/slides forward without snagging the support |
| In-place hand rotation | Robot can rotate by hand without the front support digging in |
| Low-PWM turn test | Robot turns slowly without front support chatter |
| Camera/IMU wobble check | Camera and MPU6050 do not visibly shake from support movement |

## Phase 1 Exit Requirements

Mechanical side of Phase 1 is ready only when:

- Front support type is recorded.
- Front support height is measured.
- Wheel diameter and wheelbase are measured.
- Chassis sits level enough for camera tilt to be measured consistently.
- Both powered wheels keep traction during low-PWM tests.
- The support passes the low-PWM turn test.

Record final results in `wiki/architecture/phase-1-measurement-worksheet.md`.
