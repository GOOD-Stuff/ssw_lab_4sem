#include <iostream>

#ifndef CLASS_DOUBLE_LIST_H
#define CLASS_DOUBLE_LIST_H

template<class T>
struct Node {
    Node<T>* prev;
    Node<T>* next;
    T item;
};

template<class T>
class Iterator {
    private:
        Node<T>* node {nullptr};
    public:
        Iterator(Node<T>* ptr) : node(ptr) {};

        Iterator& operator ++ ()
		{
            if(node == nullptr)
			    throw std::runtime_error("The iterator is empty");

			node = node->next;
			return *this;
		}

		Iterator operator ++ (int)
		{
			if(node == nullptr)
			    throw std::runtime_error("The iterator is empty");

			Node<T>* oldNode = node;
			node = node->next;
			return oldNode;
		}

        Iterator& operator -- ()
		{
            if(node == nullptr)
			    throw std::runtime_error("The iterator is empty");

			node = node->prev;
			return *this;
		}

		Iterator operator -- (int)
		{
			if(node == nullptr)
			    throw std::runtime_error("The iterator is empty");

			Node<T>* oldNode = node;
			node = node->prev;
			return oldNode;
		}

        Iterator operator - (int offset)
		{
			if(node == nullptr)
			    throw std::runtime_error("The iterator is empty");

			Iterator iterator(node);

			for (int i = 0; i < offset; i++)
				iterator--;

			return iterator;
		}

		Iterator operator + (int offset)
		{
			if(node == nullptr)
			    throw std::runtime_error("The iterator is empty");

			Iterator iterator(node);

			for (int i = 0; i < offset; i++)
				iterator++;

			return iterator;
		}

		T operator * ()
		{
			if(node == nullptr)
			    throw std::runtime_error("The iterator is empty");

			return node->item;
		}

		bool operator == (const Iterator& iterator) const {
            return node == iterator.node;
        }

		bool operator != (const Iterator& iterator) const {
            return node != iterator.node;
        }
};

template<class T>
class DoubleList {
    private:
        Node<T>* first {nullptr};
        Node<T>* last {nullptr};
        int size {0};
        Node<T>* getNodeByIndex(int) const;
    public:
        ~DoubleList();
        void pushFront(T);
        void pushBack(T);
        void insert(int, T);
        void erase(int);
        void tie();
        void untie();
        Iterator<T> begin() const;
        Iterator<T> end() const;
        T popFront();
        T popBack();
        int count() const;

        bool operator<(const DoubleList<T>& right);
        bool operator>(const DoubleList<T>& right);
        bool operator==(const DoubleList<T>& right);
        bool operator!=(const DoubleList<T>& right);
        bool operator<=(const DoubleList<T>& right);
        bool operator>=(const DoubleList<T>& right);

    template<class U>
    friend std::ostream& operator<<(std::ostream&, const DoubleList<U>&);
};

template<class T>
void DoubleList<T>::tie() {
    if(first == nullptr || last == nullptr)
        throw new std::runtime_error("List is empty");

    last->next = first;
}

template<class T>
void DoubleList<T>::untie() {
    if(first == nullptr || last == nullptr)
        throw new std::runtime_error("List is empty");

    last->next = nullptr;
}

template<class T>
void DoubleList<T>::pushBack(T item) {
    Node<T>* nodeItem = new Node<T> {last, nullptr, item};

    if(last)
        last->next = nodeItem;

    last = nodeItem;

    if(size++ == 0)
        first = nodeItem;
}

template<class T>
void DoubleList<T>::pushFront(T item) {
    Node<T>* nodeItem = new Node<T> {nullptr, first, item};

    if(first)
        first->prev = nodeItem;

    first = nodeItem;

    if(size++ == 0)
        last = nodeItem;
}

