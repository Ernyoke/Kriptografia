//============================================================================
// Name        : lab7_rabin.cpp
// Author      : ervin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <NTL/ZZ.h>

using namespace std;

int main() {

	ifstream keys("keys.txt");
	ifstream file("cryptedRabin", ifstream::binary);

	if(!keys.is_open()) {
		cerr << "File keys.txt could not be opened!" << endl;
		return 0;
	}

	if(!file.is_open()) {
		cerr << "File cryptedRabin could not be opened!" << endl;
		return 0;
	}

	NTL::ZZ p, q, n;

	bool whatPrime = false;

	while(!keys.eof()) {
		NTL::ZZ value;
		keys >> value;

		if(NTL::ProbPrime(value, 100) == 1) {
			if(!whatPrime) {
				p = value;
				whatPrime = true;
			}
			else {
				if(whatPrime) {
					q = value;
					break;
				}
			}
		}
	}

	cout << "p=" << p << endl;
	cout << "q=" << q << endl;

	n = q * p;

	cout << "n=" << n << endl;

	file.seekg(0, std::ios::end);
	streamsize size = file.tellg();

	unsigned char *buffer = new unsigned char[size];

	file.seekg(0, std::ios::beg);

	file.read((char*)buffer, size);

	NTL::ZZ nr;

	NTL::ZZFromBytes(nr, buffer, size);

	cout << "nr=" << nr << endl;

	NTL::ZZ mp = NTL::PowerMod(nr % p, (p + 1) / 4, p);
	NTL::ZZ mq = NTL::PowerMod(nr % q, (q + 1) / 4, q);

	cout << "mp=" << mp << endl;
	cout << "mq=" << mq << endl;

	NTL::ZZ d, x, y;
	NTL::XGCD(d, x, y, p, q);

	cout << "d=" << d << endl;

	NTL::ZZ m1 = (x * p * mq + y * q * mp) % n;
	if(m1 < 0) {
		m1 += n;
	}

	cout << "m1=" << m1;

	NTL::ZZ m11 = -m1;
	if(m11 < 0) {
		m11 += n;
	}

	cout << "m11=" << m1;

	NTL::ZZ m2 = (x * p * mq - y * q * mp) % n;
	if(m1 < 0) {
		m1 += n;
	}

	NTL::ZZ m22 = -m2;
	if(m22 < 0) {
		m22 += n;
	}


	unsigned char *res = new unsigned char[182];

	NTL::BytesFromZZ(res, m1, 182);
	cout << res << endl;
	NTL::BytesFromZZ(res, m11, 182);
	cout << res << endl;
	NTL::BytesFromZZ(res, m2, 182);
	cout << res << endl;
	NTL::BytesFromZZ(res, m22, 182);
	cout << res << endl;


	cout << "" << endl; // prints 
	return 0;
}
