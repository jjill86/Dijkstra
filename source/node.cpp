#include "node.h"

// constructor - assign name to the node
node::node(string nm) :ngb_amt(0), name(nm), parent(nullptr)
{
	//ngbs = new ngb[MAX_NGBS];
}


// destructor - removes neighbours list
node::~node()
{
	if (ngbs){
		delete [] ngbs;
	}
}

// add a neighbour - requires a pointer to a node
//					and a elt_val value (or distance)
int node::add_ngb(node * elt, double elt_val){
	if (!ngbs) ngbs = new ngb[MAX_NGBS];
	if (!((elt_val < 0.0) || (ngb_amt >= MAX_NGBS))){  // to prohibit addint itself to its lis add " || (this == elt) "  || !(this->is_ngb(elt))
		ngbs[ngb_amt].elt  = elt;
		ngbs[ngb_amt].elt_val = elt_val;
		ngb_amt++;
		return 0;
	}
	else { throw 1; return 1; }
}

// add a neighbour - requires a node instance
int node::add_ngb(node &elt, double elt_val){
	return node::add_ngb(&elt, elt_val);
}

// change the elt_val of a neghbour by it's name
int node::set_ngb_mass(string nm, double new_mass){
	if (new_mass < 0.0) throw 1;
	for (int i = 0; i < ngb_amt; i++){
		if (nm == ngbs[i].elt->name){
			ngbs[i].elt_val = new_mass;
			return 0;
		}
	}
	throw 2;
}

// change the elt_val of a neghbour by it's pointer
int node::set_ngb_mass(node * elt, double new_mass){
	if (new_mass < 0.0) throw 1;
	for (int i = 0; i < ngb_amt; i++){
		if (elt == ngbs[i].elt){
			ngbs[i].elt_val = new_mass;
			return 0;
		}
	}
	throw 2;
}

// get the elt_val of a neghbour by it's name
double node::get_ngb_mass(const string nm)const{
	if (node::is_ngb(nm)){
		for (int i = 0; i < ngb_amt; i++){
			if (nm == ngbs[i].elt->name){
				return ngbs[i].elt_val;
			}
		}
	}
	throw 2;
	return 0.0;
}

// check if node is a neighbour by name
bool node::is_ngb(const string nm)const{
	for (int i = 0; i < ngb_amt; i++){
		if ((ngbs[i].elt->name == nm)){
			return 1;
		}
	}
	return 0;
}

// check if node is a neighbour by pointer
bool node::is_ngb(const node * elt)const{
	for (int i = 0; i < ngb_amt; i++){
		if (ngbs[i].elt == elt)	return true;
	}
	return false;
}

// Operator overload
bool node::operator==(const node &rhs) const { 
	return (this->name == rhs.name); 
};
bool node::operator!=(const node &rhs) const {
	return (this->name != rhs.name);
};

node& node::operator=(const node& rhs) {
	if (rhs != *this) {
		this->name = rhs.name;
		this->ngbs = rhs.ngbs;
		this->ngb_amt = rhs.ngb_amt;
	}
	return *this;
}

// print out operator by object
ostream& operator<<(ostream& out, const node& lhs){
	cout << lhs.name;
	return out;
}

// print out operator by pointer to the object
ostream& operator<<(ostream& out, const node * lhs){
	out << *lhs;
	return out;
}