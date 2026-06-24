# Code Changes Log

## Log Routing Notice

Entries before `2026-06-18 - Car Vault robotics planning compile` are legacy Onara/SaaS history. Keep them for recoverability only. Do not use those older entries for current Car Vault robotics decisions.

## 2026-05-15

### Phase 1 marked complete + hooks paths fixed

**Files affected**: `TASKS.md`, `.claude/settings.json`

**What changed**:
- `TASKS.md`: Legacy Onara Phase 1 status was marked complete. Credential inventory details were redacted during Car Vault cleanup.
- `.claude/settings.json`: Fixed SessionStart hook path from `obsidian-vault/TASKS.md` → `Onara_Vault/TASKS.md` and `obsidian-vault/wiki/_code-map.md` → `Onara_Vault/wiki/_code-map.md`. Paths were pointing to old folder name.

**Notes from credentials scan**:
- Redacted legacy credential inventory details. Do not use this historical section for current robotics decisions.

**Why**: Historical Onara setup state was recorded before the Car Vault robotics reset. Hook paths referenced non-existent legacy folders and were corrected at the time.

---

### Seeded GBP leads tracker + created Facebook groups research file

**Files affected**: `output/gbp-leads-tracker.csv`, `wiki/research/facebook-groups.md`, `wiki/research/gbp-search-process.md`, `wiki/research/_index.md`

**What changed**:
- `gbp-leads-tracker.csv`: Populated with 73 contractor lead rows from DC/NoVA Craigslist skilled trade services (plumbers 25, electricians 11, HVAC 9, handymen 8, roofers 9, landscapers 2, other 9). Each row has business name, trade category, service city, phone (where available), `has_website: false`, and notes indicating source + GBP verification needed. 3 additional leads from Yelp search snippets (DC plumbers with addresses).
- `facebook-groups.md`: New file documenting 10 DC/NoVA contractor Facebook groups across 3 tiers: Tier 1 (contractor-facing trade groups), Tier 2 (neighborhood homeowner groups with contractor activity), Tier 3 (national trade group). Includes join order, 30-minute lurk protocol (what pain points/digital signals to observe), and outreach guidance (post only after 1–2 weeks observation).
- `gbp-search-process.md`: Added "Supplementary Source: Craigslist" section explaining how to verify pre-seeded leads on Google Maps (search phone number → confirm GBP listing → copy URL into tracker). Expected hit rate ~60–70%, projecting 44–51 confirmed GBP listings from current 73 seeds. Updated Related Files section.
- `wiki/research/_index.md`: Added `facebook-groups.md` entry.

**Why**: Phase 0 tasks "Identify 50+ GBP listings" and "Join 5–10 contractor Facebook groups" were flagged as incomplete by user. Browser extension not available for Google Maps scraping; Yelp/YellowPages/Porch.com return 403. Used Craigslist DC skilled trades section (accessible via WebFetch) as primary lead source — Craigslist operators are the strongest proxy for no-website contractors. Facebook groups file documents the 10 groups found via web search for the user to join manually.

**Remaining manual steps**:
- GBP task: User opens each lead in tracker → searches phone on Google Maps → pastes GBP URL → deletes non-GBP leads → target is 50 confirmed GBP+no-website leads
- Facebook task: User joins groups 1–6 from facebook-groups.md → reads each for 30 min → records observations in `output/facebook-lurk-notes.md`

---

### Added WTP section to ICP document

**Files affected**: `wiki/business/icp.md`, `TASKS.md`

**What changed**: Added a "Willingness to Pay (WTP)" section to the ICP document between the Pain Points section and the Secondary ICP section. The new section covers:
- Current spend benchmarks (what the ICP already pays web designers, Wix, etc.)
- Observed WTP for Onara pricing tiers ($12/month, $29/month, $99/year)
- Price sensitivity triggers and framing notes
- Per-segment WTP table (5 segments with current spend, WTP, and notes)

**Why**: Phase 0 Task 1 required the ICP document to include business type, geography, size, pain point, AND WTP. The WTP field was the only missing component.

**TASKS.md**: Moved "Fill out ICP document" from Active → Done.

---

### Committed launch metro area + created GBP leads infrastructure

**Files affected**: `wiki/business/gtm.md`, `wiki/research/gbp-search-process.md`, `wiki/research/_index.md`, `output/gbp-leads-tracker.csv`, `TASKS.md`

**What changed**:
- `gtm.md`: Replaced TBD metro area with "Washington DC / Northern Virginia" (committed 2026-05-15)
- `gbp-search-process.md`: New file — step-by-step Google Maps search process for DC/NoVA, covering 3 rounds of search terms across DC proper + 5 NoVA suburbs, tips for spotting no-website listings, field-by-field recording guide, and volume targets
- `gbp-leads-tracker.csv`: New file — blank CSV tracker with 19 columns (id, business_name, category, address, city, state, phone, has_website, website_url, gbp_url, facebook_url, email, rating, review_count, contacted, contact_method, contact_date, response, notes)
- `TASKS.md`: Marked "Commit to target metro area" done; annotated "Identify 50+ GBP listings" with tracker/process file references

**Why**: "Identify 50+ GBP listings" requires a committed metro area. Browser extension was not connected so listings could not be pulled automatically — tracker and process created for manual execution (60–90 min).

---

### Created contractor-specific features list

**Files affected**: `wiki/features/contractor-features.md`, `wiki/features/_index.md`, `TASKS.md`

**What changed**: New file `contractor-features.md` documents 8 contractor-specific UI features for generated sites:
1. Emergency banner (sticky, above nav, with emergency hook copy + 24/7 phone)
2. Service area section (city tag list, SEO-optimized, Agent 1 inference)
3. License & insurance badge (user-input number or generic claim, never fabricated)
4. Google reviews badge (★ rating + count from GBP, omitted if < 3 reviews)
5. Prominent phone CTA (large hero placement + mobile sticky button)
6. Services list (Agent 2 generated, 5–8 items from category)
7. Free estimate CTA + contact form (Supabase Edge Function, lead SMS hook)
8. Years in business chip (extracted from GBP description or user input)

Also documents 5 new Blackboard fields, a v1/later priority table, and design references back to PlumberMock.

**Why**: Phase 0 task required a niche-specific features list covering the 4 mentioned features. Expanded to a complete 8-feature spec since all 8 are needed for a credible contractor site.

---

### Decided v1 retention mechanisms

**Files affected**: `wiki/_decision-log.md`, `wiki/features/retention.md`, `TASKS.md`

**What changed**:
- `_decision-log.md`: Added 2026-05-15 retention entry — decision rationale and build-time estimates for all 3 chosen mechanisms
- `retention.md`: Updated target versions — Feature 2 (Reviews Badge) and Feature 3 (Lead SMS) changed from v1.5 → v1; Feature 1 (GBP Sync) amended to note v1 covers change-detection email only, auto-deploy remains v2.5
- `TASKS.md`: Marked "Decide which 2–3 retention mechanisms" as done

