//
// Created by artyom on 05.02.19.
//

#ifndef PERF_HASHING_BOOK_H
#define PERF_HASHING_BOOK_H

#include "Commons.h"

class Book {

public:
    explicit Book(string author);

    static unsigned int staticHash(Book book, Params params);
    unsigned int hash(Params params);
    string retAuthor();

private:

    string mAuthor;

};


#endif //PERF_HASHING_BOOK_H
