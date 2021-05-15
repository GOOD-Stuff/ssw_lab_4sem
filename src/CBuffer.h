#ifndef CLASS_CIRCULAR_BUFFER_H
#define CLASS_CIRCULAR_BUFFER_H

#include <ostream>
#include <stdexcept>
#include <memory>
#include <functional>

template <typename T>
class CBuffer
{
private:
	class Iterator;
	friend class Iterator;

	static void throw_if(bool condition, const char* message);
	size_t get_idx_by_it(const Iterator& it);

	std::unique_ptr<T[]> storage;

	size_t size {0};
	size_t max_size;

public:
	CBuffer(size_t capacity);
	CBuffer(const std::initializer_list<T>& list);

	CBuffer(const CBuffer<T>& buffer) { *this = buffer; }
	CBuffer(CBuffer<T>&& buffer) { *this = std::move(buffer); }

	void push(T value);
	void pop();

	void insert(const Iterator& it, T value);
	void erase(const Iterator& it);

	Iterator begin() const { return storage.get(); }
	Iterator end() const { return storage.get() + size; }

	size_t count() { return size; }
	size_t max_count() { return max_size; }

	bool empty() { return size == 0; }
	void clear();

	static CBuffer<T> merge_and_sort(const CBuffer<T>& buffer_1, const CBuffer<T>& buffer_2);
	CBuffer<T> merge_and_sort(const CBuffer<T>& buffer);

	std::pair<T, T> clear_min_max();

	CBuffer<T>& operator = (const CBuffer<T>& buffer);
	CBuffer<T>& operator = (CBuffer<T>&& buffer) noexcept;

	bool operator == (const CBuffer<T>& buffer);
	bool operator != (const CBuffer<T>& buffer);

	bool operator < (const CBuffer<T>& buffer);
	bool operator > (const CBuffer<T>& buffer);

	bool operator <= (const CBuffer<T>& buffer);
	bool operator >= (const CBuffer<T>& buffer);


	class Iterator
	{
	private:
		friend class CBuffer<T>;
		// Pointer to a container cell
		T* ptr {nullptr};

		Iterator(T* p) : ptr(p) {}

	public:
		Iterator() = default;

		// Prefix operator ++
		Iterator& operator ++ ()
		{
			throw_if(ptr == nullptr, "Trying to work with empty pointer!");

			ptr++;
			return *this;
		}

		// Postfix operator ++
		Iterator operator ++ (int)
		{
			throw_if(ptr == nullptr, "Trying to work with empty pointer!");

			T* old_ptr = ptr;
			ptr++;
			return old_ptr;
		}

		// Shift operator
		Iterator operator + (size_t offset)
		{
			throw_if(ptr == nullptr, "Trying to work with empty pointer!");

			Iterator it(ptr);

			for (size_t i = 0; i < offset; i++)
				++it;

			return it;
		}

		// Prefix operator --
		Iterator& operator -- ()
		{
			throw_if(ptr == nullptr, "Trying to work with empty pointer!");

			return *this;
		}

		// Postfix operator --
		Iterator operator -- (int)
		{
			throw_if(ptr == nullptr, "Trying to work with empty pointer!");

			T* old_ptr = ptr;
			return old_ptr;
		}

		// Shift operator
		Iterator operator - (size_t offset)
		{
			throw_if(ptr == nullptr, "Trying to work with empty pointer!");

			Iterator it(ptr);

			for (size_t i = 0; i < offset; i++)
				--it;

			return it;
		}

		// Operator for getting data
		T& operator * ()
		{
			throw_if(ptr == nullptr, "Trying to work with empty pointer!");
			return *ptr;
		}

		// Comparison operators
		bool operator == (const Iterator& it) { return ptr == it.ptr; }
		bool operator != (const Iterator& it) { return ptr != it.ptr; }
	};
};

template <typename T>
CBuffer<T>::CBuffer(size_t capacity)
{
	max_size = capacity;
	storage = std::unique_ptr<T[]>(new T[max_size]);
}

template <typename T>
CBuffer<T>::CBuffer(const std::initializer_list<T>& list) : CBuffer(list.size())
{
	for (auto& element : list)
		push(element);
}

template <typename T>
void CBuffer<T>::push(T value)
{
	insert(end(), value);
}

template <typename T>
void CBuffer<T>::pop()
{
	erase(begin());
}

template <typename T>
void CBuffer<T>::insert(const Iterator& it, T value)
{
	size_t idx = get_idx_by_it(it);

	if (++size <= max_size)
		for (size_t i = size - 1; i > idx; i--)
			storage.get()[i] = storage.get()[i - 1];
	else
	{
		for (size_t i = 0; i < idx; i++)
			storage.get()[i] = storage.get()[i + 1];

		size = max_size;
	}

	if (idx == size)
		idx--;

	storage.get()[idx] = value;
}

