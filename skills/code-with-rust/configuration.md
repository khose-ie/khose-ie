# Configuration

This section provides a guide to configuring and verifying the setup of Rust project repositories, including checking project configuration files and Git repository status.



## Initialize the Repository

The condition to judge whether to initialize a new Rust project or not is based on the presence of the Rust project configuration file (`Cargo.toml`) in the project directory.

If the project directory already contains a Rust project configuration file (e.g., `Cargo.toml`), you can skip the initialization step and proceed with configuring the repository.



If the project directory has been created by the user but does not contain a Rust project configuration file (e.g., `Cargo.toml`), initialize a new Rust project using the command:

```shell
cargo init
```



If the project directory does not exist, create it using the command:

```shell
cargo new <project-directory>
```



## Create Rust Formatter Configuration

To create a Rust formatter configuration, ensure that a `rustfmt.toml` file exists in the project directory. This file contains the formatting rules for the Rust code in the project.
If the `rustfmt.toml` file does not exist in the project directory, make a copy of the file `assets/rustfmt.toml` to the project directory.



## Initialize the Git Environment

The condition to judge whether to initialize the Git environment is based on the presence of the `.git` directory in the project directory.



To initialize the Git environment for the Rust project, follow these steps:

1. Navigate to the project directory.
2. Check if the Git repository is already initialized by looking for the `.git` directory.
3. If the Git repository is not initialized, run the command:

```shell
git init
```



## Create Git Attributes Configuration

To create a Git attributes configuration, ensure that a `.gitattributes` file exists in the project directory. This file contains the Git attributes for the project.
If the `.gitattributes` file does not exist in the project directory, make a copy of the file `assets/.gitattributes` to the project directory.
