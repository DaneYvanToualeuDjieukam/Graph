#ifndef NODES_H
#define NODES_H
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
using namespace std;

///CLASS NODE
template<class T>
class Node {
private:
	T value;						//can be of any type

public:
	Node();							// default constructor
	Node(T);						// regular constructor
	Node(const Node&);				//copy constructor
	~Node();						//destructor, use of polymorphism

	void setvalue(T);				// set the value
	T getvalue();					// get the value
	void print()const;				//print function

};

//default constructor
template<class T>
Node<T>::Node() {

}

// regular constructor
template<class T>
Node<T>::Node(T v) {
	value = v;
}

//copy constructor
template<class T>
Node<T>::Node(const Node& n) {
	value = n.value;
}

//modify a node's value
template<class T>
void Node<T>::setvalue(T nvalue) {
	value = nvalue;
}

// get the value
template<class T>
T Node<T>::getvalue() {
	return value;
}

//destructor
template<class T>
Node<T>::~Node() {
	//empty
};

//print Node's value
template<class T>
void Node<T>::print()const {
	cout << "\n" << value << endl;
}
#endif