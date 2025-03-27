
#if 0
#include "Utils.h"
#include <string>
#include <tuple>
#include <vector>
#include <array>
#include <functional>
#include <thread>
#include <algorithm>
#include <memory>
#endif

#if 0
// Methods to deal with multiple return values
void Function(int* integer, std::string* string)
{
	if (integer) (*integer) = 1;
	if (string) (*string) = "F1";
}

void Function(int& integer, std::string& string)
{
	integer = 2;
	string = "F2";
}

std::tuple<int, std::string> Function()
{
	// return std::tuple<int, std::string>{ 3, "F3" };
	// return std::make_tuple( 3, "F3" );
	return { 3, "F3" };
}

int main()
{
	int integer;
	std::string string;
	Function(&integer, nullptr);
	LOG(integer);

	LOG("");
	Function(integer, string);
	LOG(integer);
	LOG(string);

	LOG("");
	std::tuple<int, std::string> result = Function();
	LOG(std::get<0>(result));
	LOG(std::get<1>(result));

	LOG("");
	std::tie(integer, string) = Function();
	LOG(integer);
	LOG(string);

	LOG("");
	auto aTuple = Function();
	LOG(std::get<int>(aTuple));
	LOG(std::get<std::string>(aTuple));

	// Following is in-and-after C++17
	LOG("");
	auto [anInteger, aString] = Function();
	LOG(anInteger, aString);

	// Other methods can be: returning a struct
	// or an std::pair, there are many methods
}
#endif

#if 0
// Compiled only if called, versions are created of it,
// depending on the type of value provided as argument
template<typename Type>
void Function(Type value)
{
	LOG(value);
}

template<typename Type, int size>
class AClass
{
private:
	Type array[size];
public:
	void Print()
	{
		LOG(typeid(Type).name());
		LOG(size);
	}
};

int main()
{
	Function<int>(1);
	Function("String");
	Function(1.2);

	LOG("");
	AClass<int, 10> ac;
	ac.Print();

	LOG("");
	AClass<std::string, 5> ac1;
	ac1.Print();
}
#endif

#if 0
// Allocation time matters in heap vs stack, stack size is already set as the program starts execution,
// while heap may need to ask the OS for free memory, stack is prefered due to its better cache locality,
// better would be to allocate say 1GB of memory from heap one time, and then work around in that space
#endif

#if 0
int main()
{
	// This is about where the auto keyword can be helpful
	std::vector<int> numbers;
	numbers.push_back(1);
	numbers.push_back(2);

	for (std::vector<int>::iterator it = numbers.begin(); it != numbers.end(); it++)
	{
		LOG(*it);
	}

	LOG("");
	for (auto it = numbers.begin(); it != numbers.end(); it++)
	{
		LOG(*it);
	}

	LOG("");
	for (std::vector<int>::iterator::value_type num : numbers)
	{
		LOG(num);
	}

	LOG("");
	for (auto num : numbers)
	{
		LOG(num);
	}
}
#endif

#if 0
// This is about the standard and raw arrays
template<typename Type, size_t size>
void Function(std::array<Type, size>& arr)
{
	LOG(arr[0]);
	LOG(size);
}

int main()
{
	// Both work kind of the same except,
	// standard array has more features
	std::array<int, 2> arr1;
	arr1[0] = 1;
	Function(arr1);

	int arr2[2];
	arr2[0] = 2;
	LOG(arr2[0]);
}
#endif

#if 0
// This is an example for raw function pointers
void PrintItems(int& item)
{
	LOG(item);
}

void ReplaceItems(int& item)
{
	item = 1;
}

void ForArray(std::vector<int>& vecArray, void(*function)(int&))
{
	for (int& item : vecArray)
	{
		function(item);
	}
}

int main()
{
	std::vector<int> vecArray;
	vecArray = { 1,2,3,4,5 };

	ForArray(vecArray, PrintItems);
	ForArray(vecArray, ReplaceItems);
	ForArray(vecArray, [](int& item) { LOG(item); });
}
#endif

#if 0
// This is an example for lambdas and standard function pointers
void ForArray(const std::vector<int>& vecArray, const std::function<void(int)>& function)
{
	for (auto& item : vecArray)
	{
		function(item);
	}
}

int main()
{
	std::vector<int> vecArray;
	vecArray = { 1,2,3,4,5 };
	int x = 1;

	auto it = std::find_if(vecArray.begin(), vecArray.end(), [&x](int& value) { return value == x; });
	if (it != vecArray.end()) LOG("xFound");
	else LOG("xNotFound");

	auto print = [](int value) { LOG(value); };
	ForArray(vecArray, print);
}
#endif


#if 0
// This is an example about using std::atomic and std::thread
static std::atomic_bool isRunning = true;

