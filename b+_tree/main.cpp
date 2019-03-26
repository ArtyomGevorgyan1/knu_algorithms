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



    // useless variable
    //unsigned m_counter;
    unsigned m_balance_factor;
    shared_node_t <T> m_root;
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}