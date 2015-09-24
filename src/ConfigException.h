/*
 * ConfigException.h
 *
 *  Created on: 23 Sep 2015
 *      Author: joe
 */

#ifndef SRC_CONFIGEXCEPTION_H_
#define SRC_CONFIGEXCEPTION_H_
#include <iostream>
#include <exception>

class ConfigException: public std::exception {
public:
	std::string errorMessage;
	ConfigException(std::string msg) : errorMessage(msg) {}
	virtual ~ConfigException() throw() {}
	virtual const char* what() const throw() { return errorMessage.c_str(); }
};

#endif /* SRC_CONFIGEXCEPTION_H_ */
