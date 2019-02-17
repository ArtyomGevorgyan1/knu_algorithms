//
// Created by artyom on 05.02.19.
//

#ifndef PERF_HASHING_HTLIBRARY_H
#define PERF_HASHING_HTLIBRARY_H

#include "Commons.h"
#include "Book.h"
#include "HTFlexible.h"

class HTLibrary {
public:
    HTLibrary();
    explicit HTLibrary(vector <Book> contents);


    /*debug methods*/
    int getTableSize() {
        return mTable.size();
    }
    vector <HTFlexible> getTable() {
        return mTable;
    }

private:
    Params mParams;
    vector <HTFlexible> mTable;
    vector <Book> mContents;
    unsigned int mSize;
    void rollAndFill();
};

#endif //PERF_HASHING_HTLIBRARY_H
