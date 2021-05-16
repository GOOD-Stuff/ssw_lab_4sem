#ifndef CLASS_CIRCULAR_BUFFER_H
#define CLASS_CIRCULAR_BUFFER_H

#include <ostream>
#include "List.h"

template <typename T>
class CBuffer
{
private:
	// Base container for CBuffer
	List<T> list;

	// Max number of elements
	size_t max_size;

	// Private move constructor
	CBuffer(List<T>&& lst) : max_size(lst.count()), list(std::move(lst)) {}

public:
	class Iterator;

	explicit CBuffer(size_t capacity) : max_size(capacity) {}

	// Constructor with support initializer list
	CBuffer(const std::initializer_list<T>& lst) : max_size(lst.size()), list(lst) {}

	// Copy constructor
	CBuffer(const CBuffer<T>& buffer) { *this = buffer; }

	// Move constructor
	CBuffer(CBuffer<T>&& buffer) { *this = std::move(buffer); }

	// Add item to back
	void push(T value);

	// Remove first element
	void pop() { list.pop_front(); }

	// Insert element in any position of container
	void insert(const Iterator& it, T value);

	// Remove element from any position of container
	void erase(const Iterator& it) { list.erase(it); }

	// Get iterator to begin buffer
	Iterator begin() const { return reinterpret_cast<Iterator&>(list.begin()); }

	// Get iterator to end buffer
	Iterator end() const { return reinterpret_cast<Iterator&>(list.end()); }

	// Get current elements count
	size_t count() const { return list.count(); }

	// Get max elements count
	size_t max_count() const { return max_size; }

	// Container is empty?
	bool empty() const { return list.empty(); }

	// Delete all items from container
	void clear() { list.clear(); }

	// Individual task 1, variant 3
	CBuffer<T> merge_and_sort(const CBuffer<T>& buffer) { return list.merge_and_sort(buffer.list); }

	// Individual task 2, variant 3
	std::pair<T, T> clear_min_max() { return list.clear_min_max(); }

	// Copy operator
	CBuffer<T>& operator = (const CBuffer<T>& buffer);

	// Move operator
	CBuffer<T>& operator = (CBuffer<T>&& buffer) noexcept;

	// Lexicographic comparison operators
	bool operator == (const CBuffer<T>& buffer) const { return list == buffer.list; }
	bool operator != (const CBuffer<T>& buffer) const { return list != buffer.list; }

	bool operator < (const CBuffer<T>& buffer) const { return list < buffer.list; }
	bool operator > (const CBuffer<T>& buffer) const { return list > buffer.list; }

	bool operator <= (const CBuffer<T>& buffer) const { return list <= buffer.list; }
	bool operator >= (const CBuffer<T>& buffer) const { return list >= buffer.list; }

	// Class for convenient container passage
	class Iterator : public List<T>::Iterator
	{
	public:
		// Don't kill me for this horror...
		Iterator& operator ++ () { return reinterpret_cast<Iterator&>(List<T>::Iterator::operator ++ ()); }
		Iterator operator ++ (int) { return reinterpret_cast<Iterator&>(List<T>::Iterator::operator ++ (0)); }
		Iterator operator + (size_t offset) { return reinterpret_cast<Iterator&>(List<T>::Iterator::operator + (offset)); }
		Iterator& operator -- () { return reinterpret_cast<Iterator&>(List<T>::Iterator::operator -- ()); }
		Iterator operator -- (int) { return reinterpret_cast<Iterator&>(List<T>::Iterator::operator -- (0)); }
		Iterator operator - (size_t offset) { return reinterpret_cast<Iterator&>(List<T>::Iterator::operator - (offset)); }
	};
};

template <typename T>
void CBuffer<T>::push(T value)
{
	list.push_back(value);

	if (list.count() > max_size)
		list.pop_front();
}

template <typename T>
void CBuffer<T>::insert(const Iterator& it, T value)
{
	bool is_begin = const_cast<Iterator&>(it) == begin();

	list.insert(it, value);

	if (list.count() > max_size)
	{
		if (is_begin)
			list.erase(++begin());
		else
			list.pop_front();
	}
}

template <typename T>
CBuffer<T>& CBuffer<T>::operator = (const CBuffer<T>& buffer)
{
	if (&list == this)
		return *this;

	clear();

	max_size = buffer.max_size;
	list = buffer.list;

	return *this;
}

template <typename T>
CBuffer<T>& CBuffer<T>::operator = (CBuffer<T>&& buffer) noexcept
{
	if (&list == this)
		return *this;

	clear();

	max_size = buffer.max_size;
	list = std::move(buffer.list);

	return *this;
}

template <typename T>
std::ostream& operator << (std::ostream& out, const CBuffer<T>& buffer)
{
	for (auto& element : buffer)
		out << element << "\n";

	return out;
}

#endif