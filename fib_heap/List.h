//
// Created by artyom on 07.04.19.
//

#ifndef FIB_HEAP_LIST_H
#define FIB_HEAP_LIST_H



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

template <typename T> class List;

template <typename T> class ListIterator
{
public:

    // this is called from end() / begin() function only, so this constructor is
    // technically valid in the context of this program
    // the index is either 0 or m_size of the container object

    ListIterator(List <T> &container, unsigned index)
            :   m_cotainer(container), m_index(index)
    {
        if (index == container.m_count)
        {
            // refers to the object that is one-past-the last one
            m_cur_item = container.m_tail;
        } else if (index == 0)
        {
            m_cur_item = container.m_tail;
        } else // this should never be called
        {
            throw std::logic_error("poor design xD");
            m_cur_item = nullptr;
        }
    }

    bool operator != (const ListIterator& other)
    {
        return (m_index != other.m_index);
    }

    const ListIterator& operator ++()
    {
        m_cur_item = m_cur_item -> m_right;
        m_index++;
    }

    shared_ptr<Node <T>> operator *()
    {
        return m_cur_item;
    }

private:
    unsigned m_index;
    shared_ptr <Node <T>> m_cur_item;
    List <T> &m_cotainer;
};

template <typename T>
class List
{
public:

    // needs default constructor

    ListIterator <T> begin()
    {
        return  ListIterator <T> (*this, 0);
    }

    ListIterator <T> end()
    {
        return ListIterator <T> (*this, m_count);
    }

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

        if (cur == second -> m_head)
        {
            insert(cur);
            return;
        }

        while (cur && cur != second -> m_head)
        {
            insert(cur);
            cur = cur -> m_right;
            if (cur == second -> m_head)
            {
                insert(cur);
                break;
            }
        }
    }

    shared_ptr <Node <T>> m_head, m_tail;
    unsigned m_count;
};

#endif //FIB_HEAP_LIST_H
