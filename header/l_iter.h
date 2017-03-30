#pragma once
using namespace std;

// structure to keep in memory
template <class T, class D>
struct elem {
	T* elt;
	D e_val;
	elem* prev;
	elem* next;
};

// iterator for a extended list 
// it is bidirectional iterator
template <class T, class D>
class l_iter
{
	typedef elem<T, D> element;
public:
	// constructor with list to iterate over
	l_iter(element * e): p(e) {};

	// constructor with existing iterator
	l_iter(l_iter * i): p(i->p) {}

	// destructor
	~l_iter(){ delete p; };

	friend element * operator++(const l_iter);
	friend element * operator--(const l_iter);

	element * p;
};

