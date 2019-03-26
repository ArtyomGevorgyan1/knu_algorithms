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

    explicit Node (unsigned balance_factor, bool leaf = true, const shared_node_t <T> &parent = nullptr) :
    m_is_leaf(leaf)
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
    shared_node_t <T> m_parent;
    unsigned m_count;
    bool m_is_leaf;
};

template <typename T>
class BPT {
public:

    BPT(unsigned balance_factor) : m_balance_factor(balance_factor)
    {
        m_root = make_shared<shared_node_t <T>>(m_balance_factor);
    }

    // finds the leaf where the key should lay
    pair <shared_node_t <T>, unsigned > get_leaf(const shared_node_t <T> &key)
    {
        shared_node_t <T> cur = m_root;
        while (!m_root -> m_is_leaf)
        {
            unsigned i = 1;
            while (i <= get_cnt(cur) && key.getKey() > get_key(cur, i))
            {
                ++i;
            }
        }
        return cur;
    };


    // 2t keys, we split seems good
    void split(shared_node_t <T> src, const T &key) {
        // move left / right pointers

        shared_node_t<T> n = make_shared<shared_node_t<T>>(m_balance_factor, src->m_is_leaf, src->m_parent);
        shared_ptr<T> mid = get_key(src, m_balance_factor + 1);
        unsigned i = 1;

        /// move keys
        while (i <= m_balance_factor - 1) {
            get_key(n, i) = get_key(src, 1 + m_balance_factor + i);
            ++i;
        }

        i = 1;

        // move children
        while (i <= m_balance_factor) {
            get_child(n, i) = get_child(src, m_balance_factor + 1 + i);
            ++i;
        }

        get_cnt(n);


        if (src -> m_is_leaf)
        {
            ++get_cnt(n);
            n -> m_is_leaf = true;

            unsigned i = 1;
            while (i <= get_cnt(n))
            {
                get_key(n, i + 1) = get_key(n, i);
            }
            get_key(n, 1) = mid;
            ++get_cnt(n);
        }

        if (src == m_root)
        {
            m_root = make_shared<Node <T>>(m_balance_factor, false, nullptr);
            get_cnt(m_root) = 1;
            get_child(m_root, 1) = src;
            get_child(m_root, 2) = n;
            get_key(m_root, 1) = mid;
            src -> m_parent = m_root;
            n -> m_parent = m_root;
        }

        else
        {
            n -> m_parent = src -> m_parent;
            shared_node_t <T> parent = src -> m_parent;

            unsigned pos = 1;

            while (pos <= get_cnt(parent) && get_key(parent, pos) < mid.getKey())
            {
                ++(pos);
            }

            unsigned i = pos;
            while (i <= get_cnt(parent))
            {
                get_key(parent, i + 1) = get_key(parent, i);
                ++i;
            }

            i = pos;
            while (i <= get_cnt(parent))
            {
                get_child(parent, i + 2) = get_child(parent, i + 1);
            }

            get_key(parent, pos) = mid;
            get_child(parent, pos + 1) = mid;

            i = pos + 1;
            while (i <= get_cnt(parent) + 1)
            {
                get_child(parent, i + 1) = get_child(parent, i);
                ++i;
            }

            ++get_cnt(parent);
            if (get_cnt(parent) == 2 * m_balance_factor)
            {
                split(parent);
            }
        }
    }

    // useless variable
    //unsigned m_counter;
    unsigned m_balance_factor;
    shared_node_t <T> m_root;
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}