#pragma once
#include <ostream>
using namespace std;
// Extended Linked list class. Will take 2 values
// Made to replace a structure of node+edge value
// elements will keep 2 values of specified type,
// and have a pointer to the next element in the list
template <class T, class D>
class le_list{
protected:
	// structure to keep in memory
	struct element {
		T* elt;
		D e_val;
		element* prev;
		element* next;
	};
public:
	le_list() :cnt(0),sum_val(0.0), first(nullptr), last(nullptr), current(nullptr){};
	~le_list(){
		if (first){
			current = first;
			while (current) {
				element* tmp = current;
				current = tmp->next;
				delete tmp;
			}
		}
	};

	// add an element(s) to the end of the list
	void add(T&elm, D&val) {
		// allocating memory for the new element
		current = new element();
		current->elt = new T(elm);
		current->e_val = val;

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
		sum_val += val;
	}; // add a single element

	void add(T*&elm, D*val){
		this->add(*elm,*val);
	}; // add a single element by pointer

	void add(T*&elm, D val){
		this->add(*elm, val);
	}; // add a single element by pointer

	// print out the chain
	void print(){
		element* next;
		next = first;
		while (next != nullptr){
			cout << "[" << *(next->elt) << ":" << next->e_val << "]";
			if (next != last) cout << "->";
			next = next->next;
		}
		cout << endl;
	};


	unsigned int size() const { return cnt; }
	double sum() const { return sum_val; }
	T head()const{ return *(first->elt); }
	T end()const{ return *(last->elt); }

public:
	// print out operator by object
	friend ostream& operator<<(ostream& out, const le_list& lhs){
		element* iter;
		iter = lhs.first;
		while (iter != nullptr){
			cout << "[" << *(iter->elt) << ":" << iter->e_val << "]";
			if (iter != lhs.last) out << "->";
			iter = iter->next;
		}
		return out;
	}

private:
	unsigned int cnt;
	double sum_val;
	element* first; // pointer to the first element of the list
	element* last; // pointer to the last element of the list

	element* current; // pointer to the current element
	// used internally to allocate new elements

};