**Decision**: Lead SMS Notification + Reviews Badge Weekly Refresh + GBP Change Detection Email (email only, no auto-deploy)

**Why**: Selected on direct churn-reduction impact vs. build complexity. All three are buildable in 2–2.5 days total. Lead SMS provides the strongest "site is working" signal; reviews refresh keeps the site feeling alive; GBP change detection email seeds the v2.5 moat at minimal cost.

---

### Phase 1 Tasks 1–2: GitHub setup guide + .env.template scaffolded

**Files affected**:
- `wiki/dev/phase1-github-setup.md` (new)
- `Onara_Code/config/.env.template` (new)
- `wiki/dev/setup.md` (fix)
- `wiki/dev/_index.md` (updated)
- `TASKS.md` (updated)

**What changed**:
- `phase1-github-setup.md`: New step-by-step guide for Task 1 (GitHub account creation + Education verification at education.github.com, with proof-of-enrollment options) and Task 2 (fine-grained PAT creation with exact field values: name "Onara Copilot", 90 days, no repositories, GitHub Copilot read-only only)
- `.env.template`: All 45 env vars scaffolded with `[PENDING]` / `[AUTO]` status labels, grouped by service (GitHub, Google, Supabase, Cloudflare, Stripe, Resend, NIM, Ollama, Pipeline, ChromaDB, Next.js, Monitoring, Feature Flags). Created in `Onara_Code/config/` — the first file in the code directory.
- `setup.md`: Redacted legacy token-permission detail during Car Vault cleanup.
- `TASKS.md`: Annotated Phase 1 Tasks 1–2 with guide + template file references

**Why**: Both tasks require manual browser interaction (account creation, token generation). Deliverable is the exact-click guide + `.env.template` so the user can execute both tasks in under 10 minutes each and immediately paste values into the right file.

---

## 2026-06-09

### Wiki execution cleanup and secret redaction

**Files affected**: `TASKS.md`, `wiki/_code-map.md`, `wiki/_coding-rules.md`, `wiki/_decision-log.md`, `wiki/_master-index.md`, `wiki/architecture/*`, `wiki/ai_agents/*`, `wiki/dev/*`, `wiki/features/*`, `wiki/integrations/*`, `wiki/data/*`, `wiki/operations/*`, `wiki/business/pricing.md`, `wiki/content/*`, `wiki/legal/privacy-policy.md`, `wiki/onara_credentials.md`, `Onara_Code/config/.env.template`

**What changed**:
- Clarified that Phase 3 is the next actionable phase and Stripe live payouts are deferred.
- Standardized implementation paths around `Onara_Code/`, design source around `Onara_Design/`, and schema names around `users`, `projects`, `pipeline_jobs`, `revisions`, and `pipeline_errors`.
- Made the recommended dev topology explicit: FastAPI and Ollama run on the same host; `cloudflared` runs where FastAPI runs.
- Aligned model docs with the active 10-agent pipeline and the pulled Ollama models `qwen3:8b` and `llama3.3:8b`.
- Aligned Stripe price ID names, plan limits, reverse-trial behavior, annual-plan flag, and local concurrency defaults.
- Replaced `wiki/onara_credentials.md` with a no-secret checklist/template.

**Why**: The wiki had conflicting execution guidance, stale schema and agent names, old env var names, and sensitive configuration material stored in a wiki file. These conflicts would cause wrong implementation choices during Phase 3 and later phases.

---

### Raw-supported pricing, subscription, and model audit

**Files affected**: `TASKS.md`, `Onara_Code/config/.env.template`, `wiki/architecture/env-vars.md`, `wiki/business/pricing.md`, `wiki/business/roadmap.md`, `wiki/content/email-copy.md`, `wiki/content/landing-page.md`, `wiki/dev/phase-checklist.md`, `wiki/features/billing.md`, `wiki/features/build-flow.md`, `wiki/features/dashboard.md`, `wiki/features/revision-system.md`, `wiki/integrations/nvidia-nim.md`, `wiki/integrations/stripe.md`, `wiki/legal/terms-of-service.md`, `wiki/operations/billing-ops.md`, `wiki/testing/test-strategy.md`, `wiki/onara_credentials.md`

**What changed**:
- Confirmed raw sources use local Ollama models `qwen3:8b` and `llama3.3:8b`; no raw plan source supports `qwen3.5:9b`.
- Standardized paid plans as Stripe subscriptions: Starter at `$12/month or $99/year`, Pro at `$29/month`.
- Restored annual Starter support through `STRIPE_STARTER_ANNUAL_PRICE_ID` and `FEATURE_ANNUAL_PLAN=true`.
- Standardized plan limits: Trial 3 sites/unlimited revisions during trial, Free 1 preview site/3 revisions, Starter 1 live site/10 revisions, Pro 3 live sites/unlimited revisions.
- Updated revision reset guidance: Free resets via pg_cron on the 1st; Starter resets on Stripe billing period; Trial/Pro use unlimited revision limits.
- Updated trial expiry copy so Free keeps dashboard preview but hides the public URL after Day 14.
- Added a Phase 24 task for Starter annual checkout price support without marking the annual price ID as completed.

**Why**: The wiki still contained old Starter/Pro limits, disabled annual-plan guidance, stale customer emails, and inconsistent Agent 6 routing. The raw 30-step plan and business plan were used as the support source for the corrected wiki behavior.

---

### June 2026 model refresh + v1 business scope alignment

**Files affected**: `TASKS.md`, `PROJECT_CONTEXT.md`, `Onara_Code/config/.env.template`, `wiki/_decision-log.md`, `wiki/ai_agents/*`, `wiki/integrations/ollama.md`, `wiki/dev/*`, `wiki/business/*`, `wiki/content/landing-page.md`, `wiki/features/retention.md`, `wiki/operations/scaling.md`, `wiki/testing/unit-tests.md`

**What changed**:
- Standardized current Ollama local models to `qwen3.5:9b` primary and `gemma4:e4b` fallback/supervisor.
- Moved the model pull/verification task to the top of Phase 3, before Node/Python/pnpm and `cloudflared`.
- Confirmed Starter and Pro subscriptions remain in scope, with Starter monthly + annual pricing documented.
- Re-centered launch strategy on Washington DC / Northern Virginia contractors and home-service businesses.
- Removed fake landing-page social proof and replaced it with honest early-access positioning.
- Kept v1 retention focused on lead SMS and weekly reviews badge refresh; moved GBP polling/change detection, seasonal SEO, and custom domains to post-v1.
- Corrected MRR tracking so active trials are not counted as recurring revenue.
- Updated infrastructure guidance to treat 16 GB RAM as minimum and 24 GB as recommended for reliable local fallback with both Ollama models.

