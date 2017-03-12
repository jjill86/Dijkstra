#include "list.h"
#include "node.h"

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

template <class T>
void l_list<T>::add(T& newguy) {
	if (!cnt) {
		current->elt = newguy;
		first = last = current;
	}
	last->elt = newguy;


	cnt++;
}

template void l_list<int>::add(int& newguy);
template void l_list<node>::add(node& newguy);