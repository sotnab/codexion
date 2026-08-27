*This project has been created as part of the 42 curriculum by wbaran.*

# Codexion

## Description

Codexion is a 42 curriculum concurrency project written in C with POSIX threads.
It is an extended version of the dining philosophers problem. This version
simulates coders competing for shared dongles while they compile, debug, and
refactor code. There is N number of coders and N USB dongles. Each coder needs
two dongles to compile. Then they debug, refactor and wait for dongles again.

The goal is to coordinate several coder threads safely and fairly. Each coder
must acquire two dongles before compiling, respect the cooldown of each dongle,
and compile a set number of times. A monitor thread watches the coders and
stops the simulation when all coders have finished or one coder burns out.

The request queue supports two scheduling methods:

- `fifo`: first-in, first-out request handling.
- `edf`: earliest-deadline-first handling, using each request's
	calculated burnout deadline.

## Instructions

### Requirements

- A POSIX-compatible system
- A C compiler with pthread support
- `make`

### Compilation

From the repository root, build the executable with:

```sh
make
```

Useful build commands are:

```sh
make clean   # Remove object files
make fclean  # Remove object files and the executable
make re      # Rebuild from scratch
```

### Execution

Run the program with eight arguments:

```text
./codexion number_of_coders burnout_time compile_time debug_time refactor_time compiles_required dongle_cooldown scheduler
```

All time values are in milliseconds. `scheduler` must be `fifo` or `edf`.

Example:

```sh
./codexion 5 800 200 150 100 3 50 edf
```

The program prints coder events with timestamps in milliseconds. It ends with
either a burnout message or a message confirming that all coders
reached the required compile count.

## Blocking cases handled

### Deadlock prevention

- **Mutual exclusion:** every dongle has its own mutex. This means
  that only one coder can hold a dongle at a time.
- **Hold and wait:** a coder can hold its first dongle while waiting for the
  second. The fixed order and request queue prevent this from creating a cycle.
- **No preemption:** a coder releases its dongles after compiling. The program
  stores the next available time before unlocking each dongle.
- **Circular wait:** each coder has a fixed order for acquiring its two dongles.
  Odd and even coders use different orders, so the coders cannot create a
  circular wait.

### Starvation prevention

Because of equal times of compilation, debugging, refactoring and cooldown
every coder is doing the same cycle. This means that their requests
even in FIFO scheduling come in the order that is optimal to not cause
starvation. EDF is ensuring that dongle is passed to a dongle that has
a closer deadline. In practice it rarely happens.

### Cooldown handling

After a dongle is released, releasing thread is setting its `available_at`
property to the current time plus cooldown. Another thread that is requesting
this dongle either takes it immidiately if cooldown has passed or uses
`pthread_cond_timedwait` to wait until the cooldown passes.

### Precise burnout detection

The monitor thread is checking each coder's state every 5ms.
It detects either a burnout or a completion of required number of compiles.
Coders have `last_compile` property and after `burnout_time` since last
compile they burn out.

### Log serialization

Printing log and final messages is protected by `pthread_mutex_t`.
This prevents threads from interrupting each others logs.

### Shutdown of waiting threads

After monitor detects a burnout or completion, it sets the `finish` property
to true. After the `pthread_cond_broadcast` is used to wake up threads
that currently wait for their turn and. Threads that sleep because they're
currently compiling/debugging/refactoring use special sleep function
which every millisecond checks if the simulation is finished. In every case
threads are skipping all of the logic, free the memory and join the main thread.

## Thread synchronization mechanisms

### `pthread_mutex_t`

- Each dongle has a mutex that protects access to it.
- `queue_lock` protects queue operations.
- `data_lock` protects `finish`, coder counters, compile and dongle cooldown timestamps.
- `print_lock` protects terminal output.

When one coder is printing/modifying shared data and
another one tries to do so, second one has to wait for its turn.

### `pthread_cond_t`

The queue has a condition variable used to protect queue data.
Since every thread is updating/checking queue data on their own
this is used to prevent data races.

`pthread_cond_timedwait` is used to wait until dongle cooldown passes,
there is a change in queue or simulation is finished.
`pthread_cond_broadcast` is used to signal other waiting threads that there is
a change in the queue or simulation has ended.

The condition variable is used with `queue_lock` in a while loop to
wait until its the waiting threads turn.

## Project structure

- `main.c`: entry point. Validates parameters and starts the program.
- `src/parsing/`: validates and parses the parameters.
- `src/init/`: initializes coders, dongles, the queue, and mutexes.
- `src/coder/`: coder routines, dongle requests, and event logging.
- `src/queue/`: FIFO and EDF queue operations, EDF heap.
- `src/monitor/`: burnout, completion, and shutdown handling.
- `src/utils/`: timing, shared-state getters, and cleanup.

## Resources

- Youtube tutorials about pthread API
- Linux man pages
- GeeksForGeeks https://www.geeksforgeeks.org/

### AI usage

- Structure of this README.md file
- Explaining clearly pthread API functions
- Generating test data for fifo/edf scheduling
