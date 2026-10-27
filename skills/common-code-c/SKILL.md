---
name: common-code-c
description: "Use when implementing, refactoring, debugging, or reviewing C/C++ code: enforce consistent coding style, module organization, deterministic behavior, and explicit error handling."
---

# embedded-mcu-code-c

## Objective
Provide a reusable, project-agnostic workflow for embedded MCU development so generated code stays consistent in:
- coding style
- project organization style
- reliability and maintainability expectations

This skill is **style-driven**: generated code must follow this kit's author-defined style first.

## When to Use
Use this skill when working on:
- bare-metal or RTOS-based MCU firmware
- hardware abstraction and middleware modules
- driver/service/module integration changes
- bug fixes and feature additions in embedded C/C++

## Required Workflow
1. **Clarify scope and ownership**
   - Confirm which folders/modules are in scope.
   - Identify external/vendor/BSP/generated code and treat them as read-only unless explicitly requested.
2. **Read before edit**
   - Read neighboring headers, source files, and call-sites.
   - Identify API shape, error model, init/deinit flow, and concurrency assumptions needed for compatibility.
3. **Apply author style profile (mandatory)**
   - Use the style constraints in [Style Rules](./assets/style-rules.md).
   - Avoid anti-patterns listed in [Style Anti-Patterns](./assets/style-anti-patterns.md).
4. **Keep module boundary safety**
   - Keep includes and dependencies aligned with existing module boundaries.
   - Avoid introducing new cross-module dependencies unless required by the task.
5. **Implement surgically but completely**
   - Change only relevant files, but include all tightly coupled updates (headers, call-sites, config, tests).
   - Reuse existing helpers before introducing new abstractions.
6. **Guarantee explicit failure semantics**
   - Do not silently swallow errors.
   - Validate inputs and return clear status/error codes.
   - Keep timeout/retry behavior explicit and traceable.
7. **Run style self-check (mandatory)**
   - Verify all touched code against [Style Rules](./assets/style-rules.md).
   - Verify no listed anti-pattern from [Style Anti-Patterns](./assets/style-anti-patterns.md) is introduced.
   - Emit a short pass/fail style gate report for changed files.
8. **Format**
   - Use clang-format to ensure consistent code formatting.
   - If there is no .clang-format file in the root directory of the project, please ask the project maintainer for the correct formatting configuration.
9. **Validate with smallest effective checks**
   - Run the narrowest build/test/lint command covering the change.
   - Expand validation only when targeted checks are insufficient.
10. **Report outcome**
   - List changed files and behavior impact.
   - State compatibility considerations and any intentional deviations.
   - Provide executed validation commands and results.

## Non-Negotiable Rules
- Determinism first for timing-sensitive and ISR-adjacent code paths.
- Avoid dynamic allocation in constrained or timing-critical paths unless project conventions explicitly allow it.
- Prefer fixed-width integer types and explicit units in interfaces.
- Keep APIs minimal, cohesive, and ownership-clear (who initializes, who owns buffers, who releases resources).
- No speculative refactors unrelated to the requested change.

## Style Baseline
Use this style as the default target style:
- short, single-purpose functions
- explicit naming over clever abbreviations
- top-down readability (public API, then internal helpers)
- minimal but clear comments for non-obvious hardware/protocol behavior
- predictable control flow with explicit error/cleanup paths
- and the module skeleton in [C Module Template](./templates/c-module-template.c)

## Project Organization Baseline
- Keep public interface in headers and implementation in source files.
- Keep module-local helpers private/static where possible.
- Co-locate module config, adapter, and tests with the module when repository conventions allow.
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
- [C Header Template](./templates/c-module-template.h)
- [C Source Template](./templates/c-module-template.c)
- [C++ Header Template](./templates/c++-module-template.hpp)
- [C++ Source Template](./templates/c++-module-template.cpp)
