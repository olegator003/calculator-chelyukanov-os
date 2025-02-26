# calculator-chelyukanov-os
# Arithmetic Calculator in C

This is a simple C program that reads an arithmetic expression from standard input, parses it, and evaluates the result. The program supports the following operations on integers: addition (+), subtraction (-), multiplication (*), division (/), and parentheses (( and )).

## Features
- Supported operations: +, -, *, /, (, ).
- Handles whitespace in the input expression.
- Recursive parsing of expressions with operator precedence.
- Outputs only the result (no extra messages).

## Requirements
- A C compiler (e.g., `gcc`).
- Standard C library (`libc`).
- Googletest framework for unit testing (included in the repo).

## Repository Structure
- `src/` -- Contains the Pure C calculator source files.
- `tests/unit/` -- Contains C++ unit tests using the Googletest framework.
- `tests/integration/` -- Contains Python integration tests (for DOP-1/2).
- `build/` -- Contains all build artifacts (ignored by git).
- `googletest/` -- Symlink or folder to the Googletest repository.

## Files
- `README.md` -- Description of the repository.
- `Makefile` -- Build system for the repository.
- `.gitignore` -- Specifies files and folders to be ignored by git.
- `.clang-format` -- Formatting rules for C/C++ sources based on the WebKit ruleset.

## Building and Running
- **Build the project:**
   `make akk`
- **Run the calculator in integer mode:**
   `make run-int`
- **Run the calculator in integer mode:**
   `make run-float`
- **Run unit tests:**
   `make run-unit-test`
- **Clean the repository (remove build artifacts):**
   `make clean`

## Sourses
- https://stackoverflow.com/questions/1726302/remove-spaces-from-a-string-in-c
- https://www.geeksforgeeks.org/operator-precedence-and-associativity-in-c/?ref=header_search
- DeepSeek and Gpt
