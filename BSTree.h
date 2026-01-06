#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
private:
    int nelem;
    BSNode<T>* root;

    BSNode<T>* search(BSNode<T>* n, T e) const;
    BSNode<T>* insert(BSNode<T>* n, T e);
    BSNode<T>* remove(BSNode<T>* n, T e);
    void delete_cascade(BSNode<T>* n);
    T max(BSNode<T>* n) const;
    BSNode<T>* remove_max(BSNode<T>* n);
    void print_inorder(std::ostream& out, BSNode<T>* n) const;

public:
    BSTree();
    ~BSTree();
    int size() const;
    T search(T e) const;
    void insert(T e);
    void remove(T e);
    friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst);
};

#endif
