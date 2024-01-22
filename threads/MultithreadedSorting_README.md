
# Multithreaded Merge Sort

## Introduction
Multithreaded Merge Sort is a Java application that demonstrates the use of multithreading in sorting algorithms. It divides an unsorted array into two subarrays, sorts each of them in separate threads, and then merges the sorted arrays in a third thread.

## How it Works
The application uses Java's ExecutorService to manage threads efficiently. The number of threads used is equal to the number of available processor cores.

## Requirements
- Java (JDK)

## Running the Program
1. Compile the Java file:
   ```
   javac MultithreadedMergeSort.java
   ```
2. Run the compiled class:
   ```
   java MultithreadedMergeSort
   ```

## Implementation Details
- The program takes an unsorted integer array, divides it into two halves, and sorts each half in a separate thread.
- After both halves are sorted, a third thread merges these sorted halves into a single sorted array.
- The main thread waits for the sorting and merging to complete before printing the sorted array.
