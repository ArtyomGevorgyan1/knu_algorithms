#include "BPT.h"

class B {
public:
    B(unsigned i)
    {
        m = i;
    }
    unsigned getKey() {
        return m;
    }

    unsigned m;
};

#include <gtest/gtest.h>

void write()
{

}

void w(shared_node_t <B> source, int h = 0)
{
    if (!source) return;
    for (int i = 1; i <= get_cnt(source); i++)
    {
        w(get_child(source, i), h + 1);
        for (int j = 1; j <= h; j++)
            std::cout << " ";
        std::cout << get_key(source, i) << "\n";
    }
    w(get_child(source, get_cnt(source) + 1));
}

int main()
{
    B_tree <B> t(2);
    for (int i = 1; i <= 20; i++)
    {
        B tt(i);
        t.insert(tt);
    }
    w(t.m_root);
    return 0;
}

TEST(insert_trivial, test1)
{

}