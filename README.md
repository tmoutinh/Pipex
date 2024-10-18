# Pipex

## Table of Contents
- [Project Overview](#project-overview)
- [Technologies Used](#technologies-used)
- [Lessons Learned](#lessons-learned)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [License](#license)

## Project Overview
The Pipex project is an implementation that mimics the behavior of the Unix shell pipe. It aims to demonstrate proficiency in process creation, inter-process communication, and file handling in C.

## Technologies Used
- **C**: 96.3%
- **Makefile**: 3.7%

## Lessons Learned
Throughout the development of this project, I have learned:
- **Inter-Process Communication**: Techniques for exchanging data between processes using pipes.
- **Process Management**: Creating and managing processes using `fork`, `exec`, and `wait` system calls.
- **File Handling**: Opening, reading, writing, and closing files in C.
- **C Programming**: Advanced usage of C programming for systems programming.

## Getting Started
To get a local copy up and running, follow these simple steps:

1. **Clone the repo**
   ```sh
   git clone https://github.com/tmoutinh/Pipex.git
   ```
2. **Navigate to the project directory and compile**

    2.a. **The main program**
    ```sh
    cd Pipex && make
    ```

    2.b. **The bonus program**
    ```sh
    cd Pipex && make bonus
    ```

## Usage
 - Run the program with the following command:
   ```sh
   ./pipex file1 cmd1 cmd2 file2
   ```

## License
Distributed under the MIT License. See LICENSE for more information.


