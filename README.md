# **OS**
This repository is a collection of small, self-contained **C programs** about **systems programming on Linux**. Each topic lives in its own directory, every program compiles on its own, and most topics include a `report.txt` with the code, its output, and observations.

### `pointers/`
The fundamentals: pointer arithmetic, pointers as function arguments, pointers to pointers, and strings through character pointers.

### `alignment/`
How the compiler lays out data in memory: data alignment, struct padding, and what changes under `#pragma pack`.

### `compilation_units/`
A program split across multiple translation units (`main.c`, `math_utils.c/.h`) to show how separate compilation and linking work.

### `dynamic_memory_allocation/`
`malloc`, `calloc`, and `realloc` exercises, growing, shrinking, and initializing arrays, plus **`my_realloc`** and an **`aligned_malloc`** implementation.

### `files/`
POSIX file I/O: appending log entries, byte-wise file comparison, copying, truncation, in-place overwriting, reading a file backwards, and creating **sparse files**.

### `processes/`
The process lifecycle: `fork`, exit statuses, `wait`, `atexit` handlers, and **zombie processes**, both how to create one and how to avoid it.

### `fork_exec/`
Combining `fork` with `exec`: passing arguments, running shell commands, and forking multiple children.

### `process_scheduling/`
A simulation of **FCFS** and **SJF** scheduling: it takes processes with arrival and burst times, then prints a Gantt chart, a per-process table (waiting, turnaround, and response times), and the averages for each algorithm. Has its own README.

### `threads/`
pthread basics: creating threads and splitting work across them.

### `synchronization/`
Race conditions and the tools that fix them: a deliberately **broken counter** (with its mutex and spinlock fixes), a thread-safe bank account, a producer–consumer **bounded buffer** on semaphores, ordered printing, and a printer pool.

---

## Usage
There is no build system — every program is standalone:

```
gcc program.c -o program
./program

```

The programs in `threads/` and `synchronization/` use pthreads:

```
gcc bounded_buffer.c -o bounded_buffer -pthread

```
