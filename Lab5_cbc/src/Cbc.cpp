/*
 * Cbc.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: ervin
 */

#include "Cbc.h"

Cbc::Cbc(Crypt *method) {
	this->method = method;
}

Cbc::~Cbc() {
	delete method;
}

void Cbc::decrypt(char *iv, const string &inFile, const string &outFile) {
	ifstream file_in(inFile.c_str(), ios::binary | ios::in);
	ofstream file_out(outFile.c_str(), ofstream::binary);

	int length = 64 * method->getBlockSize();
	int bytesRead = 0;
	char buffer[length];
	char resBuffer[length];

	int j = 0;

	if(!file_in.is_open()) {
		//throw exception
	}
	if(!file_out.is_open()) {
		//throw exception
	}

	while(!file_in.eof()) {
		file_in.read(buffer, length);
		bytesRead = file_in.gcount();
		for(int i = 0; i < bytesRead; i = i + method->getBlockSize()) {
			char *block = new char[method->getBlockSize()];
			for(int it = 0; it < method->getBlockSize(); ++it) {
				block[it] = buffer[i + it];
			}
			method->setBlock(block);
			char* decr = method->decrypt();
			for(int it = 0; it < method->getBlockSize(); ++it) {
				resBuffer[i + it] = iv[it] ^ decr[it];
				iv[it] = buffer[i + it];
				j++;
			}
			delete decr;
		}
		file_out.write(resBuffer, bytesRead);
		cout << bytesRead << endl;
	}

	file_in.close();
	file_out.close();

}

