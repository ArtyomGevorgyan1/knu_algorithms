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
class List
{
public:

    /*NEEDS CONSTRUCTOR*/

    List <T> () : m_count(0), m_head(nullptr), m_tail(nullptr)
    {

    }

    void insert(shared_ptr <Node <T>> item)
    {
        item -> m_left = item -> m_right = nullptr;
        if (m_head == m_tail  && m_head  == nullptr)
        {
            m_head = m_tail = item;
        } else if (m_head == m_tail)
        {
            m_head = item;
            m_head -> m_left = m_tail;
            m_head -> m_right = m_tail;
            m_tail -> m_right = m_head;
            m_tail -> m_left = m_head;
            m_count = m_count;
        }
        else
        {
            m_head -> m_right = item;
            item  -> m_left = m_head;
            m_tail -> m_left = item;
            item -> m_right = m_tail;
            m_head = item;
        }
        ++m_count;
    }

    // debug
    bool remove(shared_ptr <Node <T>> item)
    {
        shared_ptr <Node <T>> cur = m_tail;

        if (!cur)
        {
            return false;
        }

        int counter = 0;

        while (counter < m_count)
        {

            if (cur -> m_key.getKey() == item -> m_key.getKey())
            {
                if (cur -> m_key.getKey() == m_head -> m_key.getKey())
                {
                    if (m_head == m_tail)
                    {
                        m_head = m_tail = nullptr;
                        m_count--;
                        return true;
                    }
                    shared_ptr <Node <T>> temp = m_head -> m_right;
                    m_head = m_head -> m_left;
                    m_head -> m_right = temp;
                    temp -> m_left = m_head;
                    m_count--;
                    return true;

                } else if (cur -> m_key.getKey() == m_tail -> m_key.getKey())
                {
                    if (!m_tail -> m_right)
                    {
                        m_tail = m_head = nullptr;
                        m_count--;
                        return true;
                    }
                    shared_ptr <Node <T>> temp = m_tail -> m_left;
                    m_tail = m_tail -> m_right;
                    m_tail -> m_left = temp;
                    temp -> m_right = m_tail;
                    m_count--;
                    return true;
                } else
                {
                    shared_ptr <Node <T>> temp = cur -> m_right;
                    cur = cur -> m_left;
                    cur -> m_right = temp;
                    temp -> m_left = cur;
                    m_count--;
                    return true;
                }
            }
            cur = cur -> m_right;
            counter++;
        }
        return false;
    }

    //not tested at all
    void join(shared_ptr <List> second)
    {
        shared_ptr <Node <T>> cur = second -> m_tail;

        if (!cur) return;

        while (cur && cur != second -> m_tail)
        {
            insert(cur);
            cur = cur -> m_right;
            if (cur && cur == second -> m_tail)
            {
                insert(cur);
                break;
            }
        }
    }

    // not tested
    // todo iterator
    //

    shared_ptr <Node <T>> m_head, m_tail;
    unsigned m_count;
};

template <typename T>
class FH {
public:

    FH() : m_count(0), m_min(nullptr)
    {
        // root list is intialized when insertion is done
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
            m_root_list();
            m_min = x;
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
            // add x to the root list
            // x.p = nil

        }
        m_root_list.remove(z);
        // if z is only child remove it
        // else make its successor the nw min and call consolidate
        m_count--;
        return z;
    }



    shared_ptr <Node <T>> m_min;
    unsigned m_count;
    List <T> m_root_list;

private:

};


#endif //FIB_HEAP_FH_H
