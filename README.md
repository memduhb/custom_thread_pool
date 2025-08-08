# C++ ThreadPool Implementation

A modern C++ thread pool implementation for efficient concurrent task execution. This project demonstrates multi-threading concepts by implementing a fixed-size thread pool that manages worker threads and a thread-safe task queue using condition variables and mutex synchronization.

## Overview

This thread pool implements a producer-consumer pattern with a fixed number of worker threads that continuously process tasks from a shared queue. The implementation uses modern C++ features including `std::thread`, `std::function`, `std::mutex`, and `std::condition_variable` to provide efficient task scheduling and execution. The pool automatically manages thread lifecycle, provides clean shutdown mechanisms, and ensures thread-safe task submission and execution.

## Features

- **Thread Pool Management**: Fixed-size pool of worker threads
- **Task Queue**: Thread-safe task queuing with condition variables
- **Clean Shutdown**: Graceful thread termination and cleanup
- **Thread Safety**: Full thread-safe implementation with mutex protection
- **Performance Optimized**: Tasks executed outside locks to minimize contention
- **Move Semantics**: Efficient task transfer using move semantics

## Learning Outcomes

This project demonstrates key concepts in concurrent programming and modern C++:

- **Concurrency Control**: Mutex-based synchronization and condition variable signaling
- **Thread Management**: Worker thread creation, lifecycle management, and cleanup
- **Producer-Consumer Pattern**: Task submission and execution with thread-safe queuing
- **Memory Management**: RAII principles and automatic resource cleanup
- **Performance Optimization**: Lock contention minimization and efficient task scheduling
- **Thread Safety**: Atomic operations and proper synchronization patterns

## Layout

```
thread_pool/
├── src/
│   ├── ThreadPool.h        # Public API header with documentation
│   └── ThreadPool.cpp      # Implementation with threading logic
├── test/
│   └── main.cpp            # Test suite and usage examples
├── Makefile                # Build configuration
├── README.md               # This file
└── .gitignore              # Git ignore rules
```

## Build and Usage

### Build
```bash
make
```

### Run Tests
```bash
make run
```

### Clean
```bash
make clean
```

The test suite demonstrates thread pool functionality with concurrent task execution, showing how tasks are distributed across worker threads and executed efficiently. 