//============================================================================
// Name        : lab4_rc4.cpp
// Author      : ervin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

unsigned char S[256];
unsigned int i, j;
const int length = 64 * 1024;

void swap(unsigned char *s, unsigned int i, unsigned int j) {
    unsigned char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

/* KSA: Key-scheduling algorithm */
/* As S tömb inicializálása: kezdetben megegyezik az identitás permutációval */
/* A 256-al történo maradékos osztás 255-tel való & (AND) muvelettel van megvalósítva*/
void rc4_init(string &key, unsigned int key_length) {
    for (i = 0; i < 256; i++)
        S[i] = i;

    for (i = j = 0; i < 256; i++) {
        j = (j + key[i % key_length] + S[i]) & 255;
        swap(S, i, j);
    }
    i = j = 0;
}

/* PRGA: Pseudo-random genaration algorithm*/
/*Az álvéletlen értékeket meghatározó algoritmus*/
unsigned char rc4_output() {
    i = (i + 1) & 255;
    j = (j + S[i]) & 255;
    swap(S, i, j);

    return S[(S[i] + S[j]) & 255];
}

void _encrytp(string &filename, string &key) {
	ifstream infile;
	infile.open(filename.c_str(), ios::binary | ios::in);
	ofstream outfile;
	outfile.open("nimrod.jpg",std::ofstream::binary);
	int bytesRead = 0;
	char buffer[length];
	char cryptedBuffer[length];
	for(int k = 0; k < 256; ++k) {
		rc4_output();
	}
	if(infile) {
		while(!infile.eof()) {
			infile.read(buffer, length);
			bytesRead = infile.gcount();
//			cout << bytesRead << endl;
			for(int i = 0; i < bytesRead; ++i) {
				cryptedBuffer[i] = buffer[i] ^ rc4_output();
			}
			outfile.write(cryptedBuffer, bytesRead);
		}
	}
	else {
		cout << "File is not opened!";
	}
	outfile.close();
	infile.close();
}

void _decrypt(string &filename, string &key) {
	ifstream infile;
		infile.open("nimrod.jpg", ios::binary | ios::in);
		ofstream outfile;
		outfile.open(filename.c_str(), std::ofstream::binary);
		int bytesRead = 0;
		char buffer[length];
		char cryptedBuffer[length];
		for(int k = 0; k < 256; ++k) {
			rc4_output();
		}
		if(infile) {
			while(!infile.eof()) {
				infile.read(buffer, length);
				bytesRead = infile.gcount();
//				cout << bytesRead << endl;
				for(int i = 0; i < bytesRead; ++i) {
					cryptedBuffer[i] = buffer[i] ^ rc4_output();
				}
				outfile.write(cryptedBuffer, bytesRead);
			}
		}
		else {
			cout << "File is not opened!";
		}
		outfile.close();
		infile.close();
}

int main() {
	//a kulcs folyam létrehozása egy kezdeti kulcsérték, a key alapján történik
	string key = "9733550018915577413040213005073417262875970440139960528978542854942266781971614120479045142243552019706585545388937593006388194261133203164624295504623687";
	string filename = "asd.jpg";
	string filename2 = "decrypted2.jpg";

	clock_t begin;
	clock_t end;

//	begin = clock();
//	rc4_init(key, 12); // a kulcs hossza 12
//	_encrytp(filename, key);
//	end = clock();

//	cout << "Ecnryption time: " << double(end - begin) / CLOCKS_PER_SEC << endl;

	begin = clock();
	rc4_init(key, 12);
	_decrypt(filename2, key);
	end = clock();

	cout << "Decryption time: " << double(end - begin) / CLOCKS_PER_SEC << endl;

	return 0;
}
