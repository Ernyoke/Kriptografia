/*
 * Crypt.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: ervin
 */

#include "Crypt.h"

Crypt::Crypt() {
	this->block = NULL;

}

Crypt::~Crypt() {
	delete block;
}

void Crypt::setBlock(const char *block) {
	delete this->block;
	this->block = block;
}

pair<int, pair<int, int> > Crypt::extendedEuclid(int a, int b) {
    int x = 1, y = 0;
    int xLast = 0, yLast = 1;
    int q, r, m, n;
    while(a != 0) {
        q = b / a;
        r = b % a;
        m = xLast - q * x;
        n = yLast - q * y;
        xLast = x, yLast = y;
        x = m, y = n;
        b = a, a = r;
    }
    return make_pair(b, make_pair(xLast, yLast));
}

int Crypt::modInverse(int a, int m) {
    return (extendedEuclid(a,m).second.first + m) % m;
}

