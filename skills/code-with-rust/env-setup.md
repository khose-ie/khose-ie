# Environment Setup

This section provides a comprehensive guide to setting up the development environment for Rust, including the installation and verification of necessary toolchains, components, and project configurations.



The Rust toolkits.

| Toolkit                      | Name    |
| ---------------------------- | ------- |
| Language Toolkit             | rustup  |
| Language Compiler            | rustc   |
| Toolchain Management Toolkit | rustup  |
| Package Management Toolkit   | cargo   |
| Code Format Toolkit          | rustfmt |
| Code Static Analysis Toolkit | clippy  |



## Language Toolkit

The language toolkit of Rust is `rustup`, it can help to manage the toolchain for multiple platforms, manage language components.



### How to check

Type `rustup --version` in command terminal and expect to output the version.

The example output.

```shell
rustup 1.29.0 (28d1352db 2026-03-05)
info: This is the version for the rustup toolchain manager, not the rustc compiler.
info: the currently active `rustc` version is `rustc 1.96.0 (ac68faa20 2026-05-25)`
```



### How to install

Follow the installation steps in [Rust official website](https://rust-lang.org/tools/install/).

The example command.

```shell
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
```



### How to use

Use `rustup` to update installed toolchains, add compilation targets, or install components. For example:

```shell
rustup update
rustup target add aarch64-unknown-linux-gnu
rustup component add clippy --toolchain stable
```

Replace the target triple and toolchain with the ones required by the project.



## Language Compiler

The language compiler of Rust is `rustc`.



### How to check

Type `rustc --version` in command terminal and expect to output the version.

The example output.

```shell
rustc 1.96.0 (ac68faa20 2026-05-25)
```



### How to install

Usually the rustc will be installed in the same time when you install the `rustup`.

Also, you can use `rustup` and type the command below to manually install it when there it not work fine.

```shell
rustup component add rustc
```



### How to use

Use `rustc` to compile a standalone Rust source file:

```shell
rustc main.rs -o main
```

This creates an executable named `main`. For Cargo projects, use Cargo to build and run the project instead.



## Toolchain Management Toolkit

The `rustup` can also help to manage the toolchain.



### How to check

Type `rustup toolchain list` to list all toolchain and check whether necessary toolchains are available.

The example output.

```shell
stable-aarch64-apple-darwin (active, default)
nightly-aarch64-apple-darwin
nightly-2023-11-13-aarch64-apple-darwin
```



### How to install

Type `rustup toolchain install <toolchain>` to install the target toolchain that will be used.



> [!IMPORTANT]
>
> Usually we use the nightly Rust with `rustfmt` so please install the nightly toolchain of the target architecture of your device.
>
> For example,  the `nightly-aarch64-apple-darwin` toolchain should be installed in a MacBook.



### How to use

Set the default toolchain for your user account, or set a project-specific override from the project directory:

```shell
rustup default stable
rustup override set nightly
```

The directory override applies to the current directory and its descendants. Remove it with `rustup override unset`.



## Package Management Toolkit

The package management toolkit of Rust is `cargo`.



### How to check

Type `cargo --version` in command terminal and expect to output the version.

The example output.

```shell
cargo 1.96.0 (30a34c682 2026-05-25)
```



### How to install

Usually the rustc will be installed in the same time when you install the `rustup`.

Also, you can use `rustup` and type the command below to manually install it when there it not work fine.

```shell
rustup component add cargo
```



### How to use

From a directory containing a `Cargo.toml`, use Cargo to build, run, and test the package:

```shell
cargo build
cargo run
cargo test
```

Cargo resolves dependencies declared in `Cargo.toml` and records the resolved versions in `Cargo.lock`.



## Code Format Toolkit

The code formatting toolkit of Rust is `rustfmt`.



### How to check

Type `rustfmt +nightly --version` in the command terminal to verify that Rustfmt is available from the nightly toolchain.

To check whether the Rust files in the workspace are formatted without changing them.

```shell
cargo +nightly fmt --all -- --check
```

The command exits successfully when the files are formatted. If formatting changes are needed, it reports the differences and exits with a non-zero status.



### How to use

From the directory containing the workspace's `Cargo.toml`, run the command below to format the workspace.

Rustfmt uses the project's `rustfmt.toml` or `.rustfmt.toml` configuration when present. Follow the project configuration rather than overriding its formatting rules.

```shell
cargo +nightly fmt --all
```



### How to install

After installing the nightly toolchain, add the Rustfmt component with commends below.
If the project uses a different toolchain, replace `nightly` with that toolchain's name.

```shell
rustup component add rustfmt --toolchain nightly
```



## Code Static Analysis Toolkit

The static analysis toolkit for Rust is Clippy. It provides lints that help identify common mistakes and improve Rust code.



### How to check

Run the following command to verify that Clippy is available for the active toolchain:

```shell
cargo clippy --version
```



### How to install

Install the Clippy component for the toolchain used by the project. For example:

```shell
rustup component add clippy --toolchain stable
```

Replace `stable` with the project's toolchain name if needed.



### How to use

From a directory containing a `Cargo.toml`, run Clippy on the workspace and all targets:

```shell
cargo clippy --workspace --all-targets
```

To treat warnings as errors, for example in CI, add `-D warnings`:

```shell
cargo clippy --workspace --all-targets -- -D warnings
```

Review Clippy's diagnostics and address them according to the project's coding rules.

