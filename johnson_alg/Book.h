//
// Created by artyom on 09.04.19.
//

#ifndef JOHNSON_ALG_BOOK_H
#define JOHNSON_ALG_BOOK_H


#include <string>

class Book {
public:

    Book(unsigned key) : m_key{key} {}

    unsigned getKey()
    {
        return m_key;
    }

private:
    unsigned m_key;
};

#endif //JOHNSON_ALG_BOOK_H
