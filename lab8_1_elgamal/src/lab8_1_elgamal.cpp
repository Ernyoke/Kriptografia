//============================================================================
// Name        : lab8_1_elgamal.cpp
// Author      : ervin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <NTL/ZZ.h>
#include <boost/tuple/tuple.hpp>

using namespace std;

boost::tuple<NTL::ZZ, NTL::ZZ, NTL::ZZ, NTL::ZZ> elGamalGen(NTL::ZZ &k) {
	NTL::ZZ p;
	NTL::GenPrime(p, 1024);
	NTL::ZZ a;
	NTL::RandomBnd(a, p - 1);
	NTL::ZZ g = p % a;
	NTL::ZZ A = NTL::PowerMod(g, a, p);
	return boost::make_tuple(p, g, A, a);
}

boost::tuple<NTL::ZZ, NTL::ZZ> ElGamalencrypt (NTL::ZZ m, NTL::ZZ p, NTL::ZZ g, NTL::ZZ A) {
	NTL::ZZ b;
	RandomBnd(b, p-1);
	NTL::ZZ B = NTL::PowerMod(g, b, p);
	NTL::ZZ c1 = B;
	NTL::ZZ c2 = (PowerMod(A, b, p) * m) % p;
	return boost::make_tuple(c1, c2);
}

NTL::ZZ ElGamaldecrypt (boost::tuple<NTL::ZZ, NTL::ZZ> t, NTL::ZZ a, NTL::ZZ p) {
	NTL::ZZ a1 = p - 1 - a;
	NTL::ZZ m = (PowerMod(t.get<0>(), a1, p) * t.get<1>() ) % p;
	return m;
}

int main() {
	NTL::ZZ k(5151115);
	boost::tuple<NTL::ZZ, NTL::ZZ, NTL::ZZ, NTL::ZZ> key = elGamalGen(k);
	cout << "p=" << key.get<0>() << endl;
	cout << "g=" << key.get<1>() << endl;
	cout << "A=" << key.get<2>() << endl;
	cout << "a=" << key.get<3>() << endl;

	NTL::ZZ m;
	unsigned char* buffer = new unsigned char[5];
	buffer[0] = 'J';
	buffer[1] = 'o';
	buffer[2] = 'z';
	buffer[3] = 's';
	buffer[4] = 'i';

	NTL::ZZFromBytes(m, buffer, 5);
	boost::tuple<NTL::ZZ, NTL::ZZ> encrypted = ElGamalencrypt(m, key.get<0>(), key.get<1>(), key.get<2>());

	cout << "encrypted" << endl << encrypted.get<0>() << endl << encrypted.get<1>() << endl;

	NTL::ZZ res = ElGamaldecrypt(encrypted, key.get<3>(), key.get<0>());

	unsigned char *buff = new unsigned char[6];
	NTL::BytesFromZZ(buff, res, 6);
	cout << buff;

	return 0;
}
