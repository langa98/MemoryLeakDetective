#pragma once
#include<cstddef>

class MemoryTracker {

public:
	static void Add(void* ptr, std::size_t size);
	static void remove(void* ptr);
	static void reportLeaks();
};
