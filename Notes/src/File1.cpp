
#if 0
#include "Utils.h"
#include <array>
#include <string>
#include <memory>
#include <vector>
#endif

#if 0
class Logger
{
public:
	enum Type
	{
		Information,
		Debug
	};
private:
	Type level;

	void InformationMsg(const char* msg)
	{
		std::cout << "Information: " << msg << '\n';
	}

	void DebugMsg(const char* msg)
	{
		std::cout << "Debug: " << msg << '\n';
	}
public:
	Logger(Type l)
		: level(l)
	{
	}

	void Message(const char* msg)
	{
		if (level == Debug)
			DebugMsg(msg);
		else
			InformationMsg(msg);
	}
};

int main()
{
	Logger logger(Logger::Debug);
	logger.Message("Message");
}
#endif

#if 0
int main()
{
	// We can fill data at this char* buffer using memset,
	// here the buffer will be filled / initialized with 0s
	char* buffer = new char[8];
	memset(buffer, 0, 8);
	delete[] buffer;
}
#endif

#if 0
class InterfaceClass // Pure virtual class
{
public:
	virtual void IAmHere() = 0; // Pure virtual function
};

class AnotherClass : public InterfaceClass
{
public:
	void IAmHere() override { LOG("AnotherClass"); } // Must override the pure virtual function
};

class AndAnotherClass : public AnotherClass
{
public:
	void IAmHere() override { LOG("AndAnotherClass"); } // Must override the pure virtual function
};

void PrintOfTypeInterface(InterfaceClass& ic)
{
	ic.IAmHere();
}

int main()
{
	AnotherClass ac;
	AndAnotherClass aac;

	PrintOfTypeInterface(ac);
	PrintOfTypeInterface(aac);
}
#endif

#if 0
int main()
{
	// Creating a simple array of integers on the stack
	int intArray[5];
	intArray[0] = 33;
	LOG(intArray[0]);

	// Accessing an index or updating data of array through a pointer
	int* ptr = intArray;
	*(ptr + 1) = 44;
	LOG(intArray[1]);

	// Creating an array on the heap
	int* intArrayOnHeap = new int[5];
	intArrayOnHeap[0] = 22;
	LOG(intArrayOnHeap[0]);
	delete[] intArrayOnHeap;

	// Finding size and count of array located at stack
	int intArray1[5];
	int size = sizeof(intArray1);
	int count = size / sizeof(int);

	// You can't reliably find the size or count of array located on heap,
	// so define it beforehand and it should be static to work,
	// because it has to be a compile time known constant
	static const int sizeOfIntArrayOnHeap = 5;
	int* intArrayOnHeap1 = new int[sizeOfIntArrayOnHeap];
	int count = sizeOfIntArrayOnHeap / sizeof(int);
	delete[] intArrayOnHeap1;

	// C++ 11 standard array, it maintaining the size is considered an overhead,
	// but standard arrays are considered safer and more useful
	std::array<int, 5> standardIntArray;
	int size = standardIntArray.size();
	int count = size / sizeof(int);
}
#endif

#if 0
void PrintString(const std::string& string)
{
	// const meaning we won't change it and,
	// & reference because otherwise it would be a copy
	LOG(string);
}

int main()
{
	// Each string has 1 byte more than the actual length of its characters,
	// because there is a '\0' at the end, to signal the end of the string
	std::string string = "Hello";
	string += " World!";

	// If we declare a char array manually and want it to not print garbage values for unused space,
	// we can specify '\0' meaning null terminator, telling it where to stop, it effects C-style functions,
	// not for loops that iterate over the entire length of the array, for example the strlen function would be effected
	char charArray[5] = { 'd', 'D', '\0', 'A' };
	LOG(strlen(charArray)); // Should print 2 instead of 4 (number of characters) because it ends at index2/size3(uncounted) '\0'

	// Since std::string is an array of const char* therefore,
	// one operand must be std::string for connecting them in serious
	std::string string1 = "Hello" + std::string(" World!");
	std::cout << string << "\n";

	// Or we can use string_literals to make the process easier
	using namespace std::string_literals;
	std::string string1 = "Hello"s + " World!";

	// Find in string, npos means no-position, meaning not found at any position
	bool containsThis = string1.find("ll") != std::string::npos;

	// Different types of strings, in-and-after C++ 11
	const char* cChar = u8""; // 1 byte
	const wchar_t* wcChar = L""; // 2 bytes on Windows, 4 bytes on Linux/Unix(macOS)

	const char16_t* c16Char = u""; // 4 bytes
	const char32_t* c32Char = U""; // 8 bytes

	std::u32string u32String = U""; // And more similar

	// To ignore escape characters we can use row(),
	// here we don't need to do + or \n etc
	const char* ignoreEscape = R"(FF
FF
FF)";
}
#endif

