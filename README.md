# Minishell

<p align="center">
  <img src="https://raw.githubusercontent.com/FeridBiberoglu/minishell-assets/main/minishell_logo.png" alt="Minishell Logo" width="200">
</p>

A simple shell implementation inspired by bash, developed as part of the 42 curriculum.

## 📋 Overview

Minishell is a simplified shell that implements core functionalities of bash. It provides a command-line interface where users can execute commands, use pipes, redirections, and environment variables.

## ✨ Features

- **Command execution**: Run commands with arguments
- **Built-in commands**: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`
- **Signal handling**: Handle signals like Ctrl+C (SIGINT), Ctrl+D (EOF), and Ctrl+\ (SIGQUIT)
- **Redirections**: Support for `<`, `>`, `<<` (heredoc), and `>>` (append)
- **Pipes**: Connect the output of one command to the input of another using `|`
- **Environment variables**: Access and modify environment variables, including `$?` for exit status
- **Quote handling**: Support for single quotes (`'`) and double quotes (`"`)

## 🛠️ Technical Implementation

- **Lexer/Parser**: Tokenizes and parses the command line input
- **Command execution**: Executes commands using `execve` and handles pipes and redirections
- **Signal handling**: Custom signal handlers for interactive shell experience
- **Memory management**: Proper allocation and deallocation of resources

## 📁 Project Structure

```
minishell/
├── files/                  # Source code files
│   ├── buildins/           # Built-in command implementations
│   ├── execute/            # Command execution logic
│   ├── extra/              # Helper functions
│   ├── parsing/            # Input parsing logic
│   ├── main.c              # Main program entry point
│   ├── main_helper.c       # Helper functions for main
│   ├── signals.c           # Signal handling
│   └── signals2.c          # Additional signal handling
├── libft/                  # Custom C library
├── makefile                # Build configuration
└── minishell.h             # Main header file
```

For a more detailed breakdown of the project structure, see [project_structure.md](project_structure.md).

## 🚀 Getting Started

### Prerequisites

- GCC compiler
- Make
- Readline library

On Ubuntu/Debian:
```bash
sudo apt-get install libreadline-dev
```

On macOS (using Homebrew):
```bash
brew install readline
```

### Compilation

```bash
make
```

### Running the Shell

```bash
./minishell
```

## 📝 Usage Examples

```bash
# Simple command execution
$ ls -la

# Using pipes
$ ls -l | grep ".c"

# Redirections
$ ls > output.txt
$ cat < input.txt
$ ls >> output.txt
$ cat << EOF

# Environment variables
$ echo $PATH
$ export MY_VAR=value
$ echo $MY_VAR

# Built-in commands
$ cd /path/to/directory
$ pwd
$ echo Hello World
$ exit
```

## 🧪 Testing

The shell has been tested with various edge cases and common usage patterns:

- Command execution with different arguments
- Pipe chains with multiple commands
- Various redirection combinations
- Environment variable expansion in different contexts
- Signal handling in different states
- Error handling for invalid commands and syntax

## 👥 Contributors

- [Ferid Biberoglu](https://github.com/FeridBiberoglu)
- [Twan Goossen](https://github.com/tgoossen)

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details. 