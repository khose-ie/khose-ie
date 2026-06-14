---
name: 'RUST Code Standards'
description: Condensed coding conventions
applyTo: "**/*.rs"
---

# Rust Code Standards

- Exempt third-party/open-source code.
- Organize modules in `modules/` with `modules.rs`; avoid `mod.rs`.
- Prefer placing opening `{` on a new line, except for short one-line blocks.
- Although it violates the default style of Rust, I prefer to start a new line with curly braces unless the content of the curly braces is short enough to fit on one line.
