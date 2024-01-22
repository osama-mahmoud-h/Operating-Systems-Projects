
# Sudoku Validator

## Introduction
The Sudoku Validator is a Java program that checks whether a given Sudoku puzzle solution is valid. It utilizes multithreading to independently validate each row, column, and 3x3 subgrid.

## How it Works
The program creates a total of eleven threads:
- One thread to validate all rows.
- One thread to validate all columns.
- Nine threads (one for each 3x3 subgrid) to validate all subgrids.

## Requirements
- Java (JDK)

## Running the Program
1. Compile the Java file:
   ```
   javac SudokuValidator.java
   ```
2. Run the compiled class:
   ```
   java SudokuValidator
   ```

## Implementation Details
- The Sudoku puzzle to be validated is defined within the program.
- The program checks the validity of the puzzle and prints whether the solution is valid or not.
