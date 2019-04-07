//
// Created by artyom on 03.04.19.
//

#ifndef FIB_HEAP_FH_H
#define FIB_HEAP_FH_H

#include <memory>
#include <vector>
#include "List.h"

using std::shared_ptr;
using std::make_shared;
using std::vector;


// will be tested when list works
template <typename T>
class FH {
public:

    FH() : m_count(0), m_min(nullptr), m_root_list()
    {

    }

    shared_ptr <Node <T>> insert(T key)
    {
        shared_ptr <Node <T>> _key = make_shared<Node <T>>(key);
        return insert_ptr(_key);
    }

    shared_ptr <Node <T>> insert_ptr(shared_ptr <Node <T>> &x)
    {
        x -> m_degree = 0;
        x -> m_parent = nullptr;
        x -> m_child = nullptr;
        x -> m_mark = false;
        if (m_min == nullptr)
        {
            m_min = x;
            m_root_list.insert(x);
        } else
        {
            m_root_list.insert(x);
            if (x -> m_key.getKey() < m_min -> m_key.getKey())
            {
                m_min = x;
            }
        }
        m_count++;
        return x;
    }

    shared_ptr <FH <T>> unify(shared_ptr <FH<T>> first, shared_ptr <FH <T>> second)
    {
        shared_ptr <FH <T>> new_heap = make_shared<FH <T>>();
        new_heap -> m_min = first -> m_min;
        new_heap -> m_root_list.join(first);
        new_heap -> m_root_list.join(second);
        if (!first -> m_min || (!second -> m_min && (second -> m_min -> m_key.getKey() < first -> m_min -> m_key.getKey())))
        {
            new_heap -> m_min = second -> m_min;
        }
        new_heap -> m_count = first -> m_count + second -> m_count;
        return new_heap;
    }

    shared_ptr <Node <T>> extract_min()
    {
        shared_ptr <Node <T>> z = m_min;
        if (z)
        {
            // add each child of z - x - to the root list

            // x.p = nil
        }
        m_root_list.remove(z);
        if (z == m_root_list.m_head && m_root_list.m_head == m_root_list.m_tail)
        {
            m_min = nullptr;
        } else
        {
            m_min = z -> m_right;
            //consolidate();
        }
        m_count--;
        return z;
    }

    // this will be moved to private soon
    shared_ptr <Node <T>> m_min;
    unsigned m_count;
    List <T> m_root_list;

private:

};

#endif //FIB_HEAP_FH_H
