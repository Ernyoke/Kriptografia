/*
 * Hill.h
 *
 *  Created on: Feb 28, 2015
 *      Author: ervin
 */

#ifndef HILL_H_
#define HILL_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <eigen3/Eigen/Eigen>

#include "Crypt.h"
//#include "FileException.h"

using namespace std;
using namespace Eigen;

class Hill : public Crypt{
public:
	Hill();
	virtual ~Hill();

	char* decrypt();
	char* encrypt();
	int getBlockSize() const;

	void setKey(const string &file);

private:
	MatrixXi *key;
	int blockSize;

	MatrixXi calculateInverse();


};

#endif /* HILL_H_ */
