//
// Created by artyom on 02.04.19.
//

#ifndef B_TREE_BPT_H
#define B_TREE_BPT_H

// use node_key([shared_ptr<Node <T>>]) to get the node's key hash value
#define get_key(k, i) k -> m_keys[i] -> getKey()
#define get_cnt(k) k -> m_count
#define get_child(k, i) k -> m_children[i]

#include <vector>
#include <string>
#include <memory>
#include <algorithm>

using std::vector;
using std::string;
using std::shared_ptr;
using std::make_pair;
using std::make_shared;
using std::pair;

template <typename T> class Node;

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

    explicit Node (unsigned balance_factor)

    {
        m_is_leaf = true;
        m_count = 0;
        m_keys.resize(2 * balance_factor);
        m_children.resize(2 * balance_factor + 1);
    }

    vector <shared_ptr<Node<T>>> m_children;
    vector <shared_ptr<T>> m_keys;
    shared_ptr <Node <T>> m_parent, m_left, m_right;
    unsigned m_count;
    bool m_is_leaf;
};

template <typename T>
class B_tree {
public:

    explicit B_tree(unsigned balance_factor) : m_counter(0), m_balance_factor(balance_factor)
    {
        m_root = make_shared<Node<T>>(balance_factor);
    }


    pair <shared_node_t <T> , unsigned > search(T key)
    {
        shared_node_t <T> cur = m_root;
        unsigned i;
        while (!cur -> m_is_leaf)
        {
            i = 1;
            while (i <= get_cnt(cur))
            {
                ++i;
            }
            cur = get_child(cur, i);
        }

        // look for the key
        i = 1;
        while (i <= get_cnt(cur) && get_key(cur, i) != key.getKey())
        {
            ++i;
        }

        if (i == 2 * m_balance_factor)
        {
            // cur is where th key should be inserted
            return make_pair<shared_node_t <T> , unsigned > (std::move(cur), 0);
        } else
        {
            return make_pair<shared_node_t <T> , unsigned > (std::move(cur), std::move(i));
        }
    }

    void insert(T key)
    {
        shared_node_t <T> leaf;

        auto info = search(key);

        // the key is already there
        if (info.second != 0) return;

        else
        {
            leaf = info.first;
        }

        if (get_cnt(leaf) == 2 * m_balance_factor)
        {
            shared_node_t <T> z = make_shared<Node <T> >(m_balance_factor);
            unsigned i = 1;
            while (i <= m_balance_factor)
            {
                //get_key(z, i) = get_key(leaf, i + m_balance_factor);
                z -> m_keys[i] = leaf -> m_keys[i + m_balance_factor];
                ++i;
            }

            if (key.getKey() > get_key(z, 1))
            {
                insert_trivial(z, key);
            } else
            {
                insert_trivial(leaf, key);
            }

            shared_node_t <T> parent = leaf -> m_parent;

            if (!parent)
            {
                parent = make_shared<Node <T> >(m_balance_factor);
                parent -> m_parent = parent -> m_left = parent -> m_right = nullptr;
                m_root = parent;
            }

            leaf -> m_right = z;
            z -> m_left = leaf;
            z -> m_parent = leaf -> m_parent;

            //insert(parent, get_key(leaf, get_cnt(leaf)));

        } else
        {
            insert_trivial(leaf, key);
        }
    }


    // ok inserts T not unsigned
    void insert_trivial(shared_node_t <T> leaf, T key)
    {
        unsigned pos;
        unsigned i = 1;
        while (i <= get_cnt(leaf) && key.getKey() > get_key(leaf, i))
        {
            ++i;
        }

        pos = i;
        while (i <= get_cnt(leaf))
        {
            leaf -> m_keys[i + 1] = leaf -> m_keys[i];
        }
        ++get_cnt(leaf);

        (leaf -> m_keys)[pos] = make_shared<T> (key);
    }


private:

    // пр балансе надо смотреть не на m_counter а на кол-во узлов внутри !
    shared_node_t <T> m_root;
    unsigned m_counter;
    unsigned m_balance_factor;
};




#endif //B_TREE_BPT_H
