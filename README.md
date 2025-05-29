> **Owner:** _[Abdellah Nsila](https://github.com/Abdellah-Nsila)_

This repository handles the **execution engine** of the shell. It is responsible for:
- Variable expansion (`$VAR`, `$?`)
- Process forking and `execve` calls
- Built-in command handling
- Redirections (`<`, `>`, `>>`, `<<`)
- Pipes (`|`)
- Subshells and grouping
- Environment management
- File descriptor restoration and isolation
