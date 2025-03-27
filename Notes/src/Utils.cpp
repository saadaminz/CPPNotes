
#if 1
#include "Utils.h"

unsigned int allocCount = 0;
unsigned int allocSize = 0;
unsigned int deAllocCount = 0;
unsigned int deAllocSize = 0;

// Track count and size of memory allocations
// Add extra memory for metadata to store size
void* operator new(size_t size)
{
	void* ptr = malloc(size + sizeof(size_t));
	if (!ptr) throw std::bad_alloc();
	*(reinterpret_cast<size_t*>(ptr)) = size;
	allocCount++;
	allocSize += size;
	return static_cast<void*>(static_cast<char*>(ptr) + sizeof(size_t));
}

// Track count and size of memory deallocations
void operator delete(void* memory) noexcept
{
	if (memory) {
		void* realMemory = static_cast<void*>(static_cast<char*>(memory) - sizeof(size_t));
		size_t size = *(reinterpret_cast<size_t*>(realMemory));
		deAllocCount++;
		deAllocSize += size;
		free(realMemory);
	}
}

// Output memory usage to console
void LOGM()
{
	std::cout << "Allocations:\n  count(" << allocCount << ") size(" << allocSize << ")\n";
	std::cout << "Deallocations:\n  count(" << deAllocCount << ") size(" << deAllocSize << ")\n";
}
#endif
