#pragma once
#include <iostream>
using namespace std;


template <typename T>
class stack {
private:
	int size;
	T *buffer;
public:
	stack();
	~stack();
	void push(T);       //vstavka elementa v strukturu;
	void pop();         //vytalkivanie elementa iz struktury;
	T peek();           //vozvrat vershiny struktury (verhnego elementa);
	int count();        //vozvrat kolichestva elementov v strukture;
	T sum();            //summy vsekh elementov;
	void display();     //otobrazit';

	friend bool operator ==(stack<T> &arr1, stack<T> &arr2) {  //peregruzka operatora ravno;
		if (arr1.size != arr2.size) {
			return false;
		} else {
		    int i = 0;
			int m = arr1.size;
			while (i < m) {
				if (arr1.buffer[i] != arr2.buffer[i]) return false;
				i++;
			}
			return true;
		}
	};

	friend bool operator !=(stack<T> &arr1, stack<T> &arr2) {  //peregruzka operatora ne ravno;
		return !(arr1 == arr2);
	};

	friend bool operator >(stack<T> &arr1, stack<T>&arr2) {  //peregruzka operatora bol'she;
		int min = 0;
		if (arr1.size < arr2.size) min = arr1.size;
		else min = arr2.size;
		int i = 0;
		while (i < min) {
			if (arr1.buffer[i] < arr2.buffer[i]) return false;
			if (arr1.buffer[i] > arr2.buffer[i]) return true;
			i++;
		}
		return arr1.size > arr2.size;
	};

	friend bool operator >=(stack<T> &arr1, stack<T> &arr2) {  //peregruzka operatora bol'she ili ravno;
		return !(arr1 < arr2);
	};

	friend bool operator < (stack<T> &arr1, stack<T> &arr2) {  //peregruzka operatora men'she;
		int min = 0;
		if (arr1.size < arr2.size) min = arr1.size;
		else min = arr2.size;
		int i = 0;
		while (i < min) {
			if (arr1.buffer[i] > arr2.buffer[i]) return false;
			if (arr1.buffer[i] < arr2.buffer[i]) return true;
			i++;
		}
		return arr1.size < arr2.size;
	};

	friend bool operator <= (stack<T> &arr1, stack<T> &arr2) {  //peregruzka operatora men'she ili ravno;
		return !(arr1 > arr2);
	};
};

template <typename T>
stack<T>::stack() {
	size = 0;
	buffer = new T[size];
};

template <typename T>
stack<T>::~stack() {
	delete[] buffer;
};

template <typename T>
void stack<T>::display() {
	cout << "\nElement output stack\n";
	for (int i = size - 1; i >= 0; i--) {
		cout << buffer[i] << " ";
	};
};

template <typename T>
void  stack<T>::push(T x) {
	T *f = new T[size + 1];
	for (int i = 0; i < size; i++) {
		f[i] = buffer[i];
	};
	f[size] = x;
	delete[] buffer;
	size++;
	buffer = f;
};

template <typename T>
void stack<T>::pop() {
	if (size > 0) {
		T *f = new T[size - 1];
		for (int i = 0; i < size - 1; i++) { 
			f[i] = buffer[i]; 
		};
		delete[] buffer;
		size--;
		buffer = f;
	}
	else cout << "\nStack is empty\n";
};

template <typename T>
T stack<T>::peek() {
	if (size > 0) return buffer[size - 1];
	else cout << "\nStack is empty\n";
};

template <typename T>
int stack<T>::count() {
	return size;
};

template <typename T>
T stack<T>::sum() {
	T s = 0;
	for (int i = 0; i < size; i++) {
		s = s + buffer[i];
	};
	return s;
};
