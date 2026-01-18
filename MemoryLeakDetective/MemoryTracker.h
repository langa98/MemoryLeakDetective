#pragma once
#include <cstddef>

class MemoryTracker {
public:
    static void Add(void* ptr, std::size_t size, const char* file, int line);
    static void Remove(void* ptr);
    static void ReportLeaks();
    static void Enable();
};

// Placement new operators MUST be declared exactly like this
void* operator new(std::size_t size, const char* file, int line);
void* operator new[](std::size_t size, const char* file, int line);

// Regular new/delete operators
void* operator new[](std::size_t size);
void operator delete(void* ptr) noexcept;
void operator delete[](void* ptr) noexcept;
void operator delete(void* ptr, std::size_t size) noexcept;
void operator delete[](void* ptr, std::size_t size) noexcept;

// Special placement delete operators to match placement new
void operator delete(void* ptr, const char* file, int line) noexcept;
void operator delete[](void* ptr, const char* file, int line) noexcept;

// Macros for easier use
#define TRACK_NEW new(__FILE__, __LINE__)
#define TRACK_NEW_ARRAY new(__FILE__, __LINE__)