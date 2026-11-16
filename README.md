# Philosopher

## Description

Philosopher is a multithreading concurrency project implemented in C, based on the classic Dining Philosophers problem. The goal is to simulate several philosophers sharing a limited number of forks and to ensure they can eat, sleep, and think without causing deadlocks or starvation.

This project was developed as part of the 42 curriculum and focuses on thread synchronization, mutex management, timing control, and real-time coordination between concurrent tasks. It demonstrates how shared resources must be handled carefully to maintain correctness in multithreaded programs.

## Features

### Core Simulation
- **Multiple philosophers**: Simulates a configurable number of philosophers sitting around a table
- **Shared forks**: Each philosopher needs two forks to eat, forcing proper synchronization
- **Concurrency control**: Uses mutexes to protect critical sections and prevent race conditions
- **Time tracking**: Monitors meal timing and death conditions based on elapsed time
- **Mandatory eating cycle**: Supports the optional requirement that all philosophers eat a specific number of times

### Threading and Safety
- **Mutex-based synchronization**: Protects fork access and shared state updates
- **Death monitoring**: Detects when a philosopher has exceeded the allowed time without eating
- **Message output**: Prints the state transitions in a synchronized and readable way
- **Single philosopher edge case**: Handles the special case of a lone philosopher correctly

## Technologies Used

- **Language**: C
- **Parallelism**: POSIX threads (`pthread`)
- **Synchronization**: Mutexes
- **Timing**: `gettimeofday()` / millisecond timestamps
- **Build System**: Makefile
- **Platform**: Linux / Unix-like systems

## Prerequisites

- Linux operating system
- GCC compiler
- Make
- POSIX thread support

## Installation

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd philosopher
   ```

2. Build the project:
   ```bash
   make
   ```

3. Run the simulation:
   ```bash
   ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_must_eat]
   ```

## Usage

### Example runs
```bash
./philo 5 800 200 200
./philo 4 410 200 200
./philo 5 800 200 200 7
```

### Parameters
- **number_of_philosophers**: total philosophers at the table
- **time_to_die**: time in milliseconds before a philosopher dies if they have not eaten
- **time_to_eat**: time in milliseconds spent eating
- **time_to_sleep**: time in milliseconds spent sleeping
- **number_of_times_each_must_eat**: optional stop condition when all philosophers have eaten enough

## Key Algorithms & Concepts

- **Thread synchronization**: Coordinating multiple threads that share resources
- **Mutex locking**: Ensuring exclusive access to forks and state updates
- **Race condition prevention**: Protecting accesses to shared meal timing and death flags
- **Deadlock avoidance**: Implementing a safe fork acquisition strategy
- **Time-based monitoring**: Checking whether a philosopher has starved
- **State modeling**: Representing eating, sleeping, thinking, and death transitions

## Learning Outcomes

This project demonstrates:
- Multithreading fundamentals in C
- Proper use of mutexes and synchronization primitives
- Concurrency problem analysis and deadlock prevention
- Real-time coordination and timing considerations
- Robustness in systems with shared resources
- Practical understanding of the Dining Philosophers problem and its edge cases