**Why**: The user selected newer local models and asked for one more full wiki/business audit. The wiki now treats raw files as historical source material, while `TASKS.md`, `PROJECT_CONTEXT.md`, and the decision log carry the current operating truth.

---

### Phase 3 Ollama models verified

**Files affected**: `TASKS.md`, `wiki/dev/phase-checklist.md`

**What changed**:
- Marked the Phase 3 Ollama model pull/verification task complete.
- Confirmed the active local model pair is `qwen3.5:9b` primary and `gemma4:e4b` fallback.
- Reordered the phase checklist so the completed model verification appears before the remaining toolchain install task.

**Why**: User confirmed both Ollama models were pulled and responded successfully.

---

### Phase 3 toolchain check

**Files affected**: `TASKS.md`, `wiki/dev/phase-checklist.md`

**What changed**:
- Confirmed Node.js is installed at `v22.22.1`.
- Confirmed Python is installed at `Python 3.14.4`, satisfying the Python 3.11+ requirement.
- Split the remaining toolchain task so `pnpm` is the only unchecked install item.

**Why**: The original task bundled three tools together, but only `pnpm` is still missing.

---

## 2026-06-18

### Car Vault robotics planning compile

**Files affected**: `raw/New Text Document.txt`, `PROJECT_CONTEXT.md`, `TASKS.md`, `CONTEXT_INDEX.md`, `CONTEXT_LOCK.md`, `AGENTS.md`, `wiki/_master-index.md`, `wiki/_code-map.md`, `wiki/_coding-rules.md`, `wiki/_decision-log.md`, `wiki/architecture/*`, `wiki/features/*`, `wiki/testing/*`, `wiki/operations/*`, `wiki/ai_agents/_index.md`, `wiki/ai_agents/perception-yolo.md`, `logs/compile-log.md`

**What changed**:
- Replaced the active vault context from prior website-builder documentation to Car Vault Tier 3 robotics planning.
- Compiled the new raw input into engineering docs for system architecture, hardware design, sensor calibration, ORB-SLAM3 configuration, navigation, control, software architecture, testing, and failure handling.
- Updated the code map to define future `project-code/car_vault/` implementation paths.
- Updated task tracking so the next active work is filling in real hardware measurements and part choices.

**Why**: User requested `compile raw in car vault replace everything` using the Tier 3 robotics planning source text.

---

### Drivetrain architecture documented

**Files affected**: `TASKS.md`, `wiki/architecture/hardware-design.md`, `wiki/architecture/system-design.md`, `wiki/features/control-system.md`

**What changed**:
- Added the selected 4-wheel physical layout with 2 powered encoder motors and 2 passive/free-spinning wheels.
- Added Amazon-orderable low-power motor recommendation: 2x DFRobot TT Motor with Encoder, 6V 160RPM, 120:1.
- Added motor driver recommendation: DRV8833 or TB6612FNG, and explicitly avoid L298N for this low-power 6V robot.
- Updated tasks so ordering and final confirmation are tracked separately from the architecture decision.

**Why**: User clarified that the robot has 4 wheels and requested `TASKS.md` and wiki updates after confirming the 2-powered-motor drivetrain approach.

---

### Amazon motor recommendation updated

**Files affected**: `TASKS.md`, `wiki/architecture/hardware-design.md`

**What changed**:
- Replaced the unavailable DFRobot TT Motor with Encoder recommendation.
- Set the primary Amazon motor recommendation to 2x uxcell GA12-N20 6V 100RPM DC Gear Motor with Encoder.
- Added MECCANIXITY 2pcs 300RPM Micro Gear Motor with Encoder, N20 DC6V as the budget fallback.
- Marked the DFRobot Amazon listing as unavailable/do not rely on.

**Why**: User reported the DFRobot TT Motor with Encoder Amazon listing is currently unavailable.

---

### Exact Amazon encoder motor selected

**Files affected**: `TASKS.md`, `wiki/architecture/hardware-design.md`

**What changed**:
- Set the primary motor recommendation to `MECCANIXITY 2pcs 100RPM Micro Gear Motor with Encoder, N20 DC6V`.
- Recorded key specs from the Amazon product details: 1:150 reduction ratio and 0.15A.
- Moved uxcell GA12-N20 6V 100RPM to backup status.

**Why**: User found a cheaper 2-pack listing whose product details explicitly confirm `DC6V`, `100RPM`, and `with encoder`.

---

### Pi 5 and Arduino Uno compute split documented

**Files affected**: `TASKS.md`, `wiki/architecture/hardware-design.md`, `wiki/architecture/system-design.md`, `wiki/architecture/modules.md`, `wiki/features/control-system.md`

**What changed**:
- Recorded Raspberry Pi 5 as the main compute board for vision, camera capture, SLAM experiments, mapping, planning, and high-level navigation.
- Recorded Arduino Uno as an available low-level motor-control board for encoder interrupts, wheel PID, PWM, and direction outputs.
- Added USB serial as the recommended Pi 5 to Arduino Uno communication path.
- Added power and signal safety notes: do not power motors from Pi/Arduino, share ground when signals cross boards, and avoid direct 5V Arduino UART into Pi GPIO.

**Why**: User confirmed the robot will run on Raspberry Pi 5, use vision, and can also use Arduino Uno.

---

### Remaining robot hardware list documented

**Files affected**: `TASKS.md`, `wiki/_code-map.md`, `wiki/architecture/hardware-design.md`, `wiki/architecture/system-design.md`, `wiki/architecture/modules.md`, `wiki/architecture/sensor-calibration.md`

**What changed**:
- Removed the stale decision task about whether Pi 5 or Arduino Uno owns encoder/PID work; Arduino Uno is now selected for v1 low-level motor control.
- Added remaining hardware tasks: motor driver, N20 wheels, N20 brackets, front support, MPU6050 IMU, Pi 5 camera cable compatibility, motor power, and Pi 5 power/storage.
- Added Arduino firmware path: `project-code/firmware/arduino_uno/motor_controller.ino`.
- Documented first-pass Uno encoder wiring using `D2` and `D3` interrupts plus channel-B direction pins.

**Why**: User confirmed they already own an Arduino Uno and asked to update the wiki/docs before listing remaining needed hardware.

---

### Wheel inventory and CAD front support documented

**Files affected**: `TASKS.md`, `wiki/architecture/hardware-design.md`, `wiki/architecture/system-design.md`, `wiki/features/control-system.md`

**What changed**:
- Recorded that the user has 3 wheels available.
- Set the practical wheel plan to use 2 wheels as powered drive wheels and CAD/print a passive front support.
- Updated the preferred front support from purchased passive wheels to a CAD/printed center skid or ball-caster-style support.
- Added front support height as a required measurement.

