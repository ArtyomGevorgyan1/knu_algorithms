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

int main()
{
    B_tree <B> t(2);
    for (int i = 1; i <= 20; i++)
    {
        B tt(i);
        t.insert(tt);
    }
    return 0;
}

TEST(insert_trivial, test1)
{

}