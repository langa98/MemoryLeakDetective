#include "MemoryTracker.h"
#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <new>

namespace {
    std::unordered_map<void*, std::size_t> allocations;  
    bool trackingEnabled = false;                        
    bool reentryGuard = false;// prevent recursion in operator new

    // RAII guard ensures reentryGuard is reset automatically
    struct TrackingGuard {
        bool& guardRef;
        TrackingGuard(bool& r) : guardRef(r) {
            guardRef = true;
        }

        ~TrackingGuard() {
            guardRef = false;
        }
    };
}

void MemoryTracker::Enable() {
    trackingEnabled = true;
}

void MemoryTracker::Add(void* ptr, std::size_t size) {

    if (!trackingEnabled || reentryGuard) {
        return;
    }

    TrackingGuard guard(reentryGuard);

    allocations[ptr] = size;
}

void MemoryTracker::Remove(void* ptr) {

    if (!trackingEnabled || reentryGuard) {
        return;
    }

    TrackingGuard guard(reentryGuard);

    allocations.erase(ptr);
}

void MemoryTracker::ReportLeaks() {

    if (allocations.empty()) {
        std::cout << "The is no leaks in the System!\n" << std::endl;
        return;

    }
    std::cout << "Memory leaks detected:\n";
    for (const auto& entry : allocations) {
        std::cout << "Leaked " << entry.second
            << " bytes at address " << entry.first << '\n';
    }


}

/*void MemoryTracker::ReportLeaks() {

    if (allocations.empty()) {

        std::cout << "No memory leaks detected.\n";

        return;
    }

    std::cout << "Memory leaks detected:\n";

    for (const auto& [ptr, size] : allocations) {

        std::cout << " Leaked " << size
            << " bytes at address " << ptr << '\n';
    }
}
*/

void* operator new(std::size_t size) {

    void* ptr = std::malloc(size);

    if (!ptr) throw std::bad_alloc();

    MemoryTracker::Add(ptr, size);
    return ptr;
}

void operator delete(void* ptr) noexcept {

    if (!ptr) return;

    MemoryTracker::Remove(ptr);

    std::free(ptr);
}
