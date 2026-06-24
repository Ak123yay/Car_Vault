# Audit Log

Security and repository hygiene checks for Car Vault.

---

## 2026-06-19 - Secret-Pattern Audit

**Scope**: Repository files excluding `.git`, `.obsidian/plugins`, and `node_modules`.

**Result**:
- Found two scanner-triggering private-key header examples in deprecated Onara/SaaS wiki docs.
- No live secret values were confirmed in the inspected context.

**Action**:
- Replaced the literal private-key header example in `wiki/dev/setup.md` with non-secret local-env-only placeholder guidance.
- Replaced deprecated `wiki/integrations/github.md` with a short legacy stub that contains no secret examples.
- Replaced deprecated `wiki/dev/phase1-github-setup.md` with a short legacy stub that contains no token-format examples.
- Replaced deprecated `wiki/architecture/security.md` with a short legacy stub that contains no web-app secret-handling instructions.
- Redacted a legacy credential inventory summary from `logs/code-changes.md` so old account/key status details are not preserved in the active log.
- Redacted an old token-permission detail from `logs/code-changes.md` so searches do not surface legacy credential setup guidance.

**Verification**:
- Re-ran the secret-pattern scan after cleanup.
- Result: `NO_SECRET_PATTERN_HITS`.
- Ran a redacted key-name audit against `raw/`; no current raw credential file was present.
- Ran a broader legacy credential-detail search.
- Result: `NO_LEGACY_CREDENTIAL_DETAIL_TERMS`.
- Verified `wiki/_master-index.md` references existing files.
- Result: `MASTER_INDEX_LINKS_OK`.

---

## 2026-06-19 - Wiki Routing Integrity Audit

**Scope**: All Markdown files under `wiki/`.

**Result**:
- `WikiFileCount`: 101
- `ActiveRefCount`: 25
- `DeprecatedFileRefCount`: 41
- `DeprecatedFolderCount`: 8
- `UnclassifiedCount`: 0

**Verification**:
- Result: `ALL_WIKI_FILES_ROUTED`.
- Every wiki Markdown file is either referenced by `wiki/_master-index.md`, listed as a deprecated file in `wiki/_legacy-deprecated.md`, or contained in a deprecated legacy folder listed in `wiki/_legacy-deprecated.md`.

---

## 2026-06-19 - Root Context Consistency Audit

**Scope**: Root context files and active hardware documents.

**Result**:
- Found stale generic hardware wording in `PROJECT_CONTEXT.md`.
- `PROJECT_CONTEXT.md` said exact part numbers were pending even though active docs already selected the Phase 1 motor target and motor-driver direction.

**Action**:
- Updated `PROJECT_CONTEXT.md` to match the locked Phase 1 build choices: Raspberry Pi 5, Arduino Uno, USB camera, Raspberry Pi AI HAT+ 26 TOPS / Hailo-8, provided MPU6050, two 6V N20 encoder motors, DRV8833/TB6612FNG, passive front support, and split power rails.
- Clarified that final received labels, wheel fit, encoder details, dimensions, and electrical measurements remain pending until parts arrive.

**Verification**:
- Result: `NO_STALE_ROOT_HARDWARE_WORDING`.
- Result: `MASTER_INDEX_LINKS_OK`.
- Result: `NO_SECRET_PATTERN_HITS`.
- Result: `NO_LEGACY_CREDENTIAL_DETAIL_TERMS`.

---

## 2026-06-19 - Phase 1 Power And Grounding Audit

**Scope**: Root hardware context plus active architecture power and wiring docs.

**Result**:
- Found ambiguous wording that could be read as requiring a direct Pi-to-driver ground jumper.
- Found motor-source guidance that did not distinguish 4 alkaline AA cells from 4 NiMH AA cells.

**Action**:
- Standardized the required ground reference as `Arduino GND <-> driver GND <-> motor battery negative`.
- Clarified that Pi ground normally reaches that reference through the Pi-to-Arduino USB cable.
- Clarified that a direct Pi-to-driver ground jumper is optional only if needed for a stable signal reference and must be recorded.
- Added a hard rule that motor battery positive must never connect to Pi 5V or Arduino 5V.
- Added a motor-source note: 4 fresh alkaline AA cells are near 6V; 4 NiMH AA cells are lower but acceptable for low-speed bench tests if measured under load.

**Verification**:
- Result: `NO_AMBIGUOUS_POWER_GROUND_WORDING`.
- Result: `MASTER_INDEX_LINKS_OK`.
- Result: `ALL_WIKI_FILES_ROUTED`.
- Result: `NO_SECRET_PATTERN_HITS`.
- Result: `NO_LEGACY_CREDENTIAL_DETAIL_TERMS`.
- Result: `NO_STALE_ROOT_HARDWARE_WORDING`.

---

## 2026-06-19 - Implementation Boundary Audit

**Scope**: Root directories, `project-code/`, legacy design files, and implementation-looking file extensions outside `project-code/`.