#if 0
class AClass
{
private:
	int x = 1;
	mutable int mX;
public:
	// The first const means return a pointer that cannot be modified, meaning its address
	// The second const means the data on the pointer cannot be modified
	// The third const means members of this class will not be modified in this function,
	// this allows const objects or references of this class to use this function
	const int* const GetX() const
	{
		mX = 1; // We can still change mutable variables inside a const function
		return &x;
	}
};

void AFunction(const AClass& ac)
{
	LOG(*(ac.GetX()));
}

int main()
{
	const int ConstantValue = 11;

	int* ptr = new int(3);

	// Both of the following act the same way,
	// They mean that ptr is a pointer to a constant int
	int const* ptr0 = new int(3);
	const int* ptr1 = new int(3); // I prefer this one, because its easy to understand

	// So we can change the address of ptr, but not the data
	ptr0 = &ConstantValue;

	// This means ptr is a constant pointer to an int
	int* const ptr2 = new int(3);

	// So we can change the data on ptr, but not the address
	*ptr2 = ConstantValue;

	delete ptr;
	delete ptr0;
	delete ptr1;
	delete ptr2;
}
#endif

#if 0
int main()
{
	// Using mutable to copy a variable by value into a lambda,
	// without modifying the original or copying it into another variable
	int aVariable = 10;
	auto aLambda = [=]() mutable
		{
			// This will modify only the lambda's copy of aVariable
			LOG(aVariable++);
		};

	// Here aVariable will not be changed
	aLambda();
}
#endif

#if 0
int main()
{
	int xI = 1;

	// Syntax: something = checkCondition ? ifTrue : ifFalse;

	std::string xS = xI == 0 ? "False" : "True";

	std::string xS1 = xI >= 10 ? "L10" : (xI >= 5 ? "L5" : (xI >= 1 ? "L1" : "L0"));

	LOG(xS);
	LOG(xS1);
}
#endif

#if 0
class AClass
{
public:
	AClass() { LOG("C"); }
	~AClass() { LOG("D"); }
};

int main()
{
	// This will look for 4 bytes of free memory and return a pointer to the start of it
	int* ptr = new int;
	delete ptr;

	// This will look for 20 bytes of free memory and return a pointer to the start of it
	int* ptrArray = new int[4];
	delete[] ptrArray;

	// Using NEW to create class objects automatically calls the class' constructor and destructor
	AClass* acPtr = new AClass;
	delete acPtr;

	// NEW is simply a method that finds a free block of memory of the type or its array,
	// and returns a pointer to the start of it, it works like malloc,
	// but better since malloc doesn't call the constructor or destructor,
	// following is how we can use both together in some cases

	// This will not call the constructor and will only allocate us AClass size of memory
	void* rawMemory = malloc(sizeof(AClass));

	// This will place the AClass obj at rawMemory and will also call the constructor
	AClass* acObj = new(rawMemory) AClass;

	// Manually call the destructor before freeing the memory
	acObj->~AClass();

	free(rawMemory);
}
#endif

#if 0
class AClass
{
	std::string string;
	int integer = -1;
public:
	explicit AClass(const std::string& s)
		: string(s), integer(0)
	{
	}
	explicit AClass(int i)
		: string(""), integer(i)
	{
	}
};

int main()
{
	// Class objects can be created by multiple ways, if there are constructors available to support it,
	// this is because C++ converts the types accordingly, but this should be stopped in rare safety cases
	// so if we don't want this conversion to happen, we can use the explicit keyword to stop it

	// These two won't work if their constructors are explicit
	AClass a1 = std::string("");
	AClass a2 = 20;

	AClass a3("");
	AClass a4(10);

	AClass a5 = AClass("");
	AClass a6 = AClass(30);
}
#endif

#if 0
// These are examples about operator overloading
class AClass
{
public:
	int x = 0, y = 0;

	AClass() {}
	AClass(int _x, int _y) : x(_x), y(_y) {}

	AClass operator+(const AClass& other) const
	{
		return AClass(x + other.x, y + other.y);
	}

	bool operator==(const AClass& other) const
	{
		return ((this->x == other.x) && (this->y == other.y));
	}
};

std::ostream& operator<<(std::ostream& stream, const AClass& other)
{
	stream << other.x << ", " << other.y;
	return stream;
}

int main()
{
	AClass a1;
	a1.x = 1;
	a1.y = 1;

	AClass a2;
	a2.x = 2;
	a2.y = 2;

	AClass a3 = a1 + a2;

	LOG((a1 == a2));

	LOG(a3);
}
#endif

#if 0
// These are examples about smart pointers
class AClass
{
public:
	AClass() { LOG("Constructor"); }
	~AClass() { LOG("Destructor"); }
};

