#include "MemoryTracker.h"
#include <iostream>
#include <cstdlib>
#include <new>
#include <vector>

namespace {
    struct AllocationInfo {
        std::size_t size;
        const char* file;
        int line;
    };

    struct AllocationRecord {
        void* ptr;
        AllocationInfo info;
    };


    std::vector<AllocationRecord> allocations;

    bool trackingEnabled = false;

    // search function By index
    int FindAllocationIndex(void* ptr) {

        for (int i = 0; i < static_cast<int>(allocations.size()); i++) {

            if (allocations[i].ptr == ptr) {

                return i;
            }
        }
        return -1;
    }
}
//Closing of The Anonymous Namepsace//


void MemoryTracker::Enable() {
    trackingEnabled = true;
}

void MemoryTracker::Add(void* ptr, std::size_t size, const char* file, int line) {

    if (!trackingEnabled) {
        return;
    }

    // Reserve space to avoid allocations during tracking
    if (allocations.empty()) {
        allocations.reserve(1024);
    }

    AllocationRecord record;
    record.ptr = ptr;
    record.info.size = size;
    record.info.file = file;
    record.info.line = line;
    
    allocations.push_back(record);
}

void MemoryTracker::Remove(void* ptr) {
    if (!trackingEnabled) {
        return;
    }

    int index = FindAllocationIndex(ptr);

    if (index >= 0) {

        // Move last element to current position
        allocations[index] = allocations.back();
        allocations.pop_back();

    }
}

void MemoryTracker::ReportLeaks() {
    if (!trackingEnabled) {
        std::cout << "Memory tracking is disabled.\n";
        return;
    }

    if (allocations.empty()) {
        std::cout << "No memory leaks detected.\n";
        return;
    }

    std::cout << "Memory leaks detected (" << allocations.size() << "):\n";

    for (size_t i = 0; i < allocations.size(); i++) {

        const AllocationRecord& record = allocations[i];

        std::cout << "  Leaked " << record.info.size
            << " bytes at " << record.ptr
            << " (" << record.info.file
            << ":" << record.info.line << ")\n";
    }
}

// Placement new operators (MUST have these exact signatures)
void* operator new(std::size_t size, const char* file, int line) {

    void* ptr = std::malloc(size);

    if (!ptr) throw std::bad_alloc();

    MemoryTracker::Add(ptr, size, file, line);

    return ptr;
}

void* operator new[](std::size_t size, const char* file, int line) {

    void* ptr = std::malloc(size);

    if (!ptr) throw std::bad_alloc();

    MemoryTracker::Add(ptr, size, file, line);

    return ptr;
}


void* operator new[](std::size_t size) {

    void* ptr = std::malloc(size);

    if (!ptr) throw std::bad_alloc();

    MemoryTracker::Add(ptr, size, "unknown", 0);

    return ptr;
}

// Regular delete operators
void operator delete(void* ptr) noexcept {

    if (!ptr) return;

    MemoryTracker::Remove(ptr);

    std::free(ptr);
}

void operator delete[](void* ptr) noexcept {

    if (!ptr) return;

    MemoryTracker::Remove(ptr);

    std::free(ptr);
}

// Sized delete operators 
void operator delete(void* ptr, std::size_t size) noexcept {

    if (!ptr) return;

    MemoryTracker::Remove(ptr);

    std::free(ptr);
}

void operator delete[](void* ptr, std::size_t size) noexcept {

    if (!ptr) return;

    MemoryTracker::Remove(ptr);

    std::free(ptr);
}

// Placement delete operators (required to match placement new)
void operator delete(void* ptr, const char* file, int line) noexcept {

    if (!ptr) return;

    MemoryTracker::Remove(ptr);

    std::free(ptr);
}

void operator delete[](void* ptr, const char* file, int line) noexcept {

    if (!ptr) return;

    MemoryTracker::Remove(ptr);

    std::free(ptr);
}