//
// Created by artyom on 05.02.19.
//

#ifndef PERF_HASHING_HTLIBRARY_H
#define PERF_HASHING_HTLIBRARY_H

#include "Commons.h"
#include "Book.h"
#include "HTFlexible.h"

class HTLibrary {

    Params mParams;
    void addToHT(Book book);
    vector <HTFlexible> mTable;
};

#endif //PERF_HASHING_HTLIBRARY_H
