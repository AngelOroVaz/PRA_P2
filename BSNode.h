#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T>
class BSNode{
public:
	T elem;
	BSNode<T>* izq;
	BSNode<T>* der;
	BSNode(T elem, BSNode<T>* left=nullptr, BSNode<T>* right=nullptr): elem(elem), izq(izq),der(der){}
	friend std::ostream&operator<<(std::ostream &out, const BSNode<T> &bsn);
};

#endif
