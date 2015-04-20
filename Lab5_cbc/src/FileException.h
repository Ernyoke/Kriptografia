/*
 * FileException.h
 *
 *  Created on: Mar 1, 2015
 *      Author: ervin
 */

#ifndef FILEEXCEPTION_H_
#define FILEEXCEPTION_H_

#include <iostream>

using namespace std;

class FileException {
public:
	FileException(string &msg);
	virtual ~FileException();

	string what();

private:
	string message;
};

#endif /* FILEEXCEPTION_H_ */
