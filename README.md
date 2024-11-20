# Minishell

Welcome to **Minishell**, a custom shell implementation written in C. This project is designed to emulate a simplified Unix shell, providing core functionality and a deeper understanding of shell operations.

---

## Features

- **Command Parsing**: Support for simple commands, arguments, and environment variables.
- **Built-in Commands**: Includes basic shell commands like `cd`, `echo`, `pwd`, `exit`, and more.
- **Environment Management**: Handles environment variables seamlessly.
- **Signal Handling**: Proper signal management for a smooth user experience.
- **Redirections and Pipes**: Implements input/output redirection and piping between commands.
- **Error Handling**: Robust handling of errors with informative messages.

---

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/Magalvo/Minishell.git
   cd Minishell
2. Compile this project:
   ```make```
3. Run the shell:
   ```./minishell```

---

## Usage
- Running a command:
  ```ls -la```
- Using pipes:
  ```ls | grep Minishell```
- Redirection:
  ```
  echo "Hello, World!" > output.txt
  cat < output.txt
  ```
- Environment variables:
  ```
  export MY_VAR=42
  echo $MY_VAR
  ```
- Built-in commands:
  ```
  cd ..
  pwd
  exit
  ```
 ---
 
License
This project is licensed under the MIT License.

Acknowledgements
This project is inspired by the Unix shell and developed as part of a learning exercise to explore system-level programming in C.

Contact
For any questions or feedback, feel free to reach out via the repository or open an issue.

Happy shelling! 🚀
