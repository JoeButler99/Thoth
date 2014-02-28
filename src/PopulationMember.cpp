/*
 * PopulationMember.cpp
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

#include "PopulationMember.h"


PopulationMember::PopulationMember() : method("None"), hasChanged(true), score(-1) { }

// This Constructor helps speed up the evolutions methods with copy an existing member
PopulationMember::PopulationMember(std::vector<Node> inputVec)
: method("RPN-Copy"), hasChanged(true), score(-1), rpnNodeVec(inputVec) {
}

void PopulationMember::createSelf(std::string m,int depth) {
	hasChanged = true;
	method = m;
	//rpn_node_vec.clear();
	Node n(1,true);
	// Build this population member
	rpnNodeVec.push_back(n);
	for (unsigned int x = 0; x < n.fInputs; x++) {
		fillRandomNodes(depth);
	}
}

void PopulationMember::fillRandomNodes(int max_depth) {
	// We always return a terminal node if we are out of depth,
	// or if we are on the grow method and we pass a 1/5 test
	if (( max_depth == 0 ) || ((method == "grow") && (rng.iRand(100) % 5 == 0))){
		// TODO - move the node into the push back
		Node n(rng.iRand(gm.fitnessCases.TERMINALS));
		rpnNodeVec.push_back(n);
	} else {
		Node n(gm.nodeManager.giveRandFunction());
		rpnNodeVec.push_back(n);
		for (unsigned int x = 0; x < n.fInputs; x++) {
			fillRandomNodes(max_depth -1);
		}
	}
}

void PopulationMember::setScore(double s) {
	if (gm.settings.NODE_WEIGHT != 0.0 ) {
		score = s + (rpnNodeVec.size() *  gm.settings.NODE_WEIGHT);
	} else {
		score = s;
	}
	hasChanged = false;
}