**Why**: User asked whether they should use 2 existing wheels and make the front support in CAD.

---

### Hailo-8 AI HAT documented

**Files affected**: `TASKS.md`, `PROJECT_CONTEXT.md`, `wiki/_code-map.md`, `wiki/architecture/hardware-design.md`, `wiki/architecture/system-design.md`, `wiki/ai_agents/perception-yolo.md`

**What changed**:
- Recorded the Raspberry Pi AI HAT+ 26 TOPS / Hailo-8 as owned hardware.
- Added Hailo-8 as the future YOLO/object-detection accelerator.
- Preserved architecture boundaries: ORB-SLAM3 handles localization, Arduino Uno handles motor control, and Hailo-8 handles inference only.
- Added future perception tasks for installing Hailo software and running a YOLO demo.

**Why**: User confirmed they already own the Hailo-8 26 TOPS AI HAT.

---

### USB camera selected

**Files affected**: `TASKS.md`, `PROJECT_CONTEXT.md`, `wiki/architecture/hardware-design.md`, `wiki/architecture/system-design.md`, `wiki/architecture/slam-configuration.md`, `wiki/ai_agents/perception-yolo.md`

**What changed**:
- Recorded USB camera as the selected Pi 5 camera interface.
- Removed the Pi 5 CSI camera cable compatibility task.
- Updated SLAM and YOLO docs to describe USB camera frames as the camera source.
- Changed camera measurement task to record USB camera model, resolution, FPS, mounting height, and tilt.

**Why**: User confirmed they are using a USB camera.

---

### Provided MPU6050 selected

**Files affected**: `TASKS.md`, `wiki/architecture/hardware-design.md`, `wiki/architecture/sensor-calibration.md`

**What changed**:
- Marked the provided MPU6050 module as the selected IMU.
- Removed the task to order a separate GY-521 MPU6050.
- Added verification tasks for module label, I2C wiring, I2C address, mounting position, and orientation.

**Why**: User wants to use the MPU6050 module they already have.

---

### Project materials organized

**Files affected**: `TASKS.md`, `wiki/_master-index.md`, `wiki/architecture/_index.md`, `wiki/architecture/current-build-and-materials.md`, `wiki/architecture/hardware-design.md`

**What changed**:
- Added a canonical current build and materials document.
- Separated owned parts, required buys, conditional buys, and do-not-buy items.
- Changed wheel-buy guidance from unconditional to conditional on whether existing wheels fit N20 3mm D-shafts.
- Added missing preparation tasks for motor power, chassis/base material, and fasteners/standoffs.
- Reworded drivetrain decision to 2 powered encoder wheels plus CAD/printed passive front support.

**Why**: User asked to organize the project after several hardware decisions changed quickly.

---

### Power architecture made explicit

**Files affected**: `TASKS.md`, `wiki/architecture/current-build-and-materials.md`, `wiki/architecture/hardware-design.md`, `wiki/architecture/system-design.md`

**What changed**:
- Added Pi 5 power as a first-class required item instead of a vague conditional note.
- Documented two separate power rails: Pi rail and motor rail.
- Set Pi power target to official Raspberry Pi 27W USB-C PSU for bench use, or mobile 5V 5A Pi-compatible battery/UPS for untethered use.
- Kept motor rail separate: 4xAA NiMH holder or regulated 6V source into DRV8833.
- Added common-ground requirement between Pi/Arduino and motor driver/motor battery.

**Why**: User correctly pointed out that the prior buy list did not explicitly say what powers the Pi 5.

---

### Materials list and Pi power checklist tightened

**Files affected**: `TASKS.md`, `wiki/_master-index.md`, `wiki/architecture/current-build-and-materials.md`, `wiki/architecture/hardware-design.md`, `wiki/architecture/system-design.md`, `logs/code-changes.md`

**What changed**:
- Added an Amazon-order checklist that excludes owned parts and separates required buys from conditional buys.
- Added a direct Pi power answer: official 27W USB-C PSU for bench testing; Pi 5-compatible 5V 5A battery/UPS only for mobile testing.
- Added AA NiMH cells/charger as a missing motor-power purchase if not already owned.
- Added physical-compatibility warning for mobile Pi power boards because the Raspberry Pi AI HAT+ already occupies the Pi stack.
- Cleaned stale shorthand in the active power diagrams so motor power is described as a 4xAA holder plus cells or a regulated 6V source.
- Updated the master index compile date.

**Why**: The current build needed one clear list of what to order next and how the Pi is powered without mixing it with the motor rail.

---

### Legacy wiki routing quarantined

**Files affected**: `TASKS.md`, `wiki/_master-index.md`, `wiki/_structure-guide.md`, `wiki/_legacy-deprecated.md`, `wiki/_decision-log.md`, `wiki/architecture/_index.md`, `wiki/ai_agents/_index.md`, `wiki/features/_index.md`, `wiki/operations/_index.md`, `wiki/testing/_index.md`, `wiki/business/_index.md`, `wiki/content/_index.md`, `wiki/data/_index.md`, `wiki/decisions/_index.md`, `wiki/dev/_index.md`, `wiki/integrations/_index.md`, `wiki/legal/_index.md`, `wiki/research/_index.md`, `logs/code-changes.md`

**What changed**:
- Added `wiki/_legacy-deprecated.md` as the registry for old non-robotics docs.
- Updated `wiki/_structure-guide.md` to define the active robotics folder meanings and deprecated legacy folders.
- Added `wiki/_structure-guide.md` to the master meta-file table.
- Updated active mixed section indexes to separate active robotics files from deprecated old Onara/SaaS files.
- Replaced legacy-only section indexes with deprecation notices.
- Recorded the routing decision in `wiki/_decision-log.md`.
- Marked the cleanup as done in `TASKS.md`.

**Why**: The vault still contained old Onara/SaaS documents that could be found by search. They needed explicit routing so only robotics docs are treated as active source of truth.

---

### First-pass wiring and pin plan added

**Files affected**: `TASKS.md`, `PROJECT_CONTEXT.md`, `wiki/_master-index.md`, `wiki/_code-map.md`, `wiki/architecture/_index.md`, `wiki/architecture/wiring-and-pin-plan.md`, `wiki/architecture/current-build-and-materials.md`, `wiki/architecture/hardware-design.md`, `wiki/architecture/system-design.md`, `wiki/architecture/sensor-calibration.md`, `wiki/architecture/modules.md`, `wiki/features/control-system.md`, `logs/code-changes.md`

