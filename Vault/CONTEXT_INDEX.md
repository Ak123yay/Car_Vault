# CONTEXT_INDEX.md - Car Vault Navigation Map

Read this before navigating the vault.

---

## Root Control Files

| File | Purpose |
| --- | --- |
| `AGENTS.md` | Assistant workflow rules for this vault |
| `PROJECT_CONTEXT.md` | Robotics project scope, assumptions, and boundaries |
| `TASKS.md` | Current work state and task order |
| `CONTEXT_LOCK.md` | Hard project boundaries |

---

## Active Wiki Sections

### `wiki/architecture/`

System architecture, hardware setup, software modules, sensor calibration, and SLAM configuration.

Key current files:

- `wiki/architecture/current-build-and-materials.md`
- `wiki/architecture/wiring-and-pin-plan.md`
- `wiki/architecture/phase-1-bringup-checklist.md`
- `wiki/architecture/phase-1-measurement-worksheet.md`

### `wiki/features/`

Navigation and control behavior.

### `wiki/testing/`

Validation plan and acceptance tests.

### `wiki/operations/`

Runtime failure handling and recovery behavior.

### `wiki/ai_agents/`

Future YOLO/perception planning only.

---

## Wiki Meta Files

| File | Purpose |
| --- | --- |
| `wiki/_master-index.md` | Active wiki navigation map |
| `wiki/_code-map.md` | Maps robotics concepts to future `project-code/` paths |
| `wiki/_coding-rules.md` | Coding constraints and safety rules |
| `wiki/_decision-log.md` | Running log of project decisions |
| `wiki/_legacy-deprecated.md` | Registry of old non-robotics wiki material |

---

## Working Directories

| Directory | Purpose |
| --- | --- |
| `raw/` | Input notes and unprocessed source material |
| `wiki/` | Structured robotics knowledge |
| `project-code/` | Future implementation only |
| `output/` | Generated reports, exports, and temporary review artifacts only |
| `logs/` | Compile logs and change history |
| `Onara_Design/` | Deprecated legacy Onara/SaaS frontend prototype material |

Only files listed in `wiki/_master-index.md` are active source-of-truth wiki files. Older unreferenced legacy files are deprecated material.

Do not use `Onara_Design/` for current robot UI, documentation, hardware, or software decisions unless the user explicitly reactivates it.

The JSX files in `Onara_Design/` are legacy frontend prototypes, not active robot implementation.

## Log Routing

| File | Purpose |
| --- | --- |
| `logs/_index.md` | Active/deprecated log routing |
| `logs/compile-log.md` | Robotics compile history |
| `logs/code-changes.md` | Append-only changes; pre-robotics entries are legacy history only |

## Current Settled Build

| Area | Selected direction |
| --- | --- |
| Compute | Raspberry Pi 5 |
| Low-level control | Arduino Uno over USB serial |
| Camera | USB camera |
| AI accelerator | Raspberry Pi AI HAT+ 26 TOPS / Hailo-8, future YOLO only |
| IMU | Provided MPU6050 module if verified |
| Drivetrain | Two 6V N20 encoder motors plus passive front support |
| Motor driver | DRV8833 first choice, TB6612FNG acceptable |
| Power | Separate Pi 5 USB-C rail and 6V-class motor rail with common ground |
