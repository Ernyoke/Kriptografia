//============================================================================
// Name        : lab4_rc4_known_plaintext.cpp
// Author      : ervin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ifstream plain;
	plain.open("RC4_Massag.jpg", ios::binary | ios::in);
	ifstream crypted;
	crypted.open("cryptRC4_Massag", ios::binary | ios::in);
	ifstream toDecrypt;
	toDecrypt.open("cryptRC4_UjTuristaCelpont", ios::binary | ios::in);
	ofstream result;
	result.open("result.jpg",std::ofstream::binary);

	int length = 64;
	char bufferPlain[length];
	char bufferCypted[length];
	char bufferToDecrypt[length];
	char bufferResult[length];
	int bytesRead = 0;

	if(crypted.is_open()) {
		while(!plain.eof()) {
			plain.read(bufferPlain, length);
			bytesRead = plain.gcount();
			crypted.read(bufferCypted, bytesRead);
			toDecrypt.read(bufferToDecrypt, bytesRead);
			for(int i = 0; i < bytesRead; ++i) {
				bufferResult[i] = bufferToDecrypt[i] ^ (bufferPlain[i] ^ bufferCypted[i]);
			}
			result.write(bufferResult, bytesRead);
		}
	}
	else {
		cout << "File is not opened!";
	}

	result.close();
	plain.close();
	crypted.close();
	toDecrypt.close();

	return 0;
}
