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
        initParams();

        Params params(getRandomInt() % 100, getRandomInt() % 100, primes[getRandomInt() % 100],
                      31);

        /*
         * можно придумать другую проверку - если сумма квадратов размеров вторичных ячеек превышает
         * n, то пробуем еще раз подобрать параметры функции
         */

        /*

        int numOfCollisions = 0;


        int countCollisions[params.m];
        for (int i = 0; i < params.m; i++) {
            countCollisions[i] = 0;
        }


        for (int i = 0; i < mSize; i++) {
            Book curBook = mContents[i];
            int hv = curBook.hash(params);
            countCollisions[hv % params.m]++;
        }
        */

        cont = true;
        mParams = params;

        /*
        for (int i = 0; i < params.m; i++) {
            if (countCollisions[i] > 1) {
                cont = false;
            }
        }
        */

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
