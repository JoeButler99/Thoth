/*
 * Settings.h
 *
 *  Created on: 18 Feb 2014
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

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <string>
#include <iostream>
#include "GuiFunctions.h"

class Settings {
public:
	std::string  FUNCTION_SET;
	std::string  ERROR_FUNCTION;
	unsigned int POPULATION;
	unsigned int KEEP_TOP_PERCENT;
	double       NODE_WEIGHT;
	unsigned int GENERATIONS;
	unsigned int INITIAL_MAX_DEPTH;
	bool         USE_CUT_SCORING;
	double		 EXIT_SCORE;
	unsigned int SAVE_EVERY;
	unsigned int SAVE_TOTAL;
	std::string  SAVE_FILE_PREFIX;
	bool 		 SAVE_AFTER_EACH_OPTIMISE;
	bool		 LOAD_SAVED;
	unsigned int LOAD_TOTAL;
	bool 		 SHOW_GUESSES;
	std::string  GUESSES_FILE;
	unsigned int GUESSES_EVERY;
	unsigned int OPTIMISE_CUTTER_EVERY;
	unsigned int OPTIMISE_TERMINALS_EVERY;
	unsigned int OPTIMISE_FUNCTIONS_EVERY;
	bool		 ITERATE_CUTTER;
	bool 		 ITERATE_TERMINALS;
	bool 		 ITERATE_FUNCTIONS;
	unsigned int MUTATE_NODE_PERCENT;
	unsigned int MUTATE_TREE_PERCENT;
	unsigned int CUT_TREE_PERCENT;
	unsigned int CROSSOVER_PERCENT;
	unsigned int MUTATE_TREE_MAX_DEPTH;
	unsigned int CROSSOVER_NEW_ROOT_PERCENT;
	unsigned int SHOW_HEADINGS_EVERY;
	std::string  FITNESS_CASE_FILE;
	Settings();
	~Settings();
	void displaySettings();
};

#endif /* SETTINGS_H_ */
