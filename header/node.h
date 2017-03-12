#pragma once
#include <string>
#include <iostream>
using namespace std;


// ngb - is short for neighbour
// ngbs - is short for neighbours
class node
{
	// struct to keep an array of neighbours with
	// the mass of a connection
	typedef struct ngb{
		node * n;
		double mass;
	} ngb;

private:
	const int MAX_NGBS = 35;
public:
	string name; // name of the node
	ngb * ngbs = nullptr; // array of all neighbours

	node() { node("tmp"); }
	node(string); 
	~node();
	int add_ngb(node*, double);
	int add_ngb(node&, double);

	int set_ngb_mass(node *, double);
	int set_ngb_mass(string , double);

	double get_ngb_mass(node *) const;
	double get_ngb_mass(string) const;

	bool is_ngb(const string) const;
	bool is_ngb(const node *) const;

	int ngbs_amt() const { return ngb_amt; };
	
	// operator overloads
	bool operator==(const node& rhs) const;
	bool operator!=(const node& rhs) const;

	node operator=(const node& rhs);
private:
	int ngb_amt;
};
