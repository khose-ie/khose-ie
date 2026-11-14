# Embedded MCU Style Anti-Patterns

Do not introduce these patterns unless the user explicitly requests them.

## Formatting Anti-Patterns
- Mixed indentation widths in the same file.
- Inconsistent brace styles in the same file.
- Inconsistent pointer style in the same file.

## API and Naming Anti-Patterns
- New public APIs that bypass established module prefixes.
- Generic names that hide hardware/protocol meaning.
- New parallel APIs when existing API extension is sufficient.

## Control-Flow Anti-Patterns
- Deep nested branches where guard returns are clearer.
- Silent fallback paths that hide failures.
- Early returns that skip required cleanup.

## Error-Handling Anti-Patterns
- Returning success after a failed low-level call.
- Dropping error codes from dependent layers.
- Replacing explicit errors with vague status values.

## MCU-Specific Anti-Patterns
- Heap allocation in timing-critical paths without project precedent.
- Implicit unit conversion without naming/comment clarity.
- Hidden shared-state mutations across ISR/task contexts.

## Change Hygiene Anti-Patterns
- Refactoring unrelated files in functional bug-fix patches.
- Introducing new helper frameworks when local helpers exist.
- Cross-layer include dependencies without task-required justification.
