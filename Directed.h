#ifndef DIRECTED_H
#define DIRECTED_H
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include "Graph.h"
using namespace std;

///CLASS DIRECTED, INHERITE FROM GRAPH
template<class T>
class Directed :public Graph<T> {
private:
	int node;			//maximum number of node in the stack
public:
	Directed();										//default destructor
	Directed(int);									//constructor
	Directed(const Directed&);						//copy constructor
	virtual ~Directed();							//virtual destructor
	void insert_an_edge(Edge<T>*);
	bool a_cycle(int, bool[], bool*);				//essential to find a loop in a graph
	bool close_loop();								//return true if there is a close loop on the graph
	virtual void print();									//print the different element of the Graph-class***************call the pure virtual print in Graph
};
// default constructor
template<class T>
Directed<T>::Directed() :Graph<T>() {
	//empty
}

//constructor
template<class T>
Directed<T>::Directed(int t) :Graph<T>() {
	node = t;		//maximum number of node in the graph
}

//destructor
template<class T>
Directed<T>::~Directed() {
	//empty
}

//copy constructor
template<class T>
Directed<T>::Directed(const Directed& Bryan) :Graph<T>(Bryan) {
	node = Bryan.node;
}

//add an element in the class
template<class T>
void Directed<T>::insert_an_edge(Edge<T>* Econo2) {

	Edge<T>* Compare = new Edge<T>(Econo2->ptrDestination(), Econo2->ptrSource());		//will be use to cheq if user wants to create an Undirected graph

	if (!find_a_pair(Econo2)) {		//True if the pair doesn't exist

		if (!find_a_pair(Compare)) {
			Graph<T>::map_set[Econo2->getEdgeSource()].push_back(Econo2->getEdgeDestination());//push back the value into the vector

			cout << "\nEdge {" << Econo2->getEdgeSource() << "," << Econo2->getEdgeDestination() << "} added " << endl;
		}
		else {
			cout << "\nUndirected Graph detected.";
			exit(1);
		}
	}
}

//cheq if there is a loop in the graph---only works with int
template<class T>
bool Directed<T>::a_cycle(int N, bool is_visited[], bool* stack) {//*******************************************************

	if (is_visited[N] == false) {		//if the element have not been set
		is_visited[N] = true;			//set the element has been visited
		stack[N] = true;				//set the element has been in the stack
	}

	auto search = Graph<T>::map_set.find(N);			//return an iterator to search which correspond to the position of N
	if (search == Graph<T>::map_set.end()) {			//define if the number N doesn't exist;
														//empty---essential for the "for loop" to not creating "first" values that don't exist
	}
	else {
		for (auto i = Graph<T>::map_set[N].begin(); i != Graph<T>::map_set[N].end(); ++i)		//goes throught the vector
		{
			if (!is_visited[*i] && a_cycle(*i, is_visited, stack))								// if the number has not been visited, call the recursive function
				return true;					//return true, has the element is seen twice in the stack
			else {
				if (stack[*i])
					return true;				//return true, has the element is seen twice in the stack
			}
		}
	}
	stack[N] = false;  // remove the vertex from recursion stack
	return false;      //return false if there are no close loop in the graph
}



//print the different element of the Graph-class***************call the pure virtual print in Graph
template<class T>
void Directed<T>::print() {
	cout << "\nThe different paths are:\n";
	if (Graph<T>::map_set.empty() == false) {
		if (close_loop()) {			//DSF AND BSF
			cout << "\nGraph contains cycle" << endl;
		}
		else {
			for (it = Graph<T>::map_set.begin(); it != Graph<T>::map_set.end(); ++it) { //the initial value of the iterator "it" is the begining position of the map and stops at its end
				cout << it->first << ": ";
				unsigned int counter = 0;  //since the graph.size() will return an insigned int

				for (auto i = Graph<T>::map_set[it->first].begin(); i != Graph<T>::map_set[it->first].end(); ++i) {	//auto set automaticaly the type of the iterator'stypename
					cout << *i;																		// and the loop goes through a a given vector
					++counter;
					if (Graph<T>::map_set[it->first].size() > counter)
						cout << ", ";
				}
				cout << endl;
			}
		}
	}
	else cout << "Sorry, but the map is currently empty" << endl;
}

template<class T>
bool Directed<T>::close_loop() {

	bool* visited = new bool[node];		//will define if an integer have been visited
	bool* in_stack = new bool[node];	//will define if an integer have been in the stack

	for (int i = 1; i < node + 1; ++i) {
		visited[i] = false;			//set the integer to not visited
		in_stack[i] = false;		//set the integer to not being in the stack
	}
	typename map<T, vector<T>>::iterator it;		//define an iterator usefull in your graph
	if (node >= 3) {
		for (it = Graph<T>::map_set.begin(); it != Graph<T>::map_set.end(); ++it) {
			if (a_cycle(it->first, visited, in_stack)) {
				return true;
			}
		}
	}
	return false;
}
#endif