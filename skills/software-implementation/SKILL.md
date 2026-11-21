The typical workflow of the skill involves the following steps:

- Check the Rust environment setup.
  This step could be skipped if the environment is already properly set up in this context or it has been verified in this context.
  The development environment should be properly configured with the correct versions of Rust and Cargo, includes both stable and nightly versions of one target.
  Please follow the steps in chapter [Environment Setup](#environment-setup)

- Read the current codebase and understand its structure and functionality if applicable.
  This step could be skipped if the codebase has already been read and understood in this context.

- Organize the repository structure, including files and directories.
  This step could be skipped if the repository structure is already properly organized and no new files or directories need to be added.
  Please follow the guidelines and best practices outlined in the [Repository Structure Management](#repository-structure-management) section.

- Write idiomatic and high-quality Rust code and format it using Rustfmt.
  Please follow the guidelines and best practices outlined in the [Rust Code Best Practices](#rust-code-best-practices) section.

In addition, there are also some steps which need to be uniformly executed according to the schedule of the upper level skills (e.g., software-implementation).

- Build the project using Cargo.
  This step is necessary to ensure that the project can be successfully compiled and built.

- Use Clippy for linting and ensure code correctness.
  This step is necessary to catch potential issues and maintain code quality.

- Run tests to verify functionality and catch regressions.
  This step is necessary to ensure that the implemented features work as expected and to prevent introducing bugs.
