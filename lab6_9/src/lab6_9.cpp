//============================================================================
// Name        : lab6_9.cpp
// Author      : ervin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <NTL/ZZ.h>

using namespace std;

NTL::ZZ rsadecrypt(NTL::ZZ &txt, NTL::ZZ &p, NTL::ZZ &q, NTL::ZZ &n) {
	NTL::ZZ phi = (p - 1) * (q - 1);
	NTL::ZZ e(65537);
	NTL::ZZ d = NTL::InvMod(e, phi);
//	cout << "phi: " << phi << endl;
//	cout << "d: " << d << endl;
	NTL::ZZ m = PowerMod(txt, d, n);
	return m;
}

int main() {
	string crypted = "cryptedRSA.txt";
	string keys = "keys.txt";
	string rsa_n = "rsa_n.txt";

	string cryptedTxt;
	NTL::ZZ n, p, q;

	ifstream file_crypted;
	file_crypted.open(crypted.c_str(), ios::in);
	if(file_crypted.is_open()) {
		getline(file_crypted, cryptedTxt);
		cout << cryptedTxt << endl;
	}
	else {
		cerr << crypted << " " << "could not be opened!" << endl;
		return -1;
	}

	unsigned char *str = (unsigned char*)cryptedTxt.c_str();

	ifstream rsa_n_file;
	rsa_n_file.open(rsa_n.c_str(), ios::in);
		if(rsa_n_file.is_open()) {
			while(!rsa_n_file.eof()) {
				rsa_n_file >> n;
				cout << "n:" << n << endl;
			}
		}
		else {
			cerr << rsa_n << " " << "could not be opened!" << endl;
			return -1;
		}

	ifstream keys_file;
	keys_file.open(keys.c_str(), ios::in);
	if(keys_file.is_open()) {
		while(!keys_file.eof()) {
			keys_file >> p;
			if(n % p == 0) {
				q = n / p;
				cout << "q: " << q << endl;
				cout << "p: " << p << endl;
				break;
			}
		}
	}
	else {
		cerr << keys << " " << "could not be opened!" << endl;
		return -1;
	}

	NTL::ZZ m;
	NTL::ZZFromBytes(m, str, cryptedTxt.length());
	cout << "m: " << m << endl;
	NTL::ZZ res = rsadecrypt(m, p, q, n);

	unsigned char *cstr = new unsigned char[cryptedTxt.length()];
	NTL::BytesFromZZ(cstr, res, cryptedTxt.length());

	cout << cstr;


	return 0;
}
