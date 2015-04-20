/*
 * Affine.h
 *
 *  Created on: Feb 26, 2015
 *      Author: ervin
 */

#ifndef LAB5_CBC_SRC_AFFINE_H_
#define LAB5_CBC_SRC_AFFINE_H_

#include <iostream>
#include <memory>
#include <fstream>
#include "Crypt.h"

using namespace std;

class Affine : public Crypt {
public:
	Affine();
	~Affine();

	char* decrypt();
	char* encrypt();

	void setKey(int, int);
	void setKey(const string &file);

	int getBlockSize() const;

private:
	int key1;
	int key2;

};

#endif /* LAB5_CBC_SRC_AFFINE_H_ */
