
#if 0
#include "Utils.h"
#endif

#if 0
// This is a part replica of std::array
template<typename Type, size_t Size>
class Array
{
private:
	Type _data[Size];

public:
	constexpr size_t size() const { return Size; }

	Type& operator[](size_t index) { return _data[index]; }

	const Type& operator[](size_t index) const { return _data[index]; }

	Type* begin() { return _data; }

	const Type* begin() const { return _data; }

	Type* end() { return _data + Size; }

	const Type* end() const { return _data + Size; }
};

int main()
{
	Array<int, 3> arr;

	std::fill(arr.begin(), arr.end(), 1);

	for (int i = 0; i < arr.size(); i++) LOG(arr[i]);
}
#endif


#if 0
// This is a part replica of std::vector
template<typename Vector>
class VectorIterator
{
public:
	using ValueType = typename Vector::ValueType;

private:
	ValueType* _ptr;

public:
	VectorIterator(ValueType* ptr)
		: _ptr(ptr)
	{
	}

	VectorIterator& operator++() {
		_ptr++;
		return *this;
	}

	VectorIterator operator++(int) {
		VectorIterator iterator = *this;
		++(*this);
		return iterator;
	}

	VectorIterator& operator--() {
		_ptr--;
		return *this;
	}

	VectorIterator operator--(int) {
		VectorIterator iterator = *this;
		--(*this);
		return iterator;
	}

	ValueType& operator[](int index) { return *(_ptr + index); }

	ValueType* operator->() { return _ptr; }

	ValueType& operator*() { return *_ptr; }

	bool operator==(const VectorIterator& other) const { return _ptr == other._ptr; }

	bool operator!=(const VectorIterator& other) const { return !(*this == other); }
};

template<typename T>
class Vector
{
public:
	using ValueType = T;
	using Iterator = VectorIterator<Vector<T>>;

private:
	T* _data = nullptr;
	size_t _size = 0;
	size_t _capacity = 0;

	void ReAlloc(size_t newCapacity)
	{
		T* newBlock = (T*)::operator new(newCapacity * sizeof(T));

		if (newCapacity < _size)
			_size = newCapacity;

		for (size_t i = 0; i < _size; i++)
			new (&newBlock[i]) T(std::move(_data[i]));

		for (size_t i = 0; i < _size; i++)
			_data[i].~T();

		::operator delete(_data, _capacity * sizeof(T));
		_data = newBlock;
		_capacity = newCapacity;
	}

public:
	Vector() {
		ReAlloc(2);
	}

	~Vector() {
		clear();
		::operator delete(_data, _capacity * sizeof(T));
	}

	void pushback(const T& value) {
		if (_size >= _capacity)
			ReAlloc(_capacity + _capacity / 2);

		_data[_size] = value;
		_size++;
	}

	void pushback(T&& value) {
		if (_size >= _capacity)
			ReAlloc(_capacity + _capacity / 2);

		_data[_size] = std::move(value);
		_size++;
	}

	template<typename... Args>
	T& emplaceback(Args&&... args) {
		if (_size >= _capacity)
			ReAlloc(_capacity + _capacity / 2);

		new(&_data[_size]) T(std::forward<Args>(args)...);
		return _data[_size++];
	}

	void popback() {
		if (_size > 0) {
			_size--;
			_data[_size].~T();
		}
	}

	void clear() {
		for (size_t i = 0; i < _size; i++)
			_data[i].~T();
		_size = 0;
	}

	Iterator begin() { return Iterator(_data); }

	Iterator end() { return Iterator(_data + _size); }

	size_t size() const { return _size; }

	T& operator[](size_t index) { return _data[index]; }

	const T& operator[](size_t index) const { return _data[index]; }
};

template<typename T>
void PrintVector(const Vector<T>& vector)
{
	for (size_t i = 0; i < vector.size(); i++)
		LOG(vector[i]);
}

struct Vector3
{
	int x = 0.0f, y = 0.0f, z = 0.0f;
	int* mBlock = nullptr;

	Vector3() {
		mBlock = new int[4];
	}

	Vector3(float scaler)
		: x(scaler), y(scaler), z(scaler)
	{
		mBlock = new int[4];
	}

	Vector3(float x, float y, float z)
		: x(x), y(y), z(z)
	{
		mBlock = new int[4];
	}

	/*
	Vector3(const Vector3& other)
		: x(other.x), y(other.y), z(other.z)
	{
		LOG("Vector3 Copied");
	}
	*/

	Vector3(Vector3&& other) noexcept
		: x(other.x), y(other.y), z(other.z)
	{
		LOG("Vector3 Moved");
		mBlock = other.mBlock;
		other.mBlock = nullptr;
	}

	/*
	Vector3& operator=(const Vector3& other)
	{
		LOG("Vector3 Copied");
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
	*/

	Vector3& operator=(Vector3&& other) noexcept
	{
		LOG("Vector3 Moved");
		mBlock = other.mBlock;
		other.mBlock = nullptr;
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	~Vector3() {
		LOG("Vector3 Destroyed");
		delete[] mBlock;
	}
};

template<>
void PrintVector(const Vector<Vector3>& vector)
{
	for (size_t i = 0; i < vector.size(); i++)
		LOG(vector[i].x, vector[i].y, vector[i].z);
}

int main()
{
#if 0
	Vector<std::string> vector;

	vector.pushback("First");
	vector.pushback("Second");
	vector.pushback("Third");

	PrintVector(vector);
#endif

#if 0
	Vector<Vector3> vector;

	vector.pushback(Vector3(1.0f));
	vector.pushback(Vector3(2, 3, 4));
	vector.pushback(Vector3());

	PrintVector(vector);
#endif

#if 0
	Vector<Vector3> vector;

	vector.emplaceback(1.0f);
	vector.emplaceback(2, 3, 4);
	vector.emplaceback();

	PrintVector(vector);
#endif

#if 0
	Vector<Vector3> vector;

	vector.emplaceback(1.0f);
	vector.emplaceback(2.0f);
	vector.popback(); LOG("popback");
	PrintVector(vector);

	vector.clear(); LOG("clear");
	PrintVector(vector);

	vector.pushback(Vector3(3));
	vector.emplaceback(4.0f);
	PrintVector(vector);
#endif

#if 1
	Vector<std::string> vector;
	vector.emplaceback("First");
	vector.emplaceback("Second");
	vector.emplaceback("Third");

	for (auto vec : vector) LOG(vec);
#endif
}
#endif
