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
   git clone https://github.com/AnyNamePlease/Sudoku.git
   cd Sudoku
   
2. Compile the project:
   ```sh
   gcc -o sudoku Sudoku.c Generate.c

### Usage

Run the compiled program:
   ```sh
   ./sudoku
   ```
Follow the on-screen instructions to either input your own Sudoku puzzle or generate a new one.

## Code Structure

### Main File (main.c)

Functions:
1. setGreenText(): Sets the text color to green.
2. resetTextColor(): Resets the text color to default.
3. getString(): Reads a string from the console.
4. readArray(): Reads an array of numbers from the console.
5. printMatrix(): Prints the Sudoku grid with highlighted current element.
6. GetChar(): Reads a single character from the keyboard without displaying it.
7. Replace(): Replaces an element in the Sudoku grid.
8. isElementUniqueInBlock(): Checks if a number is unique within a 3x3 block.
9. check(): General check function to ensure the number is valid in the row, column, and block.
10. printMatrixWithGreen(): Prints the Sudoku grid with the current trial process.
11. tryAllValues(): Tries all possible numbers in places with '.' and visualizes the process.
12. main(): Main function to handle user input and interaction.

### Generate File (Generate.c)

Functions:
1. isElementUnique(): Checks if a number can be placed in a specific cell.
2. check2(): General check function to ensure the number is valid in the row, column, and block.
3. solveSudoku(): Recursive function to solve the Sudoku puzzle.
4. generateSudoku(): Generates a valid Sudoku puzzle.
5. removeElements(): Removes elements from the Sudoku grid while ensuring the puzzle has a unique solution.
