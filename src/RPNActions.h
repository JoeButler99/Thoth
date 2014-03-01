/*
 * RPNActions.h
 *
 *  Created on: 1 Mar 2014
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

#ifndef RPNACTIONS_H_
#define RPNACTIONS_H_

#include "Globals.h"

inline void rpnAdd(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -=2;
	rpnStack[highest] =  rpnStack[highest+1] + rpnStack[highest];
}

inline void rpnSubtract(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -=2;
	rpnStack[highest] =  rpnStack[highest+1] - rpnStack[highest];
}

inline void rpnMultiply(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -=2;
	rpnStack[highest] =  rpnStack[highest+1] * rpnStack[highest];
}

inline void rpnDivide(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -=2;
	if (rpnStack[highest] == 0.0) { rpnStack[highest] = rpnStack[highest+1]; }
	else { rpnStack[highest] =  rpnStack[highest+1] / rpnStack[highest]; }
}




#endif /* RPNACTIONS_H_ */
