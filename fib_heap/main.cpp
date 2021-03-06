#include <gtest/gtest.h>
#include "FH.h"

using namespace std;


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


/* tests for linked list*/

TEST (insert_root_list, empty) {
    FH<Book> h;
    EXPECT_EQ(h.m_root_list.m_head, h.m_root_list.m_tail);
    EXPECT_EQ(h.m_root_list.m_tail, nullptr);
    EXPECT_EQ(h.m_root_list.m_count, 0);
}

TEST (insert_root_list, single) {
    FH<Book> h;
    Book b(1);
    h.insert(b);
    EXPECT_EQ(h.m_root_list.m_tail, h.m_root_list.m_head);
    EXPECT_NE(h.m_root_list.m_head, nullptr);
    EXPECT_EQ(h.m_root_list.m_head -> m_key.getKey(), 1);
    EXPECT_EQ(h.m_root_list.m_count, 1);
    EXPECT_EQ(h.m_root_list.m_head -> m_right, h.m_root_list.m_head);
    EXPECT_EQ(h.m_root_list.m_tail -> m_right, h.m_root_list.m_head);
}

TEST (insert_root_list, multiple) {
    FH<Book> h;

    for (int i = 0; i < 5; i++)
    {
        Book b(i);
        h.insert(b);
    }

    EXPECT_NE(h.m_root_list.m_head, nullptr);
    EXPECT_NE(h.m_root_list.m_head, h.m_root_list.m_tail);
    EXPECT_EQ(h.m_root_list.m_count, 5);

    shared_ptr <Node <Book>> cur = h.m_root_list.m_tail;
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

    EXPECT_EQ(h.m_root_list.remove(ptr), false);
}

TEST(remove_root_list, single)
{
    FH <Book> h;
    Book b(0);
    shared_ptr <Node <Book>> ptr = make_shared<Node <Book>>(b);
    h.insert_ptr(ptr);
    h.m_root_list.remove(ptr);
    EXPECT_EQ(h.m_root_list.m_count, 0);
    EXPECT_EQ(h.m_root_list.m_head, h.m_root_list.m_tail);
    EXPECT_EQ(h.m_root_list.m_head, nullptr);
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
        h.m_root_list.insert(ptr);
    }

    // check that it leaves the list in a valid state

    // remove key 1
    h.m_root_list.remove(vec[1]);
    EXPECT_EQ(h.m_root_list.m_count, 4);
    EXPECT_EQ(h.m_root_list.search_by_value(0) -> m_right -> m_key.getKey(), 2);
    EXPECT_EQ(h.m_root_list.search_by_value(2) -> m_left -> m_key.getKey(), 0);
    // remove key 0
    h.m_root_list.remove(vec[0]);
    EXPECT_EQ(h.m_root_list.m_count, 3);
    EXPECT_EQ(h.m_root_list.search_by_value(4) -> m_right -> m_key.getKey(), 2);
    EXPECT_EQ(h.m_root_list.search_by_value(2) -> m_left -> m_key.getKey(), 4);
    // remove key 4
    h.m_root_list.remove(vec[4]);
    EXPECT_EQ(h.m_root_list.m_count, 2);
    EXPECT_EQ(h.m_root_list.search_by_value(3) -> m_right -> m_key.getKey(), 2);
    EXPECT_EQ(h.m_root_list.search_by_value(2) -> m_left -> m_key.getKey(), 3);
    EXPECT_EQ(h.m_root_list.search_by_value(2) -> m_right -> m_key.getKey(), 3);
    EXPECT_EQ(h.m_root_list.search_by_value(3) -> m_left -> m_key.getKey(), 2);
    // remove key 2
    h.m_root_list.remove(vec[2]);
    EXPECT_EQ(h.m_root_list.m_count, 1);
    EXPECT_EQ(h.m_root_list.search_by_value(3) -> m_left -> m_key.getKey(), 3);
    EXPECT_EQ(h.m_root_list.search_by_value(3) -> m_right -> m_key.getKey(), 3);
    // remove key 3
    h.m_root_list.remove(vec[3]);
    EXPECT_EQ(h.m_root_list.m_count, 0);
}

