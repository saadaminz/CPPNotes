#pragma once

#if 1
#include <iostream>
#include <chrono>

// Console level logging methods
template<typename T1>
void LOG(const T1& x) { std::cout << x << '\n'; }

template<typename T1, typename T2>
void LOG(const T1& x, const T2& y) { std::cout << x << " : " << y << '\n'; }

template<typename T1, typename T2, typename T3>
void LOG(const T1& x, const T2& y, const T3& z) { std::cout << x << " : " << y << " : " << z << '\n'; }

// Overloads for tracking memory usage
extern unsigned int allocCount;
extern unsigned int allocSize;
extern unsigned int deAllocCount;
extern unsigned int deAllocSize;

void* operator new(size_t size);
void operator delete(void* memory) noexcept;
void LOGM();

// Timer for performance measurement
struct Stopwatch
{
	std::string name;
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;
	bool started = false;

	Stopwatch(std::string name) : name(name) {}

	void Start() {
		start = std::chrono::high_resolution_clock::now();
		started = true;
	}

	void Stop() {
		if (!started) return;
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		std::cout << name << ": " << duration.count() * 1000.0f << "ms\n";
		started = false;
	}

	~Stopwatch() { Stop(); }
};
#endif
