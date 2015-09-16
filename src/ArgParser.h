/*
 * ArgParser.h
 *
 *  Created on: 17 Feb 2014
 *      Author: joe

    Copyright (C) 2013-2014 Joe Butler
    This file is part of Thoth.

    Thoth is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Thoth is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Thoth.  If not, see <http://www.gnu.org/licenses/>.

 */

#ifndef ARGPARSER_H_
#define ARGPARSER_H_
#include <string>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "GuiFunctions.h"

class ArgParser {
public:
	std::string action;
	std::string nodetree;
	std::string caseVars;
	std::string fitnessCases;
	std::string configFile;
	int numVars;


	void usage(bool exit, int exitcode);
	void loadArgs(int argc, char* argv[],bool dieOnError = true);
	void displayArgs();
	bool isValid(bool dieOnError = true);
	ArgParser();
	~ArgParser();
};


#endif /* ARGPARSER_H_ */

