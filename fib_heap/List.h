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
class List;

template <typename T>
struct Node {

    explicit Node(T key) : m_key(key), m_degree(0), m_mark(false), m_child(nullptr), m_parent(nullptr), m_child_list()
    {

    }

    T m_key;
    int m_degree;
    shared_ptr <Node <T>> m_child, m_parent, m_left, m_right;
    List <T> m_child_list;
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
            item -> m_left = item -> m_right = item;
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

    shared_ptr <Node <T>> search_by_value(T key)
    {
        for (auto i : *this)
        {
            if (i -> m_key.getKey() == key.getKey())
            {
                return i;
            }
        }
        return nullptr;
    }

    shared_ptr <Node <T>> search_by_ref(shared_ptr <Node <T>> key)
    {
        for (auto i : *this)
        {
            if (i -> m_key.getKey() == key -> m_key.getKey())
            {
                return i;
            }
        }
        return nullptr;
    }

    bool remove(shared_ptr <Node <T>> item, bool by_value = true)
    {
        if (!m_count)
        {
            return false;
        }

        shared_ptr <Node <T>> to_remove;
        if (by_value)
        {
            to_remove = search_by_value(item -> m_key.getKey());
        } else
        {
            to_remove = search_by_ref(item);
        }

        if (to_remove)
        {
            // only child
            if (to_remove -> m_right == nullptr && to_remove -> m_left == nullptr)
            {
                m_head = m_tail = nullptr;
            } else
            {
                if (m_head == to_remove && to_remove == m_tail)
                {
                    m_head = m_tail = nullptr;
                    m_count--;
                    return true;
                }

                if (m_head == to_remove)
                {
                    m_head = m_head -> m_left;
                    m_tail -> m_left = m_head;
                } else if (m_tail == to_remove)
                {
                    m_tail = m_tail -> m_right;
                    m_head -> m_right = m_tail;
                }

                auto prev = to_remove -> m_left, next = to_remove -> m_right;
                prev -> m_right = next;
                next -> m_left = prev;
            }
            m_count--;
            return true;
        } else
        {
            return false;
            // todo throw exception instead
        }
    }

    void join(shared_ptr < List <T> > second)
    {
        for (auto i : *second)
        {
            insert(i);
        }
    }

    shared_ptr <Node <T>> m_head, m_tail;
    unsigned m_count;
};

#endif //FIB_HEAP_LIST_H
