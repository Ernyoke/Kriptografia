/*
 * Affine.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: ervin
 */

#include "Affine.h"

Affine::Affine() {
	this->key1 = 0;
	this->key2 = 0;

}

Affine::~Affine() {
	// TODO Auto-generated destructor stub
}

void Affine::setKey(int key1, int key2) {
	this->key1 = key1;
	this->key2 = key2;
}

void Affine::setKey(const string &file) {
	ifstream key_in(file.c_str());
	if(key_in.is_open()) {
		key_in >> key1;
		key_in >> key2;
	}
}


char* Affine::decrypt() {
	char* result = new char[this->getBlockSize()];
	char s = block[0];
	if(s < 0) {
		s = s + 256;
	}
	int inv = modInverse(key1, 256);
	result[0] = (inv * s - inv * key2) % 256;
	if(result[0] < 0) {
//		result += 256;
	}
	return result;
}

int Affine::getBlockSize() const {
	return 1;
}

char* Affine::encrypt() {
	return NULL;
}


