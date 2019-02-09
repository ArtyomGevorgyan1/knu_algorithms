//
// Created by artyom on 09.02.19.
//

#include "Commons.h"

void primes::initPrimes() {
    vector <unsigned int> primes;
    unsigned int hmPrimes = 0;
    unsigned int currTest = 3;
    while (hmPrimes < 100) {
        bool prime = true;
        for (unsigned int i = 2; i < currTest; i++) {
            if (currTest % i == 0) prime = false;
        }
        if (prime && currTest > 31) {primes.push_back(currTest); hmPrimes++;}
        currTest++;
    }

    container.resize(0);
    primes.resize(100);
    container = primes;
    container.resize(100);
}

