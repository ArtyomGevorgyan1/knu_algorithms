//
// Created by artyom on 06.02.19.
//
#include "Commons.h"
#include "HTFlexible.h"
#include <iostream>

int main() {
    HTFlexible htf;
    Book a("maria"), b("ivan"), c("george");
    htf.push(a);
    htf.push(b);
    htf.push(c);
    htf.roll();

    return 0;
}