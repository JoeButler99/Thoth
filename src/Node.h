/*
 * Node.h
 *
 *  Created on: 4 May 2013
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

#ifndef NODE_H_
#define NODE_H_
#include <vector>
#include "Function.h"

class Node {
public:
	int fNo;
	unsigned int fInputs, tNo;
	bool isTerminal;

	Node(Function & f);
	Node(int t);
	Node(int inputs, bool headnode); // We throw away the bool, we just need to differentiate the call

	inline void setFromFunc (Function & f) {
		isTerminal = false;
		fNo 	= f.mynum;
		fInputs = f.inputs;
	}

	inline void setTerminal (int t) {
		isTerminal = true;
		tNo = t;
	}


};

#endif /* NODE_H_ */
