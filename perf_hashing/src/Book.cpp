//
// Created by artyom on 05.02.19.
//

#include "Book.h"

string Book::retAuthor() {
    return mAuthor;
}

unsigned int Book::hash(Params params) {
    string author = retAuthor();
    unsigned int hv = 0;
    for (int i = 0; i < author.length(); i++) {
        hv += author[i];
    }
    return hv;
}

Book::Book(string author) :
mAuthor(author) {}

unsigned int Book::staticHash(Book book, Params params) {
    string author = book.retAuthor();
    unsigned int hv = 0;
    for (int i = 0; i < author.length(); i++) {
        hv += author[i];
    }
    return hv;
}
