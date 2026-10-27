# Embedded MCU Style Rules

## Priority Rule
1. Follow this document and templates as the primary style source.
2. Keep style stable across the patch; do not drift between mixed styles.
3. Third-party or directly included open-source code is exempt.

## Naming
- Keep naming consistent with this style kit.
- Name shall not start/end with `_`.
- Files and directories must be lowercase and use `-` as separator. Repeat the module name in the directory and filename to avoid name collisions (e.g. `module-a/module-a-submodule1.c`, `module-b.cpp`).
- Module (includes struct, class and enum-class) naming convention: `module_` for functions, `module<PascalCase>_t` for C types, `module::<PascalCase>` for C++ types.
- Function names should be snake_case and start with the module name, and then use verb-first function names for actions (for example: `module_a_initialize()`), and noun-first for getters and setters (for example: `module_a_status()` or `module_a_set_config()`). For class member functions, should not start with the module name.
- Variables, struct/class members, and function parameters use lower_snake_case
- Static global variables use lower_snake_case and start with module name.
- C-style enum members use UPPER_SNAKE_CASE and should be prefixed with the enum name in uppercase (e.g. `COLOR_RED`). `enum class` members use PascalCase.
- For C++ class, if a member variable has the same name with a getter function, the getter function could be end of `_value` (e.g., `timeout_ms` member variable and `timeout_ms_value()` getter function).

## Data Types
- Prefer fixed-width integers (`uint8_t`, `uint16_t`, `uint32_t`, `int32_t`) for hardware-facing logic.
- Keep units explicit in parameter names and comments where needed (`timeout_ms`, `period_us`).

## Macro Definition
- Macro definition names should be in UPPER_SNAKE_CASE and prefixed with the module name if applicable.
- Macro function names should be in snake_case but don't need to be prefixed with the module name.
- Starter Macro in the head file should start with an underscore and the module name, and end with `_H_` or `_HPP_` depending on the file type (e.g., `_MODULE_A_H_`).
- Macro values should be enclosed in parentheses to avoid unexpected precedence issues when used in expressions (e.g., `#define MACRO_VAL (100U)`).
- Macro function parameters and the entire macro expression should be enclosed in parentheses to avoid unexpected precedence issues when used in expressions (e.g., `#define macro_func(x) ((x) + 1)`).
- Macro functions shall not depend on external state or have side effects; they should be self-contained and deterministic.
- Avoid using multi-line macro functions unless necessary; prefer inline functions for type safety and readability.

## API Coding Rules
- Keep APIs explicit about ownership and buffer length.
- Prefer returning status codes over implicit success assumptions.
- Use `const` correctness for read-only inputs.

## Control Flow
- Validate arguments at function entry.
- Use explicit error branches and cleanup labels when cleanup is non-trivial.
- Avoid deeply nested conditionals when a guarded early return is clearer.

## Memory and Concurrency
- Avoid heap allocation in timing-critical paths unless established by project convention.
- Keep concurrency behavior explicit for shared state and ISR/task interactions.
- Minimize critical section scope.

## Comments
- Keep comments in English and tie them to rationale, not restating code.
- Required Doxygen block with `@file`, `@author`, `@date`, `@brief`.
- Must add a Doxygen style comment for files, functions (includes macro functions), classes, structs, enums, macros and global variable.
- Comment only non-obvious logic in the internal of a function or struct field definitions.

## Quick Style Fingerprint (before editing)
Capture and enforce these 8 items in generated code:
1. Indentation: spaces-4.
2. Brace placement style: Allman.
3. Pointer spacing style: `type* ptr`.
4. Include grouping/order: standard library, then third-party, then local headers.
5. Function declaration and definition layout: return type on the same line as function name.
6. Error code naming and return pattern: `<MODULE_RET>_ERR_*`, return `<MODULE_RET>_OK` for success.
7. Static helper placement in source files: before the first public function.
8. Operators must have spaces on both sides.
9. Parenthesize sub-expressions in compound conditional expressions.
10. Place a space between control keywords and the following `(`. Control blocks must use `{}`. In `switch`, `case` labels should be indented; the case contents and the `break` should be included with brace and be indented.
11. `goto` is forbidden (use `do { ... } while(0)` if necessary). Function parameter count should not exceed 5; if exceeded, add a one-line comment explaining why.
12. An `if/if-else`, `while/do-while`, or `for` statement block must be separated from the statement block above and below it by a single blank line.
13. When a block contains consecutive assignment statements followed by a function call, insert one blank line before the function call to separate the state-update section from the action section.
14. When a block contains consecutive assignment statements or consecutive function calls immediately before a return, insert one blank line before the return to separate the state-update/action section from the exit path.
