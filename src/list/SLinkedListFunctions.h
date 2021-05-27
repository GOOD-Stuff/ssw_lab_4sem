#include "SLinkedList.h"

template<typename T>
bool isLoop(SLinkedList<T>& list) {
    int count = 0;

    for(typename SLinkedList<T>::iterator i = list.begin(); i != list.end(); i++) {
        count++;

        if(count > list.count())
            return true;
    }

    return false;
}

template<typename T>
typename SLinkedList<T>::iterator search(SLinkedList<T>& list, T item) {
    if(isLoop(list))
        throw new std::runtime_error("The list should not be looped");

    for(typename SLinkedList<T>::iterator i = list.begin(); i != list.end(); i++) {
        if(*i == item)
            return i;
    }

    return nullptr;
}
