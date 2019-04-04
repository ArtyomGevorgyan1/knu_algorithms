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
#include <iostream>
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

template <typename T>
struct Node {

    explicit Node (unsigned balance_factor)

    {
        m_is_leaf = true;
        m_count = 0;
        m_keys.resize(2 * balance_factor + 1);
        m_children.resize(2 * balance_factor + 2);
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
            while (i <= get_cnt(cur) && key.getKey() > get_key(cur, i))
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

        if (i == get_cnt(cur) + 1)
        {
            // cur is where th key should be inserted
            return make_pair<shared_node_t <T> , unsigned > (std::move(cur), 0);
        } else
        {
            return make_pair<shared_node_t <T> , unsigned > (std::move(cur), std::move(i));
        }
    }

    void split(shared_node_t <T> source, bool for_leaf = true)
    {
        shared_node_t <T> z = make_shared<Node <T>>(m_balance_factor);
        z -> m_left = source;
        source -> m_right = z;
        z -> m_parent = source -> m_parent;

        unsigned i = 1;
        while (i <= m_balance_factor)
        {
            z -> m_keys[i] = source -> m_keys[i + m_balance_factor];
            if (!for_leaf)
                z -> m_children[i] = source -> m_children[i + m_balance_factor];
            ++i;
        }
        if (!for_leaf)
            z -> m_children[m_balance_factor + 1] = source -> m_children[m_balance_factor + 1];

        get_cnt(z) = get_cnt(source) = m_balance_factor;
    }

    void insert_trivial(shared_node_t <T> source, T key, shared_node_t <T> child = nullptr)
    {
        if (source == m_root && child)
        {
            std::cout << "err\n";
        }
        unsigned i = 1;
        while (i <= get_cnt(source) && key.getKey() > get_key(source, i))
        {
            ++i;
        }

        unsigned pos = i;
        i = get_cnt(source);
        while (i >= pos)
        {

            source -> m_keys[i + 1] = source -> m_keys[i];
            source -> m_children[i + 2] = source -> m_children[i + 1];
            i--;
        }

        auto dummy = make_shared<T>(key);
        source -> m_keys[pos] = dummy;
        ++get_cnt(source);

        if (child)
        {
            if (get_child(source, pos) && key.getKey() > get_key(get_child(source, pos), get_cnt(get_child(source, pos))))
            {
                get_child(source, pos) = child;
                child -> m_parent = source;
            } else
            {
                get_child(source, pos + 1) = child;
                child -> m_parent = source;
            }
        }

    }

    void insert(T key, shared_node_t <T> source = nullptr, shared_node_t <T> child = nullptr)
    {
        unsigned pos;
        if (!source)
        {
            auto info = search(key);
            if (info.second != 0) return;
            source = info.first;
            pos = info.second;
        }

        if (get_cnt(source) == 2 * m_balance_factor)
        {
            split(source);
            shared_node_t <T> z = source -> m_right;
            shared_node_t <T> parent = source -> m_parent;
            if (key.getKey() > get_key(z, 1))
            {
                insert_trivial(z, key);
            } else
            {
                insert_trivial(source, key);
            }


            if (!parent)
            {
                parent = make_shared<Node <T>>(m_balance_factor);
                parent -> m_parent = parent -> m_right = parent -> m_left = nullptr;
                parent -> m_is_leaf = false;
                m_root = parent;


                get_child(parent, 1) = source;
                get_child(parent, 2) = z;
                source -> m_parent = parent;
                z -> m_parent = parent;
                parent -> m_keys[1] = source -> m_keys[get_cnt(source)];
                get_cnt(parent) = 1;
                return;
            }
            T dummy(get_key(source, get_cnt(source)));

            insert(dummy, parent, z);
        } else
        {
            insert_trivial(source, key, child);
        }
    }
