**What changed**:
- Added a dedicated wiring and pin plan for Pi 5, Arduino Uno, DRV8833, MPU6050, encoder channels, USB camera, and split power rails.
- Set first-pass Arduino pins for encoder interrupts, encoder direction channels, and DRV8833 motor inputs.
- Clarified that Arduino Uno owns v1 encoder/PID/motor control and streams ticks to Pi 5 over USB serial.
- Clarified that MPU6050 should prefer Pi 5 I2C only if the module works from 3.3V and does not pull I2C to 5V, otherwise use level shifting or Arduino fallback.
- Replaced vague shared-battery wording in `PROJECT_CONTEXT.md` with explicit split compute and motor rails.
- Added follow-up tasks to confirm DRV8833 labels and MPU6050 voltage/logic safety.

**Why**: The build docs needed a concrete safe assembly bridge between the materials list and future firmware implementation.

---

### Phase 1 bring-up checklist added

**Files affected**: `TASKS.md`, `wiki/_master-index.md`, `wiki/architecture/_index.md`, `wiki/architecture/phase-1-bringup-checklist.md`, `wiki/architecture/current-build-and-materials.md`, `wiki/testing/test-strategy.md`, `logs/code-changes.md`

**What changed**:
- Added a Phase 1 checklist that orders purchase confirmation, bench wiring, motor power checks, low-PWM motor tests, encoder tick tests, MPU6050 checks, USB camera checks, and mechanical measurement capture.
- Added a clear Phase 1 gate before Phase 2 calibration.
- Linked the bring-up checklist from current materials and testing docs.
- Marked the checklist creation as done and added the Phase 1 completion gate to `TASKS.md`.

**Why**: The vault needed one execution checklist connecting the materials list, wiring plan, and validation plan before any production robot code is written.

---

### Phase 1 measurement worksheet added

**Files affected**: `TASKS.md`, `wiki/_master-index.md`, `wiki/_code-map.md`, `wiki/architecture/_index.md`, `wiki/architecture/phase-1-measurement-worksheet.md`, `wiki/architecture/phase-1-bringup-checklist.md`, `wiki/architecture/hardware-design.md`, `wiki/architecture/current-build-and-materials.md`, `wiki/testing/test-strategy.md`, `logs/code-changes.md`

**What changed**:
- Added a fill-in worksheet for received part confirmation, power measurements, final wiring, mechanical measurements, encoder measurements, IMU checks, camera checks, and Phase 1 pass/fail gates.
- Linked the worksheet from the bring-up checklist, hardware design, current materials, testing strategy, master index, and architecture index.
- Updated `_code-map.md` so future `robot.yaml` measured values come from the worksheet and hardware design.
- Added a backlog task to fill the worksheet as parts arrive and tests pass.

**Why**: Phase 1 needed one authoritative place to record real values instead of spreading measured hardware data across multiple docs.

---

### Log routing and legacy notices added

**Files affected**: `TASKS.md`, `CONTEXT_INDEX.md`, `CONTEXT_LOCK.md`, `logs/_index.md`, `logs/compile-log.md`, `logs/code-changes.md`, `logs/devlog-002-real-pipeline-billing.md`

**What changed**:
- Added `logs/_index.md` to define active logs and deprecated legacy logs.
- Added a routing notice at the top of `logs/code-changes.md` so pre-robotics entries are historical only.
- Marked the old Onara pipeline devlog as deprecated legacy material.
- Updated `CONTEXT_INDEX.md` and `CONTEXT_LOCK.md` to include legacy wiki/log routing.
- Added a compile-log follow-up entry summarizing the 2026-06-19 robotics cleanup passes.
- Marked the log-routing cleanup as done in `TASKS.md`.

**Why**: Old Onara/SaaS logs still appeared in searches and could be mistaken for current instructions. The vault needed explicit log routing like the wiki already has.

---

### Root context hardware decisions locked

**Files affected**: `TASKS.md`, `CONTEXT_INDEX.md`, `CONTEXT_LOCK.md`, `logs/code-changes.md`

**What changed**:
- Added settled Phase 1 build choices to `CONTEXT_LOCK.md`: Raspberry Pi 5, USB camera, Raspberry Pi AI HAT+ 26 TOPS, Arduino Uno, provided MPU6050, two 6V N20 encoder motors, passive front support, DRV8833/TB6612FNG, and split power rails.
- Added do-not-regress hardware boundaries: no 12V motors, no extra front drive motors, no extra IMU unless verification fails, no L298N final driver, and no Pi power from the motor rail.
- Added quick current-build summary and key Phase 1 architecture files to `CONTEXT_INDEX.md`.
- Marked the context-lock cleanup as done in `TASKS.md`.

**Why**: The root context files needed to reflect the same settled hardware choices as the active wiki so future work does not re-open already-corrected decisions.

---

### Legacy design folder and project-code placeholder handled

**Files affected**: `AGENTS.md`, `CONTEXT_INDEX.md`, `CONTEXT_LOCK.md`, `TASKS.md`, `project-code/README.md`, `logs/code-changes.md`

**What changed**:
- Marked `Onara_Design/` as deprecated legacy Onara/SaaS frontend prototype material.
- Added explicit rules not to use `Onara_Design/` for current robot design, hardware, software, or purchasing decisions unless explicitly reactivated.
- Added `project-code/README.md` so the implementation target exists while staying locked against production code until Phase 1 measurements and task authorization are ready.
- Marked the cleanup as done in `TASKS.md`.

**Why**: Root-level legacy assets still existed outside wiki/log routing. They needed classification, and the future implementation directory needed a clear no-code-yet placeholder.

---

### Legacy secret-pattern placeholders sanitized

**Files affected**: `TASKS.md`, `wiki/dev/setup.md`, `wiki/integrations/github.md`, `logs/audit-log.md`, `logs/code-changes.md`

**What changed**:
- Ran a repository secret-pattern scan excluding `.git`, `.obsidian/plugins`, and `node_modules`.
- Confirmed the only hits were literal private-key header examples in deprecated Onara/SaaS wiki docs, not confirmed live secrets.
- Replaced the scanner-triggering FastAPI `.env` example in `wiki/dev/setup.md` with local-env-only placeholder guidance.
- Replaced deprecated `wiki/integrations/github.md` with a short legacy stub containing no secret examples.
- Replaced deprecated `wiki/dev/phase1-github-setup.md` with a short legacy stub containing no token-format examples.
- Replaced deprecated `wiki/architecture/security.md` with a short legacy stub containing no web-app secret-handling instructions.
- Redacted a legacy credential inventory summary from the old 2026-05-15 log entry.
- Redacted an old token-permission detail from the old 2026-05-15 log entry.
- Added `logs/audit-log.md` to record the repository hygiene audit.
- Verified the final scan returns `NO_SECRET_PATTERN_HITS`.
- Verified broad legacy credential-detail search returns `NO_LEGACY_CREDENTIAL_DETAIL_TERMS`.
- Verified master-index references return `MASTER_INDEX_LINKS_OK`.
- Marked the audit as complete in `TASKS.md`.

