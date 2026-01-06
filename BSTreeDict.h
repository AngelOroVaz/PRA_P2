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
    friend std::ostream& operator<<(std::ostream& out, const BSTreeDict<V>& bs);
    V operator[](std::string key);
    void insert(TableEntry<V> entry);
    TableEntry<V> search(std::string key);
    void remove(std::string key);
};

template <typename V>
BSTreeDict<V>::BSTreeDict() {
    tree = new BSTree<TableEntry<V>>();
}

template <typename V>
BSTreeDict<V>::~BSTreeDict() {
    delete tree;
}

template <typename V>
std::ostream& operator<<(std::ostream& out, const BSTreeDict<V>& bs) {
    out << *bs.tree;
    return out;
}

template <typename V>
V BSTreeDict<V>::operator[](std::string key) {
    TableEntry<V> entry = search(key);
    return entry.getValue();
}

template <typename V>
void BSTreeDict<V>::insert(TableEntry<V> entry) {
    tree->insert(entry);
}

template <typename V>
TableEntry<V> BSTreeDict<V>::search(std::string key) {
    TableEntry<V> entry(key, V());
    TableEntry<V> result = tree->search(entry);
    return result;
}

template <typename V>
void BSTreeDict<V>::remove(std::string key) {
    TableEntry<V> entry(key, V());
    tree->remove(entry);
}

#endif
