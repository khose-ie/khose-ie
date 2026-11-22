# project-avoid-mod-rs-dir

> Avoid to use mod.rs for multi-file modules

## Why It Matters

Rust offers two styles for multi-file modules. The `mod.rs` style is considered outdated and can be confusing. The adjacent file style is preferred for clarity and consistency. Choose one style consistently.

## Two Styles

### Style 1: mod.rs (Recommended for larger modules)

```
src/
├── user/
│   ├── mod.rs          # Module root
│   ├── model.rs
│   └── repository.rs
└── lib.rs
```

```rust
// src/lib.rs
mod user;  // Looks for user/mod.rs or user.rs

// src/user/mod.rs
mod model;
mod repository;
pub use model::User;
```

### Style 2: Adjacent file (Recommended for smaller modules)

```
src/
├── user.rs             # Module root
├── user/
│   ├── model.rs
│   └── repository.rs
└── lib.rs
```

```rust
// src/lib.rs
mod user;  // Looks for user.rs, then user/ for submodules

// src/user.rs
mod model;
mod repository;
pub use model::User;
```

## When to Use Each

Always use Style 2 to crate a module file in the same level of the directory as the module. This keeps the module structure flat and easier to navigate, and avoid so many nested `mod.rs` files.

## Consistency Rule

Pick one style for your project and stick with it:

```rust
// Cargo.toml or clippy.toml
[lints.clippy]
self_named_module_files = "warn"  # Enforces adjacent style
```

## See Also

- [project-flat-small](./project-flat-small.md) - Keep small projects flat
- [project-mod-by-feature](./project-mod-by-feature.md) - Feature organization
- [project-pub-use-reexport](./project-pub-use-reexport.md) - Re-export patterns