**Result**:
- `project-code/` contains only `README.md`; no production robot code is present.
- Implementation-looking files outside `project-code/` are legacy `Onara_Design/*.jsx` prototypes and Obsidian configuration files.
- `Onara_Design/` was already deprecated in root context, but the folder itself had no local README.
- `output/` was listed as a core directory but had no guard file.

**Action**:
- Added `Onara_Design/README.md` stating that the JSX files are deprecated legacy Onara/SaaS prototypes and not active robot implementation.
- Added `output/README.md` stating that generated artifacts belong there and production robot code must not.
- Updated `CONTEXT_INDEX.md` to include `output/` and explicitly classify `Onara_Design/*.jsx` as legacy prototypes.

**Verification**:
- Result: `PROJECT_CODE_PLACEHOLDER_ONLY`.
- Result: `NO_ACTIVE_CODE_OUTSIDE_PROJECT_CODE`.
- Result: `BOUNDARY_GUARD_READMES_PRESENT`.
- Result: `MASTER_INDEX_LINKS_OK`.
- Result: `ALL_WIKI_FILES_ROUTED`.
- Result: `NO_SECRET_PATTERN_HITS`.
- Result: `NO_LEGACY_CREDENTIAL_DETAIL_TERMS`.
- Result: `NO_AMBIGUOUS_POWER_GROUND_WORDING`.

---

## 2026-06-19 - MPU6050 Verification Audit

**Scope**: Active IMU, wiring, sensor calibration, bring-up, worksheet, testing, and hardware-boundary docs.

**Result**:
- Existing docs selected the provided MPU6050 but did not fully spell out the physical inspection and voltage-safety gate before direct Pi I2C wiring.
- The fallback path existed but needed to be tied to a concrete decision: direct Pi I2C only when the module works from 3.3V and does not pull I2C to 5V; otherwise logic-level shifter or Arduino Uno fallback.

**Action**:
- Added a `MPU6050 Verification Before Wiring` section to `wiki/architecture/sensor-calibration.md`.
- Added explicit module-label, pin-label, I2C-address, and voltage-safety checks to the wiring plan, bring-up checklist, worksheet, hardware design, and test strategy.
- Added `No 5V I2C signal goes into Pi GPIO` to wiring safety checks.
- Added root lock rules: do not connect MPU6050 `SDA`/`SCL` directly to Pi GPIO unless confirmed safe for 3.3V I2C; use level shifting or Arduino fallback when safety is unknown.

**Verification**:
- Result: `MPU6050_VERIFICATION_GATE_PRESENT`.
- Result: `NO_MPU6050_SHORTHAND_SAFETY_WORDING`.
- Result: `MASTER_INDEX_LINKS_OK`.
- Result: `ALL_WIKI_FILES_ROUTED`.
- Result: `NO_SECRET_PATTERN_HITS`.
- Result: `NO_LEGACY_CREDENTIAL_DETAIL_TERMS`.
- Result: `PROJECT_CODE_PLACEHOLDER_ONLY`.
- Result: `NO_AMBIGUOUS_POWER_GROUND_WORDING`.

---

## 2026-06-19 - Encoder And Controller Boundary Audit

**Scope**: Active controller, encoder wiring, calibration, bring-up, worksheet, hardware, control, and testing docs.

**Result**:
- Existing docs selected Arduino Uno for encoder/PID/motor control but did not fully lock it against accidental ESP32-S3 substitution.
- Encoder voltage guidance existed, but the docs did not require encoder `VCC`, `GND`, `A`, `B`, supply voltage, and output voltage to be recorded before signal wiring.

**Action**:
- Added root lock rules that Phase 1 encoder A/B outputs go to Arduino Uno, not Pi GPIO.
- Added root lock rules that ESP32-S3 or another 3.3V controller cannot replace Arduino Uno unless `TASKS.md` explicitly changes the controller and encoder voltage compatibility or level shifting is verified.
- Added an encoder verification gate to the wiring plan and sensor calibration docs.
- Added encoder supply/output voltage and controller-path recording to the bring-up checklist and measurement worksheet.
- Added control and testing checks for no direct encoder-to-Pi-GPIO wiring during Phase 1.

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

---

## 2026-06-19 - Phase 1 Purchase List Audit

**Scope**: Active materials, hardware, bring-up, decision, task, and log docs.

**Result**:
- The materials doc had the right hardware direction but still mixed first-cart purchases with conditional-later items.
- Mobile Pi power, N20 replacement wheels, extra front support hardware, and I2C level shifting needed clearer wait conditions.
- The first-cart list needed to explicitly exclude owned parts and prevent ESP32-S3 from being purchased as a Phase 1 controller replacement.

**Action**:
- Added purchase rules to `wiki/architecture/current-build-and-materials.md`.
- Split the materials list into already-owned parts, buy/prepare-now items, conditional-later items, and do-not-buy items.
- Added a first-cart table that excludes owned parts and removes mobile Pi UPS from required buys.
- Added conditional-later guidance for N20 wheels, mobile Pi power, I2C logic-level shifter, extra jumper wires, and extra front support hardware.
- Updated hardware design and bring-up checklist to keep conditional purchases separate from the first cart.
- Added a `Phase 1 Purchase Triage` entry to `wiki/_decision-log.md`.
- Added a conditional `TASKS.md` backlog item for buying an I2C logic-level shifter only if the MPU6050 direct-Pi-I2C gate fails and Arduino fallback is not chosen.

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