    /*
    void insert(T key, shared_node_t <T> source = nullptr, shared_node_t <T> child = nullptr)
    {
        shared_node_t <T> leaf;
        if (source)
        {
            leaf = source;
        }
        else
        {
            auto info = search(key);

            // the key is already there
            if (info.second != 0) return;

            else
            {
                leaf = info.first;
            }
        }

        if (get_cnt(leaf) == 2 * m_balance_factor)
        {
            shared_node_t <T> z = make_shared<Node <T> >(m_balance_factor);
            unsigned i = 1;
            while (i <= m_balance_factor)
            {
                z -> m_keys[i] = leaf -> m_keys[i + m_balance_factor];
                if (!z -> m_is_leaf)
                    z -> m_children[i] = leaf -> m_children[i + m_balance_factor];
                ++i;
            }
            if (!z -> m_is_leaf)
                z -> m_children[m_balance_factor + 1] = leaf -> m_children[2 * m_balance_factor + 1];

            get_cnt(z) = m_balance_factor;
            get_cnt(leaf) = m_balance_factor;

            if (key.getKey() > get_key(z, 1))
            {
                insert_trivial(z, key, source, child);
            } else
            {
                insert_trivial(leaf, key, source, child);
            }

            shared_node_t <T> parent = leaf -> m_parent;

            // good
            if (!parent)
            {
                parent = make_shared<Node <T> >(m_balance_factor);
                parent -> m_parent = parent -> m_left = parent -> m_right = nullptr;
                parent -> m_is_leaf = false;
                leaf -> m_parent = parent;
                z -> m_parent = parent;
                get_child(parent, 1) = leaf;
                get_child(parent, 2) = z;
                ++get_cnt(parent);

                leaf -> m_right = z;
                z -> m_left = leaf;

                T dummy(get_key(leaf, get_cnt(leaf)));
                parent ->m_keys[1] = make_shared<T>(dummy);

                m_root = parent;
                return;
            }

            leaf -> m_right = z;
            z -> m_left = leaf;
            z -> m_parent = leaf -> m_parent;

            T dummy(get_key(z, get_cnt(z)));
            insert(dummy, parent, z);


        } else
        {
            insert_trivial(leaf, key, source, child);
        }
    }

    // ok inserts T not unsigned

    void insert_trivial(shared_node_t <T> leaf, T key, shared_node_t <T> legacy_source, shared_node_t <T> child)
    {
        if (legacy_source)
        {
            unsigned i = 1;
            while (i <= get_cnt(leaf) && key.getKey() > get_key(leaf, i))
            {
                ++i;
            }

            unsigned pos = i;

            i = get_cnt(leaf);
            while (i >= pos)
            {
                //get_key(leaf, i + 1) = get_key(leaf, i);
                leaf -> m_keys[i + 1] = leaf -> m_keys[i];
                --i;
            }

            //get_key(leaf, pos) = key;
            get_child(leaf, pos + 1) = child;
            leaf -> m_keys[pos] = make_shared<T>(key);
            ++get_cnt(leaf);

        } else
        {
            // shift children so as to make them correspond to the current positions of the keys
            unsigned i = 1;
            while (i <= get_cnt(leaf) && key.getKey() > get_key(leaf, i))
            {
                ++i;
            }

            unsigned pos = i;

            i = get_cnt(leaf);
            while (i >= pos)
            {
                //get_key(leaf, i + 1) = get_key(leaf, i);
                leaf -> m_keys[i + 1] = leaf -> m_keys[i];
                //get_child(leaf, i + 2) = get_child(leaf, i + 1);
                leaf -> m_children[i + 2] = leaf -> m_children[i + 1];
                --i;
            }
            ///get_child(leaf, pos + 1) = get_child(leaf, pos);

            leaf -> m_keys[pos] = make_shared<T>(key);
            ++get_cnt(leaf);
        }
    }*/

    shared_node_t <T> m_root;
private:

    // пр балансе надо смотреть не на m_counter а на кол-во узлов внутри !

    unsigned m_counter;
    unsigned m_balance_factor;
};




#endif //B_TREE_BPT_H