**Why**: Deprecated legacy docs can still trigger repository secret scanners. Sanitizing the examples keeps the vault cleaner without changing active robotics planning.

---

### Wiki routing integrity audit recorded

**Files affected**: `TASKS.md`, `logs/audit-log.md`, `logs/code-changes.md`

**What changed**:
- Ran an integrity audit for every Markdown file under `wiki/`.
- Confirmed all 101 wiki Markdown files are either active in `wiki/_master-index.md`, explicitly listed as deprecated in `wiki/_legacy-deprecated.md`, or contained in a deprecated legacy folder.
- Recorded the audit result `ALL_WIKI_FILES_ROUTED`.
- Marked the routing audit as complete in `TASKS.md`.

**Why**: The vault still contains legacy Onara/SaaS files for recoverability. This audit proves they are classified and prevents untracked docs from becoming accidental source-of-truth.

---

### Root project context aligned with locked hardware choices

**Files affected**: `PROJECT_CONTEXT.md`, `TASKS.md`, `logs/audit-log.md`, `logs/code-changes.md`

**What changed**:
- Replaced stale generic hardware assumptions in `PROJECT_CONTEXT.md` with the locked Phase 1 hardware direction.
- Added Raspberry Pi 5, Arduino Uno, USB camera, Raspberry Pi AI HAT+ 26 TOPS / Hailo-8, provided MPU6050, two 6V N20 encoder motors, DRV8833/TB6612FNG, passive front support, and split power rails to the root context.
- Replaced the stale statement that all part numbers are pending with a narrower statement that final received labels, wheel fit, encoder details, dimensions, and electrical measurements are pending.
- Marked the root-context alignment as complete in `TASKS.md`.
- Verified stale root hardware wording is gone with `NO_STALE_ROOT_HARDWARE_WORDING`.
- Re-ran standard integrity checks: `MASTER_INDEX_LINKS_OK`, `NO_SECRET_PATTERN_HITS`, and `NO_LEGACY_CREDENTIAL_DETAIL_TERMS`.

**Why**: `PROJECT_CONTEXT.md` is read early and must not lag behind `CONTEXT_LOCK.md` or the active hardware docs. The root summary now points future work toward the selected low-power build instead of reopening already-settled choices.

---

### Phase 1 power and ground rules tightened

**Files affected**: `PROJECT_CONTEXT.md`, `CONTEXT_LOCK.md`, `TASKS.md`, `wiki/architecture/current-build-and-materials.md`, `wiki/architecture/hardware-design.md`, `wiki/architecture/wiring-and-pin-plan.md`, `wiki/architecture/phase-1-bringup-checklist.md`, `wiki/architecture/phase-1-measurement-worksheet.md`, `wiki/architecture/system-design.md`, `logs/audit-log.md`, `logs/code-changes.md`

**What changed**:
- Standardized the required motor-control ground reference as Arduino GND, driver GND, and motor battery negative.
- Clarified that Pi ground normally reaches that reference through the Pi-to-Arduino USB cable.
- Made direct Pi-to-driver ground an optional exception that must be recorded if used.
- Added a hard safety rule that motor battery positive must never connect to Pi 5V or Arduino 5V.
- Added motor-source guidance for 4 alkaline AA cells versus 4 NiMH AA cells and required under-load voltage measurement.
- Updated the bring-up checklist and measurement worksheet to record battery chemistry, Pi ground path, and direct ground jumper changes.
- Marked the power/ground cleanup as complete in `TASKS.md`.
- Verified focused power wording with `NO_AMBIGUOUS_POWER_GROUND_WORDING`.
- Re-ran standard checks: `MASTER_INDEX_LINKS_OK`, `ALL_WIKI_FILES_ROUTED`, `NO_SECRET_PATTERN_HITS`, `NO_LEGACY_CREDENTIAL_DETAIL_TERMS`, and `NO_STALE_ROOT_HARDWARE_WORDING`.

**Why**: The earlier docs were directionally correct but too easy to misread during bench wiring. This makes the safe Phase 1 wiring path explicit before motor power is connected.

---

### Implementation boundary audit recorded

**Files affected**: `TASKS.md`, `CONTEXT_INDEX.md`, `Onara_Design/README.md`, `output/README.md`, `logs/audit-log.md`, `logs/code-changes.md`

**What changed**:
- Audited root directories and implementation-looking file types.
- Confirmed `project-code/` contains only `README.md` and no production robot code.
- Confirmed implementation-looking files outside `project-code/` are legacy `Onara_Design/*.jsx` prototypes or Obsidian configuration files.
- Added `Onara_Design/README.md` to classify the JSX files as deprecated legacy prototypes.
- Added `output/README.md` to reserve `output/` for generated reports, exports, and temporary review artifacts only.
- Updated `CONTEXT_INDEX.md` to include `output/` and clarify that `Onara_Design/*.jsx` is not active robot implementation.
- Marked the implementation-boundary audit as complete in `TASKS.md`.
- Verified `project-code/` with `PROJECT_CODE_PLACEHOLDER_ONLY`.
- Verified no active implementation files outside `project-code/` with `NO_ACTIVE_CODE_OUTSIDE_PROJECT_CODE`.
- Verified guard files with `BOUNDARY_GUARD_READMES_PRESENT`.
- Re-ran standard checks: `MASTER_INDEX_LINKS_OK`, `ALL_WIKI_FILES_ROUTED`, `NO_SECRET_PATTERN_HITS`, `NO_LEGACY_CREDENTIAL_DETAIL_TERMS`, and `NO_AMBIGUOUS_POWER_GROUND_WORDING`.

**Why**: The vault had active implementation paths locked in `_code-map.md`, but legacy JSX files could still appear in file searches. Local guard READMEs make the boundary obvious from the filesystem itself.

---

### MPU6050 verification gate added

**Files affected**: `TASKS.md`, `CONTEXT_LOCK.md`, `wiki/architecture/current-build-and-materials.md`, `wiki/architecture/hardware-design.md`, `wiki/architecture/sensor-calibration.md`, `wiki/architecture/wiring-and-pin-plan.md`, `wiki/architecture/phase-1-bringup-checklist.md`, `wiki/architecture/phase-1-measurement-worksheet.md`, `wiki/testing/test-strategy.md`, `logs/audit-log.md`, `logs/code-changes.md`

