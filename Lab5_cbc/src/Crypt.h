/*
 * Crypt.h
 *
 *  Created on: Feb 28, 2015
 *      Author: ervin
 */

#ifndef CRYPT_H_
#define CRYPT_H_

#include <iostream>

using namespace std;

class Crypt {
public:
	Crypt();
	virtual ~Crypt();

	void setBlock(const char*);

	virtual char* decrypt() = 0;
	virtual char* encrypt() = 0;
	virtual int getBlockSize() const = 0;

protected:
	const char *block;
	int modInverse(int, int);
	pair<int, pair<int, int> > extendedEuclid(int a, int b);
};

#endif /* CRYPT_H_ */
