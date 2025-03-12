# Minishell Project Structure

```
minishell/
├── files/                  # Source code files
│   ├── buildins/           # Built-in command implementations
│   │   ├── cd.c            # cd command implementation
│   │   ├── echo.c          # echo command implementation
│   │   ├── env.c           # env command implementation
│   │   ├── exit.c          # exit command implementation
│   │   ├── export.c        # export command implementation
│   │   ├── pwd.c           # pwd command implementation
│   │   └── unset.c         # unset command implementation
│   ├── execute/            # Command execution logic
│   │   ├── execute.c       # Main execution functions
│   │   ├── heredoc.c       # Heredoc implementation
│   │   ├── path.c          # Path resolution functions
│   │   └── pipes.c         # Pipe handling functions
│   ├── extra/              # Helper functions
│   │   ├── env_utils.c     # Environment variable utilities
│   │   ├── error.c         # Error handling functions
│   │   ├── free.c          # Memory management functions
│   │   └── utils.c         # Miscellaneous utility functions
│   ├── parsing/            # Input parsing logic
│   │   ├── lexer.c         # Lexical analysis
│   │   ├── parser.c        # Command parsing
│   │   ├── quotes.c        # Quote handling
│   │   ├── redirection.c   # Redirection parsing
│   │   ├── tokenizer.c     # Input tokenization
│   │   └── variables.c     # Variable expansion
│   ├── main.c              # Main program entry point
│   ├── main_helper.c       # Helper functions for main
│   ├── signals.c           # Signal handling
│   └── signals2.c          # Additional signal handling
├── libft/                  # Custom C library
│   ├── ft_*.c              # Various utility functions
│   └── libft.h             # Library header file
├── .gitignore              # Git ignore file
├── LICENSE                 # MIT License file
├── makefile                # Build configuration
├── minishell.h             # Main header file
├── project_structure.md    # This file
└── README.md               # Project documentation
```

## Component Overview

### Main Components

- **main.c**: Program entry point, command loop, and high-level control flow
- **minishell.h**: Main header file with data structures and function declarations

### Built-in Commands

Implementation of shell built-in commands like `cd`, `echo`, `pwd`, etc.

### Execution

Handles the execution of commands, including path resolution, pipes, and redirections.

### Parsing

Processes the input string into tokens and commands that can be executed.

### Signal Handling

Manages signals like SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\).

### Libft

A custom C library with implementations of various standard functions and utilities. 