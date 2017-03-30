#include <iostream>
#include <fstream>
#include <string>

#include "node.h"
#include "list.h"
#include "list_ext.h"
#include "nodenet.h"

#define _TRACE = 0
using namespace std;

int main(){
srand(time(0));
// generate a net of nodes 
// in parameters: 15 = amount of nodes, 4 = maximum edges(connections) for a node
// 10.0 = maximum value of mass per edge
	nodenet * one = new nodenet(15,2,10.0);
	cout << one << endl;
	cout <<"is it connected?:" << one->is_connected() << endl;
	
	
	ofstream f_to_graph; // file to write to
	ifstream f_fr_graph; // file to read from

	f_to_graph.open("graph.grh", ios::out);
	f_to_graph << one;
	f_to_graph.close();

	// read from the file
	f_fr_graph.open("graph.grh", ios::in);

	nodenet* two = new nodenet(f_fr_graph);
	
	f_fr_graph.close();
	
	// print out the node net
	//cout << one << endl;
	
	// print out the node net created from file
	cout << two << endl;
	cout << "is it connected?:" << two->is_connected() << endl;
	string start = "G";
	string end = "J";
	cout << "Shortest path from <"<< start <<"> to <"<< end << ">: "<< two->DijkSrch(start, end)<<endl;


	l_list<int> lst;
	l_list<node> n_lst;

/*	int one = 1;
	int two = 2;
	int three = 3;
	int four = 4;

	lst.add(one);
	lst.add(two);
	lst.add(three);
	lst.add(four);

	cout << lst << endl;

	node* a = new node("A");
	node* b = new node("B");
	node* c = new node("C");
	node* d = new node("D");

	node a1("A1");
	node b1("B1");
	node c1("C1");
	node d1("D1");

	node* arr[4] = {a,b,c,d};

	node arr1[4] = { a1, b1, c1, d1 };

	n_lst.add(arr,4);
	n_lst.add(arr1,4);

	cout << n_lst << endl;*/

/*	le_list<node, double> le01;
	node* a = new node("A");
	node* b = new node("B");
	node* c = new node("C");
	node* d = new node("D");
	node* e = new node("E");
	double val = 12.3;
	cout << "push c" << endl;
	le01.push(c, 123.9); 
	cout << le01 << endl;
	cout << "add a" << endl;
	le01.add(a, val); 
	cout << le01 << endl;
	cout << "push d" << endl;
	le01.push(d, 13.4); 
	cout << le01 << endl;
	cout << "add b" << endl;
	le01.add(b, 34.5); 
	cout << le01 << endl;

	le_list<node, double>::member memb;*/

	return 0;
}