# Deprecated Legacy Wiki Material

## Purpose

This file prevents old non-robotics material from being mistaken for active Car Vault documentation.

The current project is a Tier 3 autonomous indoor robotics platform. Use `wiki/_master-index.md`, `TASKS.md`, and `wiki/_code-map.md` for active work.

## Rule

Do not use the files listed here for robotics decisions, hardware purchases, implementation planning, or code generation unless the user explicitly reactivates one of them.

## Entire Deprecated Sections

These folders are legacy Onara/SaaS material and are not part of the active robot project:

| Folder | Status | Reason |
| --- | --- | --- |
| `wiki/business/` | deprecated | SaaS business planning, not robotics |
| `wiki/content/` | deprecated | Onara copywriting, not robotics |
| `wiki/data/` | deprecated | Supabase schema docs, not robotics |
| `wiki/decisions/` | deprecated | SaaS ADRs, not robotics ADRs |
| `wiki/dev/` | deprecated | Onara developer setup, not robot setup |
| `wiki/integrations/` | deprecated | SaaS integrations, not robot hardware/software integrations |
| `wiki/legal/` | deprecated | Onara legal docs, not robotics |
| `wiki/research/` | deprecated | Onara market research, not robotics research |

## Deprecated Files Inside Active Sections

These files remain in folders that also contain active robotics docs:

| File | Status |
| --- | --- |
| `wiki/ai_agents/agents.md` | deprecated |
| `wiki/ai_agents/blackboard.md` | deprecated |
| `wiki/ai_agents/models.md` | deprecated |
| `wiki/ai_agents/prompts.md` | deprecated |
| `wiki/ai_agents/rag.md` | deprecated |
| `wiki/ai_agents/workflows.md` | deprecated |
| `wiki/architecture/api-reference.md` | deprecated |
| `wiki/architecture/deployment-pipeline.md` | deprecated |
| `wiki/architecture/env-vars.md` | deprecated |
| `wiki/architecture/rate-limiting.md` | deprecated |
| `wiki/architecture/security.md` | deprecated |
| `wiki/features/api.md` | deprecated |
| `wiki/features/auth.md` | deprecated |
| `wiki/features/billing.md` | deprecated |
| `wiki/features/build-flow.md` | deprecated |
| `wiki/features/contractor-features.md` | deprecated |
| `wiki/features/dashboard.md` | deprecated |
| `wiki/features/google-places.md` | deprecated |
| `wiki/features/retention.md` | deprecated |
| `wiki/features/revision-system.md` | deprecated |
| `wiki/features/ui.md` | deprecated |
| `wiki/operations/billing-ops.md` | deprecated |
| `wiki/operations/monitoring.md` | deprecated |
| `wiki/operations/runbook.md` | deprecated |
| `wiki/operations/scaling.md` | deprecated |
| `wiki/testing/e2e-tests.md` | deprecated |
| `wiki/testing/unit-tests.md` | deprecated |
| `wiki/onara_credentials.md` | deprecated |

## Active Replacement Docs

Use these robotics docs instead:

| Need | Active doc |
| --- | --- |
| Current parts and buy list | `wiki/architecture/current-build-and-materials.md` |
| Hardware and wiring | `wiki/architecture/hardware-design.md` |
| System architecture | `wiki/architecture/system-design.md` |
| Software module plan | `wiki/architecture/modules.md` |
| Calibration | `wiki/architecture/sensor-calibration.md` |
| SLAM setup | `wiki/architecture/slam-configuration.md` |
| Navigation | `wiki/features/navigation-planning.md` |
| Control | `wiki/features/control-system.md` |
| Failure handling | `wiki/operations/failure-handling.md` |
| Testing | `wiki/testing/test-strategy.md` |
| Future Hailo/YOLO | `wiki/ai_agents/perception-yolo.md` |