---

## 2026-06-19 - Product Page Acceptance Criteria Audit

**Scope**: First-cart hardware purchase docs, bring-up checklist, measurement worksheet, hardware design, tasks, and logs.

**Result**:
- The first-cart list had search strings and notes, but it did not yet define enough product-page acceptance criteria to reject bad Amazon lookalikes.
- The most likely wrong purchases were 12V motors, 300RPM/1000RPM motors, motors without encoders, L298N drivers, unclear motor-driver pin labels, and Pi power supplies without a Pi 5-class output.

**Action**:
- Added a `Product Page Acceptance Checklist` to `wiki/architecture/current-build-and-materials.md`.
- Added product-page reject rules for N20 encoder motors, DRV8833, TB6612FNG, N20 brackets, Pi 5 bench power, motor battery source, AA NiMH cells, chassis/base, and fasteners.
- Added reference links for stable specs: Raspberry Pi 27W USB-C PSU, TI DRV8833, Toshiba TB6612FNG, and DigiKey TB6612FNG listing.
- Added a product-page verification section to `wiki/architecture/phase-1-measurement-worksheet.md`.
- Updated the Phase 1 bring-up checklist to require acceptance-checklist comparison before checkout.
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

---

## 2026-06-19 - Front Support Mechanical Specification Audit

**Scope**: Active mechanical, chassis, front support, bring-up, worksheet, testing, control, index, and mapping docs.

**Result**:
- Existing docs selected a CAD/printed passive front support, but the build criteria were too thin.
- The docs did not yet define height tuning, traction requirements, drag failure modes, fallback conditions, or front-support tests.

**Action**:
- Added `wiki/architecture/front-support-and-chassis-plan.md`.
- Defined the selected three-contact-point layout: two powered rear wheels plus one passive front center support.
- Added required measurements before CAD: wheel diameter/radius, chassis thickness, drive axle position, mounting area, ground clearance, and camera mount impact.
- Added CAD parameter names and fit rules for the front support.
- Added height-tuning failure modes and fixes.
- Added fallback rules for ball caster, single passive front wheel, or two passive front wheels only after skid testing fails.
- Added mechanical tests: three-point contact, drive-wheel traction, push, hand-rotation, low-PWM turn, and camera/IMU wobble.
- Linked the new doc from `_master-index.md`, `architecture/_index.md`, materials, hardware design, bring-up checklist, measurement worksheet, test strategy, control system, and `_code-map.md`.
- Added a `TASKS.md` backlog item to record front support type, CAD/version, contact height, and low-PWM turn result.

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

---

## 2026-06-19 - Serial Protocol And Motor Safety Audit

**Scope**: Pi-to-Arduino communication, motor command safety, watchdog behavior, command limits, fault reporting, bring-up checklist, worksheet, testing, control, failure handling, indexes, and code map.

**Result**:
- Existing docs only had a rough serial message shape in the wiring plan.
- There was no dedicated owner for message units, sequence IDs, watchdog behavior, duration expiry, command clamping, or serial fault handling.

**Action**:
- Added `wiki/architecture/serial-protocol-and-safety.md`.
- Defined newline ASCII commands for Phase 1: `PING`, `STOP`, `SET_PWM`, `SET_SPEED_TPS`, and `STATUS`.
- Defined Arduino responses: `PONG`, `ACK`, `TICKS`, `STATE`, and `FAULT`.
- Added initial safe limits, watchdog behavior, fault codes, and a safety state machine.
- Updated wiring, modules, control, failure handling, test strategy, bring-up checklist, worksheet, `CONTEXT_LOCK.md`, `_master-index.md`, architecture index, and `_code-map.md`.
- Added a `TASKS.md` backlog item to verify serial `PING`/`PONG`, `STOP`, watchdog stop, command clamp, and fault visibility before PID tuning.

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

---

## 2026-06-19 - Phase 1 Alkaline Motor Battery Selection

**Scope**: Active materials, hardware, wiring, bring-up, worksheet, task, and log docs.

**Result**:
- The user selected alkaline AA cells for Phase 1 motor testing.
- Existing docs still listed NiMH rechargeable cells as the default battery-cell purchase.
- The 8xAA holder question needed a documented warning so it is not treated as a normal 4-cell source.

**Action**:
- Selected 4 fresh alkaline AA cells in a 4xAA holder as the Phase 1 motor test source.
- Changed NiMH rechargeable cells and charger to an optional later upgrade for repeated testing.
- Updated `TASKS.md` to remove NiMH as a required first-cart task and add 4 fresh alkaline AA cells.
- Added a warning not to use an 8xAA holder unless it has a documented way to use exactly 4 cells as one 4-cell series bank.
- Kept the split-power rule: alkaline motor cells power only the motor driver/motors, never the Pi.

**Verification**:
- Pending verification.
