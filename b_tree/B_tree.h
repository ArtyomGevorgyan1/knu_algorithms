//
// Created by artyom on 17.03.19.
//

#ifndef B_TREE_B_TREE_H
#define B_TREE_B_TREE_H

#define num_limit long long

// use node_key([shared_ptr<Node <T>>]) to get the node's key hash value
#define get_key(k) k -> m_data_ptr -> getKey()

#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>

template <typename T> class Node;

using std::pair;
using std::shared_ptr;
using std::make_shared;
using std::vector;

template <typename T>
using shared_node_t = shared_ptr<Node <T>>;

class Book {
public:

    explicit Book(const unsigned &key) : m_key(key) {}

    unsigned getKey() const {
        return m_key;
    }

private:
    unsigned m_key;
};

// Node вызывает само дерево извне оно невызывается запятые потерял
template <typename T>
struct Node {

    Node (const T data, unsigned balance_factor)

    {
        m_is_leaf = true;
        m_children_count = 0;
        m_keys.resize(balance_factor + 1);
        m_children.resize(balance_factor + 2);
        m_data_ptr = make_shared<T>(data.getKey());
    }

    shared_ptr <T> m_data_ptr;
    vector <shared_ptr<Node<T>>> m_children;
    vector <num_limit> m_keys;
    unsigned m_children_count;
    bool m_is_leaf;
};

template <typename T>
class B_tree {
public:

    explicit B_tree(const T root, unsigned balance_factor) : m_counter(0), m_balance_factor(balance_factor)
    {
        m_root = make_shared<Node<T>>(root, balance_factor);
    }

    //--- access operations

    pair <shared_node_t <T>, unsigned> search(shared_node_t <T> , Node <T>) {
        unsigned i = 1;

    }

    // overload for integer key!


    // modification operations

private:

    // пр балансе надо смотреть не на m_counter а на кол-во узлов внутри !
    shared_ptr <Node<T>> m_root;
    unsigned m_counter;
    unsigned m_balance_factor;

    // --- b-tree specific helping operations
};

#endif //B_TREE_B_TREE_H