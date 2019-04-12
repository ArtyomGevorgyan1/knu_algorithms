//
// Created by artyom on 11.04.19.
//

#ifndef BINOM_HEAP_B_HEAP_H
#define BINOM_HEAP_B_HEAP_H

#include <memory>
#include <utility>

using std::make_shared;
using std::shared_ptr;
using std::make_pair;

#include "List.h"

#define DUMMY_MAX 4

template <typename T>
class BinaryHeap
{
public:

    BinaryHeap() : m_root_list()
    {

    }

    void merge(shared_ptr <BinaryHeap> to_merge)
    {
        shared_ptr <Node <T>> roots_internal[DUMMY_MAX + 1];
        shared_ptr <Node <T>> roots_external[DUMMY_MAX + 1];
        shared_ptr <Node <T>> roots[DUMMY_MAX + 1];
        for (int i = 0; i < DUMMY_MAX + 1; i++)
        {
            roots_internal[i] = nullptr;
            roots_external[i] = nullptr;
            roots[i] = nullptr;
        }

        for (auto i : m_root_list)
        {
            roots_internal[i -> m_degree] = i;
        }

        for (auto i : to_merge -> m_root_list)
        {
            roots_external[i -> m_degree] = i;
        }

        // do binary addition of nodes
        shared_ptr <Node <T>> carry = nullptr;
        for (int i = 0; i < DUMMY_MAX + 1; i++)
        {
            if (roots_external[i] && roots_internal[i] && !carry)
            {
                create_k_plus_one_node(roots_internal[i], roots_external[i]);
                carry = roots_internal[i];
            } else if (roots_external[i] && roots_internal[i] && carry)
            {
                roots[i] = carry;
                create_k_plus_one_node(roots_internal[i], roots_external[i]);
                carry = roots_internal[i];
            } else if (roots_external[i] && roots_internal[i] == nullptr && carry)
            {
                create_k_plus_one_node(roots_external[i], carry);
                carry = roots_external[i];
            } else if (roots_external[i] == nullptr && roots_internal[i] && carry)
            {
                create_k_plus_one_node(roots_internal[i], carry);
                carry = roots_internal[i];
            } else if (roots_external[i] == nullptr && roots_internal[i] && !carry)
            {
                roots[i] = roots_internal[i];
            } else if (roots_external[i] && roots_internal[i] == nullptr && !carry)
            {
                roots[i] = roots_external[i];
            }
        }

        // remove roots from m_roots_list
        vector <shared_ptr <Node <T>>> vec;
        for (auto i : m_root_list)
        {
            vec.push_back(i);
        }

        for (auto i : vec)
        {
            m_root_list.remove(i, false);
        }

        // add roots
        for (int i = 0;  i < DUMMY_MAX + 1; i++)
        {
            if (roots[i])
            {
                m_root_list.insert(roots[i]);
            }
        }
    }

    void create_k_plus_one_node (shared_ptr <Node <T>> first, shared_ptr <Node <T>> second)
    {
        first -> m_child_list.insert(second);
        ++first -> m_degree;
        second -> m_parent = first;
    }

    void insert(T key)
    {
        shared_ptr <Node <T>> keynode_ptr = make_shared<Node <T>>(key);
        shared_ptr <BinaryHeap <T>> key_heap = make_shared <BinaryHeap <T>>();
        key_heap -> m_root_list.insert(keynode_ptr);
        merge(key_heap);
    }

private:
    List <T> m_root_list;
};

#endif //BINOM_HEAP_B_HEAP_H
