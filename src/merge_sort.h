#ifndef MERGE_SORT_INCLUDED_H
#define MERGE_SORT_INCLUDED_H

template <class T>
void merge_sort_array(T* arr, int size)
{
    if (size < 2)
    {
        return;
    }

    merge_sort_array(arr, size / 2);
    merge_sort_array(&arr[size / 2], size - (size / 2));

    T* temp = new T[size];

    int temp_idx = 0;
    int left_idx = 0;
    int right_idx = size / 2;

    while ((left_idx < size / 2) && (right_idx < size))
    {
        temp[temp_idx++] = (arr[left_idx] < arr[right_idx]) ? arr[left_idx++] : arr[right_idx++];
    }

    while (left_idx < size / 2)
    {
        temp[temp_idx++] = arr[left_idx++];
    }

    while (right_idx < size)
    {
        temp[temp_idx++] = arr[right_idx++];
    }

    for (left_idx = 0; left_idx < size; left_idx++)
    {
        arr[left_idx] = temp[left_idx];
    }

    delete[] temp;
}

#endif