// own libraries
#include "nodenet.h"
#define HEAD "-------"
// generate random number with min and max values
double RndFloat(const double a, const double b) {
	double random = ((double)rand()) / (double)RAND_MAX;
	return a + random * (b - a);
}
// generate true/false with preset probability
bool FlipCoin(const double a) {
	double random = ((double)rand()) / (double)RAND_MAX;
	return (a > random);
}

nodenet::nodenet()
{
}
// constructor to generate a matrix of nodes to the nodenet
// params: nodes amount; maximum edges per node; maximum mass on edge
nodenet::nodenet(unsigned int nds_amt, const unsigned char max_connections, const double max_mass){
	// check input parameters
	if (nds_amt > 1 &&
		max_connections <= nds_amt &&
		max_connections > 0 &&
		max_mass > 0.0){
			// alfabet to generate nodes name
			nds_amt = nds_amt > 35 ? 35 : nds_amt;
			string alfabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
			string nm = "";

			// create all nodes
			for (int i = 0; i < nds_amt; i++){
				nm.push_back(alfabet[i]);
				this->add(node(nm));
				nm.clear();
			}

			// add edges and edge mass randomely
			for (node& it_i : net){
				for (node& it_j : net){
					if (it_i != it_j && FlipCoin((max_connections*1.0 / nds_amt*1.0))){
						it_i.add_ngb(it_j, RndFloat(1.0, max_mass));
				}
			}
		}
	}
}

nodenet::~nodenet()
{
}

// method to determine if the graph is connecte
// connected - means if all nodes are reachable
// from every oter node. e.g. for any node selected
// there's a path to every other nodes in the net
bool nodenet::is_connected() {
	// we need to keep track of opened nodes (ones we've checked)
	// and closed ones (ones we haven't checked)
	// we use a trick to keep them in neigbours of node's data
	node opened("OPN");
	node * current;
	opened.add_ngb(net.front(), 1.0);
	int i = 0;
	int size = this->size();
	while (opened.ngbs_amt() < size) {
		current = opened.ngbs[i].n;

		// add all neighbours from current to opened
		for (int j = 0; j < current->ngbs_amt(); j++) {
			if (!(opened.is_ngb(current->ngbs[j].n))) 
				opened.add_ngb(current->ngbs[j].n, 1.0);
		}
		i++;
		// if we don't add enough nodes
		// and next node counter is bigger
		// than the amount of accessible nodes
		// then we exit, with "not connected" result
		if (i >= opened.ngbs_amt()) return false;
	}
	return true;
}

// Constructor using a file
nodenet::nodenet(ifstream &fs){
	string line="";

	// read until see the header, after header, there's valuable data
	while ( line != HEAD){
		getline(fs, line);
	}

	// first line has the names of nodes separated by /t
	getline(fs, line);

	// parse this line
	vector<string> nd_names = split(line, '\t'); // nodes name

	// first element will always be empty
	if (nd_names.front() == ""){
		nd_names.erase(nd_names.begin());
	}

	for (auto const& nm : nd_names){
		try{
			this->add(node(nm));
		}
		catch (...){ cout << "Error: Couldn't add a node <"<< nm << "> to the net" << endl; }
	}

	// next get the lines with each node's edges
	// line starts with the name of the node
	// continues with edges for each corresponding node
	// devided with '\t'
	while (getline(fs, line)){

		// get the line
		vector<string> edges = split(line, '\t');
		vector<string>::iterator it = edges.begin();
		string nm = edges.front();
		it++;

		for (int i=0; it != edges.end(); it++, i++){

			string s_edge = *it;
			string::size_type sz = 0;
			double edge = 0.0;
			try{
				edge = stod(s_edge, &sz);
			}
			catch (...){
			}
			if (edge > 0.0){
				try{
					this->add_ngb_by_name(nm, nd_names[i], edge);
				}
				catch (...){
					cout << "Error: Couldn't add a neighbour <" << nd_names[i] << "> to the node <" << nm << ">" << endl;
				}
			}
		}
	}
}


// add a node to the nodenet by pointer
void nodenet::add(node * n){ nodenet::add(*n); }

// add a node to the net by node instance
void nodenet::add(const node &n){
	if (!net.empty() && (std::find(net.begin(), net.end(), n) != net.end())){
		cout << "Node <" << n.name << "> you're trying to add, is already in the net!" << endl;
		throw 1;
		return;
	}
	net.push_back(n);
}

// get a node from the net by it's name
node* nodenet::get_by_name(string& nm) {
	for (auto& it : net){
		if (it.name == nm){
			return &it;
		}
	}
	cout << "Error: Node with the name <" << nm << "> " << "was not found in the net." << endl;
	throw 1;
	return nullptr;
}

// add a neighbor to a node in the net by it's name
void nodenet::add_ngb_by_name(string& nm, string& ngb_nm, const double mass) {
	node* nd = nodenet::get_by_name(nm);
	node* ngb = nodenet::get_by_name(ngb_nm);
	try{
		nd->add_ngb(ngb, mass);
	}
	catch (...){
		cout << "Error: Couldn't add the neighbour to the node!" << endl;
	}
}

double nodenet::DijkSrch(node * start, node * end) const {
	return 0.0;
}

// apply search by the name of the node
// procedure will find start and end nodes by name 
// and pass pointers to the other DijkSearch with pointers 
double nodenet::DijkSrch(string start, string end) const {
	node * s = nullptr;
	node * e = nullptr;
	for (node it : net){
		if (!s && (it.name == start)) s = &it;
		if (!e && (it.name == end)) e = &it;
		if (s && e) break;
	}
	if (!s || !e) return 1;
	return nodenet::DijkSrch(s, e);
}

// print out operator by object
ostream& operator<<(ostream& out,const nodenet& lhs){
	out.precision(3);
	out.width(6);
	out << "nodenet" << endl;
	out << HEAD << endl;
	out << "\t";
	// print out names in header
	for (auto const& it_i : lhs.net){
		out << it_i.name << "\t";
	}
	out << endl;

	for (auto const& it_i : lhs.net){
		out << it_i.name << "\t";
		// print out the mass value if node is a neighbour
		for (auto const& it_j : lhs.net){
			if (it_i.is_ngb(it_j.name)){
				out << it_i.get_ngb_mass(it_j.name)<<"\t";
			}
			else out << "\t";
		}
		out << endl;
	}
	return out;
}

// print out operator by pointer to the object
ostream& operator<<(ostream& out, const nodenet * lhs){
	out << *lhs;
	return out;
}