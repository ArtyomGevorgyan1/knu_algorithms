#define get_key(k, i) k -> m_keys[i] -> getKey()
#define get_cnt(k) k -> m_count
#define get_child(k, i) k -> m_indexed[i]

#include <iostream>
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

template <typename T>
struct Node {

    explicit Node (unsigned balance_factor, bool leaf = true, const shared_node_t <T> &parent = nullptr,
                   const shared_node_t <T> &left = nullptr, const shared_node_t <T> &right = nullptr) :
    m_is_leaf(leaf), m_left(left), m_right(right)
    {
        if (!leaf)
        {
            m_indexed.resize(balance_factor + 2);
        }
        m_count = 0;
        m_keys.resize(2 * balance_factor + 1);
        m_parent = parent;
    }

    vector <shared_ptr<Node<T>>> m_indexed;
    vector <shared_ptr<T>> m_keys;
    shared_node_t <T> m_parent, m_left, m_right;
    unsigned m_count;
    bool m_is_leaf;
};

template <typename T>
class BPT {
public:

    unsigned m_counter;
    unsigned m_balance_factor;
    shared_node_t <T> m_root;

    explicit BPT (unsigned balance_factor) : m_balance_factor(balance_factor)
    {
        // create a leaf with null parent
        m_root = make_shared<shared_node_t <T>>(balance_factor);
    }

    /*
    bool insert(T key)
    {
        ++m_counter;


    }
     */

    pair <shared_node_t <T>, unsigned > search_leaf(T key)
    {
        shared_node_t <T> cur = m_root;
        unsigned i;
        while (!cur -> m_is_leaf)
        {
            i = 1;
            while (i <= get_cnt(cur) && key.geyKey() > get_key(cur, i))
            {
                ++i;
            }
            cur = get_child(cur, i);
        }
    }

    pair <shared_node_t <T>, unsigned > find_position (shared_node_t <T> source, T key)
    {
        unsigned i = 1;
        while (i <= get_cnt(source) && key.getKey() > get_key(source, i))
        {
            ++i;
        }

        if (i == 2 * m_balance_factor) return std::make_pair<shared_node_t <T>, unsigned >(nullptr, 0);
        else return std::make_pair<shared_node_t <T>, unsigned >(source, i);
    }

    bool remove(T key)
    {
        shared_node_t <T> leaf = search_leaf(key);
        pair <shared_node_t <T> , unsigned > result = find_position(leaf, key);
        if (!result.first)
        {
            return false;
        }

        remove_from_node(result.first, result.second);

        if (get_cnt(leaf) <= m_balance_factor - 1)
        {
            shared_node_t <T> sibling;

            // there has to be at least one sibling of leaf
            if (leaf -> m_left)
                sibling = leaf -> m_left;
            else
                sibling = leaf -> m_right;

            if (get_cnt(sibling) <= m_balance_factor + 1)
            {
                // fusion
                fuse(leaf, sibling);
            } else
            {
                // sharing
                share(leaf, sibling);
            }
        }

        m_counter--;
    }

    // ok
    bool remove_from_node (const shared_node_t<T> &leaf, unsigned pos)
    {
        unsigned i = pos;
        while (i <= get_cnt(leaf))
        {
            get_key(leaf, i + 1) = get_key(leaf, i);
        }

        i = pos;
        while (i <= get_cnt(leaf) + 1)
        {
            get_child(leaf, i + 1) = get_child(leaf, i);
        }

        --get_cnt(leaf);
    }


    // ok
    void share (shared_node_t <T> source, shared_node_t <T> sibling)
    {
        bool sibling_is_right = false;
        if (source -> m_right && source -> m_right == sibling)
            sibling_is_right = true;

        if (sibling_is_right)
        {
            // get the new delimiter
            shared_ptr <T> new_delim = get_key(sibling, 1);
            // get the child
            shared_node_t <T> new_child = get_child(sibling, 1);

            /// move the keys of sibling left - i.e. shrink it

            // keys
            unsigned i = 1;
            while (i <= get_cnt(sibling) - 1)
            {
                get_key(sibling, i) = get_key(sibling, i + 1);
                ++i;
            }

            //children
            i = 1;
            while (i <= get_cnt(sibling))
            {
                get_key(sibling, i) = get_key(sibling, i + 1);
                ++i;
            }

            // don't forget this -- cnt
            --get_cnt(sibling);

            // now insert the old delimiter to the right position in source
            get_key(source, get_cnt(source) + 1) = get_key(source -> m_parent, find_position(source -> m_parent, source));

            // the same with child
            get_child(source, get_cnt(source) + 2) = new_child;

            // update the size of the source
            ++get_cnt(source);

            get_key(source -> m_parent, find_position(source -> m_parent, source)) = new_delim;
        } else // the sibling is to the left
        {
            // get the new delimiter
            shared_node_t <T> new_delim = get_key(sibling, get_cnt(sibling));

            // get the new child
            shared_node_t <T> new_child = get_child(sibling, get_cnt(sibling) + 1);

            // free space for a new node inside of source - i.e. shift it to the right

            unsigned i = 1;
            while (i <= get_cnt(source))
            {
                get_key(source, i + 1) = get_key(source, i);
                get_child(source, i + 1) = get_child(source, i);
                ++i;
            }
            get_child(source, get_cnt(source) + 2) = get_child(source, get_cnt(source) + 1);

            // insert the data
            get_child(source, 1) = new_child;
            shared_ptr <T> new_key = get_key(source -> m_parent, find_position(source -> m_parent, source) - 1);
            get_key(source, 1) = new_key;

            // update cnt!
            ++get_cnt(source);

            get_key(source -> m_parent, find_position(source -> m_parent, source) -1) = new_delim;
        }
    }

    //checking - ok need to check merge
    void fuse(shared_node_t<T> leaf, shared_node_t<T> sibling)
    {
        shared_node_t <T> parent = leaf -> m_parent;
        bool sibling_left = (leaf -> m_left == sibling);
        if (sibling_left)
        {
            if (leaf -> m_is_leaf)
            {
                // merge
                merge(leaf, sibling, false);
            } else
            {
                // merge and replace
                merge(leaf, sibling, false, find_position(parent, leaf) - 1, parent);
            }
        } else // sibling is to the right
        {
            if (leaf -> m_is_leaf)
            {
                // merge
                merge(leaf, sibling, true);
            } else
            {
                // merge and replace
                merge(leaf, sibling, true, find_position(parent, leaf), parent);
            }

        }

        if (sibling_left)
            remove_from_node(parent, find_position(parent, leaf) - 1);
        else
            remove_from_node(parent, find_position(parent, leaf));
    }


    // todo optimization - move approx. half of the sum of the children in 2 nodes to the leaf (share function)

};