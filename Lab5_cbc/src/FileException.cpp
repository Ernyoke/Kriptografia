/*
 * FileException.cpp
 *
 *  Created on: Mar 1, 2015
 *      Author: ervin
 */

#include "FileException.h"

FileException::FileException(string &msg) {
	this->message = msg;
}

FileException::~FileException() {
	// TODO Auto-generated destructor stub
}

string FileException::what() {
	return message;
}

