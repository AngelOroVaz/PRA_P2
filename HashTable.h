#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2425_P1/ListLinked.h"  // ¡¡¡¡MODIFICAR!!!!

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
        int max;

        ListLinked<TableEntry<V>>* table;

        int h(std::string key){
            int sum = 0;
            for (char c : key) {
                sum += static_cast<int>(c);
            }
            return sum % max;
        }

    public:
        HashTable(int size) : n(0), max(size) {
            table = new ListLinked<TableEntry<V>>[max];
        }

        int capacity() const {
            return max;
        }

        int entries() const override {
            return n;
        }
        
        ~HashTable() override {
            delete[] table;
        }

        V operator[](std::string key){
            return search(key);  // reutilizamos search
        }

        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &ht) {
            for (int i = 0; i < ht.max; ++i) {
                out << "[" << i << "]: ";
                // Suponiendo que ListLinked tiene size() y get(i)
                for (int j = 0; j < ht.table[i].size(); ++j) {
                    out << ht.table[i].get(j) << " ";
                }
                out << '\n';
            }
            return out;
        }


        void insert(std::string key, V value) override {
            int idx = h(key);
            int pos = table[idx].search(TableEntry<V>(key));

            if (pos >= 0) {
                throw std::runtime_error("Clave ya esta en la tabla: " + key);
            }

            table[idx].insert(TableEntry<V>(key, value));
            ++n;
        }

        V search(std::string key) override {
            int idx = h(key);
            int pos = table[idx].search(TableEntry<V>(key));

            if (pos == -1) {
                throw std::runtime_error("Clave no esta en la tabla: " + key);
            }

            return table[idx].get(pos).value;
        }

        V remove(std::string key) override {
            int idx = h(key);
            int pos = table[idx].search(TableEntry<V>(key));

            if (pos == -1) {
                throw std::runtime_error("Clave no esta en la tabla: " + key);
            }

            V valor = table[idx].get(pos).value;
            table[idx].remove(pos);
            --n;
            return valor;
        }
};

#endif