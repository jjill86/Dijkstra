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
	l_list<node> n_lst;

	int one = 1;
	int two = 2;
	int three = 3;
	int four = 4;

	lst.add(one);
	lst.add(two);
	lst.add(three);
	lst.add(four);

	cout << lst << endl;

	node a("A");
	node b("B");
	node c("C");
	node d("D");

	n_lst.add(node("A"));

	cout << n_lst << endl;
	return 0;
}