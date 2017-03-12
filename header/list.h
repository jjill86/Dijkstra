#pragma once

// Linked list class
// elements will have a value of specified type
// and have a pointer to the next element in the list
template <class T>
class l_list{
protected:
	// structure to keep in memory
	typedef struct{
			T elt;
			T* prev;
			T* next;
	} element;
public:
	l_list() :cnt(0), first(nullptr), last(nullptr) {};

	~l_list();

	// add an element to the end of the list
	void add(T);

	element* first; // pointer to the first element of the list
	element* last; // pointer to the last element of the list

	element* current; // pointer to the current element
					  // to always keep track of the list
					  // maybe will be redundand.. we'll see ...

	unsigned int size() const { return cnt; }

private:
	unsigned int cnt;
};

