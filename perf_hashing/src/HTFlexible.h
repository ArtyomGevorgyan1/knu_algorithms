//
// Created by artyom on 05.02.19.
//

#ifndef PERF_HASHING_HTFLEXIBLE_H
#define PERF_HASHING_HTFLEXIBLE_H

#include "Commons.h"
#include "Book.h"

class HTFlexible {
public:

    HTFlexible();
    void roll();

    vector <Book> getContents() const;
    void push(Book book);
    int getSize() const;

private:
    unsigned int mSize;
    vector <Book> mContents;
    Params mParams;
};


#endif //PERF_HASHING_HTFLEXIBLE_H
