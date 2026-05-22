# Dining Philosophers

## Overview

This project is a concurrent simulation of the classic Dining Philosophers Problem implemented in C using POSIX threads and mutexes.

It explores fundamental concepts in concurrent programming such as thread synchronization, shared resource management, race conditions, deadlock prevention, and starvation detection.

## Problem Statement

A number of philosophers sit around a circular table with one fork placed between each pair of philosophers.

Each philosopher continuously cycles through three states:

- Eating
- Sleeping
- Thinking

To eat, a philosopher must acquire both the left and right forks.

The challenge is to design a synchronization strategy that:

- Preventing deadlocks
- Avoiding starvation
- Eliminating data races
- Synchronizing shared resources
- Maintaining accurate timing
- Designing safe thread termination

## Simulation Model

Each philosopher is represented as an independent thread.

Each fork is represented as a shared resource protected by a mutex.

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
 (state machines)                          (death & termination check)
        │
        ▼
 Shared Fork Mutexes
 (critical section protection)

```

### Philosopher Threads

Each philosopher thread independently executes:
```
take forks
→ eat
→ sleep
→ think
```
while competing for shared fork resources.

### Monitor Thread

A dedicated monitoring routine continuously checks:

- Time since last meal
- Death conditions
- Global termination state

This separates simulation logic from liveness monitoring.

## Synchronization Strategy

Fork access is synchronized using mutexes.

Critical sections include:

- Fork acquisition
- Printing state messages
- Updating meal timestamps
- Global stop conditions

This prevents:

- Data races
- Interleaved console output
- Inconsistent simulation state

## Deadlock Prevention

To prevent circular waiting between philosophers, fork acquisition order is controlled.

The implementation avoids scenarios where all philosophers hold one fork simultaneously while waiting indefinitely for the second.

Strategies may include:

- Asymmetric fork ordering
- Delayed start timing
- Even/odd philosopher scheduling

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

### Example and Output
```sh
./philo 3 200 60 60
```
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

### Mandatory

- POSIX threads
- Mutex-based synchronization

### Bonus

- Processes instead of threads
- Semaphore-based synchronization

The bonus implementation explores the difference between:

- shared-memory concurrency
- inter-process synchronization

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

## References


## Future Improvements