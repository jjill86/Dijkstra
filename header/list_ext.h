#pragma once
#include <ostream>
using namespace std;
// Extended Linked list class. Will take 2 values
// Made to replace a structure of node+edge value
// elements will keep 2 values of specified type,
// and have a pointer to the next element in the list
template <class T, class D>
class le_list{
	friend class l_iter;
protected:
	// structure to keep in memory
	struct element {
		T* elt;
		D e_val;
		element* prev;
		element* next;
	};
public:
	le_list() :cnt(0),sum_val(0.0),cur_pos(0),first(nullptr), 
			   last(nullptr), current(nullptr){};
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
	void fwd(unsigned int n=1){
		if (n<1 && (cur_pos + n)>cnt) return;
		for (; n > 0; n--){
			current = current->next;
			cur_pos++;
		}
	}

	// move back iterator (which is "current" member of the class)
	void rew(unsigned int n = 1){
		if (n<1 && (cur_pos - n)>=0) return;
		for (; n > 0; n--){
			current = current->prev;
			cur_pos--;
		}
	}

	// remove an element (e.g. during deletion)
	// can be used for removing element from the back/fromnt etc.
	// manage links to prev and next
	void remove(){
		T elt = *(current->elt);
		if (current==nullptr) throw -1;
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

	// insert a single element after the current position
	void insert(T&elm, D&val){
		if (current == nullptr || current == last || current == first)	{
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

	T head()const{ return *(first->elt); }
	T end()const{ return *(last->elt); }

private:
	unsigned int cnt;
	double sum_val;
	element* first; // pointer to the first element of the list
	element* last; // pointer to the last element of the list

	element* current; // pointer to the current element
	unsigned int cur_pos;
	// used internally to allocate new elements

};

