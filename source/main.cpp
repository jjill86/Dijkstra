#include <iostream>
#include <fstream>
#include <string>

#include "node.h"
#include "list.h"
#include "nodenet.h"

#define _TRACE = 0
using namespace std;

int main(){
/*	srand(time(0));
// generate a net of nodes 
// in parameters: 15 = amount of nodes, 4 = maximum edges(connections) for a node
// 10.0 = maximum value of mass per edge
	nodenet * one = new nodenet(3,0,10.0);
	cout << one << endl;
	cout <<"is it connected?:" << one->is_connected() << endl;
	
	
	ofstream f_to_graph; // file to write to
	ifstream f_fr_graph; // file to read from

//	f_to_graph.open("graph.grh", ios::out);
//	f_to_graph << one;
//	f_to_graph.close();

	// read from the file
	f_fr_graph.open("graph.grh", ios::in);

	nodenet* two = new nodenet(f_fr_graph);
	
	f_fr_graph.close();
	
	// print out the node net
	//cout << one << endl;
	
	// print out the node net created from file
	cout << two << endl; */


	l_list<int> lst;
	lst.add(1);
	lst.add(2);
	lst.add(3);


	return 0;
}