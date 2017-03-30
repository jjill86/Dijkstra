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
		delete ngbs;
	}
}

// add a neighbour - requires a pointer to a node
//					and a mass value (or distance)
int node::add_ngb(node * n, double mass){
	if (!ngbs) ngbs = new ngb[MAX_NGBS];
	if (!((mass < 0.0) || (ngb_amt >= MAX_NGBS))){  // to prohibit addint itself to its lis add " || (this == n) "  || !(this->is_ngb(n))
		ngbs[ngb_amt].n  = n;
		ngbs[ngb_amt].mass = mass;
		ngb_amt++;
		return 0;
	}
	else { throw 1; return 1; }
}

// add a neighbour - requires a node instance
int node::add_ngb(node &n, double mass){
	return node::add_ngb(&n, mass);
}

// change the mass of a neghbour by it's name
int node::set_ngb_mass(string nm, double new_mass){
	if (new_mass < 0.0) throw 1;
	for (int i = 0; i < ngb_amt; i++){
		if (nm == ngbs[i].n->name){
			ngbs[i].mass = new_mass;
			return 0;
		}
	}
	throw 2;
}

// change the mass of a neghbour by it's pointer
int node::set_ngb_mass(node * n, double new_mass){
	if (new_mass < 0.0) throw 1;
	for (int i = 0; i < ngb_amt; i++){
		if (n == ngbs[i].n){
			ngbs[i].mass = new_mass;
			return 0;
		}
	}
	throw 2;
}

// get the mass of a neghbour by it's name
double node::get_ngb_mass(string nm)const{
	if (node::is_ngb(nm)){
		for (int i = 0; i < ngb_amt; i++){
			if (nm == ngbs[i].n->name){
				return ngbs[i].mass;
			}
		}
	}
	throw 2;
	return 0.0;
}

// check if node is a neighbour by name
bool node::is_ngb(const string nm)const{
	for (int i = 0; i < ngb_amt; i++){
		if ((ngbs[i].n->name == nm)){
			return 1;
		}
	}
	return 0;
}

// check if node is a neighbour by pointer
bool node::is_ngb(const node * n)const{
	for (int i = 0; i < ngb_amt; i++){
		if (ngbs[i].n == n)	return true;
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

node node::operator=(const node& rhs) {
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