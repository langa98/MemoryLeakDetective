# MemoryLeakDetective 🕵️‍♂️  
*A lightweight C++ memory leak detection utility*

---

## 📌 Overview

**MemoryLeakDetective** is a simple, educational C++ memory tracking tool that detects
**unfreed dynamic memory allocations** at runtime.

It works by **intercepting `new` / `delete` operators** and recording:
- allocation size
- memory address
- source file and line (when available)

At program termination (or on demand), it reports all detected leaks.

This project is intended for:
- learning how memory tracking works internally
- understanding `operator new` / `operator delete`
- debugging small to medium C++ projects
- portfolio and systems-programming demonstrations

---

## ⚙️ How It Works

### Core Mechanism

The tracker overrides global allocation operators:

- `operator new`
- `operator new[]`
- `operator delete`
- `operator delete[]`

Each allocation is recorded in an internal container and removed when freed.

If an allocation is **never deleted**, it appears in the final leak report.

---

## 📂 Project Structure

MemoryLeakDetective/
│

├── MemoryTracker.h

├── MemoryTracker.cpp

├── main.cpp

└── README.md


---

## 🚀 Usage

### 1️⃣ Enable tracking

Tracking is **disabled by default** to avoid startup issues.

```cpp
MemoryTracker::Enable();
```
### 2️⃣ Allocate memory
✅ With file & line tracking (recommended)
#define TRACK_NEW new(__FILE__, __LINE__)

int* p = TRACK_NEW int(42);
int* arr = TRACK_NEW int[10];


This records:

exact file name

exact line number

⚠️ Without macro
int* p = new int(42);


This allocation will still be tracked, but will appear as:

file: unknown
line: 0


# This is a language limitation, not a bug.

### 3️⃣ Deallocate correctly
delete p;
delete[] arr;


⚠️ Always match:

new → delete

new[] → delete[]

### 4️⃣ Report leaks
MemoryTracker::ReportLeaks();

🧪 Example Output
Memory leaks detected (2):
Leaked 40 bytes at address 0000025D6B245440 (MemoryLeakDetective.cpp line:9)
  Leaked 4 bytes at address 0000025D6B2383F0 (MemoryLeakDetective.cpp line:15)

## 📐 Size Calculation (Verified)

Memory sizes are determined by the C++ runtime and passed directly to
`operator new(std::size_t size)`.

The tracker **does not calculate sizes itself** — it records the exact
`size` value provided by the runtime, which makes the results verifiable
and standards-compliant.

### Examples (Windows, MSVC, x64)

| Allocation        | Runtime Calculation        | Size Reported |
|-------------------|----------------------------|---------------|
| `new int`         | `sizeof(int)`              | 4 bytes       |
| `new int[10]`     | `10 × sizeof(int)`         | 40 bytes      |
| `new int[100]`    | `100 × sizeof(int)`        | 400 bytes     |

### Struct Example

```cpp
struct TestStruct {
    int a;
    double b;
};
```

## Layout:
```
int → 4 bytes

padding → 4 bytes

double → 8 bytes
Total: 16 bytes

All reported sizes are ABI-correct and verifiable.
```
### 🔒 Safety Measures
Re-entrancy Protection

The tracker avoids infinite recursion by using a guard when intercepting new.

This prevents:

crashes inside STL containers

recursive allocations

undefined behavior

STL Compatibility

STL allocations are tracked

File/line information cannot be recovered

Reported as unknown:0

This is expected and standard-compliant.

### ⚠️ Known Limitations (By Design)

File & Line Information

C++ does not provide file/line metadata automatically for new.

Therefore:
```
Only allocations using TRACK_NEW record source location

Plain new shows unknown:0

This limitation applies to all C++ memory debuggers, including professional ones.
```
## Not a Replacement for Valgrind / ASan
```
This tool does not:

detect use-after-free

detect buffer overflows

detect double deletes

inspect stack memory

It focuses only on leaked heap allocations.
```
## What This Tool Does Well
```
✔ Detects leaked heap memory
✔ Correctly tracks arrays and objects
✔ Safe global new interception
✔ Clear, readable output
✔ Educational and standards-compliant
```
## 🧠 Design Goals

Minimal dependencies

Clear implementation

Predictable behavior

No undefined behavior

Easy to extend

## 🔮 Possible Extensions
```
Detect delete vs delete[] mismatches

Group leaks by file

Track allocation IDs

Track total leaked bytes

Export report to file

Thread-safety support
```
### 📜 License

This project is provided for educational and personal use.
No warranty is expressed or implied.

