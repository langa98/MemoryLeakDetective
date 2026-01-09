#include "MemoryTracker.h"
#include<iostream>
#include<string>
#include<unordered_map>

namespace {
	std::unordered_map<void* , std::size_t > allocation;
}

void MemoryTracker::Add(void* ptr, std::size_t size) {
	allocation[ptr] = size;
}

void MemoryTracker::remove(void* ptr) {
	allocation.erase(ptr);
}

void MemoryTracker::reportLeaks(){

	if (allocation.empty()) {
		std::cout << "The is no leaks in the System!\n" << std::endl;
		return;

 }
	std::cout << "Memory leaks detected:\n";
	for (const auto& entry : allocation) {
		std::cout << "Leaked " << entry.second
			<< " bytes at address " << entry.first << '\n';
	}


}
