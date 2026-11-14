---
name: sw-code-rust
description: "Use when implementing, refactoring, debugging, or reviewing embedded Rust code: enforce deterministic hardware access, explicit error handling, and safe module boundaries."
---

# embedded-mcu-code-rust

## Objective
Provide a reusable, project-agnostic workflow for embedded MCU development in Rust so generated code stays consistent in:
- coding style
- module organization
- reliability and maintainability expectations

This skill is style-driven: generated code must follow the author-defined embedded Rust conventions first, even when project defaults differ.

## When to Use
Use this skill when working on:
- bare-metal or RTOS-based embedded Rust firmware
- HAL wrappers and peripheral drivers
- DMA/IRQ callback integration
- queue, event, and state-machine modules
- fixes and feature additions in embedded Rust modules

## Required Workflow
1. Clarify scope and ownership
   - Confirm which module or crate folders are in scope.
   - Treat generated, vendor, or HAL code as read-only unless explicitly requested.
2. Read before edit
   - Read neighboring modules, traits, and call sites.
   - Confirm peripheral ownership, static lifetimes, initialization flow, IRQ behavior, and error contract.
3. Apply author style profile (mandatory)
   - Use the style constraints in [Style Rules](./assets/style-rules.md).
   - Avoid anti-patterns listed in [Style Anti-Patterns](./assets/style-anti-patterns.md).
4. Keep module boundary safety
   - Keep ownership, lifetimes, and FFI boundaries explicit.
   - Avoid new cross-module dependencies unless required by the task.
5. Implement surgically but completely
   - Change only relevant files, but include tightly coupled updates such as call sites, trait impls, config, and tests.
   - Reuse established helpers before introducing new abstractions.
6. Guarantee explicit failure semantics
   - Do not silently absorb driver or HAL failures.
   - Validate arguments and return clear results such as `Result`, `RetValue<T>`, or a domain-specific error enum.
   - Keep timeouts, retries, and callback failure paths visible and testable.
7. Run style self-check (mandatory)
   - Verify touched code against [Style Rules](./assets/style-rules.md).
   - Confirm the patch does not introduce any anti-pattern from [Style Anti-Patterns](./assets/style-anti-patterns.md).
   - Provide a short pass/fail style gate for changed files.
8. Format
   - Use `cargo fmt` for Rust formatting.
   - If the project has a custom rustfmt policy, follow that project policy instead of default rustfmt.
9. Validate with the smallest effective checks
   - Run the narrowest build/test/lint command covering the change.
   - Expand validation only when the targeted check is insufficient.
10. Report outcome
    - List changed files and behavior impact.
    - State compatibility or lifetime considerations.
    - Provide executed validation commands and results.

## Non-Negotiable Rules
- Determinism first for timing-sensitive and ISR-adjacent code paths.
- Avoid heap allocation in timing-critical or static contexts unless the project already uses it and the code clearly documents why.
- Prefer explicit units in interfaces (`timeout_ms`, `period_us`, `baud_rate`).
- Keep APIs minimal, cohesive, and ownership-clear: who initializes the peripheral, who owns the buffer, and who releases it.
- Keep `unsafe` blocks narrow and justified; document the FFI invariant if non-obvious. Usually, `unsafe` block could only be used in expressions instead of statements. For example use `unsafe { (*self.value.get()).write(v) };` instead of `unsafe { (*self.value.get()).write(v); }`.
- No speculative refactors unrelated to the requested change.

## Style Baseline
Use this style as the default target style:
- small single-purpose functions
- explicit naming over clever abbreviations
- top-down readability: public API first, then private helpers
- minimal but clear doc comments for hardware behavior and callback semantics
- predictable control flow with explicit error and cleanup paths
- and the module skeleton in [Rust Module Template](./templates/rust-module-template.rs)

## Project Organization Baseline
- Keep public interfaces in the module root or trait definitions, with implementation in the same module when the project permits it.
- Keep module-local helpers private when they are only used within the module.
- Co-locate config, wrappers, and tests with the module when repository conventions allow.
- Do not move files or rename modules unless the task explicitly requires it.

## Output Contract
Each completion should include:
1. What changed (files and key symbols).
2. Why the code matches the required style and module conventions.
3. Error-handling and reliability considerations.
4. Validation performed and results.
5. Style compliance notes:
   - matched local style signature items
   - any unavoidable deviations and why

## Optional Assets
- [Style Rules](./assets/style-rules.md)
- [Style Anti-Patterns](./assets/style-anti-patterns.md)
- [Change Summary Template](./assets/change-summary-template.md)
- [Rust Module Template](./templates/rust-module-template.rs)
