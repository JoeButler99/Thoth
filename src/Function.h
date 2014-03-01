/*
 * Function.h
 *
 *  Created on: 3 May 2013
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

#ifndef FUNCTION_H_
#define FUNCTION_H_
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>		// abs math function
#include "Globals.h"



class Function {
public:
	std::string name;
	unsigned int inputs, mynum;
	Function(const std::string & n, int i, int mynum,rpn_action_ptr a);
	std::string displaySelf();
	rpn_action_ptr action;

};

#endif /* FUNCTION_H_ */
