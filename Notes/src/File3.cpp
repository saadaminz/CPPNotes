
#if 0
#include "Utils.h"
#include <optional>
#include <fstream>
#include <variant>
#include <any>
#include <array>
#include <bitset>
#include <map>
#include <unordered_map>
#endif

#if 0
// This is about std::optional (in-and-after C++17)
// Use as the return type of a method that may fail
std::optional<std::string> ReadFile(const std::string& path)
{
	std::ifstream file(path);
	if (file)
	{
		// Read file
		file.close();
		// Return data
	}
	return {};
}

int main()
{
	std::optional<std::string> data = ReadFile("folder/file.txt");

	LOG(data.has_value());
}
#endif

#if 0
// This is about std::variant (in-and-after C++17)
enum ErrorCode
{
	FileEmpty, FileNotFound, AccessToFileDenied
};

std::variant<std::string, ErrorCode> ReadFile()
{
	return {};
}

int main()
{
	std::variant<std::string, int> data;

	data = "AString";
	LOG(std::get<std::string>(data));

	data = 1;
	LOG(std::get<int>(data));
}
#endif

#if 0
// This is about std::any (in-and-after C++17)
// For small types like integers, it uses Union
// For large types it dynamically allocates memory
int main()
{
	std::any data;
	data = 1;
	data = "ACharArray";
	data = std::string("AString");
}
#endif

#if 0
// This is about optimizing the use of strings
static unsigned int allocs = 0;

// Overload NEW to track memory allocations
void* operator new(size_t size)
{
	allocs++;
	return malloc(size);
}

#if 0
// Not optimized
void Print(std::string& string)
{
	LOG(string);
}

int main()
{
	std::string app = "FFF111";

	std::string name = app.substr(0, 3);
	std::string version = app.substr(3, 5);

	Print(name);
	Print(version);

	LOG("Allocs", allocs);
}
#else
// Optimized
void Print(std::string_view& string)
{
	LOG(string);
}

int main()
{
	// For strings less than 15 characters,
	// std::string does not call malloc,
	// so we can still use std::string here
	const char* app = "FFF111";

	std::string_view name(app, 3);
	std::string_view version(app + 3, 5);

	Print(name);
	Print(version);

	LOG("Allocs", allocs);
}
#endif
#endif

#if 0
// Takes lvalue and rvalue
void Print1(const std::string& string)
{
	LOG(string);
}

// Takes only lvalue
void Print2(std::string& string)
{
	LOG(string);
}

// Takes only rvalue
void Print3(std::string&& string)
{
	LOG(string);
}

int Function1()
{
	return 10;
}

int& Function2()
{
	static int integer = 10;
	return integer;
}

int main()
{
	std::string str = "AString";
	Print1(str);
	Print2(str);

	Print1("AString");
	Print3(str + "AString");

	int i = Function1();
	Function2() = 5;
}
#endif

#if 0
// This is about std::move and Move Semantics
class String
{
private:
	char* data;
	uint32_t size;
public:
	String() = default;

	// Default constructor
	String(const char* string)
	{
		LOG("String class object created");
		size = strlen(string);
		data = new char[size + 1];
		memcpy(data, string, size);
		data[size] = 0;
	}

	// Copy constructor
	String(const String& other)
		: size(other.size)
	{
		LOG("String class object copied");
		data = new char[size + 1];
		memcpy(data, other.data, size);
		data[size] = 0;
	}

	// Move constructor for copying from String to another class
	String(String&& other) noexcept
	{
		LOG("String class object moved to another class");
		size = other.size;
		data = other.data;
		other.size = 0;
		other.data = nullptr;
	}

	// Overload for copying object from String to String
	String& operator=(String&& other) noexcept
	{
		LOG("String class object moved to String class");

		if (this != &other)
		{
			delete[] data;
			size = other.size;
			data = other.data;
			other.size = 0;
			other.data = nullptr;
		}
		return *this;
	}

	void Print()
	{
		LOG(data);
	}

	~String()
	{
		LOG("String class object destroyed");
		delete[] data;
	}
};

class AClass
{
private:
	String strObj;
public:
	AClass(const String& string)
		: strObj(string)
	{
		LOG("AClass class object created");
	}

	AClass(String&& string)
		: strObj(std::move(string)) // : strObj((String&&)string)
	{
		LOG("AClass class object created");
	}
};

int main()
{
	{
		AClass ac(String("ASTRING"));
	}
	LOG("");
	{
		String s("AASTRING");
		String ss;
		ss = std::move(s);
	}
	LOG(""); LOGM();
}
#endif

#if 0
// This is about Bitwise Operators
int main()
{
	int x = 1 << 4; // 0000 0001 l4 0001 0000
	int y = 4 >> 1; // 0000 0100 r1 0000 0010

	int a = 0b0110;
	int b = 0b0100;
	int c = a | b;
	int d = a ^ b;
	int e = a & b;
	int f = ~a;
	LOG(std::bitset<8>(c));
	LOG(std::bitset<8>(d));
	LOG(std::bitset<8>(e));
	LOG(std::bitset<8>(f));
}
#endif

#if 0
// This is about std::map and std::unordered_map
int main()
{
	std::unordered_map<int, std::string> uMap;
	uMap[1] = "First";
	uMap[2] = "Second";
	uMap[3] = "Third";

	for (const auto& key : uMap)
	{
		LOG(key.first, key.second);
	}

	for (const auto& [key, value] : uMap)
	{
		LOG(key, value);
	}
}
#endif
