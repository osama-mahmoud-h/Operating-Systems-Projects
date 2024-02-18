
# Simple Thread Synchronization Project

## Introduction

This project demonstrates the basics of thread synchronization in Java using the `synchronized` keyword. It includes a simple `Counter` class that supports thread-safe increment operations. The project creates two threads, each of which increments the shared counter 10,000 times. The main goal is to illustrate how to ensure that concurrent modifications to a shared resource are performed safely, avoiding race conditions.

## Prerequisites

- JDK 11 or higher
- Basic knowledge of Java programming
- Understanding of concurrency and the `synchronized` keyword in Java

## Project Structure

- `Counter.java`: A class that encapsulates a counter with synchronized methods for incrementing and decrementing the counter value.
- `CounterThread.java`: A `Thread` subclass that performs multiple increment operations on a `Counter` object.
- `CriticalSection.java`: Contains the `main` method that sets up the threading demonstration, including creating `Counter` objects and starting `CounterThread` instances.

## How to Run the Project

1. **Compile the Java Files**

   First, navigate to the project directory in your terminal or command prompt. Compile the Java files using the `javac` command:

   ```bash
   javac threads/*.java
   ```

2. **Run the Main Class**

   After compiling, run the `CriticalSection` class:

   ```bash
   java threads.CriticalSection
   ```

   This will start the execution of the two threads on the shared `Counter` instance and print the final count value after both threads have completed their operations.

## Expected Output

Upon successful execution, the program should output:

```
Final count is: 20000
```

This output confirms that the synchronized methods of the `Counter` class have successfully ensured that the concurrent increments by two threads are performed without data corruption or race conditions.

## Conclusion

This simple project showcases the fundamental concept of synchronizing access to shared resources in a multi-threaded environment in Java. The `synchronized` keyword plays a crucial role in ensuring that only one thread can execute a block of code that modifies a shared resource, thus maintaining consistency and preventing race conditions.

