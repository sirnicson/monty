# 0x19. C - Stacks, Queues - LIFO, FIFO - Using the Monty Language
In this project,I created a simple interpreter for Monty ByteCodes. The interpreter reads a bytecode file and executes the bytecode commands.

Monty is a simple interpreter for the Monty bytecode language. It supports operations for a stack data structure and implements functionality for pushing, popping, and printing values. The interpreter follows the stack and queue principles for handling data.


## Project Structure

```plaintext
monty/
├── monty.c
├── stack.c
├── instructions.c
├── monty.h
└── README.md
```

## Features

- Supports LIFO (Last In, First Out) functionality with stack operations.
- Implements basic opcodes:
  - `push`: Pushes an integer onto the stack.
  - `pall`: Prints all the values in the stack.
  - `pint`: Prints the value at the top of the stack.
  - `pop`: Removes the value at the top of the stack.
  - `swap`: Swaps the top two values on the stack.
  - `add`: Adds the top two values and pushes the result onto the stack.
  - `nop`: Does nothing.

## Usage

1. Compile the project using:
   ```bash
   gcc -Wall -Werror -Wextra -pedantic -std=c89 *.c -o monty

