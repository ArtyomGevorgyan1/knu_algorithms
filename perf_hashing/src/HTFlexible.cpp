//
// Created by artyom on 05.02.19.
//

#include "HTFlexible.h"
#include "Commons.h"

int HTFlexible::getSize() const {
    return mSize;
}

vector <Book> HTFlexible::getContents() const {
    return mContents;
}

void HTFlexible::roll() {

    bool cont = false;
    while (!cont) {
        int fst = getRandomInt() % 100;

        int sec = primes::getInstance()[0];//primes[0];


        Params params(getRandomInt() % 100, getRandomInt() % 100, primes::getInstance()[getRandomInt() % 100],
                (mSize + 1) * (mSize + 1));

        int numOfCollisions = 0;

        int countCollisions[params.m];
        for (int i = 0; i < params.m; i++) {
            countCollisions[i] = 0;
        }

        for (int i = 0; i < getContents().size(); i++) {
            Book curBook = getContents()[i];
            int hv = curBook.hash(params);
            countCollisions[hv % params.m]++;
        }

        cont = true;
        mParams = params;

        for (int i = 0; i < params.m; i++) {
            if (countCollisions[i] > 1) {
                cont = false;
            }
        }

    }

}

void HTFlexible::fill() {
    mSpace.resize(mParams.m);
    for (int i = 0; i < mSize; i++) {
        int hv = mContents[i].hash(mParams) % mParams.m;
        mSpace[hv] = mContents[i];
    }
}


void HTFlexible::push(Book book) {
    mContents.push_back(book);
    mSize++;
}

HTFlexible::HTFlexible() :
mSize(0)
{
}

void HTFlexible::doShit() {
    roll();
    fill();
}