TEST(join_root_list, base)
{
    FH <Book> h;
    for (int i = 0; i < 5; i++)
    {
        Book b(i);
        h.insert(b);
    }

    FH <Book> h1;
    for (int i = 5; i < 10; i++)
    {
        Book b(i);
        h.insert(b);
    }

    auto ptr = make_shared<List <Book>>(h1.m_root_list);
    h.m_root_list.join(ptr);

    int cur = 0;
    for (auto i : h.m_root_list)
    {
        EXPECT_EQ(i -> m_key.getKey(), cur);
        cur++;
    }
}

/* tests for fib heap functions*/

// insert test

TEST(fh_insert, base)
{
    FH <Book> h;
    for (int i = 0; i < 5; i++)
    {
        Book b(i);
        h.insert(b);
    }
    EXPECT_EQ(h.m_count, 5);
}

TEST(fh_unify, base)
{
    FH <Book> h1;
    for (int i = 0; i < 5; i++)
    {
        Book b(i);
        h1.insert(b);
    }

    FH <Book> h2;
    for (int i = 5; i < 10; i++)
    {
        Book b(i);
        h2.insert(b);
    }

    shared_ptr <FH <Book>> h = FH<Book>::unify(make_shared<FH <Book>>(h1), make_shared<FH <Book>>(h2));
    EXPECT_EQ(h -> m_count, 10);
    // etc ...
}

TEST(fh_extract, base)
{
    FH <Book> h;
    for (int i = 0; i < 10; i++)
    {
        Book b(i);
        h.insert(b);
    }

    for (int i = 0; i < 10; i++)
    {
        auto min = h.extract_min();
        EXPECT_EQ(min -> m_key.getKey(), i);
    }
}



#include <fstream>
#include <stack>
using std::stack;

/*
vector <shared_ptr<Node <Book>>> get_children(shared_ptr <Node <Book>> src, ostream &o)
{
    vector <shared_ptr <Node <Book>>> vec;
    for (auto i : src -> m_child_list)
    {
        vec.push_back(i);
    }
    return vec;
}
*/

void walk(shared_ptr <Node <Book>> src, ostream &o)
{
    for (auto i : src -> m_child_list)
    {
        if(i -> m_right != i)
        {
            o << i -> m_key.getKey() << " -> " << i -> m_right -> m_key.getKey() << ";\n";
        }
        o << '\t' << src -> m_key . getKey() << " -> " << i -> m_key.getKey() << '\n';
        walk(i, o);
    }
}

void stackWrite(FH <Book> &h) {
    ofstream dotFile;
    dotFile.open ("./gr.dot");
    dotFile << "digraph {\n";
    //dotFile << "\t" << "a" << " [fillcolor=red style=filled];";

    for (auto i : h.m_root_list)
    {
        dotFile << '\t' << i -> m_key.getKey() << " [fillcolor=red style=filled];" << '\n';
        if (i -> m_right != i) {
            dotFile << '\t' << i->m_key.getKey() << " -> " << i->m_right->m_key.getKey() << ";\n";
            //dotFile << '\t' << i->m_key.getKey() << " -> " << i->m_left->m_key.getKey() << ";\n";
        }
        walk(i, dotFile);
    }

    dotFile << "}\n";
    dotFile.close();
}

void show(FH <Book> &h) {
    stackWrite(h);
    system("./show_png.sh");
}


int main()
{
    FH <Book> h;
    for (int  i= 0;  i< 10; i ++)
    {
        Book b(i);
        h.insert(b);
    }
    for (int i = 0; i < 5; i++)
    {
        h.extract_min();
    }
    show(h);
}