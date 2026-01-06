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
    template <typename U> friend std::ostream& operator<<(std::ostream& out, const BSTree<U>& bst);
};

template <typename T>
BSTree<T>::BSTree() : nelem(0), root(nullptr) {}

template <typename T>
BSTree<T>::~BSTree() {
    delete_cascade(root);
}

template <typename T>
int BSTree<T>::size() const {
    return nelem;
}

template <typename T>
T BSTree<T>::search(T e) const {
    BSNode<T>* node = search(root, e);
    if (node == nullptr) throw std::runtime_error("Elemento no encontrado");
    return node->elem;
}

template <typename T>
BSNode<T>* BSTree<T>::search(BSNode<T>* n, T e) const {
    if (n == nullptr) return nullptr;
    if (e < n->elem) return search(n->izq, e);
    if (e > n->elem) return search(n->der, e);
    return n;
}

template <typename T>
void BSTree<T>::insert(T e) {
    root = insert(root, e);
    nelem++;
}

template <typename T>
BSNode<T>* BSTree<T>::insert(BSNode<T>* n, T e) {
    if (n == nullptr) return new BSNode<T>(e);
    if (e < n->elem) n->der = insert(n->der, e);
    else if (e > n->elem) n->izq = insert(n->izq, e);
    else throw std::runtime_error("Elemento duplicado");
    return n;
}

template <typename T>
void BSTree<T>::remove(T e) {
    root = remove(root, e);
    nelem--;
}

template <typename T>
BSNode<T>* BSTree<T>::remove(BSNode<T>* n, T e) {
    if (n == nullptr) throw std::runtime_error("Elemento no encontrado");
    if (e < n->elem) n->der = remove(n->der, e);
    else if (e > n->elem) n->izq = remove(n->izq, e);
    else {
        if (n->izq == nullptr) return n->der;
        if (n->der == nullptr) return n->izq;
        n->elem = max(n->izq);
        n->izq = remove_max(n->izq);
    }
    return n;
}

template <typename T>
T BSTree<T>::max(BSNode<T>* n) const {
    if (n == nullptr) throw std::runtime_error("Elemento no encontrado");
    while (n->der != nullptr) n = n->der;
    return n->elem;
}

template <typename T>
BSNode<T>* BSTree<T>::remove_max(BSNode<T>* n) {
    if (n->der == nullptr) return n->izq;
    n->der = remove_max(n->der);
    return n;
}

template <typename T>
void BSTree<T>::delete_cascade(BSNode<T>* n) {
    if (n != nullptr) {
        delete_cascade(n->izq);
        delete_cascade(n->der);
        delete n;
    }
}

template <typename T>
void BSTree<T>::print_inorder(std::ostream& out, BSNode<T>* n) const {
    if (n != nullptr) {
        print_inorder(out, n->izq);
        out << n->elem << " ";
        print_inorder(out, n->der);
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst) {
    bst.print_inorder(out, bst.root);
    return out;
}

#endif 

