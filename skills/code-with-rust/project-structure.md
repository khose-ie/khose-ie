# Project Structure

This section provides guidelines for managing directories within a Rust project, ensuring a consistent and maintainable project structure.

The following rules should be followed when managing directories within a Rust project to maintain a consistent and organized structure.

- [`project-avoid-mod-rs-dir`](rules/project-avoid-mod-rs-dir.md) - Avoid using mod.rs for multi-file modules
- [`project-bin-dir`](rules/project-bin-dir.md) - Put multiple binaries in src/bin/
- [`project-build-rs-minimal`](rules/project-build-rs-minimal.md) - Keep `build.rs` minimal, deterministic, and idempotent
- [`project-feature-additive`](rules/project-feature-additive.md) - Design Cargo features to be strictly additive
- [`project-flat-small`](rules/project-flat-small.md) - Keep small projects flat
- [`project-lib-main-split`](rules/project-lib-main-split.md) - Keep `main.rs` minimal, logic in `lib.rs`
- [`project-mod-by-feature`](rules/project-mod-by-feature.md) - Organize modules by feature, not type
- [`project-msrv-declare`](rules/project-msrv-declare.md) - Declare `rust-version` (MSRV) in Cargo.toml and test it in CI
- [`project-prelude-module`](rules/project-prelude-module.md) - Create prelude module for common imports
- [`project-pub-crate-internal`](rules/project-pub-crate-internal.md) - Use pub(crate) for internal APIs
- [`project-pub-super-parent`](rules/project-pub-super-parent.md) - Use pub(super) for parent-only visibility
- [`project-pub-use-reexport`](rules/project-pub-use-reexport.md) - Use pub use for clean public API
- [`project-workspace-deps`](rules/project-workspace-deps.md) - Use workspace dependency inheritance for consistent versions across crates
- [`project-workspace-large`](rules/project-workspace-large.md) - Use workspaces for large projects
