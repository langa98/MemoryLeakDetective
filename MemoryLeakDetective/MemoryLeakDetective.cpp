#include "MemoryTracker.h"
#include <iostream>

int main() {
    MemoryTracker::Enable();  

    int* a = new int(10);
    int* b = new int(20);

    delete a;   //correct deletion
    // b is not deleted cause we want to check and iterate

    MemoryTracker::ReportLeaks();

    std::cout << "\nPress Enter to exit...";
    std::cin.get();


    return 0;
}

