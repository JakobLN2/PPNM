#ifndef HAVE_GENLIST_H
#define HAVE_GENLIST_H
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#define SELF (*this)
#define FOR(i) for(int i=0;i<Size;i++)

template < typename T > class genlist {

private: int Size, Size_cap; T *data; /* C-array */
public : const int& size=Size;

T& operator[](int i){
	assert(i >= 0 && i < Size);
	return data[i];
	}

genlist() { /* default ctor */
	data = nullptr;
	Size = 0;
	}

genlist(genlist& other){ /* copy ctor */
	Size=other.size;
	data = new T[Size]();
	FOR(i) SELF[i]=other[i];
	}

genlist(genlist&&) = delete; /* move ctor */

~genlist() { /* dtor */
	delete[] data;
	Size = 0;
	}

genlist& operator=(genlist& other){ /* copy assignment */
	SELF.~genlist();
	Size=other.size;
	data = new T[Size]();
	FOR(i) SELF[i]=other[i];
	return SELF;
	}

genlist& operator=(genlist&&) = delete; /* move assignment */

void add(T item) {
	// T *newdata = new T[Size+1](); //Create new list with space for the element
	// FOR(i)newdata[i]=data[i]; //Copy previous data into new list, FOR(i) is a for-loop defined in the top of the file
	// newdata[Size] = item; //Add the final element to the end of the new list
	// Size++;
	// delete[] data; //Delete old list
	// data=newdata;
	
	if(Size == Size_cap) { //There is no more capacity in the list, create a new one with double the capacity
		Size_cap *= 2;
		T *newdata = new T[Size_cap](); //Create new list with space for the element
		FOR(i)newdata[i]=data[i]; //Copy previous data into new list, FOR(i) is a for-loop defined in the top of the file
		newdata[Size] = item; //Add the final element to the end of the new list
		Size++;
		delete[] data; //Delete old list
		data=newdata;
	} else { //We still have leftover spaces
		data[Size] = item;
		Size++;
	}

	}

void remove(int i) {
	T *newdata = new T[Size - 1]();
	for(int j = 0; j < i; ++j) newdata[j] = data[j];
	for(int j = i + 1; j < Size; ++j) newdata[j - 1] = data[j];
	Size--;
	delete[] data;
	data = newdata;
	}

	void print() { //Very simple print function for simple T, I don't want to think too much about it.
		for(int i = 0; i < Size ; ++i) std::cout << data[i] << "  ";
		std::cout << std::endl;
	}

};
#endif