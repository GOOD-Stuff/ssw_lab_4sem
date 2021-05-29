#include "doubleList.h"

template<class T>
bool isLoop(DoubleList<T>& list) {
    int count = 0;

    for(typename DoubleList<T>::iterator i = list.begin(); i != list.end(); i++) {
        count++;

        if(count > list.count())
            return true;
    }

    return false;
}

template<class T>
typename DoubleList<T>::iterator search(DoubleList<T>& list, T item) {
    if(isLoop(list))
        throw new std::runtime_error("The list should not be looped");

    for(typename DoubleList<T>::iterator i = list.begin(); i != list.end(); i++) {
        if(*i == item)
            return i;
    }

    return nullptr;
}