**What changed**:
- Added an explicit MPU6050 verification gate before direct Pi I2C wiring.
- Required physical checks for `MPU6050` or `GY-521` label and `VCC`, `GND`, `SDA`, `SCL` pin identification.
- Required direct Pi I2C only when the module works from 3.3V and does not pull `SDA`/`SCL` to 5V.
- Made logic-level shifter or Arduino Uno fallback mandatory when voltage safety is unknown.
- Added `0x68` or `0x69` I2C detection, connection-path recording, and safety-reason recording to the worksheet and bring-up path.
- Added test-strategy checks for IMU identity and voltage safety.
- Replaced old MPU6050 wiring shorthand with explicit direct-Pi-I2C safety-gate language.
- Marked the MPU6050 verification-gate cleanup as complete in `TASKS.md`.
- Verified the gate with `MPU6050_VERIFICATION_GATE_PRESENT`.
- Verified old shorthand is gone with `NO_MPU6050_SHORTHAND_SAFETY_WORDING`.
- Re-ran standard checks: `MASTER_INDEX_LINKS_OK`, `ALL_WIKI_FILES_ROUTED`, `NO_SECRET_PATTERN_HITS`, `NO_LEGACY_CREDENTIAL_DETAIL_TERMS`, `PROJECT_CODE_PLACEHOLDER_ONLY`, and `NO_AMBIGUOUS_POWER_GROUND_WORDING`.

**Why**: The provided MPU6050 can be used, but Pi GPIO cannot tolerate accidental 5V I2C. The docs now require proof before direct Pi wiring and keep the Arduino fallback available.

---

### Encoder/controller verification gate added

**Files affected**: `TASKS.md`, `CONTEXT_LOCK.md`, `PROJECT_CONTEXT.md`, `wiki/architecture/hardware-design.md`, `wiki/architecture/sensor-calibration.md`, `wiki/architecture/wiring-and-pin-plan.md`, `wiki/architecture/phase-1-bringup-checklist.md`, `wiki/architecture/phase-1-measurement-worksheet.md`, `wiki/features/control-system.md`, `wiki/testing/test-strategy.md`, `logs/audit-log.md`, `logs/code-changes.md`

**What changed**:
- Locked Phase 1 encoder A/B signals to Arduino Uno, not Pi GPIO.
- Recorded that ESP32-S3 or another 3.3V controller is not a drop-in replacement for Phase 1 unless `TASKS.md` changes the controller and encoder output voltage or level shifting is verified.
- Added an encoder verification gate requiring encoder `VCC`, `GND`, `A`, `B`, supply voltage, and output voltage before wiring signal lines.
- Added worksheet fields for encoder supply voltage, output voltage, controller path, and final encoder wiring.
- Added bring-up and testing checks for encoder identity, voltage safety, and controller path.
- Marked the encoder/controller verification-gate cleanup as complete in `TASKS.md`.
- Sanitized one old active log sentence that described historical sensitive configuration material too specifically.

**Verification**:
- Result: `ENCODER_CONTROLLER_GATE_PRESENT`.
- Result: `NO_BAD_ENCODER_CONTROLLER_WORDING`.
- Result: `MASTER_INDEX_LINKS_OK`.
- Result: `ALL_WIKI_FILES_ROUTED`.
- Result: `NO_SECRET_PATTERN_HITS`.
- Result: `NO_LEGACY_CREDENTIAL_DETAIL_TERMS`.
- Result: `PROJECT_CODE_PLACEHOLDER_ONLY`.
- Result: `NO_AMBIGUOUS_POWER_GROUND_WORDING`.
- Result: `MPU6050_VERIFICATION_GATE_PRESENT`.
- Result: `NO_MPU6050_SHORTHAND_SAFETY_WORDING`.
- Result: `NO_STALE_ROOT_HARDWARE_WORDING`.

**Why**: The selected motor encoders may output 5V signals. Arduino Uno can handle that in Phase 1, but Pi GPIO and future 3.3V controllers cannot be assumed safe without verification.

---

### Phase 1 purchase list triage added

**Files affected**: `TASKS.md`, `wiki/_decision-log.md`, `wiki/architecture/current-build-and-materials.md`, `wiki/architecture/hardware-design.md`, `wiki/architecture/phase-1-bringup-checklist.md`, `logs/audit-log.md`, `logs/code-changes.md`

**What changed**:
- Split Phase 1 materials into already-owned, buy/prepare-now, conditional-later, and do-not-buy categories.
- Added explicit purchase rules that the first cart excludes owned parts: Pi 5, AI HAT+, Arduino Uno, USB camera, provided MPU6050, starter-kit wiring/sensors, and existing wheels.
- Removed mobile Pi UPS from the first-cart path and made it conditional on needing untethered testing after bench bring-up.
- Made N20 replacement wheels conditional on fit failure with the existing wheels.
- Made I2C logic-level shifter conditional on MPU6050 direct Pi I2C being unsafe and Arduino fallback not being chosen.
- Added ESP32-S3 replacement controller to the Phase 1 do-not-buy path.
- Added a purchase-triage decision entry to `wiki/_decision-log.md`.
- Added a conditional logic-level-shifter backlog item in `TASKS.md`.

**Verification**:
- Result: `PURCHASE_TRIAGE_PRESENT`.
- Result: `FIRST_CART_CONDITIONALS_EXCLUDED`.
- Result: `CONDITIONAL_BUYS_WAIT_LIST_COMPLETE`.
- Result: `NO_BAD_PURCHASE_TRIAGE_WORDING`.
- Result: `MASTER_INDEX_LINKS_OK`.
- Result: `ALL_WIKI_FILES_ROUTED`.
- Result: `NO_SECRET_PATTERN_HITS`.
- Result: `NO_LEGACY_CREDENTIAL_DETAIL_TERMS`.
- Result: `PROJECT_CODE_PLACEHOLDER_ONLY`.
- Result: `NO_AMBIGUOUS_POWER_GROUND_WORDING`.
- Result: `ENCODER_CONTROLLER_GATE_PRESENT`.
- Result: `MPU6050_VERIFICATION_GATE_PRESENT`.

**Why**: The hardware plan should minimize purchases and prevent ordering parts that are only needed after fit or voltage checks fail.

---

### Product-page acceptance criteria added

**Files affected**: `TASKS.md`, `wiki/architecture/current-build-and-materials.md`, `wiki/architecture/hardware-design.md`, `wiki/architecture/phase-1-bringup-checklist.md`, `wiki/architecture/phase-1-measurement-worksheet.md`, `logs/audit-log.md`, `logs/code-changes.md`

**What changed**:
- Added a product-page acceptance checklist for first-cart hardware purchases.
- Added reject rules for wrong motor voltage/RPM, no encoder, wrong shaft, L298N drivers, unclear motor-driver pin labels, weak Pi power supplies, rectangular 9V motor source, and unsafe battery packs.
- Added source links for Raspberry Pi 27W USB-C PSU, TI DRV8833, Toshiba TB6612FNG, and a DigiKey TB6612FNG listing.
- Added product-page verification fields to the Phase 1 measurement worksheet.
- Updated the bring-up checklist to require comparing each listing against the acceptance checklist before checkout.
- Added a `TASKS.md` backlog item to verify first-cart product pages before checkout.

