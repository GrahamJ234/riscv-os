# Tiny RISC-V Operating System

## Overview

This project implements a small educational operating system for a RISC-V `virt` system running inside QEMU. It demonstrates core OS concepts including:

- Booting a kernel on real RISC-V hardware architecture
- Creating and loading multiple programs
- Cooperative multitasking / process switching
- Synchronization primitives
- Program protection via system calls
- An in-memory file system
- UART serial output
- Ability to extend the system with new programs and commands

This project was built for an Operating Systems assignment requiring a functional command-line OS capable of multitasking and running in QEMU.

---

# Features Implemented

###  Separate Programs
Each user program is compiled separately and instantiated via `proc_create`.

###  Multiple Programs Running
Our scheduler cycles through processes using cooperative context switching.

###  Scheduling
Basic round-robin scheduling implemented through `scheduler_loop()`.

###  Synchronization
- Mutex locks
- Semaphores

Used internally for:
- File system operations
- Protected access to shared structures

###  Protection
User programs must call `sys_*` functions — they cannot access kernel functionality directly.

###  File System Simulation
In-memory file system:
- `fs_create`
- `fs_read`
- `fs_write`
