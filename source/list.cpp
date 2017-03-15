#include "list.h"
#include "node.h"

template <class T>
l_list<T>::l_list() :cnt(0), first(nullptr), last(nullptr), current(nullptr){

};
template l_list<int>::l_list();
template l_list<node>::l_list();

// destructor - is going through all the chain and deleting
// elements that were created with "new" operator
// !!! this is to be updated and verified that it works correctly
template <class T> 
l_list<T>::~l_list()
{
	if (first){
		current = first;
		while (current) {
			element* tmp = current;
			current = tmp->next;
			delete tmp;
		}
	}
}
template l_list<int>::~l_list();
template l_list<node>::~l_list();


// Add a new item to the end of the linked list
template <class T>
void l_list<T>::add(T& newguy) {
	// allocating memory for the new element
	current = new element();
	current->elt = new T(newguy);

	// if this is a first entry
	// all internal pointers should be identical
	// and point to null 
	if (!cnt) {
		current->prev = nullptr;
		first = last = current;
	}
	// if this is a second element
	// update the "first" pointer to point at it
	if (cnt == 1){
		first->next = current;
		current->prev = last;
		last = current;
	}

	//all the next elements 
	// update the pointer of the "last" pointer
	else {
		last->next = current;
		current->prev = last;
		last = current;
	}
	current->next = nullptr;

	//increase counter
	cnt++;
}

template void l_list<int>::add(int& newguy);
template void l_list<node>::add(node& newguy);

// add an array of pointers to the element
// to the end of linked list
template <class T>
void l_list<T>::add(T* elms, unsigned int amt){
	if (amt <= 0) return;
	try{
		for (unsigned int i = 0; i < amt; i++){
			this->add(elms[i]);
		}
	}
	catch (...){
		cout << "Error adding array of elements to the linked list. Check the array content" << endl;
	}
}
template void l_list<int>::add(int* elms, unsigned int amt);
template void l_list<node>::add(node* elms, unsigned int amt);