template<class T>
void DoubleList<T>::insert(int index, T item) {
    if(index == 0)
        pushFront(item);
    else if (index == size - 1)
        pushBack(item);
    else {
        Node<T>* currentElementByIndex = getNodeByIndex(index);
        Node<T>* newElementByIndex = new Node<T> {currentElementByIndex->prev, currentElementByIndex, item};
        currentElementByIndex->prev->next = newElementByIndex;
        currentElementByIndex->prev = newElementByIndex;
        size++;
    }
}

template<class T>
void DoubleList<T>::erase(int index) {
    if(index == 0)
        popFront();
    else if (index == size - 1)
        popBack();
    else {
        Node<T>* currentElementByIndex = getNodeByIndex(index);
        currentElementByIndex->prev->next = currentElementByIndex->next;
        currentElementByIndex->next->prev = currentElementByIndex->prev;
        delete currentElementByIndex;
        size--;
    }
}

template<class T>
T DoubleList<T>::popBack() {
    if(size == 0)
        throw new std::runtime_error("List is empty");

    Node<T>* itemNode = last;
    T item = itemNode->item;

    if(itemNode->prev)
        itemNode->prev->next = nullptr;

    last = itemNode->prev;

    if(--size == 0)
        first = nullptr;

    delete itemNode;
    return item;
}

template<class T>
T DoubleList<T>::popFront() {
    if(size == 0)
        throw new std::runtime_error("List is empty");

    Node<T>* itemNode = first;
    T item = itemNode->item;

    if(itemNode->next)
        itemNode->next->prev = nullptr;

    first = itemNode->next;

    if(--size == 0)
        last = nullptr;

    delete itemNode;
    return item;
}

template<class T>
Node<T>* DoubleList<T>::getNodeByIndex(int index) const{
    if(index >= size || index < 0)
        throw new std::runtime_error("Going outside the list");

    int i = 0;
    Node<T>* begin = first;

    while(++i <= index)
        begin = begin->next;

    return begin;
}

template<class T>
int DoubleList<T>::count() const {
    return size;
}

template<class T>
Iterator<T> DoubleList<T>::begin() const {
    return Iterator<T>(first);
}

template<class T>
Iterator<T> DoubleList<T>::end() const {
    return nullptr;
}

template<class T>
DoubleList<T>::~DoubleList() {
    int i = 0;
    Node<T>* begin = first;

    while(++i < size) {
        begin = begin->next;
        delete begin->prev;
    }

    delete begin;
}

template<typename T>
bool DoubleList<T>::operator<(const DoubleList<T>& right) {
    int cnt = (size > right.size) ? right.size : size;

    for(int i = 0; i < cnt; i++) {
        T leftItem = getNodeByIndex(i)->item;
        T rightItem = right.getNodeByIndex(i)->item;

        if(leftItem == rightItem)
            continue;

        return leftItem < rightItem;
    }

    return right.size > size;
}

template<typename T>
bool DoubleList<T>::operator>(const DoubleList<T>& right) {
    int cnt = (size > right.size) ? right.size : size;

    for(int i = 0; i < cnt; i++) {
        T leftItem = getNodeByIndex(i)->item;
        T rightItem = right.getNodeByIndex(i)->item;

        if(leftItem == rightItem)
            continue;

        return leftItem > rightItem;
    }

    return size > right.size;
}

template<typename T>
bool DoubleList<T>::operator==(const DoubleList<T>& right) {
    if(size != right.size)
        return false;

    for(int i = 0; i < size; i++) {
        if(getNodeByIndex(i)->item != right.getNodeByIndex(i)->item)
            return false;
    }

    return true;
}

template<typename T>
bool DoubleList<T>::operator!=(const DoubleList<T>& right) {
    return !(*this == right);
}

template<typename T>
bool DoubleList<T>::operator<=(const DoubleList<T>& right) {
    return (*this == right) || (*this < right);
}

template<typename T>
bool DoubleList<T>::operator>=(const DoubleList<T>& right) {
    return (*this == right) || (*this > right);
}


template<class T>
std::ostream& operator<<(std::ostream& stream, const DoubleList<T>& list) {
    for(int i = 0; i < list.size; i++)
		stream << list.getNodeByIndex(i)->item << " ";

    return stream;
}

#endif
