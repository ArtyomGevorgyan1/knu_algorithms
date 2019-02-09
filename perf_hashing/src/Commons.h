//
// Created by artyom on 05.02.19.
//

#ifndef PERF_HASHING_COMMONS_H
#define PERF_HASHING_COMMONS_H

#include <vector>
#include <string>
#include <iostream>
#include <random>

using std::string;
using std::vector;

struct Params {
    unsigned int a, b, p, m;
    Params() = default;
    Params(unsigned int _a, unsigned int _b, unsigned int _p, unsigned int _m) :
    a(_a), b(_b), p(_p), m(_m) {}
};

inline int binPow(int x) {
    if (x > 0) {
        if (x % 2) return 2 * binPow(x / 2) * binPow(x / 2);
        else return binPow(x / 2) * binPow(x / 2);
    } else return 1;
}


/*
inline vector <unsigned int> getPrimes() {
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

    primes.resize(100);
    return primes;
}

namespace commons {
    static vector <unsigned int> primes;
}


inline void initParams() {



    vector <unsigned int> ret = getPrimes();
    primes.resize(0);
    for (auto i : ret) {
        primes.push_back(i);
    }

    for (auto i : primes) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
*/

struct primes {
    static primes& getInstance() {
        static primes s;
        return s;
    }
    unsigned int operator[](int id) {
        return primes::getInstance().container[id];
    }
    primes() {
        initPrimes();
    }
    primes(primes const &) = delete;
    void operator = (primes const &) = delete;

private:
    vector <unsigned int> container;
    void initPrimes();
};


inline unsigned int getRandomInt() {
    std::random_device rd;
    return rd();
}

#endif //PERF_HASHING_COMMONS_H
