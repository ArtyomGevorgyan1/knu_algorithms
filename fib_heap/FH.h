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
    shared_ptr <Node <T>> m_child, m_parent, m_left, m_right;
    bool m_mark;
};

template <typename T>
class FH {
public:

    FH() : m_count(0), m_min(nullptr), m_roots_head(nullptr), m_roots_count(0)
    {

    }

    void insert_to_root_list(shared_ptr <Node <T>> item)
    {
        if (m_roots_head == m_roots_tail  && m_roots_head  == nullptr)
        {
            m_roots_head = m_roots_tail = item;
            m_roots_head -> m_right = m_roots_tail;
            m_roots_tail -> m_left = m_roots_head;
        }
        else
        {
            m_roots_head -> m_right = item;
            m_roots_head = m_roots_head -> m_right;
            m_roots_head -> m_right = m_roots_tail;
            m_roots_tail -> m_left = m_roots_head;
        }
        ++m_roots_count;
    }

    bool remove_from_root_list(shared_ptr <Node <T>> item)
    {


        --m_roots_count;
    }

    shared_ptr <Node <T>> m_min;
    shared_ptr <Node <T>> m_roots_head, m_roots_tail;
    unsigned m_count;
    unsigned m_roots_count;

private:


};


#endif //FIB_HEAP_FH_H
