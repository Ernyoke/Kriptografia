//============================================================================
// Name        : lab6_1.cpp
// Author      : ervin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

int main() {

	ZZ nr;
	string str = "Sapientia University";
	unsigned char *u_str = (unsigned char*)str.c_str();
	int newLength = str.length() + 1;
	unsigned char *cstr = new unsigned char[newLength];

	ZZ p = to_ZZ("282755483533707287054752184321121345766861480697448703443857012153264407439766013042402571");
	ZZ q = to_ZZ("370332600450952648802345609908335058273399487356359263038584017827194636172568988257769601");
	ZZ n = p * q;
	ZZ e = to_ZZ("65537");
	ZZ d = InvMod(e, (p - 1) * (q - 1));
	ZZFromBytes(nr, u_str, str.length());
	cout << "nr:" << nr << endl;

	ZZ cnr = PowerMod(nr, e, n);
	BytesFromZZ(cstr, cnr, newLength);

	cout << "cnr:" << cnr << endl;
	ZZ nnr = PowerMod(cnr, d, n);
	cout << "nnr:" << nnr << endl;
	BytesFromZZ(u_str, nnr, str.length());

	cout << u_str;


	return 0;
}