void Log()
{
	while (isRunning.load())
	{
		LOG("Running");
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

int main()
{
	std::thread run(Log);

	std::cin.get();

	isRunning.store(false);

	if (run.joinable())
		run.join();

	LOG("Stopped");
}
#endif

#if 0
// This is about the various ways std::chrono can be used
struct Stopwatch
{
	std::string name;
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;

	Stopwatch(std::string _name)
		: name(_name)
	{
		start = std::chrono::high_resolution_clock::now();
	}

	~Stopwatch()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		LOG(name, duration.count() * 1000.0f);
	}
};

void Function()
{
	Stopwatch sw("Function");

	std::string string = "String";

	for (int i = 0; i < 10; i++)
	{
		std::reverse(string.begin(), string.end());
	}
}

int main()
{
	auto start = std::chrono::high_resolution_clock::now();

	Function();

	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> duration = end - start;

	LOG("MainLoop", duration.count() * 1000.0f);
}
#endif

#if 0
// This is about multi-dimensional arrays on stack
int main()
{
	// Arrays can be of any number of dimensions, but above 4D is rarely practical,
	// for example a 10D array would require 10 billion integers and 40GB of memory

	// Arrays till 5D: [Groups][Blocks][Layers][Rows][Columns]

	int arr3D[2][2][2] = {
		{{1,2}, {3,4}},
		{{5,6}, {7,8}}
	};

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				std::cout << "[" << i << "][" << j << "][" << k << "] = " << arr3D[i][j][k] << '\n';
			}
			LOG("");
		}
		LOG("");
	}

	int arr4D[2][2][2][2] = {
		{{{1,2},{3,4}},{{5,6},{7,8}}},
		{{{9,10},{11,12}},{{13,14},{15,16}}}
	};

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				for (int l = 0; l < 2; l++)
				{
					std::cout << "[" << i << "][" << j << "][" << k << "][" << l << "] = " << arr4D[i][j][k][l] << '\n';
				}
				LOG("");
			}
			LOG("");
		}
		LOG("");
	}
}
#endif

#if 0
// This is about multi-dimensional arrays on heap [Todo]

#endif

#if 0
// These are examples for std::sort
int main()
{
	std::vector<int> vec = { 4,1,5,3,2 };

	std::sort(vec.begin(), vec.end());
	for (int& v : vec) LOG(v); LOG("");

	std::sort(vec.begin(), vec.end(), std::greater<int>());
	for (int& v : vec) LOG(v); LOG("");

	std::sort(vec.begin(), vec.end(), [](int& a, int& b) { return a < b; });
	for (int& v : vec) LOG(v); LOG("");

	std::sort(vec.begin(), vec.end(), [](int& a, int& b) {
		if (a == 1)
			return false;
		if (b == 1)
			return true;
		return a < b;
		});
	for (int& v : vec) LOG(v); LOG("");
}
#endif

#if 0
// This is an example about Type Punning, punning is when two pointers point to the same location,
// but represent them as different types, the compiler treats them both as unrelated to each other
struct AStruct
{
	int x, y;
};

int main()
{
	AStruct as{ 11,12 };

	int* positions = (int*)&as;
	int valueOfY = *(int*)((char*)&as + 4);

	LOG(positions[0], positions[1]);
	LOG(valueOfY);
}
#endif

#if 0
// This is about Unions, and is related to Type Punning
union AUnion
{
	// The size of the Union is equal to its largest member,
	// all members share the same memory location,
	// therefore modifying any one member will effect all,
	// and accessing a different member afterwards,
	// may result in Type Punning and undefined behaviour
	char c;
	int i;
};

int main()
{
	AUnion au;
	au.c = 'A';
	LOG(au.c);

	au.i = 2;
	LOG(au.i);
	LOG(au.c);

	LOG(sizeof(au));
}
#endif

#if 0
// This is about where Virtual Destructors are needed
class A
{
public:
	A() { LOG("Constructor A"); }
	virtual ~A() { LOG("Destructor A"); }
};

class B : public A
{
public:
	B() { LOG("Constructor B"); }
	~B() { LOG("Destructor B"); }
};

int main()
{
	A* a = new A();
	delete a;

	LOG("");

	B* b = new B();
	delete b;

	LOG("");

	// In the following part, if the destructor of class A was not marked as virtual, then deleting an object of class B,
	// through the pointer of class A would result in only class A's destructor being executed, causing undefined behaviour
	A* bb = new B();
	delete bb;
}
#endif

#if 0
// This is about Type Casting
int main()
{
	double d = 1.2;
	double dd = (int)d + d;
	LOG(dd);

	// C++ cast, better than the above C-style casting as it provides compile time checks,
	// easy to search through Ctrl+F, and some other checks are possible with it as well
	double ddd = static_cast<int>(d) + d;
	LOG(ddd);
}
#endif

#if 0
// This is about Dynamic Casting
class Food
{
public:
	virtual void Function() {}
};

class Banana : public Food
{
};

class Orange : public Food
{
};

int main()
{
	Banana* banana = new Banana;
	Food* banana_food = banana;
	Food* orange_food = new Orange;

	// Banana* banana1 = (Banana*)orange_food; // No
	// Banana* banana1 = static_cast<Banana*>(orange_food); // No

	Banana* banana1 = dynamic_cast<Banana*>(orange_food);

	if (banana1)
		LOG("True");
	else
		LOG("False");
}
#endif
