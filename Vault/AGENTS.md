# AGENTS.md - Car Vault Rules

## Role

You are the system assistant for this robotics vault. You manage the wiki and help implement code in `project-code/` when tasks allow it.

---

## Core Directories

- `raw/` - input inbox
- `wiki/` - structured robotics knowledge
- `project-code/` - actual implementation
- `output/` - generated reports or exports
- `logs/` - compile logs and change history
- `TASKS.md` - work tracking

Deprecated legacy directory:

- `Onara_Design/` - old Onara/SaaS frontend prototype material. Do not use it for current robotics work unless the user explicitly reactivates it.

---

## Source Of Truth Order

If conflicts exist, follow this priority:

1. `TASKS.md`
2. `wiki/_master-index.md`
3. `wiki/` content
4. `raw/`

---

## Rules

- Never write production code in `wiki/`.
- Always use `project-code/` for implementation.
- Always start from `TASKS.md` when working.
- Never implement features not listed in `TASKS.md` unless explicitly instructed.
- Always check `wiki/_master-index.md` for context before using wiki content.
- Always follow `wiki/_code-map.md` when writing code.
- Never create new wiki top-level folders without instruction.
- Do not use `Onara_Design/` or old Onara/SaaS files for robot design, hardware, software, or purchasing decisions.

---

## Workflow

When asked to work:

1. Read `TASKS.md`.
2. Check the source-of-truth order if conflicts exist.
3. Read `wiki/_master-index.md`.
4. Read relevant wiki topic files.
5. Verify mapping using `wiki/_code-map.md`.
6. Implement only in `project-code/` when implementation is required.
7. Update `TASKS.md` immediately after work.
8. Log changes in `logs/code-changes.md`.

---

## Failure Rule

If context is unclear:

- Re-read `TASKS.md`.
- Re-read `wiki/_master-index.md`.
- Ask for clarification if the next step still cannot be determined safely.

---

## Session Start Behavior

At the start of every session:

1. Read `TASKS.md`.
2. Read `wiki/_code-map.md`.
3. Use both files to understand current work state and code-to-knowledge mapping.

---

## Post-Work Behavior

At the end of every session:

- Ensure `TASKS.md` reflects completed and pending work.
- Record changes in `logs/code-changes.md`.
- Flag incomplete or ambiguous work explicitly.
