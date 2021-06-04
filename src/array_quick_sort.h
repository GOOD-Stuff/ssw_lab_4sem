#ifndef ARRAY_QUICK_SORT_H
#define ARRAY_QUICK_SORT_H

template <typename T>
void array_quick_sort(T* array, int count)
{
	T& center = array[count / 2];

	int i = 0;
	int j = count - 1;

	do {
		while (array[i] < center) {
			i++;
		}

		while (array[j] > center) {
			j--;
		}

		if (i <= j) {
			T temp = array[i];
			array[i++] = array[j];
			array[j--] = temp;
		}
	} while (i <= j);

	if (j > 0) {
		array_quick_sort<T>(array, j + 1);
	}

	if (i < count) {
		array_quick_sort<T>(array + i, count - i);
	}
}

#endif