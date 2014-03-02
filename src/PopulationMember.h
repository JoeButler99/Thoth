/*
 * PopulationMember.h
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

#ifndef POPULATIONMEMBER_H_
#define POPULATIONMEMBER_H_
#include <vector>
#include <string>
#include "Node.h"
#include "Function.h"
#include "RNG.h"
#include "GlobalManager.h"
#include "FitnessCases.h"
#include "NodeManager.h"


class PopulationMember {
public:
	std::string method;
	bool hasChanged;
	double score;
	std::vector<Node> rpnNodeVec;

	PopulationMember();
	PopulationMember(std::vector<Node> inputVec);

	void createSelf(std::string m,int depth);
	void fillRandomNodes(int max_depth);
	void displaySelf();
	void setScore(double s);

	inline bool operator< (const PopulationMember& rhs) const{
		return this->score < rhs.score;
	}

	inline static double rpnVecSolve(double * var_set, std::vector<Node> & rpnNodeVec) {
		double rpnStack[RPN_STACK_LIMIT] = {0};
		int highest = 0;
		for (int x = rpnNodeVec.size()-1; x > 0; x -- ) {
			if (rpnNodeVec[x].isTerminal) {
				// Add to stack
				rpnStack[highest] = var_set[rpnNodeVec[x].tNo];
				highest ++;
			} else {
				gm.nodeManager.functionlist.at(rpnNodeVec[x].fNo).action(rpnStack,highest);
				highest ++;
			}
		}
		return rpnStack[0];
	}

	inline double rpnVecSolveSelf(double * var_set) const {
		double rpnStack[RPN_STACK_LIMIT] = {0};
		int highest = 0;
		for (int x = rpnNodeVec.size()-1; x > 0; x -- ) {
			if (rpnNodeVec[x].isTerminal) {
				// Add to stack
				rpnStack[highest] = var_set[rpnNodeVec[x].tNo];
				highest ++;
			} else {
				gm.nodeManager.functionlist.at(rpnNodeVec[x].fNo).action(rpnStack,highest);
				highest ++;
			}
		}
		return rpnStack[0];
	}

};

#endif /* POPULATIONMEMBER_H_ */
