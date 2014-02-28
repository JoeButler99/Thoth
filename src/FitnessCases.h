/*
 * FitnessCases.h
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

#ifndef FITNESSCASES_H_
#define FITNESSCASES_H_
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "ConstantPool.h"
#include "GuiFunctions.h"


class FitnessCases {
public:
	unsigned TOTAL_CASES;
	unsigned TERMINALS;
	unsigned NUM_VARS;
	unsigned NUM_CONSTS;
	double   CONST_LOWER;
	double   CONST_UPPER;
	double   TARGET_SCORE;
	bool 	SCALING_ENABLED;
	double 	 SCALING_LOWER;
	double 	 SCALING_UPPER;
	std::vector<double> multipliers;
	std::vector<double> targets;
	std::vector<std::vector<double> > cases;
	std::vector<double> cliCase;
	std::string errorstr;
	std::string inputFile;
	bool error;
	ConstantPool cp;

	FitnessCases();
	~FitnessCases();

	// Class Methods
	void loadString(const char * var_set,int num_vars);
	void updateConstantSet(ConstantPool newCP);
	void addConstantsToCliCase();
	bool loadFile(std::string inputfile);
	void displayFitnessCases();
	bool clear() {
		TOTAL_CASES = 0;
		TERMINALS   = 0;
		NUM_VARS    = 0;
		NUM_CONSTS  = 0;
		CONST_LOWER = 0;
		CONST_UPPER = 0;
		TARGET_SCORE = 0;
		SCALING_ENABLED = false;
		SCALING_LOWER = 1;
		SCALING_UPPER = 1;
		multipliers.clear();
		targets.clear();
		cases.clear();
		errorstr.clear();
		inputFile.clear();
		error = false;
		cp.constantSet.clear();
		return true;
	}
};

#endif /* FITNESSCASES_H_ */
