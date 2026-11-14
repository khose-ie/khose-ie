# Embedded Rust Anti-Patterns

Do not introduce these patterns unless the user explicitly requests them.

## Formatting Anti-Patterns
- Mixed naming conventions within the same module.
- Inconsistent import ordering or inconsistent use of doc comments.
- Reformatting unrelated sections of a file in the same patch.

## API and Naming Anti-Patterns
- Public APIs that hide hardware or protocol meaning with generic names.
- New parallel APIs when existing trait or module extension is sufficient.
- `unsafe` abstractions that leak raw pointers across module boundaries without clear ownership rules.

## Control-Flow Anti-Patterns
- Deep nesting when guard returns or `match` arms would be clearer.
- Silent fallback paths that hide hardware or protocol failures.
- Callback logic that mutates shared state without documenting the concurrency assumptions.

## Error-Handling Anti-Patterns
- Swallowing `Result` errors with `unwrap()` or `expect()` in production driver paths.
- Dropping error details when converting from HAL return values to higher-level errors.
- Returning success after a failed low-level operation.

## Embedded-Specific Anti-Patterns
- Heap allocation in timing-critical or static peripheral paths without project precedent.
- Implicit unit conversion without explicit parameter names.
- Hidden shared-state mutations across ISR/task contexts.
- Excessive `unsafe` code scattered across unrelated functions.

## Change Hygiene Anti-Patterns
- Refactoring unrelated files in bug-fix patches.
- Introducing new framework layers when a local helper or trait extension is enough.
- Broad cross-module reorganization without task-required justification.
