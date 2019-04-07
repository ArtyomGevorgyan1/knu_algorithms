//
// Created by artyom on 03.04.19.
//

#ifndef FIB_HEAP_FH_H
#define FIB_HEAP_FH_H

#include <memory>
#include <vector>
#include "List.h"

#define MAGIC 1000

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

    static shared_ptr <FH <T>> unify(shared_ptr <FH <T>> h1, shared_ptr <FH <T>> h2)
    {
        FH <T> h;
        h.m_min = h1 -> m_min;
        auto h1p = make_shared<List <T>>(h1 -> m_root_list);
        auto h2p = make_shared<List <T>>(h2 -> m_root_list);
        h.m_root_list.join(h1p);
        h.m_root_list.join(h2p);
        if (h1 -> m_min == nullptr || (h2 -> m_min != nullptr && (h2 -> m_min ->m_key.getKey() < h1 -> m_min -> m_key.getKey())))
        {
            h.m_min = h2 -> m_min;
        }
        h.m_count = h1 -> m_count + h2 -> m_count;
        auto ret = make_shared<FH <T>>(h);
        return ret;
    }

    shared_ptr <Node <T>> extract_min()
    {
        auto z = m_min;
        if (z)
        {
            for (auto x : z -> m_child_list)
            {
                x -> m_parent = nullptr;
                m_root_list.insert(x);
            }
            m_root_list.remove(z);
            if (z == z -> m_right)
            {
                m_min = nullptr;
            }
            else
            {
                m_min = z -> m_right;
                consolidate();
            }
            m_count--;
        }
        return z;
    }

    void consolidate ()
    {
        shared_ptr <Node <T>> A[MAGIC];
        for (int i = 0; i < MAGIC; i++)
        {
            A[i] = nullptr;
        }
        for (auto w : m_root_list)
        {
            shared_ptr <Node <T>> x = w;
            unsigned d = x -> m_degree;
            while (A[d] != nullptr)
            {
                shared_ptr <Node <T>> y = A[d];
                if (x -> m_key.getKey() > y -> m_key.getKey())
                {
                    swap(x, y);
                }
                link(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
        }
        m_min = nullptr;
        for (int i = 0; i < MAGIC; i++)
        {
            if (A[i] != nullptr)
            {
                if (m_min == nullptr)
                {
                    m_root_list.insert(A[i]);
                    m_min = A[i];
                } else
                {
                    m_root_list.insert(A[i]);
                    if (A[i] -> m_key.getKey() < m_min -> m_key.getKey())
                    {
                        m_min = A[i];
                    }
                }
            }
        }
    }

    void link(shared_ptr <Node <T>> y, shared_ptr <Node <T>> x)
    {
        m_root_list.remove(y);
        x -> m_child_list.insert(y);
        x -> m_degree++;
        y -> m_mark = false;
    }



    // log2(n) + 1

    // implement link

    // this will be moved to private soon
    shared_ptr <Node <T>> m_min;
    unsigned m_count;
    List <T> m_root_list;

private:

};

#endif //FIB_HEAP_FH_H
