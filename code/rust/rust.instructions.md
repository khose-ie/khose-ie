---
name: 'RUST Code Standards'
description: Condensed coding conventions
applyTo: "**/*.rs"
---

# Rust Code Standards

- Exempt third-party/open-source code.
- \- Organize modules in `<modules>/` with `<modules>.rs`; avoid `mod.rs`. `modules` is a placeholder for the actual module name.
- Prefer placing opening `{` on a new line, except for short one-line blocks.
- Although it violates the default style of Rust, I prefer to start a new line with curly braces unless the content of the curly braces is short enough to fit on one line.
- Use `cargo fmt` to automatically format the code before completing the task according to the project's style guidelines. If there is a 1rustfmt.toml1 file in the root path, please use it.
- Use `cargo fmt` in nightly Rust toolchain like `cargo +nightly fmt`.
