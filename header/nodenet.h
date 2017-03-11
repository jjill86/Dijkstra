#pragma once
#include <vector>
#include <iterator>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <time.h>
#include "node.h"
using namespace std;
class nodenet
{
public:
	nodenet();
	nodenet(const unsigned int nds_amt, const unsigned char avg_connections, const double avg_mass);
	nodenet(ifstream &fs);
	~nodenet();

	void add(node *);
	void add(const node&);

	node* get_by_name(string&);
	void add_ngb_by_name(string&, string&, const double);

	bool is_connected();
	unsigned int size() const { return static_cast<int>(net.size()); }

	double DijkSrch(node *, node *) const;
	double DijkSrch(string, string) const;

	friend ostream& operator<<(ostream& out, const nodenet&);
	friend ostream& operator<<(ostream& out, const nodenet*);
public:
	vector<node> net; // array of nodes



	// Code to add a split function to string
	template<typename Out>
	void split(const string &s, char delim, Out result) {
		stringstream ss;
		ss.str(s);
		string item;
		while (getline(ss, item, delim)) {
			*(result++) = item;
		}
	}


	vector<string> split(const string &s, char delim) {
		vector<string> elems;
		split(s, delim, back_inserter(elems));
		return elems;
	}

};