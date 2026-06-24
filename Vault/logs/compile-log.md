# compile-log.md - Compile History

---

## 2026-06-18 - Car Vault Robotics Compile

**Trigger**: User instruction `compile raw in car vault replace everything` with Tier 3 robotics planning text.

**Raw files processed**:

- `raw/New Text Document.txt` -> replaced with the new Tier 3 robotics planning source and compiled into active wiki docs.

**Files created or replaced this compile**:

| File | Source |
| --- | --- |
| `PROJECT_CONTEXT.md` | New robotics project context |
| `TASKS.md` | New robotics work state |
| `CONTEXT_INDEX.md` | New robotics navigation map |
| `CONTEXT_LOCK.md` | New robotics structural rules |
| `AGENTS.md` | New Car Vault assistant rules |
| `wiki/_master-index.md` | New active wiki map |
| `wiki/_code-map.md` | Future robotics implementation mapping |
| `wiki/_coding-rules.md` | Robotics coding and safety rules |
| `wiki/_decision-log.md` | Robotics reset decision |
| `wiki/architecture/_index.md` | Architecture index |
| `wiki/architecture/system-design.md` | System architecture |
| `wiki/architecture/hardware-design.md` | Hardware design |
| `wiki/architecture/sensor-calibration.md` | Sensor calibration |
| `wiki/architecture/slam-configuration.md` | ORB-SLAM3 configuration |
| `wiki/architecture/modules.md` | Software architecture |
| `wiki/features/_index.md` | Feature index |
| `wiki/features/navigation-planning.md` | Occupancy grid and A* planning |
| `wiki/features/control-system.md` | PID and motor control |
| `wiki/testing/_index.md` | Testing index |
| `wiki/testing/test-strategy.md` | Validation plan |
| `wiki/operations/_index.md` | Operations index |
| `wiki/operations/failure-handling.md` | Failure handling |
| `wiki/ai_agents/_index.md` | Future perception index |
| `wiki/ai_agents/perception-yolo.md` | Future YOLO boundary |

**Result**: Active source of truth now describes a Tier 3 autonomous indoor robot stack: camera, IMU, encoders, ORB-SLAM3, occupancy grid, A*, PID, and future YOLO.

**Note**: Older legacy files may still exist on disk as deprecated material, but they are no longer referenced by `wiki/_master-index.md`.

---

## 2026-06-19 - Robotics Documentation Cleanup Passes

**Trigger**: Continued user instruction to keep fixing the vault after hardware decisions changed.

**Follow-up active docs added**:

| File | Purpose |
| --- | --- |
| `wiki/architecture/current-build-and-materials.md` | Canonical owned parts, buy list, do-not-buy list, and first assembly order |
| `wiki/architecture/wiring-and-pin-plan.md` | Safe first-pass Pi 5, Arduino Uno, DRV8833, encoder, MPU6050, and split-power wiring |
| `wiki/architecture/phase-1-bringup-checklist.md` | Ordered Phase 1 purchase, wiring, motor, encoder, IMU, camera, and measurement procedure |
| `wiki/architecture/phase-1-measurement-worksheet.md` | Fill-in received-parts and measurement worksheet |
| `wiki/_legacy-deprecated.md` | Registry of old non-robotics wiki material |
| `logs/_index.md` | Active/deprecated log routing |

**Result**: Active docs now define the selected low-power robot architecture: Raspberry Pi 5, USB camera, AI HAT+ 26 TOPS, Arduino Uno, provided MPU6050, two 6V N20 encoder motors, DRV8833/TB6612FNG motor driver, split Pi/motor power rails, and a passive front support.

**Legacy routing**: Old Onara/SaaS wiki files and log entries remain on disk for recoverability but are explicitly marked deprecated or historical.
