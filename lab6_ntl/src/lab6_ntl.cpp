//============================================================================
// Name        : lab6_ntl.cpp
// Author      : ervin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

int main()
{
   ZZ a, b, c;

   cin >> a;
   cin >> b;
   c = (a+1)*(b+1);
   cout << c << "\n";
}
