# _master-index.md - Car Vault Wiki Master Index

Last compiled: 2026-06-19

This file lists the active wiki source of truth for the Tier 3 robotics system. Older unreferenced legacy documents are deprecated material and should not be used unless explicitly reactivated.

---

## Meta Files

| File | Status | Description |
| --- | --- | --- |
| `wiki/_master-index.md` | active | Navigation map for active robotics docs |
| `wiki/_code-map.md` | active | Maps robotics concepts to future implementation paths |
| `wiki/_coding-rules.md` | active | General code safety and implementation rules |
| `wiki/_decision-log.md` | active | Running decisions for the robotics project |
| `wiki/_structure-guide.md` | active | Defines active robotics wiki folder meanings and deprecated legacy folders |
| `wiki/_legacy-deprecated.md` | active | Registry of old non-robotics files that must not be used for current robot work |

---

## Architecture

| File | Status | Description |
| --- | --- | --- |
| `wiki/architecture/_index.md` | active | Architecture section index |
| `wiki/architecture/current-build-and-materials.md` | active | Current owned parts, remaining purchases, conditional buys, and assembly order |
| `wiki/architecture/system-design.md` | active | End-to-end sensor, SLAM, planning, control, and motor architecture |
| `wiki/architecture/hardware-design.md` | active | Physical robot setup, measurements, mounting, power, and wiring |
| `wiki/architecture/front-support-and-chassis-plan.md` | active | Passive front support and chassis mechanical design constraints |
| `wiki/architecture/phase-1-bringup-checklist.md` | active | Ordered first build, power, wiring, motor, encoder, IMU, camera, and measurement checklist |
| `wiki/architecture/phase-1-measurement-worksheet.md` | active | Fill-in worksheet for received parts, wiring, measurements, and Phase 1 bring-up results |
| `wiki/architecture/wiring-and-pin-plan.md` | active | First-pass safe wiring, pin assignments, and bring-up order |
| `wiki/architecture/serial-protocol-and-safety.md` | active | Pi-to-Arduino serial protocol, command limits, watchdog, and motor safety rules |
| `wiki/architecture/sensor-calibration.md` | active | Encoder, IMU, and camera calibration requirements |
| `wiki/architecture/slam-configuration.md` | active | ORB-SLAM3 camera/IMU configuration plan |
| `wiki/architecture/modules.md` | active | Software module structure, loop rates, and data contracts |

---

## Features

| File | Status | Description |
| --- | --- | --- |
| `wiki/features/_index.md` | active | Feature section index |
| `wiki/features/navigation-planning.md` | active | Occupancy grid, A* rules, costs, and waypoint behavior |
| `wiki/features/control-system.md` | active | PID, motor mixing, speed limits, and turning behavior |

---

## Testing

| File | Status | Description |
| --- | --- | --- |
| `wiki/testing/_index.md` | active | Testing section index |
| `wiki/testing/test-strategy.md` | active | Sensor, SLAM, mapping, navigation, and control validation plan |

---

## Operations

| File | Status | Description |
| --- | --- | --- |
| `wiki/operations/_index.md` | active | Operations section index |
| `wiki/operations/failure-handling.md` | active | Lost tracking, encoder mismatch, IMU drift, and sudden obstacle behavior |

---

## Future Perception

| File | Status | Description |
| --- | --- | --- |
| `wiki/ai_agents/_index.md` | active | Future perception section index |
| `wiki/ai_agents/perception-yolo.md` | active | YOLO integration boundaries after base navigation is stable |

---

## Compile Rules

When compiling raw input:

1. Read `TASKS.md`.
2. Read this index.
3. Compile new material into existing active wiki sections.
4. Update `TASKS.md`.
5. Log the compile in `logs/compile-log.md`.
6. Log changed files in `logs/code-changes.md`.