**Verification**:
- Result: `PRODUCT_ACCEPTANCE_CHECKLIST_PRESENT`.
- Result: `PRODUCT_ACCEPTANCE_ROWS_COMPLETE`.
- Result: `NO_BAD_PRODUCT_ACCEPTANCE_WORDING`.
- Result: `MASTER_INDEX_LINKS_OK`.
- Result: `ALL_WIKI_FILES_ROUTED`.
- Result: `NO_SECRET_PATTERN_HITS`.
- Result: `NO_LEGACY_CREDENTIAL_DETAIL_TERMS`.
- Result: `PROJECT_CODE_PLACEHOLDER_ONLY`.
- Result: `FIRST_CART_CONDITIONALS_EXCLUDED`.
- Result: `ENCODER_CONTROLLER_GATE_PRESENT`.
- Result: `MPU6050_VERIFICATION_GATE_PRESENT`.

**Why**: Amazon search results can show close-looking parts that fail the actual robot requirements. The vault now requires product-page evidence before buying.

---

### Front support mechanical specification added

**Files affected**: `TASKS.md`, `wiki/_master-index.md`, `wiki/_code-map.md`, `wiki/architecture/_index.md`, `wiki/architecture/front-support-and-chassis-plan.md`, `wiki/architecture/current-build-and-materials.md`, `wiki/architecture/hardware-design.md`, `wiki/architecture/phase-1-bringup-checklist.md`, `wiki/architecture/phase-1-measurement-worksheet.md`, `wiki/features/control-system.md`, `wiki/testing/test-strategy.md`, `logs/audit-log.md`, `logs/code-changes.md`

**What changed**:
- Added a dedicated front support and chassis mechanical design spec.
- Defined the three-contact-point layout: two powered rear wheels plus passive front center support.
- Added CAD parameters, required measurements, fit rules, height-tuning guidance, failure modes, fallback rules, and mechanical tests.
- Linked the new spec from the master index, architecture index, materials doc, hardware design, bring-up checklist, worksheet, control doc, testing doc, and code map.
- Added a `TASKS.md` backlog item to record front support type, CAD/version, contact height, and low-PWM turn test result.
- Replaced older shorthand that implied front support height simply equals wheel radius with tuned-height wording.

**Verification**:
- Result: `FRONT_SUPPORT_SPEC_PRESENT`.
- Result: `NO_OVERSIMPLIFIED_FRONT_SUPPORT_HEIGHT_WORDING`.
- Result: `NO_BAD_FRONT_SUPPORT_DRIVETRAIN_WORDING`.
- Result: `MASTER_INDEX_LINKS_OK`.
- Result: `ALL_WIKI_FILES_ROUTED`.
- Result: `NO_SECRET_PATTERN_HITS`.
- Result: `NO_LEGACY_CREDENTIAL_DETAIL_TERMS`.
- Result: `PROJECT_CODE_PLACEHOLDER_ONLY`.
- Result: `PRODUCT_ACCEPTANCE_CHECKLIST_PRESENT`.
- Result: `PURCHASE_TRIAGE_PRESENT`.
- Result: `NO_AMBIGUOUS_POWER_GROUND_WORDING`.
- Result: `ENCODER_CONTROLLER_GATE_PRESENT`.
- Result: `MPU6050_VERIFICATION_GATE_PRESENT`.
- Result: `NO_MPU6050_SHORTHAND_SAFETY_WORDING`.
- Result: `NO_STALE_ROOT_HARDWARE_WORDING`.

**Why**: The front support affects traction, turning, camera stability, and encoder/PID quality. It needed explicit build criteria before the CAD/print task can be considered ready.

---

### Serial protocol and motor safety specification added

**Files affected**: `TASKS.md`, `CONTEXT_LOCK.md`, `wiki/_master-index.md`, `wiki/_code-map.md`, `wiki/architecture/_index.md`, `wiki/architecture/serial-protocol-and-safety.md`, `wiki/architecture/wiring-and-pin-plan.md`, `wiki/architecture/modules.md`, `wiki/architecture/phase-1-bringup-checklist.md`, `wiki/architecture/phase-1-measurement-worksheet.md`, `wiki/features/control-system.md`, `wiki/operations/failure-handling.md`, `wiki/testing/test-strategy.md`, `logs/audit-log.md`, `logs/code-changes.md`

**What changed**:
- Added a dedicated Pi-to-Arduino serial protocol and motor safety spec.
- Defined first-pass newline ASCII command and response messages.
- Added explicit command units, safe initial limits, sequence IDs, watchdog stop, duration expiry, and fault codes.
- Added a serial safety state machine and bring-up sequence.
- Linked the spec from wiring, modules, control, failure handling, testing, bring-up, worksheet, indexes, and code map.
- Added a `TASKS.md` backlog item to verify `PING`/`PONG`, `STOP`, watchdog stop, command clamp, and fault visibility before PID tuning.

**Verification**:
- Result: `SERIAL_PROTOCOL_SPEC_PRESENT`.
- Result: `SERIAL_COMMANDS_AND_FAULTS_COMPLETE`.
- Result: `NO_STALE_SERIAL_PROTOCOL_SHAPE`.
- Result: `MASTER_INDEX_LINKS_OK`.
- Result: `ALL_WIKI_FILES_ROUTED`.
- Result: `NO_SECRET_PATTERN_HITS`.
- Result: `NO_LEGACY_CREDENTIAL_DETAIL_TERMS`.
- Result: `PROJECT_CODE_PLACEHOLDER_ONLY`.
- Result: `FRONT_SUPPORT_SPEC_PRESENT`.
- Result: `PRODUCT_ACCEPTANCE_CHECKLIST_PRESENT`.
- Result: `NO_AMBIGUOUS_POWER_GROUND_WORDING`.

**Why**: Future motor firmware needs a clear safety contract before any code is written. Stale or malformed serial commands must not leave motors running.

---

### Phase 1 alkaline motor battery selected

**Files affected**: `TASKS.md`, `wiki/architecture/current-build-and-materials.md`, `wiki/architecture/hardware-design.md`, `wiki/architecture/phase-1-bringup-checklist.md`, `wiki/architecture/phase-1-measurement-worksheet.md`, `wiki/architecture/wiring-and-pin-plan.md`, `logs/audit-log.md`, `logs/code-changes.md`

**What changed**:
- Set the Phase 1 motor source to 4 fresh alkaline AA cells in a 4xAA holder.
- Changed NiMH rechargeable cells and charger from first-cart required item to optional later upgrade.
- Updated product acceptance and worksheet fields to record alkaline cells.
- Added a warning not to use an 8xAA holder unless it can use exactly 4 cells as one 4-cell series bank.
- Kept the motor rail separate from Pi power.

**Verification**:
- Pending verification.

**Why**: The user chose alkaline cells for the first motor tests. The docs now match that decision while preserving safe split power and under-load voltage measurement.