template <typename T>
void CBuffer<T>::erase(const Iterator& it)
{
	size_t idx = get_idx_by_it(it);

	for (size_t i = idx; i < size; i++)
		storage.get()[i] = storage.get()[i + 1];

	size--;
}

template <typename T>
void CBuffer<T>::clear()
{
	while (size != 0)
		pop();
}

template <typename T>
CBuffer<T> CBuffer<T>::merge_and_sort(const CBuffer<T>& buffer_1, const CBuffer<T>& buffer_2)
{
	CBuffer<T> buffer(buffer_1.size + buffer_2.size);

	for (auto& element : buffer_1)
		buffer.push(element);

	for (auto& element : buffer_2)
		buffer.push(element);

	std::function<void(T*, int)> sort = [&](T* buff, int size)
	{
		int i = 0;
		int j = size - 1;

		T& mid = buff[size / 2];

		do
		{
			while (buff[i] < mid)
				i++;

			while (buff[j] > mid)
				j--;

			if (i <= j)
				std::swap(buff[i++], buff[j--]);
		}
		while (i <= j);

		if (j > 0)
			sort(buff, j + 1);

		if (i < size)
			sort(buff + i, size - i);
	};

	sort(buffer.storage.get(), buffer.size);
	return buffer;
}

template <typename T>
CBuffer<T> CBuffer<T>::merge_and_sort(const CBuffer<T>& buffer)
{
	return merge_and_sort(*this, buffer);
}

template <typename T>
std::pair<T, T> CBuffer<T>::clear_min_max()
{
	std::pair<T, T> pair;

	Iterator min_it = begin();

	for (auto it = begin() + 1; it != end(); ++it)
		if (*it < *min_it)
			min_it = it;

	pair.first = *min_it;
	erase(min_it);

	Iterator max_it = begin();

	for (auto it = begin() + 1; it != end(); ++it)
		if (*it > *max_it)
			max_it = it;

	pair.second = *max_it;
	erase(max_it);

	return pair;
}

template <typename T>
CBuffer<T>& CBuffer<T>::operator = (const CBuffer<T>& buffer)
{
	if (&buffer == this)
		return *this;

	clear();
	max_size = buffer.max_size;

	for (auto& element : buffer)
		push(element);

	return *this;
}

template <typename T>
CBuffer<T>& CBuffer<T>::operator = (CBuffer<T>&& buffer) noexcept
{
	if (&buffer == this)
		return *this;

	clear();

	storage = std::move(buffer.storage);
	size = buffer.size;
	max_size = buffer.max_size;

	return *this;
}

template <typename T>
bool CBuffer<T>::operator == (const CBuffer<T>& buffer)
{
	if (&buffer == this)
		return true;

	if (size != buffer.size)
		return false;

	auto this_begin = begin();
	auto buffer_begin = buffer.begin();

	while (this_begin != end() && buffer_begin != buffer.end())
		if (*(this_begin++) != *(buffer_begin++))
			return false;

	return true;
}

template <typename T>
bool CBuffer<T>::operator != (const CBuffer<T>& buffer)
{
	return !(*this == buffer);
}

template <typename T>
bool CBuffer<T>::operator < (const CBuffer<T>& buffer)
{
	if (&buffer == this)
		return false;

	auto this_begin = begin();
	auto buffer_begin = buffer.begin();

	while (this_begin != end() && buffer_begin != buffer.end())
	{
		T& this_value = *(this_begin++);
		T& buffer_value = *(buffer_begin++);

		if (this_value != buffer_value)
			return this_value < buffer_value;
	}

	return size < buffer.size;
}

template <typename T>
bool CBuffer<T>::operator > (const CBuffer<T>& buffer)
{
	return !(*this < buffer) && *this != buffer;
}

template <typename T>
bool CBuffer<T>::operator <= (const CBuffer<T>& buffer)
{
	return *this < buffer && *this == buffer;
}

template <typename T>
bool CBuffer<T>::operator >= (const CBuffer<T>& buffer)
{
	return *this > buffer && *this == buffer;
}

template <typename T>
void CBuffer<T>::throw_if(bool condition, const char* message)
{
	if (condition)
		throw std::runtime_error(message);
}

template <typename T>
size_t CBuffer<T>::get_idx_by_it(const Iterator& it)
{
	int idx = it.ptr - storage.get();
	
	if (idx < 0)
		idx *= -1;

	return idx;
}

template <typename T>
std::ostream& operator << (std::ostream& out, const CBuffer<T>& buffer)
{
	for (auto& element : buffer)
		out << element << "\n";

	return out;
}

#endif