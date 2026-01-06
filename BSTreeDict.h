#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {
private:
    BSTree<TableEntry<V>>* tree;

public:
    BSTreeDict();
    ~BSTreeDict();
    V operator[](std::string key);
    void insert(std::string key, V value);
    V search(std::string key);
    V remove(std::string key);
    int entries();  

    BSTree<TableEntry<V>>* getTree() const { return tree; }

};

template <typename V>
std::ostream& operator<<(std::ostream& out, const BSTreeDict<V>& bs) {
    out << *bs.getTree(); 
    return out;
}

template <typename V>
BSTreeDict<V>::BSTreeDict() {
    tree = new BSTree<TableEntry<V>>();
}

template <typename V>
BSTreeDict<V>::~BSTreeDict() {
    delete tree;
}

template <typename V>
V BSTreeDict<V>::operator[](std::string key) {
    TableEntry<V> entry(key, V());
    TableEntry<V> result = tree->search(entry);
    return result.getValue();
}

template <typename V>
void BSTreeDict<V>::insert(std::string key, V value) {
    TableEntry<V> entry(key, value);
    tree->insert(entry);
}

template <typename V>
V BSTreeDict<V>::search(std::string key) {
    TableEntry<V> entry(key, V());
    TableEntry<V> result = tree->search(entry);
    return result.getValue();
}

template <typename V>
V BSTreeDict<V>::remove(std::string key) {
    TableEntry<V> entry(key, V());
    tree->remove(entry);
    return entry.getValue();
}

template <typename V>
int BSTreeDict<V>::entries() {
    return tree->size();
}

#endif 
