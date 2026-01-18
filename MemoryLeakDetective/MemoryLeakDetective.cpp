#include "MemoryTracker.h"
#include <iostream>

int main() {
    MemoryTracker::Enable();

    // Test Decalaration with direct macros
    int* single = new(__FILE__, __LINE__) int(42);
    int* array = new(__FILE__, __LINE__) int[10];

   // delete single;          // Use delete for single objects
    delete[] array;         // Use delete[] for arrays
    
    // Then This is testing the macros
    int* p1 = TRACK_NEW int(100);
    int* p2 = TRACK_NEW int[20];

    //delete p1;
    delete[] p2;  // Note: MUST use delete[] for arrays!

    MemoryTracker::ReportLeaks();

    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();

    return 0;
}