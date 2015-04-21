//============================================================================
// Name        : lab9_2_dsa.cpp
// Author      : ervin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <fcntl.h>
#include "sha1.h"
#include <NTL/ZZ.h>
using namespace std;

int main() {

	SHA1 sha;
	unsigned message_digest[5];

	ifstream file("vlc-1.0.5-win32", ifstream::binary);
	ifstream sign("sign.txt");

	if(!file.is_open()) {
		cerr << "File vlc.exe could not be opened!" << endl;
		return 0;
	}

	if(!sign.is_open()) {
		cerr << "File keys.txt could not be opened!" << endl;
		return 0;
	}

	file.seekg(0, std::ios::end);
	streamsize size = file.tellg();

	unsigned char *buffer = new unsigned char[size];

	file.seekg(0, std::ios::beg);

	file.read((char*)buffer, size);

	sha.Reset();

	for(int i = 0; i < size; ++i) {
		sha.Input(buffer[i]);
	}

	NTL::ZZ pr(1);
	NTL::ZZ H(0);

	if (!sha.Result(message_digest))
	{
		cerr << "SHA_1 error" << endl;
	}
	else {
		for(int i = 0; i < 5; ++i) {
			printf("%x ", message_digest[i]);
			H = H + NTL::to_ZZ(message_digest[4 - i]) * pr;
			pr = pr * NTL::power(NTL::to_ZZ(2), 32);
		}
	}

	cout << endl << H << endl;

	NTL::ZZ p = NTL::to_ZZ("867595813995627420412176531744496618562872409386813107576863469000992767382424886992142260793016591594369290654336768028436587452406397880630282830876656771240010707610432270060455942772089900873459289140643136395159074393052293399156987366649737992141299168059971034318887282569437706596464388867281");
	NTL::ZZ q = NTL::to_ZZ("976007367225122768242793623709024760771239023387");
	NTL::ZZ g = NTL::to_ZZ("108511223480278973255432329303064318044890703198447528611112527418873360139631374462310306911905714919404721994803958496898236693219536873532174028476963080421402460095689873582702548798733875257927691086666470012811313452469887878847526240217958198946589262060577248072593630253653555418250880270479");
	NTL::ZZ A = NTL::to_ZZ("842172662005496902391505769322803234980163956365321208149394132017637549949644833411542587895160934258074834366282375356814778739793178810282730119301846783422006138576291032069392627158116900616098305536209308311508479274210616189223319729150643392297400788031574662419138669162217717310137554543777");

	while(!sign.eof()) {
		NTL::ZZ B, c;
		sign >> B;
		sign >> c;
		if(sign.eof()) {
			break;
		}
		NTL::ZZ c1 = NTL::InvMod(c, q);
//		cout << "B=" << B << endl;
//		cout << "C=" << c << endl;
		NTL::ZZ kit1 = (c1 * H) % q;
		NTL::ZZ kit2 = (c1 * B) % q;

		NTL::ZZ mult1 = NTL::PowerMod(g, kit1, p);
		NTL::ZZ mult2 = NTL::PowerMod(A, kit2, p);
		NTL::ZZ res = ((mult1 * mult2) % p) % q;

		if(res == B) {
			cout << "B=" << B << endl;
			cout << "C=" << c << endl;
			break;
		}

	}

	return 0;
}
