/*
 * FitnessCases.cpp
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

#include "FitnessCases.h"


FitnessCases::FitnessCases() :
TOTAL_CASES(0),
TERMINALS(0),
NUM_VARS(0),
NUM_CONSTS(0),
CONST_LOWER(0),
CONST_UPPER(0),
TARGET_SCORE(0),
SCALING_ENABLED(false),
SCALING_LOWER(0),
SCALING_UPPER(0),
errorstr(""),
error(false)
{}

FitnessCases::~FitnessCases() { }


// Load in a std::string set given by the cli. We could get some error handling here
void FitnessCases::loadString(const char * var_set,int num_vars) {
	NUM_VARS    = num_vars;
	std::string vars = (std::string)var_set;
	std::string v;
	std::istringstream iss(vars);
	while ( getline(iss,v,' ')) {
		cliCase.push_back(atof(v.c_str()));
	}
	if (cliCase.size() != NUM_VARS) {
		std::cout << "LOOKING FOR: " << NUM_VARS << " VARS." << std::endl;
		std::cout << "BUT GOT " << cliCase.size() << std::endl;
		exit(3);
	}

	TERMINALS = NUM_VARS; // Constants can be added in later
}

bool FitnessCases::loadFile(std::string inputfile) {
	std::ifstream infile(inputfile.c_str());
	if (!infile.is_open()) {
		return false;
	} else {
		inputFile = inputfile;
	}
	std::string line;
	unsigned ln = 0;
	targets.clear();
	cases.clear();
	multipliers.clear();
	// read the file by line and fill some shizzle with it
	for( std::string line; getline( infile, line ); )
	{
		std::istringstream iss(line);
		if ( ln == 0 ) {
			// Process the first line of the file to fill some details about the test cases
			if (!(iss >> NUM_VARS >> NUM_CONSTS >>  CONST_LOWER >> CONST_UPPER )) {
				error = true;
				errorstr = "Unable to unpack fitness cases file. (Line 1)";
				break;
			}
			if (NUM_CONSTS != 0) {
				// We need to setup a constant pool for this fitness case
				cp = ConstantPool(CONST_UPPER,CONST_LOWER,NUM_CONSTS);
			}
		} else if (ln == 1) {
			if (!(iss >> TARGET_SCORE >> TOTAL_CASES >> SCALING_LOWER >> SCALING_UPPER)) {
				error = true;
				errorstr = "Unable to unpack fitness cases file. (Line 2)";
				break;
			}
			TERMINALS = NUM_VARS + NUM_CONSTS;
			if (SCALING_LOWER == 1 && SCALING_UPPER == 1) {
				SCALING_ENABLED = false;
			} else {
				SCALING_ENABLED = true;
			}
		} else {
			// Add this row as a FitnessCase
			double temp;
			double target;

			std::vector<double> v;
			std::vector<double> t;
			bool lineerror = false;
			for (unsigned a = 0; a < NUM_VARS; a++) {
				if ( !(iss >> temp) ) {
					lineerror = true;
				} else {
					v.push_back(temp);
				}
			}
			if(!lineerror) {
				cases.push_back(v);
			}




			iss >> target;
			targets.push_back(target);
			double diff = (SCALING_UPPER - SCALING_LOWER) / (TOTAL_CASES * 1.0);

			if (SCALING_ENABLED) {
				multipliers.push_back(SCALING_LOWER + (ln -2) * diff);
			} else {
				multipliers.push_back(1);
			}
		}

		//update loop and break if ready
	    ln++;
	    if ((ln > 1) && (ln - 2 > TOTAL_CASES)) {
	    	break;
	    }
	}
	infile.close();

	// If we created constants, they need to be appended onto every fitness case set
	if (NUM_CONSTS != 0 ) {
		for (unsigned x = 0; x < cases.size(); x++) {
			cases.at(x).insert(cases.at(x).end(), cp.constantSet.begin(),cp.constantSet.end());
		}
	}

	// Check how we did and return
	if (!error && ln > 2) {
		return true;
	} else {
		return false;
	}
}


void FitnessCases::updateConstantSet(ConstantPool newCP) {
	if (newCP.constantSet.size() == cp.constantSet.size()) {
		cp = newCP;
		for (unsigned x = 0; x < cases.size(); x++) {
			for (unsigned y = 0; y < cp.constantSet.size(); y++) {
				cases.at(x).at(NUM_VARS + y) = cp.constantSet.at(y);
			}
		}
	} else {
		// We are updating, but should not touch any cases
		cp = newCP;
		NUM_CONSTS = cp.constantSet.size();
		TERMINALS = NUM_CONSTS + NUM_VARS;

	}
}

void FitnessCases::addConstantsToCliCase() {
	for (unsigned x = 0; x < cp.constantSet.size(); x++) {
		cliCase.push_back(cp.constantSet.at(x));
	}
}


void FitnessCases::displayFitnessCases() {
	question_msg("Fitness Case settings: - ("+inputFile+ ") \n\n");
	std::cout << "TOTAL_CASES:\t\t\t" <<  TOTAL_CASES << std::endl;
	std::cout << " TERMINALS:\t\t\t" <<  TERMINALS << std::endl;
	std::cout << " NUM_VARS:\t\t\t" <<  NUM_VARS << std::endl;
	std::cout << " NUM_CONSTS:\t\t\t" <<  NUM_CONSTS << std::endl;
	std::cout << " CONST_LOWER:\t\t\t" <<  CONST_LOWER << std::endl;
	std::cout << " CONST_UPPER:\t\t\t" <<  CONST_UPPER << std::endl;
	std::cout << " TARGET_SCORE:\t\t\t" <<  TARGET_SCORE << std::endl;
	std::cout << " SCALING_ENABLED:\t\t" <<  display_bool(SCALING_ENABLED) << std::endl;
	std::cout << " SCALING_LOWER:\t\t\t" <<  SCALING_LOWER << std::endl;
	std::cout << " SCALING_UPPER:\t\t\t" <<  SCALING_UPPER << std::endl;
	std::cout << std::endl;
}

