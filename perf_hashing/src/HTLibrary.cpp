//
// Created by artyom on 05.02.19.
//

#include "HTLibrary.h"
#include "Commons.h"
#include <gtest/gtest.h>

HTLibrary::HTLibrary(vector<Book> contents) :
mContents(contents), mSize(static_cast<unsigned int>(contents.size()))

{
    mTable.resize(31);
    rollAndFill();

}

HTLibrary::HTLibrary() : mSize(0)
{
    mTable.resize(31);
    rollAndFill();
}



void HTLibrary::rollAndFill()
{
    bool cont = false;
    while (!cont) {

        Params params(getRandomInt() % 100, getRandomInt() % 100, primes::getInstance()[getRandomInt() % 100],
                      31);

        /*
         * можно придумать другую проверку - если сумма квадратов размеров вторичных ячеек превышает
         * n, то пробуем еще раз подобрать параметры функции
         *
        */

        cont = true;
        mParams = params;

    }

    for (int i = 0; i < mSize; i++) {
        mTable[Book::staticHash(mContents[i].retAuthor(), mParams) % mParams.m].push(mContents[i]);

    }
    for (int i = 0; i < mParams.m; i++) {
        if (mTable[i].getSize() > 0) {
            mTable[i].doShit();
        }
    }

}

