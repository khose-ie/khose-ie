---
name: code-with-rust
description: >
  Implements software features, modules, and refactors in idiomatic, production-ready Rust.
  Use when writing or modifying Rust code, resolving ownership or borrow-checker errors, designing APIs with traits and generics, handling errors with Result/thiserror/anyhow, writing async Rust with Tokio, improving performance, or running cargo, clippy, fmt, and test workflows.
  Also use when the user mentions Rust, Cargo, ownership, borrow checker, lifetimes, async Rust, clippy, or idiomatic Rust.
license: MIT
metadata: 
  version: 1.0.0
  author: Khose-ie<khose-ie@outlook.com>
---

# Software Implementation in Rust

The skill provides a comprehensive guide to write idiomatic, high-quality and production-ready Rust code.
It covers topics such as ownership and borrowing, lifetimes, error handling, async programming, performance optimization, and best practices for using Cargo, Clippy, and Rustfmt.

Rust could be divided into two parts: general Rust (with std) and embedded-specific Rust (no-std).
Always use no-std for embedded mcu development and use std for embedded Linux development or general-purpose applications.
Some rules are common, some rules are only for std, some rules are only for no-std. Rules only for std are marked as `#only-for-std`, and rules only for no-std are marked as `#only-for-no-std`, rules for common without any marks.

The skill mainly includes the following parts:

- Environment Setup, includes the check and installation guide of compiler toolchains, package management toolkit, static analysis tools and unit testing tools. Please refer to `env-setup.md`.
- Configuration, includes Git repository initialization, attribute configuration, and version control best practices. Please refer to `configuration.md`.
- Project Structure, includes file and directory organization methods. Please refer to `project-structure.md`.
- Code Rules, includes the coding rules and best practices of idiomatic Rust, error handling, async programming, and performance optimization. Please refer to `code-rules.md`.
- Testing, includes unit tests, integration tests, and best practices for testing Rust code. Please refer to `test.md`.
