#include <gtest/gtest.h>
#include "FH.h"

class Book;


class Book
{
public:

    Book(unsigned key) : m_key(key)
    {}

    unsigned getKey()
    {
        return m_key;
    }

private:
    unsigned m_key;
};

/* tests for linked list

TEST (insert_root_list, empty) {
    FH<Book> h;
    EXPECT_EQ(h.m_roots_head, h.m_roots_tail);
    EXPECT_EQ(h.m_roots_tail, nullptr);
    EXPECT_EQ(h.m_roots_count, 0);
}

TEST (insert_root_list, single) {
    FH<Book> h;
    Book b(1);
    shared_ptr <Node <Book>> ptr = make_shared<Node <Book>>(b);
    h.insert_to_root_list(ptr);
    EXPECT_EQ(h.m_roots_tail, h.m_roots_head);
    EXPECT_NE(h.m_roots_head, nullptr);
    EXPECT_EQ(h.m_roots_head -> m_key.getKey(), 1);
    EXPECT_EQ(h.m_roots_count, 1);
    EXPECT_EQ(h.m_roots_head -> m_right, nullptr);
    EXPECT_EQ(h.m_roots_tail -> m_right, nullptr);
}

TEST (insert_root_list, multiple) {
    FH<Book> h;

    for (int i = 0; i < 5; i++)
    {
        Book b(i);
        shared_ptr <Node <Book>> ptr = make_shared<Node <Book>>(b);
        h.insert_to_root_list(ptr);
    }

    EXPECT_NE(h.m_roots_head, nullptr);
    EXPECT_NE(h.m_roots_head, h.m_roots_tail);
    EXPECT_EQ(h.m_roots_count, 5);

    shared_ptr <Node <Book>> cur = h.m_roots_tail;
    int val = 0;

    while (cur && val < 5)
    {
        if (val == 0)
        {
            EXPECT_EQ(cur -> m_left -> m_key.getKey(), 4);
        } else if (val == 4)
        {
            EXPECT_EQ(cur -> m_right -> m_key.getKey(), 0);
        } else
        {
            EXPECT_EQ(cur -> m_left -> m_key.getKey(), val - 1);
            EXPECT_EQ(cur -> m_right -> m_key.getKey(), val + 1);
        }
        EXPECT_EQ(cur -> m_key.getKey(), val);
        val++;
        cur = cur -> m_right;
    }
}

TEST(remove_root_list, empty)
{
    FH<Book> h;
    Book b(0);
    shared_ptr <Node <Book>> ptr = make_shared<Node <Book>>(b);

    EXPECT_EQ(h.remove_from_root_list(ptr), false);
}

TEST(remove_root_list, single)
{
    FH <Book> h;
    Book b(0);
    shared_ptr <Node <Book>> ptr = make_shared<Node <Book>>(b);
    h.insert_to_root_list(ptr);

    h.remove_from_root_list(ptr);
    EXPECT_EQ(h.m_roots_count, 0);
    EXPECT_EQ(h.m_roots_head, h.m_roots_tail);
    EXPECT_EQ(h.m_roots_tail, nullptr);
}

TEST(remove_root_list, multiple)
{
    FH <Book> h;
    vector <shared_ptr <Node <Book>> > vec;
    for (int i = 0; i < 5; i++)
    {
        Book b(i);
        shared_ptr <Node <Book>> ptr = make_shared<Node <Book>>(b);
        vec.push_back(ptr);
        h.insert_to_root_list(ptr);
    }

    // check it leaves the list in a valid state

    // remove key 1
    // remove key 0
    // remove key 4
    // remove key 2
    // remove key 3
}

*/

