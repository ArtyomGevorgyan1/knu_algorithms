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
}

TEST (insert_root_list, two) {
    FH<Book> h;
    Book b(1);
    shared_ptr <Node <Book>> ptr = make_shared<Node <Book>>(b);
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
        EXPECT_EQ(cur -> m_key.getKey(), val);
        val++;
        cur = cur -> m_right;
    }
}