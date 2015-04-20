/*
 * Hill.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: ervin
 */

#include "Hill.h"

Hill::Hill() {

}

Hill::~Hill() {
	delete key;
}

void Hill::setKey(const string &file) {
	ifstream key_in(file.c_str());
	if(key_in.is_open()) {
		key_in >> blockSize;
		key = new MatrixXi(blockSize, blockSize);
		int value;
		for(int i = 0; i < blockSize; ++i) {
			for(int j = 0; j < blockSize; ++j) {
				key_in >> value;
				(*key)(i, j) = value;
			}
		}
	}
	else {
		string msg = file + " can not be opened!";
//		FileException *ex = new FileException(msg);
//		throw ex;
	}
}

char* Hill::decrypt() {
	MatrixXi mat(blockSize, 1);
	MatrixXi inv_mat = calculateInverse();
	char *decrypted = new char[blockSize];
	for(int i = 0; i < blockSize; ++i) {
		mat(i, 0) = block[i];
	}
	MatrixXi res = inv_mat * mat;
	for(int i = 0; i < blockSize; ++i) {
		int c = (res(i, 0) % 256);
		if(c < 0) {
			c += 256;
		}
		char ch = c;
		decrypted[i] = ch;
	}
	return decrypted;
}

char* Hill::encrypt() {

	return NULL;
}

MatrixXi Hill::calculateInverse() {
	MatrixXf fl = key->template cast<float>();

	int det = round(fl.determinant());
	int inv = modInverse(det, 256);

	MatrixXf adjugate = det * fl.inverse();
//	cout << "Adjugate:" << endl;
//	cout << adjugate << endl;

	MatrixXi inv_mat(blockSize, blockSize);
	for(int i = 0; i < blockSize; ++i) {
		for(int k = 0; k < blockSize; ++k) {
			double aux = adjugate(i, k);
			inv_mat(i, k) = round(aux);
		}
	}
	inv_mat = inv * inv_mat;
//	cout << "Inverse:" << endl;
//	cout << inv_mat << endl;

	for(int i = 0; i < blockSize; ++i) {
		for(int j = 0; j < blockSize; ++j) {
			inv_mat(i, j) = inv_mat(i, j) % 256;
			if(inv_mat(i, j) < 0) {
				inv_mat(i, j) = inv_mat(i, j) + 256;
			}
		}
	}

	return inv_mat;
}

int Hill::getBlockSize() const {
	return this->blockSize;
}

