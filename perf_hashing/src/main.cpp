//
// Created by artyom on 06.02.19.
//
#include "Commons.h"
#include "HTFlexible.h"
#include "HTLibrary.h"
#include <iostream>

int main() {
    vector <Book> f;
    Book b("hey");
    f.push_back(b);
    HTLibrary lib(f);
    return 0;
}