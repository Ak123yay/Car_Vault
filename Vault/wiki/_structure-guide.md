# Wiki Structure Guide

## Purpose

This wiki is the structured knowledge base for the Car Vault robotics project.

The active project is a Tier 3 autonomous indoor robot, not the old Onara/SaaS project. Use `wiki/_master-index.md` as the navigation source of truth and `wiki/_legacy-deprecated.md` to identify old files that must be ignored.

## Active Folder Meanings

### architecture/

Robot system architecture, hardware design, power, sensors, SLAM configuration, and software module planning.

### features/

Robot behavior requirements such as navigation, A*, PID control, and drivetrain behavior.

### ai_agents/

Future robot perception only. Currently active for Hailo-8/YOLO planning after baseline navigation works.

### operations/

Robot runtime failure handling and recovery behavior.

### testing/

Robot validation plans for sensors, SLAM, odometry, control, and navigation.

## Deprecated Legacy Folders

The following folders are old Onara/SaaS material and are not active robotics docs:

- `business/`
- `content/`
- `data/`
- `decisions/`
- `dev/`
- `integrations/`
- `legal/`
- `research/`

## Rules

- Start with `TASKS.md`, then `wiki/_master-index.md`, then active wiki files.
- Do not use deprecated files for robot hardware, software, or purchasing decisions.
- Every folder must have an `_index.md`.
- Every active file must belong to a category listed in `wiki/_master-index.md`.
- Keep content concise and structured.
