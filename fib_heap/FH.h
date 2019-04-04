//
// Created by artyom on 03.04.19.
//

#ifndef FIB_HEAP_FH_H
#define FIB_HEAP_FH_H

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;
using std::vector;

template <typename T>
struct Node {

    Node(T key) : m_key(key), m_degree(0), m_mark(false), m_child(nullptr), m_parent(nullptr)
    {

    }

    T m_key;
    int m_degree;
    shared_ptr <Node <T>> m_child, m_parent;
    bool m_mark;
};

template <typename T>
class FH {
public:

    FH() : m_count(0), m_min(nullptr)
    {
        m_roots.resize(0);
    }

    void insert(T key) {
        shared_ptr<Node<T> > x = make_shared<Node<T> >(key);
        if (!m_min) {
            m_roots.push_back(x);
            m_min = x;
        } else {
            m_roots.push_back(x);
            if (m_min->m_key.getKey() > x->m_key.getKey()) {
                m_min = x;
            }
        }
        ++m_count;
    }

    shared_ptr <FH> unite(shared_ptr <FH> &first, shared_ptr <FH> &second)
    {
        shared_ptr <FH> z = make_shared <FH>();
        z -> m_min = first -> m_min;

        for (unsigned i = 0; i < first -> m_roots.size(); ++i)
        {
            z -> m_roots.push_back(first -> m_roots[i]);
        }

        for (unsigned i = 0; i < second -> m_roots.size(); ++i)
        {
            z -> m_roots.push_back(second -> m_roots[i]);
        }

        if (first -> m_min == nullptr || first -> m_min -> m_key.getKey() > second -> m_min -> m_key.getKey())
        {
            z -> m_min = second -> m_min;
        }

        z -> m_count = first -> m_count + second -> m_count;
        return z;
    }



private:
    shared_ptr <Node <T>> m_min;
    vector <shared_ptr <Node <T>> > m_roots;
    unsigned m_count;
};


#endif //FIB_HEAP_FH_H
