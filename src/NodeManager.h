/*
 * NodeManager.h
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

#ifndef NODEMANAGER_H_
#define NODEMANAGER_H_

#include <vector>
#include "Globals.h"
#include "RPNActions.h"
#include "Function.h"
#include "RNG.h"



extern RNG rng;

class NodeManager {
public:
	std::vector<Function> functionlist;

	NodeManager();
	~NodeManager();

	void setupSelf();
	void initFunctions();
	void buildFunctionSets();


	inline Function & getFunctionByNum(unsigned int fNo) {

		for(unsigned int x = 0; x < functionlist.size(); x++) {
			if(functionlist.at(x).mynum == fNo) {
				return functionlist.at(x);
			}
		}
		std::cout << "ERROR CAN'T FIND FUNCTION NUMBER:" << fNo << std::endl;
		exit(5);
		return functionlist.at(0);
	}

	inline Function & giveRandFunction() {
		return functionlist.at(rng.iRand(functionlist.size()));
	}

	inline Function & giveRandFunction(unsigned int inputs) {
		int f;
		while (true) {
			f = rng.iRand(functionlist.size());
			if (functionlist.at(f).inputs == inputs) {
				break;
			}
		}
			return functionlist.at(f);
	}

};

#endif /* NODEMANAGER_H_ */