int main()
{
	{
		// shared_ptr gets destroyed when its reference count becomes 0
		std::shared_ptr<AClass> sharedPtr;
		std::weak_ptr<AClass> weakPtr;
		{
			// unique_ptr cannot be copied into another pointer
			std::unique_ptr<AClass> uniquePtr = std::make_unique<AClass>();

			// This method is not recommended due to exception reasons
			std::unique_ptr<AClass> uniquePtr1(new AClass);

			// sharedPtr1 will be deleted when sharedPtr is out of scope as well
			std::shared_ptr<AClass> sharedPtr1 = std::make_shared<AClass>();
			sharedPtr = sharedPtr1;

			// weak_ptr acts as an observer, in the following case,
			// the reference count for sharedPtr1 won't increase,
			// the weakPtr can be used for asking about the sharedPtr1
			weakPtr = sharedPtr1;
		}
		LOG(weakPtr.expired());
	}
}
#endif

#if 0
// This is about copy constructor, if we copy the char* pointer here without allocating new memory,
// the destructor would fail for the copy object since they will both be pointing to the same address,
// therefore we create a copy constructor to allocate new memory to each copy and then copy the contents
class String
{
private:
	char* buffer;
	unsigned int size;
public:
	String(const char* string)			// Default constructor
	{
		size = strlen(string);			// Get the length of string, without null terminator
		buffer = new char[size + 1];	// Allocate memory for characters + null terminator
		memcpy(buffer, string, size);	// Copy only the characters, not null terminator
		buffer[size] = 0;				// Add the null terminator at the end
	}

	String(const String& other)			// Copy constructor
		: size(other.size)
	{
		LOG("String copied");
		buffer = new char[size + 1];
		memcpy(buffer, other.buffer, size);
		buffer[size] = 0;
	}

	~String()
	{
		delete[] buffer;
	}

	friend std::ostream& operator<<(std::ostream& stream, const String& string);
};

std::ostream& operator<<(std::ostream& stream, const String& string)
{
	stream << string.buffer;
	return stream;
}

int main()
{
	String string = "String";
	LOG(string);

	String copy = string;
	LOG(copy);
}
#endif

#if 0
struct AStruct
{
	int i, j, k;
	void Print() { LOG("AStruct"); }
};

struct ScopeAStruct
{
private:
	AStruct* asObj;
public:
	ScopeAStruct(AStruct* as)
		: asObj(as)
	{
	}

	~ScopeAStruct()
	{
		delete asObj;
	}

	AStruct* operator->()
	{
		return asObj;
	}
};

int main()
{
	// Finds the offset of data members in class or struct
	LOG((int)&((AStruct*)nullptr)->i);

	AStruct as;
	as.Print();

	AStruct* asPtr = &as;
	asPtr->Print();

	ScopeAStruct sasPtr = new AStruct();
	sasPtr->Print();
}
#endif

#if 0
struct AStruct
{
	int i, j;
};

std::ostream& operator<<(std::ostream& stream, const AStruct& aStruct)
{
	stream << aStruct.i << ',' << aStruct.j << '\n';
	return stream;
}

int main()
{
	// The inefficient part about std::vector is that each time the vector reaches its capacity,
	// it creates a new larger array and copies the elements over, then deletes the older array,
	// an alternative is to use pointers, but the downside to that is that it will be on the heap,
	// and fragmentaiton can occur, arrays on stack are stored in contiguous memory, better for iterations
	std::vector<AStruct> asVector;

	asVector.push_back({ 1, 2 });
	asVector.push_back({ 3, 4 });

	for (int i = 0; i < asVector.size(); i++)
	{
		LOG(asVector[i]);
	}

	// Remove the vector on index 1
	asVector.erase(asVector.begin() + 1);

	AStruct as;
	as.i = 5;
	as.j = 6;

	asVector.push_back(as);

	for (AStruct& vector : asVector)
	{
		LOG(vector);
	}

	asVector.clear();
}
#endif

#if 0
class AClass
{
public:
	int i;
	AClass(int _i) : i(_i) {}
	AClass(const AClass& ac) : i(ac.i) { LOG("COPY"); }
};

int main()
{
	// Use of reserve: to avoid resizing of vector list resulting in no unecessary copies
	// Use of emplace_back instead of push_back: to avoid creation of temporary objects,
	// this constructs the objects directly inside the list with the provided parameters
	// By these two steps, in the following case we avoid 6 uneccessary copies of AClass
	std::vector<AClass> vector;
	vector.reserve(3);
	vector.emplace_back(1);
	vector.emplace_back(2);
	vector.emplace_back(3);
}
#endif

#if 0
class Singleton
{
public:
	static Singleton& Instance()
	{
		// Because of static we would always get the same instance
		static Singleton instance;
		return instance;
	}

	// Deleting the copy constructor and assignment operator prevents copying
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	void Print() { LOG("Singleton Instance"); }

private:
	// Private constructor prevents object creation
	Singleton() {}
};

int main()
{
	Singleton::Instance().Print();
	Singleton::Instance().Print();

	// Cannot do because we have deleted the constructor and copy constructor
	// Singleton s1(Singleton::Instance());

	// Cannot do because we have deleted the constructor and assignment operator
	// Singleton s2 = Singleton::Instance();
}
#endif
