# Rust Style Rules

Rust could be divided into two parts: general Rust (with std) and embedded-specific Rust (no-std).
Always use no-std for embedded mcu development and use std for embedded Linux development or general-purpose applications.
Some rules are common, some rules are only for std, some rules are only for no-std. Rules only for std are marked as `(only for std)`, and rules only for no-std are marked as `(only for no-std)`, rules for common without any marks.

## Priority Rule
1. Follow this document and templates as the primary style source.
2. Keep style stable across the patch; do not mix conventions within the same module.
3. Third-party or generated code is exempt even though the file is modified directly.

## Naming
- Use snake_case for functions, variables, arguments, fields, and module-local constants.
- Use CamelCase for types, traits, enums, and enum variants.
- Use UPPER_SNAKE_CASE for true constants and public compile-time values.
- Keep names descriptive; avoid abbreviations that hide hardware or protocol meaning.
- Keep module-local static state prefixed by the module name when needed, for example `modulea_queue` or `modulea_handle_table`.
- Do not start or end names with `_`.
- Prefer verb-first function names for actions (`moda_init`, `moda_transmit`, `moda_abort`) and noun-first names for getters or status queries (`moda_status`, `moda_handle`).

## Type and API Rules
- Prefer explicit fixed-width integer types for hardware-facing interfaces when needed (`u8`, `u16`, `u32`, `i32`).
- Keep unit names visible in parameter names and comments when critical (`timeout_ms`, `baud_rate`, `period_us`).
- Prefer `Result<T, E>` or project-specific `RetValue<T>` conventions over silent `Option`-based success/failure for driver APIs.
- Keep ownership and buffer lifetimes explicit; use wrapper types such as `NonNull<T>` when the HAL requires raw pointer handles.
- Keep `unsafe` blocks minimal and closely scoped to the exact FFI operation.

## Control Flow
- Validate inputs at function entry.
- Use early returns for invalid parameters or failed preconditions.
- Use explicit `match` arms and `if let` branches instead of silent fallbacks.
- Avoid deep nesting when guard clauses make the flow clearer.
- Keep callback/error cleanup paths explicit and deterministic.

## Memory and Concurrency
- Avoid heap allocation in timing-critical or static contexts unless the project already does so and the pattern is established (only for no-std).
- Keep shared state mutation explicit, especially around ISR or DMA callbacks.
- Keep critical sections short and document the reason when necessary.
- Prefer static arrays and fixed-size queues for embedded peripherals (only for no-std).

## Documentation
- Add Rustdoc comments (`///`) for public types, functions, and critical callback semantics.
- Use doc comments to explain hardware behavior, resource ownership, and unusual invariants.
- Keep comments in English and tied to rationale, not to restate the code.
- For FFI or `unsafe` code, briefly document why the operation is safe within the stated contract.

## Style Fingerprint
Use these conventions as the default target style for embedded Rust code:
1. Indentation: 4 spaces.
2. Brace placement: next-line for blocks, but keep the file consistent with project style.
3. Use rustfmt defaults, with explicit formatting in complex blocks when necessary.
4. Keep imports grouped logically: std/core first, then external crates, then local crate modules.
5. Separate public API from internal helpers.
6. Keep functions single-purpose and small.
7. Put local helper functions before the first public function when they are module-private and used throughout the file.
8. Ensure binary operators have spaces on both sides.
9. Parenthesize sub-expressions in compound conditions when clarity benefits the reader.
10. Use explicit `match`/`if` blocks rather than implicit truthiness or dropped results.
11. Prefer `Result` and `?` for error propagation at the driver boundary, but do not hide essential error context.
12. Do not use `unsafe` for convenience; use it only when required by the HAL/FFI contract.
13. Keep callback handlers short and delegate hardware-specific logic to helpers when appropriate.
14. Preserve a single blank line between logical sections within a function when the code has a state-update section and a follow-up action.

## Rust-Specific Embedded Patterns
- Prefer `NonNull<T>` wrappers around raw peripheral handles when the vendor HAL expects raw pointers.
- For HAL callbacks, remain explicit about which peripheral instance is being handled and whether the callback is safe to ignore.
- When implementing trait methods that bridge to C/FFI, keep the conversion boundary small and avoid leaking raw pointers beyond the module.
- Prefer `static mut` only when the project already uses that pattern for peripheral registration; otherwise, make the ownership model explicit and safer.
- If a module requires global registration, document the lifetime assumptions and usage constraints.
