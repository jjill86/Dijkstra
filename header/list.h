#pragma once
#include <ostream>
using namespace std;
// Linked list class
// elements will have a value of specified type
// and have a pointer to the next element in the list
template <class T>
class l_list{
protected:
	// structure to keep in memory
	struct element {
			T* elt;
			element* prev;
			element* next;
	};
public:
	l_list();
	~l_list();

	// add an element to the end of the list
	void add(T&);

	// print out the chain
	void print(){
		element* next;
		next = first;
			while (next!=nullptr){
				cout << *(next->elt);
				if (next != last) cout << "->";
				next = next->next;
			}
			cout << endl;
	};


	unsigned int size() const { return cnt; }
	T head()const{ return *(first->elt); }
	T end()const{ return *(last->elt); }

public:
	// print out operator by object
	friend ostream& operator<<(ostream& out, const l_list& lhs){
		element* iter;
		iter = lhs.first;
		while (iter != nullptr){
			out << *(iter->elt);
			if (iter != lhs.last) out << "->";
			iter = iter->next;
		}
		return out;
	}

	// print out operator by pointer to the object
//	friend ostream& operator<<(ostream& out, const l_list* lhs){
//		out << *lhs;
//		return out;
//	}

private:
	unsigned int cnt;
	element* first; // pointer to the first element of the list
	element* last; // pointer to the last element of the list

	element* current; // pointer to the current element
	// used internally to allocate new elements

};

