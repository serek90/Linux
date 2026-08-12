# Linux System Programming Experiments

Small C programs for learning Linux processes, system calls,
scheduling and interaction between user space and the kernel.

The goal is not to build production software, but to understand
how Linux works by writing small experiments and observing their
behavior.

## Experiments

### 01 - Process information

Topics:
- PID
- PPID
- `getpid()`
- `getppid()`
- observing processes with `ps`

The program prints its own PID and the PID of its parent process.
It can then be observed from another terminal using `ps`.

### 02 - Process priority

Topics:
- `getpriority()`
- `setpriority()`
- nice value
- `errno`
- process permissions


