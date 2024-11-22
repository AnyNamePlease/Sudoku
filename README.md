# Sudoku
# Sudoku Solver and Generator

This project provides a Sudoku solver and generator implemented in C. The solver uses a backtracking algorithm to fill in the Sudoku grid, while the generator creates a valid Sudoku puzzle by filling the grid with random numbers and ensuring that the puzzle has a unique solution.

## Features

- **Sudoku Solver**: Solves a given Sudoku puzzle using a backtracking algorithm.
- **Sudoku Generator**: Generates a valid Sudoku puzzle with a unique solution.
- **Interactive Mode**: Allows the user to input their own Sudoku puzzle or generate a new one.
- **Visualization**: Displays the process of solving the Sudoku puzzle step-by-step in the console.

## Getting Started

### Prerequisites

- A C compiler (e.g., GCC)
- Standard C libraries

### Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/sudoku-solver-generator.git
   cd sudoku-solver-generator
   
2. Compile the project:
   ```sh
   gcc -o sudoku main.c Generate.c

### Usage

Run the compiled program:
   ```sh
   ./sudoku
   ```
Follow the on-screen instructions to either input your own Sudoku puzzle or generate a new one.

## Code Structure

1. Main File (main.c)

Functions:
setGreenText(): Sets the text color to green.
resetTextColor(): Resets the text color to default.
getString(): Reads a string from the console.
readArray(): Reads an array of numbers from the console.
printMatrix(): Prints the Sudoku grid with highlighted current element.
GetChar(): Reads a single character from the keyboard without displaying it.
Replace(): Replaces an element in the Sudoku grid.
isElementUniqueInBlock(): Checks if a number is unique within a 3x3 block.
check(): General check function to ensure the number is valid in the row, column, and block.
printMatrixWithGreen(): Prints the Sudoku grid with the current trial process.
tryAllValues(): Tries all possible numbers in places with '.' and visualizes the process.
main(): Main function to handle user input and interaction.

2. Generate File (Generate.c)

Functions:
isElementUnique(): Checks if a number can be placed in a specific cell.
check2(): General check function to ensure the number is valid in the row, column, and block.
solveSudoku(): Recursive function to solve the Sudoku puzzle.
generateSudoku(): Generates a valid Sudoku puzzle.
removeElements(): Removes elements from the Sudoku grid while ensuring the puzzle has a unique solution.
