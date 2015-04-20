/*
 * Cbc.h
 *
 *  Created on: Feb 28, 2015
 *      Author: ervin
 */

#ifndef CBC_H_
#define CBC_H_

#include <iostream>
#include <fstream>
#include "Crypt.h"

using namespace std;

class Cbc {
public:
	Cbc(Crypt *);
	virtual ~Cbc();

	void decrypt(char *iv, const string &inFile, const string &outFile);

private:
	Crypt *method;
};

#endif /* CBC_H_ */
