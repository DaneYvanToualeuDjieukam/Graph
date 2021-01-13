#ifndef UNDIRECTED_H
#define UNDIRECTED_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include "Graph.h"
using namespace std;

template<class T>
class Undirected :public Graph<T> {
private:
	int node;			//maximum number of node in the stack
public:
	int counter;
	int parent;
	int skip;
	Undirected();									//default destructor
	Undirected(int);								//constructor
	Undirected(const Undirected&);					//copy constructor
	virtual ~Undirected();							//virtual destructor
	void insert_an_edge(Edge<T>*);					//insert an endge, and it opposit in the map*******************call the pure virtual print in graph
	bool a_cycle(int, bool[], int);					//essential to find a loop in a graph
	bool close_loop();								//return true if there is a close loop on the graph
	bool is_parent(int, int);						//function that determine if it's a daughter
	virtual void print();									//print the different element of the graph-class***************call the pure virtual print in graph
};

// default constructor
template<class T>
Undirected<T>::Undirected() :Graph<T>() {
	//empty
}

//constructor
template<class T>
Undirected<T>::Undirected(int t) :Graph<T>() {
	node = t;		//maximum number of node in the graph
}

//destructor
template<class T>
Undirected<T>::~Undirected() {
	//empty
}

//copy constructor
template<class T>
Undirected<T>::Undirected(const Undirected& bryan) :Graph<T>(bryan) {
	node = bryan.node;
}

//add an element in the class
template<class T>
void Undirected<T>::insert_an_edge(Edge<T>* Econo3) {
	if (Graph<T>::map_set.empty()) {
		map_set[Econo3->getEdgeSource()].push_back(Econo3->getEdgeDestination());//push back the value into the vector
		map_set[Econo3->getEdgeDestination()].push_back(Econo3->getEdgeSource());//push back the opposite value into the vector
	}

	if (!find_a_pair(Econo3)) {		//True if the pair doesn't exist
		map_set[Econo3->getEdgeSource()].push_back(Econo3->getEdgeDestination());//push back the value into the vector
		map_set[Econo3->getEdgeDestination()].push_back(Econo3->getEdgeSource());//push back the opposite value into the vector
		cout << "\nEdges: {" << Econo3->getEdgeSource() << "," << Econo3->getEdgeDestination() << "}, {" << Econo3->getEdgeDestination() << "," << Econo3->getEdgeSource() << "}  added." << endl;
	}
}


//function that determine if it's a daughter
template<class T>
bool  Undirected<T>::is_parent(int x, int y) {
	//goes throught the vector
	if (counter == 1)
		return false;
	else
		if (parent == y)			//verify if it's par of the parent it's vector
			return true;

	return false;
}
//cheq if there is a loop in the graph---only works with int
template<class T>
bool Undirected<T>::a_cycle(int N, bool is_visited[], int parent) {//*******************************************************

	if (is_visited[N] == false) {		//if the element have not been set
		is_visited[N] = true;			//set the element has been visited
		skip = false;
	}
	++counter;		//counter on how many "first"  passed! passed

	auto search = Graph<T>::map_set.find(N);			//return an iterator to search which correspond to the position of N
	if (search == Graph<T>::map_set.end()) {}			//define if the number N doesn't exist;, and skip it;
														//empty---essential for the "for loop" to not creating "first" values that don't exist in the graph
	else {
		for (auto t = Graph<T>::map_set[N].begin(); t != Graph<T>::map_set[N].end(); ++t) {		//goes throught the vector

			for (typename map<T, vector<T>>::iterator i = Graph<T>::map_set.begin(); i != Graph<T>::map_set.find(*t); i++) {

				for (auto j = Graph<T>::map_set[i->first].begin(); j != Graph<T>::map_set[i->first].end(); j++) {  ///use the search function, as the one in the remove_a_node*****
					if (*j == *t)
						skip = true;
				}
				if (!skip) {

					if (!is_visited[*t] && !is_parent(this->parent, *t)) {					// if the number has not been visited, call the recursive function
						this->parent = N;
						if (a_cycle(*t, is_visited, this->parent))
							return true;			//return true, has the element is seen twice in the stack
					}
					else {
						if (is_visited[*t] && !is_parent(this->parent, *t))
							return true;				//return true, has the element is seen twice in the stack
					}
				}
			}
			is_visited[*t] = true;
		}
	}
	return false;      //return false if there are no close loop in the graph
}

//DSF, verify if there is a close loop in the nodes.
template<class T>
bool Undirected<T>::close_loop() {

	bool* visited = new bool[node];		//will define if an integer have been visited

	for (int i = 1; i < node + 1; ++i) {
		visited[i] = false;			//set the integer to not visited
	}
	if (node >= 3) {

		for (auto it = Graph<T>::map_set.begin(); it != Graph<T>::map_set.end(); ++it) {

			parent = it->first;
			if (a_cycle(it->first, visited, parent)) {
				return true;
			}
		}
	}return false;
}


//print the different element of the Graph-class***************call the pure virtual print in Graph
template<class T>
void Undirected<T>::print() {
	cout << "\nThe different paths are:\n";
	if (Graph<T>::map_set.empty() == false) {

		for (it = Graph<T>::map_set.begin(); it != Graph<T>::map_set.end(); ++it) { //the initial value of the iterator "it" is the begining position of the map and stops at its end
			cout << it->first << ": ";
			unsigned int counter = 0;		//unsigned, since the graph.size() will return an unsigned int;

			for (auto i = Graph<T>::map_set[it->first].begin(); i != Graph<T>::map_set[it->first].end(); ++i) {	//auto set automaticaly the type of the iterator'stypename
				cout << *i;																		// and the loop goes through a a given vector
				++counter;
				if (counter < Graph<T>::map_set[it->first].size())
					cout << ", ";
			}
			cout << endl;
		}

	}
	else cout << "Sorry, but the map is currently empty." << endl;
}
#endif