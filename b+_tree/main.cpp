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


int main()
{
    B_tree <B> t(2);

    unsigned i = 1;
    while (i <= 10)
    {
        auto f = B(i);
        t.insert(f);
        ++i;
    }

    return 0;
}