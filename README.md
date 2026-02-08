# minishell

A compact Unix-like shell implemented in C as part of the 42 Berlin core curriculum.

This project reproduces essential features of a POSIX shell, including command parsing, process management, and signal handling.

---

## Table of Contents

- [Features](#features)
- [Scope](#scope)
- [Built-in Commands](#built-in-commands)
- [Usage](#usage)
- [Technical Focus](#technical-focus)
- [Project Constraints](#project-constraints)
- [Notes](#notes)

---

## Features

- Command parsing and execution
- Built-in commands
- Process management (`fork`, `execve`, `wait`), pipes, and redirections
- Environment variable management
- Error handling and exit status management
- Leak-free memory handling (validated with Valgrind)

---

## Scope

This shell supports the following behaviors as defined by the project specification:

- Input/output redirections: `<`, `>`, `>>`
- Here-documents using `<<`
- Command pipelines with `|`
- Environment variable expansion (`$VAR`, `$?`)
- Proper handling of single (`'...'`) and double (`"..."`) quotes
  - Single quotes preserve literal text
  - Double quotes allow variable expansion
- Exit status propagation and expansion via `$?`
- Robust handling of common edge cases in parsing and execution
- Signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`)

---

## Built-in Commands

The shell implements the following built-in commands:

- `cd` — Change the current working directory
- `echo` — Print text to standard output (supports `-n` option)
- `env` — Display environment variables
- `export` — Set environment variables
- `unset` — Remove environment variables
- `pwd` — Print the current working directory
- `exit` — Exit the shell

---

## Usage

### Build

```bash
make
```

### Clean

```bash
make clean
make fclean
make re
```

### Run

```bash
./minishell
```

### Command Examples

```bash
ls -l | grep txt > output.txt
export PATH=/usr/bin
echo $HOME
```

---

## Technical Focus

- Process creation and management (`fork`, `execve`, `wait`)
- File descriptor handling and redirections
- Inter-process communication (pipes)
- Signal handling with `signal` / `sigaction`
- Manual memory management
- Modular program structure

---

## Project Constraints

- No external parsing libraries
- Limited standard library usage (per project rules)
- Strict memory management requirements
- Norm-compliant code style

---

## Notes & Compatibility

- This implementation aims to be robust, readable, and maintainable while respecting the project specifications.
- Compatible with Linux and MacOS
