# bootcamp
# Password Strength Checker

A C programming project built for the bootcamp assignment. This program validates user-inputted passwords against standard security requirements to ensure they are robust and safe.

## Password Validation Criteria

| Criterion | Requirement |
| :--- | :--- |
| **Minimum Length** | Must be strictly greater than 8 characters |
| **Uppercase Characters** | Must contain at least one uppercase letter (`A-Z`) |
| **Lowercase Characters** | Must contain at least one lowercase letter (`a-z`) |
| **Numeric Digits** | Must contain at least one digit (`0-9`) |
| **Special Symbols** | Must contain at least one special character (e.g., `!`, `@`, `#`, `$`) |

## How to Compile and Run

Follow these steps sequentially to run the program locally:

1. Clone this repository to your local machine.
2. Open your terminal or command prompt inside the project folder.
3. Compile the source file using a C compiler (like GCC):
   ```bash
   gcc password-strength-checker.c -o password-strength-checker
   ```
4. Execute the compiled program:
   * **Linux/macOS:**
     ```bash
     ./password-strength-checker
     ```
   * **Windows:**
     ```cmd
     password-strength-checker.exe
     ```
