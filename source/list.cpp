#include "list.h"

template <class T> 
l_list<T>::~l_list()
{
	if (first){
		current = first->next;
		while (next) {
			next = current->next;
			delete current;
			current = next;
		}
	}
}

template <class T>
void l_list<T>::add(T newguy) {
	cnt++;
	element e;
	e.elt = newguy;
	e.prev = last;
	e.next = nullptr;
	last->next = *e;
}