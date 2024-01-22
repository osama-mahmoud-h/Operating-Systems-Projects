package threads;

import java.util.HashSet;
import java.util.Set;

public class SudokuValidator {

    private static final int GRID_SIZE = 9;
    private static final int NUM_THREADS = 11;
    private static final int[][] sudoku = {
            {5, 3, 4, 6, 7, 8, 9, 1, 2},
            {6, 7, 2, 1, 9, 5, 3, 4, 8},
            {1, 9, 8, 3, 4, 2, 5, 6, 7},
            {8, 5, 9, 7, 6, 1, 4, 2, 3},
            {4, 2, 6, 8, 5, 3, 7, 9, 1},
            {7, 1, 3, 9, 2, 4, 8, 5, 6},
            {9, 6, 1, 5, 3, 7, 2, 8, 4},
            {2, 8, 7, 4, 1, 9, 6, 3, 5},
            {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };
    private static final boolean[] results = new boolean[NUM_THREADS];

    public static void main(String[] args) throws InterruptedException {
        Thread[] threads = new Thread[NUM_THREADS];
        int threadIndex = 0;

        // Create threads for rows and columns
        threads[threadIndex++] = new Thread(new RowChecker());
        threads[threadIndex++] = new Thread(new ColumnChecker());

        // Create threads for 3x3 subgrids
        for (int row = 0; row < GRID_SIZE; row += 3) {
            for (int col = 0; col < GRID_SIZE; col += 3) {
                threads[threadIndex] = new Thread(new SubgridChecker(row, col));
                threadIndex++;
            }
        }

        // Start all threads
        for (Thread thread : threads) {
            thread.start();
        }

        // Wait for all threads to finish
        for (Thread thread : threads) {
            thread.join();
        }

        // Check if Sudoku is valid
        if (isValidSudoku()) {
            System.out.println("Sudoku solution is valid.");
        } else {
            System.out.println("Sudoku solution is invalid.");
        }
    }

    private static boolean isValidSudoku() {
        for (boolean result : results) {
            if (!result) {
                return false;
            }
        }
        return true;
    }

    static class RowChecker implements Runnable {
        @Override
        public void run() {
            for (int row = 0; row < GRID_SIZE; row++) {
                if (!isUnique(sudoku[row])) {
                    return;
                }
            }
            results[0] = true;
        }
    }

    static class ColumnChecker implements Runnable {
        @Override
        public void run() {
            for (int col = 0; col < GRID_SIZE; col++) {
                int[] column = new int[GRID_SIZE];
                for (int row = 0; row < GRID_SIZE; row++) {
                    column[row] = sudoku[row][col];
                }
                if (!isUnique(column)) {
                    return;
                }
            }
            results[1] = true;
        }
    }

    static class SubgridChecker implements Runnable {
        private final int startRow, startCol;

        public SubgridChecker(int startRow, int startCol) {
            this.startRow = startRow;
            this.startCol = startCol;
        }

        @Override
        public void run() {
            int[] subgrid = new int[GRID_SIZE];
            int index = 0;
            for (int row = startRow; row < startRow + 3; row++) {
                for (int col = startCol; col < startCol + 3; col++) {
                    subgrid[index++] = sudoku[row][col];
                }
            }
            if (isUnique(subgrid)) {
                results[startRow + startCol / 3 + 2] = true;
            }
        }
    }

    private static boolean isUnique(int[] array) {
        Set<Integer> foundNumbers = new HashSet<>();
        for (int number : array) {
            if (!foundNumbers.add(number)) {
                return false; // Duplicate found
            }
        }
        return true;
    }
}

