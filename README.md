# Dining Philosophers
*This project has been created as part of the 42 curriculum by tmitsuya*

## Overview

This project is a concurrent simulation of the classic Dining Philosophers Problem implemented in C using POSIX threads and mutexes.

It focuses on core concepts of concurrent programming, including:

- Thread synchronization
- Shared resource management
- Deadlock prevention
- Race condition handling
- Starvation detection
- Time-sensitive system behavior

### Problem Statement

A number of philosophers sit around a circular table with one fork placed between each pair of philosophers.

Each philosopher continuously cycles through three states:

- Eating
- Sleeping
- Thinking

To eat, a philosopher must acquire both the left and right forks.

### Constraints

The system must ensure:

- No deadlocks
- No data races
- No starvation (if possible under timing constraints)
- Accurate state transitions
- Clean termination of all threads

Philosophers do not communicate directly and have no global knowledge of the system state.

## Simulation Model

- Each philosopher is represented as an independent thread.
- Each fork is represented as a shared resource protected by a mutex.

The simulation ends when:

- A philosopher dies from starvation
- Or all philosophers have eaten the required number of times

## Concurrency Architecture

```text
                          Main Thread
                        (initialization)
                                 │
        ┌────────────────────────┴────────────────────────┐
        │                                                 │
        ▼                                                 ▼
 Philosopher Threads                              Monitor Thread
 (independent state machines)              (liveness supervision)
        │
        ▼
 Shared Fork Mutexes
 (critical section protection)

```

### Philosopher Threads

Each philosopher thread independently executes:
```
take forks → eat → sleep → think
```
while competing for shared fork resources.

### Monitor Thread

A dedicated monitoring routine continuously checks:

- Time since last meal
- Death conditions
- Global termination state

This separates simulation logic from liveness monitoring.

## Synchronization Strategy

All shared resources are protected using mutexes to ensure safe concurrent access.

Critical sections include:

- Fork acquisition and release
- Writing log messages (to prevent output interleaving)
- Updating last meal timestamps
- Checking global termination state

This guarantees:

- No data races
- Consistent simulation state
- Deterministic logging output

## Deadlock Prevention

Deadlock is prevented by breaking the circular wait condition.

Philosophers acquire forks in a consistent global order.

To avoid symmetric locking patterns that could lead to circular dependencies, one philosopher uses an asymmetric acquisition strategy.

This ensures that no cyclic dependency can form in the resource graph.

## Timing & Monitoring

The simulation uses millisecond-level timestamps based on `gettimeofday()`.

Timing constraints include:

- Detecting philosopher death within 10ms
- Accurate sleep/eat durations
- Precise starvation monitoring

Special attention is required because:

- `usleep()` is not perfectly precise
- Thread scheduling is controlled by the OS kernel
- Timing drift accumulates under contention

## Usage

### Build
```sh
git clone https://github.com/takato7/philosophers-concurrency.git
cd philosophers-concurrency/philo
make
```
### Run

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [must_eat_count]
```

### Parameters

| Argument                 | Description                      |
| ------------------------ | -------------------------------- |
| `number_of_philosophers` | Number of philosophers and forks |
| `time_to_die`            | Max time without eating          |
| `time_to_eat`            | Eating duration                  |
| `time_to_sleep`          | Sleeping duration                |
| `must_eat_count`         | Optional termination condition   |

### Example
```sh
./philo 3 200 60 60
```
Example output:
```
0 2 is thinking
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
0 3 is thinking
60 1 is sleeping
60 3 has taken a fork
60 3 has taken a fork
60 3 is eating
120 1 is thinking

```

## Mandatory vs Bonus

### Mandatory (Threads + Mutexes)

- POSIX threads
- Mutex-based synchronization

### Bonus (Processes + Semaphores)

In the bonus version, philosophers are implemented as independent processes.

Forks are no longer represented individually.

Instead, a counting semaphore is used to represent the global availability of resources.

Behavior:
- A philosopher must acquire permission from the semaphore before eating
- The semaphore acts as a global resource controller
- This eliminates deadlock by design

## Key Learnings

This project provided hands-on experience with:

- POSIX threads (pthread)
- Mutex synchronization
- Semaphores
- Concurrent system design
- Race condition debugging
- Deadlock analysis
- Process vs thread architecture
- Timing-sensitive programming in C

## Future Improvements

### Thread Visualizer

A graphical visualization of philosopher states and fork ownership.

### Web-Based Concurrency Simulation

A browser-based version using WebAssembly and JavaScript visualization.

### Performance Analysis

Profiling thread scheduling latency and synchronization overhead under heavy contention.
