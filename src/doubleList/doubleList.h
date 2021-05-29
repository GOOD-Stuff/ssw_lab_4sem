#include <iostream>

#ifndef CLASS_DOUBLE_LIST_H
#define CLASS_DOUBLE_LIST_H

template<class T>
class DoubleList {
    private:
        struct Node {
            Node* prev;
            Node* next;
            T item;
        };

        Node* first {nullptr};
        Node* last {nullptr};
        int size {0};
        Node* getNodeByIndex(int) const;
    public:
        class iterator;
	    friend class iterator;

        ~DoubleList();
        void pushFront(T);
        void pushBack(T);
        void insert(int, T);
        void erase(int);
        void tie();
        void untie();
        iterator begin() const;
        iterator end() const;
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

        class iterator {
            private:
                Node* node {nullptr};
            public:
                iterator(Node* ptr) : node(ptr) {};

                iterator& operator ++ ()
        		{
                    if(node == nullptr)
        			    throw std::runtime_error("The iterator is empty");

        			node = node->next;
        			return *this;
        		}

        		iterator operator ++ (int)
        		{
        			if(node == nullptr)
        			    throw std::runtime_error("The iterator is empty");

        			Node* oldNode = node;
        			node = node->next;
        			return oldNode;
        		}

                iterator& operator -- ()
        		{
                    if(node == nullptr)
        			    throw std::runtime_error("The iterator is empty");

        			node = node->prev;
        			return *this;
        		}

        		iterator operator -- (int)
        		{
        			if(node == nullptr)
        			    throw std::runtime_error("The iterator is empty");

        			Node* oldNode = node;
        			node = node->prev;
        			return oldNode;
        		}

                iterator operator - (int offset)
        		{
        			if(node == nullptr)
        			    throw std::runtime_error("The iterator is empty");

        			iterator iterator(node);

        			for (int i = 0; i < offset; i++)
        				iterator--;

        			return iterator;
        		}

        		iterator operator + (int offset)
        		{
        			if(node == nullptr)
        			    throw std::runtime_error("The iterator is empty");

        			iterator iterator(node);

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

        		bool operator == (const iterator& iterator) const {
                    return node == iterator.node;
                }

        		bool operator != (const iterator& iterator) const {
                    return node != iterator.node;
                }
        };
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
    Node* nodeItem = new Node {last, nullptr, item};

    if(last)
        last->next = nodeItem;

    last = nodeItem;

    if(size++ == 0)
        first = nodeItem;
}

template<class T>
void DoubleList<T>::pushFront(T item) {
    Node* nodeItem = new Node {nullptr, first, item};

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
        Node* currentElementByIndex = getNodeByIndex(index);
        Node* newElementByIndex = new Node {currentElementByIndex->prev, currentElementByIndex, item};
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
        Node* currentElementByIndex = getNodeByIndex(index);
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

    Node* itemNode = last;
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

    Node* itemNode = first;
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
typename DoubleList<T>::Node* DoubleList<T>::getNodeByIndex(int index) const{
    if(index >= size || index < 0)
        throw new std::runtime_error("Going outside the list");

    int i = 0;
    Node* begin = first;

    while(++i <= index)
        begin = begin->next;

    return begin;
}

template<class T>
int DoubleList<T>::count() const {
    return size;
}

template<class T>
typename DoubleList<T>::iterator DoubleList<T>::begin() const {
    return iterator(first);
}

template<class T>
typename DoubleList<T>::iterator DoubleList<T>::end() const {
    return nullptr;
}

template<class T>
DoubleList<T>::~DoubleList() {
    int i = 0;
    Node* begin = first;

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
