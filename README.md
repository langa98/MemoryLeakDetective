# Memory Leak Detective

## Overview

**Memory Leak Detective** is a **C++ diagnostic tool** that identifies and reports **heap memory leaks** in programs.  
It works by **intercepting all dynamic memory allocations (`new`) and deallocations (`delete`)**, tracking every allocated memory block, and reporting those that are never freed at program termination.  

This project demonstrates **advanced C++ expertise**, including:

- Raw pointer handling and memory management  
- Operator overloading (`new` / `delete`)  
- Object lifetime and RAII principles  
- Multi-file C++ project organization  
- Debugging and runtime diagnostics  

It is designed as a **portfolio-ready project** to showcase your systems-level C++ skills.

---

## Key Features

- **Global memory tracking:** Overrides global `new` and `delete` to monitor all heap allocations  
- **Leak detection:** Reports unfreed memory with size and pointer address  
- **Modular design:** Clean separation of interface (`.hpp`) and implementation (`.cpp`)  
- **Easy to extend:** Supports adding call-site tracking, thread safety, and array tracking  
- **Educational:** Simulates concepts from professional tools like Valgrind and AddressSanitizer  

---

## How It Works

1. Every call to `new` is intercepted and stored in a global registry (`MemoryTracker`).  
2. Every call to `delete` removes the corresponding allocation from the registry.  
3. At program termination, `MemoryTracker::reportLeaks()` outputs any remaining allocations.

**Example Output:**

Memory leaks detected:
Leaked 4 bytes at address 0x7ffee3a0b4c0


This clearly indicates **exactly which memory was not freed**, helping prevent runtime errors and undefined behavior.

---

## Project Structure

MemoryLeakDetective/
│
├── include/
│ └── MemoryTracker.h # Class declarations and interface
│
├── src/
│ ├── MemoryTracker.cpp # Implementation of memory tracking logic
│ └── main.cpp # Example usage of the tool
│
└── README.md # Project documentation


---

## Skills Highlighted

- **Memory Management:** Tracking heap allocations and deallocations  
- **Pointer Mastery:** Raw pointers, void pointers, and pointer identity  
- **Operator Overloading:** Global `new` and `delete` operators  
- **Debugging & Diagnostics:** Detecting memory leaks and analyzing runtime behavior  
- **Systems-Level Thinking:** Avoiding undefined behavior and handling object lifetimes correctly  
- **Professional C++ Practices:** Multi-file organization and modular design  

---

## How to Run

1. Compile using a modern C++ compiler (C++11 or later):

```bash
g++ -std=c++11 src/*.cpp -o MemoryLeakDetective

./MemoryLeakDetective

2.Run the executable:

./MemoryLeakDetective


**Major**
Observe the memory leak report in the console
