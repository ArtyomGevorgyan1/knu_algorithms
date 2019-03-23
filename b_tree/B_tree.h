//
// Created by artyom on 17.03.19.
//

#ifndef B_TREE_B_TREE_H
#define B_TREE_B_TREE_H

#define num_limit long long

#include <memory>
#include <vector>
#include <algorithm>

using std::pair;
using std::shared_ptr;
using std::make_shared;
using std::vector;

class Book {
public:
    //Book() = default;

    explicit Book(const int &key) : m_key(key) {}

    int getKey() const {
        return m_key;
    }

private:
    int m_key;
};

// Node вызывает само дерево извне оно невызывается запятые потерял
template <typename T>
struct Node {

    Node (const T data, int balance_factor)

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
    int m_children_count;
    bool m_is_leaf;
};

template <typename T>
class B_tree {
public:

    explicit B_tree(const T root, int balance_factor) : m_counter(0), m_balance_factor(balance_factor)
    {
        m_root = make_shared<Node<T>>(root, balance_factor);
    }

    //--- access operations

    // modification operations

private:

    // пр балансе надо смотреть не на m_counter а на кол-во узлов внутри !
    shared_ptr <Node<T>> m_root;
    int m_counter;
    int m_balance_factor;

    // --- b-tree specific helping operations
};

#endif //B_TREE_B_TREE_H