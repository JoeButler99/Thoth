/*
 * Globals.h
 *
 *  Created on: 7 May 2013
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

#ifndef GLOBALS_H_
#define GLOBALS_H_
#include <iostream>
#include <fstream>
#include <string>
#include "RNG.h"
#include "GlobalManager.h"


//// Global Objects
class GlobalManager;
extern RNG rng;
extern GlobalManager gm;

// Global Constants
const unsigned RPN_STACK_LIMIT = 250;
const double EULER = 2.71828182845;
const unsigned int MAX_ARGS = 4;


// Function Pointers
typedef void (*function_ptr)(void);
typedef void (*function_ptr_uint)(unsigned);
typedef void (*rpn_action_ptr)(double rpnStack[RPN_STACK_LIMIT],int & highest);

#endif /* GLOBALS_H_ */
