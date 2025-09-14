# Ticket-Tango

Ticket-Tango is a console-based application built in C++ that allows a user to manage locations, events, and tickets through a simple menu-driven interface.

## Features

  * **Object-Oriented Design:** The project utilizes three core classes—`Location`, `Event`, and `Ticket`—to model real-world concepts.
  * **Encapsulation & Data Hiding:** Private member variables are used to protect data, with public accessor (getter) and mutator (setter) methods providing controlled access.
  * **The Rule of Three:** Each class correctly implements a destructor, a copy constructor, and a copy assignment operator to handle dynamic memory allocation safely.
  * **Composition:** The `Event` class "has-a" `Location`, and the `Ticket` class "has-an" `Event`, showcasing object composition.
  * **Operator Overloading:** Custom behavior is defined for operators like `<<` (stream insertion), `>>` (stream extraction), `[]` (subscript), and `!` (logical negation) for intuitive object manipulation.
  * **Static Members:** Static variables and methods are used to track the total count of each object type created during runtime.
  * **Input Validation:** The `InputValidation` utility class ensures robust user input, preventing common errors.

## Getting Started

### Prerequisites

  * **A C++ compiler:** The project is configured to build with **MinGW-w64**.
  * **Visual Studio Code:** Recommended for a seamless development and build experience.

### How to Build and Run
1.  Open the project folder in VS Code.
2.  Open the Command Palette (`Ctrl+Shift+P`).
3.  Type and select `Tasks: Run Build Task`.
4.  If multiple build tasks exist, select the one for your compiler (e.g., `C/C++: g++.exe build active file`).
5.  After a successful build, a `main.exe` executable will be created in the `src` folder.

Once built, you can run the program from the terminal by navigating to the `src` folder and executing the file:

```bash
cd src
./main.exe
```
