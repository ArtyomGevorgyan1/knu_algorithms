#include <iostream>

#include "Graph.h"
#include "Book.h"
#include <iostream>

/*
 * 0 5 1000 1000
    1000 0 1000 6
    1000 1000 0 1000
    1000 1000 7  0
 *
 *
 * negative cycle test
 *
 * 0 -3 1000 1000
 * 1000 0 -4 1000
 * -5 1000 0 6
 * 1000 1000 1000 0
 *
 * */
#include <iostream>
using std::cin;

int main() {

    vector <Book> vec;
    for (int i = 0; i < 4; i ++)
    {
        Book b(i);
        vec.push_back(b);
    }


    vector <vector<int>>m(4);
    for (int i = 0; i < 4; i++)
    {
        m[i].resize(5);
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cin >> m[i][j];
        }
    }
    Graph <Book> gr(m,vec);
    auto k = gr.johnson();
    if (k.empty())
    {
        std::cout << "neg\n";
    }

    return 0;
}