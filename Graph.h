#ifndef GRAPH_H
#define GRAPH_H
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include "Edges.h"
#include "Nodes.h"
using namespace std;

///CLASS MAP
template<class T>
class Graph {	///use class composition with classes Edges and Nodes
protected:
	map<T, vector<T>>map_set;					//will contains all the different data
	typename map<T, vector<T>>::iterator it;	//"typename" is used since the compiler doesn't know whether listtNode<T>*>::iterator is either a static field or a type.

public:
	Graph();												//default constructor
	Graph(const Graph&);									//copy constructor
	virtual ~Graph();										//virtual estructor

	bool find_a_node(Node<T>*);								//search a node within the map
	bool find_a_pair(Edge<T>*);								//search the key with "find_a_node" and if true, search for value in the vector
	virtual void insert_an_edge(Edge<T>*) = 0;				//pure virtual function; has different definitions in Directed and Undirected classes;
	void insert_a_node(Node<T>*);							//add a non-connected node in the graph
	void remove_a_node(Node<T>*);							//remove a specific key and it's elements
	void remove_an_edge(Edge<T>*);							//remove the link between two nodes
	void clear_map();										//use clear map's function
	void display_node(Node<T>*);							//print a node's different connections 
	virtual void print() = 0;								//virtual function that prints all the keys and elements of a map						
};

//default constructor
template<class T>
Graph<T>::Graph() {
	//empty
}

//Graph's copy constructor
template<class T>
Graph<T>::Graph(const Graph& Benjamin) {
	map_set = Benjamin.map_set;
}

//destructor
template<class T>
Graph<T>::~Graph() {
	//empty
}

//find a node in the map 
template<class T>
bool Graph<T>::find_a_node(Node<T>* key) {
	if (!map_set.empty()) {		//verifies if the map is empty -->  "if (map_set.empty==false)

		auto search = map_set.find(key->getvalue());			//return an iterator to search which correspond to the position of "Key"-----------------auto get the type automatucaly
		if (search != map_set.end()) 	//return an iterator which corresponds to the end of the map, if the "Key" is not found
			return true;
	}
	return false;
}

//find a pair of values in the map
template<class T>
bool Graph<T>::find_a_pair(Edge<T>* Econo) {
	if (find_a_node(Econo->ptrSource())) {  				// same as " if(map_set.find_a_node(Econo)==true)"   

		for (auto i = map_set[Econo->getEdgeSource()].begin(); i != map_set[Econo->getEdgeSource()].end(); ++i) {		//Goes through a given vector of a given "node"
			if (*i == Econo->getEdgeDestination())
				return true;					//return true if the edge's destination is found
		}
	}
	return false;					//return false if the "edge's destination" is founded
}

//isolated node in the graph
template<class T>
void Graph<T>::insert_a_node(Node<T>* Alex) {
	map_set[Alex->getvalue()]; //create an isolated Node
	cout << "\nNode " << Alex->getvalue() << " has been inserted" << endl;
}

//remove a key and its element from the map
template<class T>
void Graph<T>::remove_a_node(Node<T>* Panther) {
	if (find_a_node(Panther)) {
		it = map_set.find(Panther->getvalue());		//get the position of "Panther" in the map
		map_set.erase(it);

		for (it = map_set.begin(); it != map_set.end(); ++it) {

			Node<T>* First = new Node<T>(it->first);					//create a node for the source 
			Node<T>* Second = new Node<T>(Panther->getvalue());		//create a node for the destination
			Edge<T>* Delete = new Edge<T>(First, Second);			//create an edge for the delete 
			remove_an_edge(Delete);		//call the remove function "remove an edge", call the find_a_pair and find_a_node functions

		}
		cout << "\nThe Node, " << Panther->getvalue() << " and its elements have been deleted" << endl;
	}
}

//remove a value (since it's in the vector) from a Key in map
template<class T>
void Graph<T>::remove_an_edge(Edge<T>* Samourai) {

	if (find_a_pair(Samourai)) {

		for (unsigned int i = 0; i < map_set[Samourai->getEdgeSource()].size(); i++) {

			if (i == map_set[Samourai->getEdgeSource()].size() - 1 && map_set[Samourai->getEdgeSource()][i] == Samourai->getEdgeDestination())
				map_set[Samourai->getEdgeSource()].pop_back();

			else {
				if (map_set[Samourai->getEdgeSource()][i] == Samourai->getEdgeDestination()) {		//only if the value, Chasseur have been founded
					for (unsigned int j = i; j < map_set[Samourai->getEdgeSource()].size() - 1; j++) {
						map_set[Samourai->getEdgeSource()][j] = map_set[Samourai->getEdgeSource()][j + 1];	//remove the value, Chasseur, and shift the rest of the vector
						map_set[Samourai->getEdgeSource()].pop_back();
					}
				}
			}
		}
		cout << "\nEdge: {" << Samourai->getEdgeSource() << "," << Samourai->getEdgeDestination() << "} was removed" << endl;
	}
}

//reset the map
template<class T>
void Graph<T>::clear_map() {
	map_set.clear(); //clear the map
}

//display a node's connections!
template<class T>
void Graph<T>::display_node(Node<T>* David) {

	if (find_a_node(David)) {
		if (!map_set[David->getvalue()].empty()) {
			cout << "\nAll the edges of Node " << David->getvalue() << ": ";
			for (auto i = map_set[David->getvalue()].begin(); i != map_set[David->getvalue()].end(); i++) {		//for loop that goes throught the vector's elements
				cout << "{" << David->getvalue() << "," << *i << "} ";
			}
		}
		else cout << "\nThe node " << David->getvalue() << " is isolated" << endl;

	}
}
#endif