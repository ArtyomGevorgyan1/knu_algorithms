//
// Created by artyom on 05.02.19.
//

#ifndef PERF_HASHING_COMMONS_H
#define PERF_HASHING_COMMONS_H

#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <fstream>

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
