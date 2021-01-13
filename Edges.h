#ifndef EDGES_H
#define EDGES_H
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include "Nodes.h"
using namespace std;

///CLASS EDGE
template<class T>
class Edge {
private:
	Node<T>* source;
	Node<T>* destination;

public:
	Edge();										//Default Constructor
	Edge(Node<T>*, Node<T>*);					//Constructor
	Edge(const Edge&);							//Copy Constructor
	~Edge();									//Destructor, use of polymorphism

	void setEdge(Node<T>*, Node<T>*);			//set the Edge
	T getEdgeSource();							//return the starting edge
	T getEdgeDestination();						//return the ending edge
	Node<T>* ptrSource();						//return the "Node" source
	Node<T>* ptrDestination();					//return the "Node" destination
	void print()const;							//print the Edge
};

//Edge's default constructor
template<class T>
Edge<T>::Edge() {
	source = 0;				//initialize the 
	destination = 0;		//pointers to the nullptr
}

//Edge's constructor
template<class T>
Edge<T>::Edge(Node<T>* Future, Node<T>* Kendrix) {
	source = Future;
	destination = Kendrix;
}

//Edge class's copy constructor
template<class T>
Edge<T>::Edge(const Edge& another_Edge) {
	source = another_Edge.source;				//assigne the new
	destination = another_Edge.destination;		//edges
}

//virtual destructor of edge class
template<class T>
Edge<T>::~Edge() {
	delete[]source;				//delete
	delete[]destination;		//the pointers
}

//modify the edges
template<class T>
void Edge<T>::setEdge(Node<T>* DY1, Node<T>* DY2) {
	source = DY1;
	destination = DY2;
}

//return a starting node's value
template<class T>
T Edge<T>::getEdgeSource() {
	return source->getvalue();			//can be used since source is a "Node"
}

//return an ending node's value
template<class T>
T Edge<T>::getEdgeDestination() {
	return destination->getvalue();		//can be used since destination is a "Node"
}

//return the source
template<class T>
Node<T>* Edge<T>::ptrSource() {
	return source;
}

//return the destination
template<class T>
Node<T>* Edge<T>::ptrDestination() {
	return destination;
}

//virtual print Edges
template<class T>
void Edge<T>::print()const {
	cout << "\nStarting point: " << source->getvalue()
		<< "\nEnding point:   " << destination->getvalue() << endl;
}
#endif