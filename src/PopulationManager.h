/*
 * PopulationManager.h
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

#ifndef POPULATIONMANAGER_H_
#define POPULATIONMANAGER_H_

#include <omp.h>		// Paralisation functions
#include <algorithm> 	// Sort method
#include "Globals.h"
#include "PopulationMember.h"
#include "TvectorPM.h"



class TvectorPM;


class PopulationManager {
public:
	TvectorPM populationlist;
	PopulationManager();
	~PopulationManager();
	int pos; // Cheat int for recursion tracking
	double cutScore; // We can stop scoring in certain conditions
	int	   missedCut;

	void generateRequired();
	void scoreAllVecRpn();
	void sortByScore();
	void cullWeak();
	void writeMembersToDisk();
	void removeMembersFromDisk();
	void writeGuesses();
	void addNodesToFile(int population_member_id, std::ofstream * writefile,int depth);
	void addConstantsToFile(std::ofstream * writefile);
	void loadMembersFromDisk();
	void loadMemberFromFilename(const char * filename);
	void scoreOneMember(int memberid);
	double solveVecCaseSet(int memberid);

};

#endif /* POPULATIONMANAGER_H_ */
