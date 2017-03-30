#pragma once
#include <ostream>
#include "node.h"
using namespace std;

// Extended Linked list class. Will take 2 values
// Made to replace a structure of node+edge value
// elements will keep 2 values of specified type,
// and have a pointer to the next element in the list
template <class T, class D>
class le_list{
	typedef struct element {
		T* elt;
		D e_val;
		element* prev;
		element* next;
	};
public:
	le_list() :cnt(0),sum_val(0.0),cur_pos(0),first(nullptr), 
			   last(nullptr), current(nullptr){};
	le_list(T* elt, D val = 0) :cnt(0), sum_val(0), cur_pos(0), 
		first(nullptr), last(nullptr), current(nullptr){
		this->add(elt, val);
	};

	~le_list(){
		if (first){
			current = first;
			while (current) {
				element* tmp = current;
				current = current->next;
				delete tmp->elt;
				delete tmp;
			}
		}
	};

	typedef node::ngb member;

	// add an element(s) to the beginning of the list
	void push(T&elm, D&val) {
		// allocating memory for the new element
		current = new element();
		current->elt = new T(elm);
		current->e_val = val;

		// if this is a first entry
		// all internal pointers should be identical
		// and point to null 
		if (!cnt) {
			current->next = nullptr;
			current->prev = nullptr;
			first = last = current;
		}
		
		// if this is a second element
		// update it to be "first" element
		else if (cnt == 1){
			last->prev = current;
			current->next = last;
			first = current;
		}

		//all the next elements 
		// update the pointer of the "first" pointer
		else {
			first->prev = current;
			current->next = first;
			first = current;
		}
		current->prev = nullptr;

		//increase counter
		cnt++;
		cur_pos = 0;
		sum_val += val;
	}; // add a single element

	// add a single element to the front by pointer
	void push(T*&elm, D*val){
		this->push(*elm, *val);
	};

	// add a single element to the front by pointer
	void push(T*&elm, D val){
		this->push(*elm, val);
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
		cur_pos=cnt;
		sum_val += val;
	}; // add a single element

	// add a single element by pointer
	void add(T*&elm, D*val){
		this->add(*elm,*val);
	};

	// add a single element by pointer
	void add(T*&elm, D val){
		this->add(*elm, val);
	}; // add a single element by pointer

	// add an element as a pointer to a stucture
	void add(member* m){
		this->add(m->n, m->mass);
	}
	// add an element as a stucture
	void add(member& m){
		this->add(m.n, m.mass);
	}
	// add an array of elements to the list
	void add(member elts[], int amt){
		if (amt <= 0) return;
		for (int i = 0; i < amt; i++){
			this->add(elts[i]);
		}
	}

// =============== adding elements and sorting them =============
	void add_sort(member &m, D base_len=0.0){
		m.mass += base_len;
		if (this->is_duplicate(m, true)) return;
		if (current == nullptr) this->add(m);// adding first element
		else if (current == last && m.mass > current->e_val) this->add(m); // adding the largest element
		else if (current == first && m.mass <= current->e_val) this->push(m.n, m.mass); // addding the smallest element		
		else if (m.mass > current->e_val && m.mass <= current->next->e_val) {
			this->insert(m);
		}
		else if (m.mass <= current->e_val){
			this->rew();
			this->add_sort(m);
			return;
		}
		else if (m.mass > current->e_val){
			this->fwd();
			this->add_sort(m);
			return;
		}
		else {
			cout << "add_sort: this one slipped! " << m.n << endl;
		}
		return;
	}
	void add_sort(member *m){
		this->add_sort(*m);
	}

	// find if there'an element with a higher or equal e_val value in the list
	// remove it if remove parameter is true
	bool is_duplicate (member& m, bool remove = false){
		element *tmp = this->first;
		while (tmp){
			if (m.n->name == tmp->elt->name){
				if (m.mass < tmp->e_val){
					if (remove){
						current = tmp;
						this->remove();
					}
					return false;
				}
				else return true;
			}
			tmp = tmp->next;
		}
		return false;
	}
	
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

	// print out operator by object
	friend ostream& operator<<(ostream& out, const le_list& lhs){
		element* iter;
		iter = lhs.first;
		while (iter != nullptr){
			if (iter == lhs.current) cout << "^";
			cout << "[" << *(iter->elt) << ":" << iter->e_val << "]";
			if (iter != lhs.last) out << "->";
			iter = iter->next;
		}
		return out;
	}

	// return size of the list
	unsigned int size() const { return cnt; }

	// return the total sum of all nodes
	double sum() const { return sum_val; }

private:
	// advance iterator (which is "current" member of the class)
	const element* fwd(const int n=1){
		if (n<0) this->rew(n * -1);
		if (n<1 && (cur_pos + n)>cnt) throw -1;
		for (int i=n; i > 0; i--){
			current = current->next;
			cur_pos++;
		}
		return current;
	}

	// move back iterator (which is "current" member of the class)
	const element* rew(const int n = 1){
		if (n<0) return this->fwd(n * -1);
		if (n<1 && (cur_pos - n)>=0) throw -1;
		for (int i=n; i > 0; i--){
			current = current->prev;
			cur_pos--;
		}
		return current;
	}

	// insert a single element after the current position
	void insert(T&elm, D&val){
		if (current == nullptr || (current == last && current == first))	{
			this->add(elm, val);
			return;
		}
		element* tmp = new element();
		tmp->elt = new T(elm);
		tmp->e_val = val;

		tmp->prev = current;
		tmp->next = current->next;
		tmp->next->prev = tmp;
		tmp->prev->next = tmp;

		current = tmp;
		
		sum_val += val;
		cnt++;
		return;// elm;
	}

	// insert a single element by pointer
	void insert(T*&elm, D*val){
		this->insert(*elm, *val);
	};

	// insert a single element by pointer
	void insert(T*&elm, D val){
		this->insert(*elm, val);
	}; // add a single element by pointer

	// insert a member struct
	void insert(member m){
		this->insert(m.n, m.mass);
	}
	void insert(member* m){
		this->insert(m->n, m->mass);
	}

public:
	// remove an element (e.g. during deletion)
	// can be used for removing element from the back/fromnt etc.
	// manage links to prev and next
	void remove(){
		if (current == nullptr) throw - 1;
		if (current == last){
			last = current->prev;
			last->next = nullptr;
			current = last;
		}
		else if (current == first){
			first = current->next;
			first->prev = nullptr;
			current = first;
		}
		else{
			current->next->prev = current->prev;
			current->prev->next = current->next;
			current = current->next;
		}
		sum_val -= current->e_val;
		cnt--;
		return;// elt;
	}

public:
	T head()const{ return *(first->elt); }
	T end()const{ return *(last->elt); }
	void to_start(){ current = first; }
	void to_end(){ current = last; }
	member curr_pos(){ 
		member tmp = { current->elt, current->e_val };
		return tmp;
	}

private:
	unsigned int cnt;
	double sum_val;
	element* first; // pointer to the first element of the list
	element* last; // pointer to the last element of the list

	element* current; // pointer to the current element
	unsigned int cur_pos;
	// used internally to allocate new elements

};
