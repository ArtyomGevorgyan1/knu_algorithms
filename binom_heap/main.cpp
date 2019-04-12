#include "B_heap.h"

class B {
public:
    B(int _k) : k{_k} {}
    int getKey() {return k;}
private:
    int k;
};

int main()
{
    BinaryHeap <B> heap;
    heap.insert(B(1));
    return 0;
}