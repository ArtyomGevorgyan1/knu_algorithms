//
// Created by artyom on 06.02.19.
//
#include "Commons.h"
#include "HTFlexible.h"
#include "HTLibrary.h"
#include <iostream>


#include <cstdlib>
using namespace std;

int main() {

    vector <Book> f;

    cout << "how many books?\n";
    int num;
    cin >> num;
    string str;
    for (int i = 0; i < num; i++) {
        cin >> str;
        Book b(str);
        f.push_back(b);
    }

    /*
    Book b("hey");
    Book a("heyf");
    Book c ("ccc");
    f.push_back(b);
    f.push_back(a);
    f.push_back(c);
     */

    HTLibrary lib(f);



    ofstream dotFile;
    dotFile.open ("./gr.dot");

    dotFile << "digraph {\n";

    vector <HTFlexible> ff = lib.getTable();
    for (int i = 0; i < lib.getTableSize(); i++) {
        HTFlexible g = ff[i];
        vector <Book> hf = g.getSpace();
        for (int j = 0; j < hf.size(); j++) {
            Book book = hf[j];

            if (book.retAuthor() == "NOTAVALUE\n") {
                continue;
            }
            //dotFile << "\t" << "lib -> " << book.retAuthor() << ";" << endl;
            dotFile << "\t" << "lib -> " << "A" << i << ";" << endl;
            dotFile << "\t" << "A" << i << " -> " << "A" << i << "B" << j << ";" << endl;
            dotFile << "\t" << "A" << i << "B" << j << " -> " << book.retAuthor() << ";" << endl;
        }
    }


    dotFile << "}\n";

    dotFile.close();

    system("./show_png.sh");

    return 0;

}