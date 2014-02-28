/*
 * Optimiser.h
 *
 *  Created on: 20 May 2013
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

#ifndef OPTIMISER_H_
#define OPTIMISER_H_
#include <vector>
#include "Node.h"
#include "PopulationMember.h"
#include "PopulationManager.h"
#include "GlobalManager.h"



class Optimiser {
public:
	Optimiser();
	~Optimiser();
	//bool silence = false; // C++ 11
	bool silence;
	void optimise(int generation,bool save);
	bool branchCutter(PopulationMember & p);
	bool terminalSwapper(PopulationMember & p);
	bool functionSwapper(PopulationMember & p);

	// We use this to score rpn_vectors we create as we try and optimise
	inline double scoreRpnVec(std::vector<Node> & rpn_vec,double score_to_beat) {
		// we bail out if we don't beat the target.
		double total_away = 0.0;
		if (gm.settings.NODE_WEIGHT != 0.0) {
			total_away  = rpn_vec.size() * gm.settings.NODE_WEIGHT;
		}

		// Loop all fitness cases
		double score;
		for (unsigned int y = 0; y < gm.fitnessCases.TOTAL_CASES; y++) {
			double result = PopulationMember::solveVecCaseSet(&gm.fitnessCases.cases[y][0],rpn_vec);

				score = result - gm.fitnessCases.targets[y];
				if (score < 0.0) { score *= -1.0;}
				if (gm.fitnessCases.SCALING_ENABLED) {
					score *= gm.fitnessCases.multipliers[y];
				}
				total_away += score;

			// Leave early if we don't beat the score
			if (total_away > score_to_beat) {
				return total_away;
			}
		}
		return total_away;
	}


};


#endif /* OPTIMISER_H_ */


