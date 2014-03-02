/*
 * Settings.cpp
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

#include "Settings.h"

// Constructor with some default initialisers
Settings::Settings() :
	FUNCTION_SET("Basic"),
	POPULATION(8000),
	KEEP_TOP_PERCENT(25),
	NODE_WEIGHT(1),
	GENERATIONS(4000),
	INITIAL_MAX_DEPTH(3),
	USE_CUT_SCORING(true),
	EXIT_SCORE(0),
	SAVE_EVERY(2),
	SAVE_TOTAL(5),
	SAVE_FILE_PREFIX("nodetree"),
	SAVE_AFTER_EACH_OPTIMISE(true),
	LOAD_SAVED(true),
	LOAD_TOTAL(5),
	SHOW_GUESSES(true),
	GUESSES_FILE("program_guesses"),
	GUESSES_EVERY(5),
	OPTIMISE_CUTTER_EVERY(20),
	OPTIMISE_TERMINALS_EVERY(40),
	OPTIMISE_FUNCTIONS_EVERY(30),
	ITERATE_CUTTER(false),
	ITERATE_TERMINALS(false),
	ITERATE_FUNCTIONS(false),
	MUTATE_NODE_PERCENT(5),
	MUTATE_TREE_PERCENT(30),
	CUT_TREE_PERCENT(35),
	CROSSOVER_PERCENT(30),
	MUTATE_TREE_MAX_DEPTH(2),
	CROSSOVER_NEW_ROOT_PERCENT(0),
	SHOW_HEADINGS_EVERY(30),
	FITNESS_CASE_FILE("")
{}

Settings::~Settings() {}

void Settings::displaySettings() {
	question_msg("Thoth Settings - (JSON & Defaults):\n\n");
	std::cout << "FUNCTION_SET:\t\t\t" << FUNCTION_SET  << std::endl;
	std::cout << " POPULATION:\t\t\t" << POPULATION  << std::endl;
	std::cout << " KEEP_TOP_PERCENT:\t\t" << KEEP_TOP_PERCENT  << std::endl;
	std::cout << " NODE_WEIGHT:\t\t\t" << NODE_WEIGHT  << std::endl;
	std::cout << " GENERATIONS:\t\t\t" << GENERATIONS  << std::endl;
	std::cout << " INITIAL_MAX_DEPTH:\t\t" << INITIAL_MAX_DEPTH  << std::endl;
	std::cout << " USE_CUT_SCORING:\t\t" << display_bool(USE_CUT_SCORING)  << std::endl;
	std::cout << " EXIT_SCORE:\t\t\t" << EXIT_SCORE  << std::endl;
	std::cout << " SAVE_EVERY:\t\t\t" << SAVE_EVERY  << std::endl;
	std::cout << " SAVE_TOTAL:\t\t\t" << SAVE_TOTAL  << std::endl;
	std::cout << " SAVE_AFTER_EACH_OPTIMISE:\t" << display_bool(SAVE_AFTER_EACH_OPTIMISE)  << std::endl;
	std::cout << " LOAD_SAVED:\t\t\t" << display_bool(LOAD_SAVED)  << std::endl;
	std::cout << " LOAD_TOTAL:\t\t\t" << LOAD_TOTAL  << std::endl;
	std::cout << " SHOW_GUESSES:\t\t\t" << display_bool(SHOW_GUESSES)  << std::endl;
	std::cout << " GUESSES_FILE:\t\t\t" << GUESSES_FILE  << std::endl;
	std::cout << " GUESSES_EVERY:\t\t\t" << GUESSES_EVERY  << std::endl;
	std::cout << " OPTIMISE_CUTTER_EVERY:\t\t" << OPTIMISE_CUTTER_EVERY  << std::endl;
	std::cout << " OPTIMISE_TERMINALS_EVERY:\t" << OPTIMISE_TERMINALS_EVERY  << std::endl;
	std::cout << " OPTIMISE_FUNCTIONS_EVERY:\t" << OPTIMISE_FUNCTIONS_EVERY  << std::endl;
	std::cout << " ITERATE_CUTTER:\t\t" << display_bool(ITERATE_CUTTER)  << std::endl;
	std::cout << " ITERATE_TERMINALS:\t\t" << display_bool(ITERATE_TERMINALS)  << std::endl;
	std::cout << " ITERATE_FUNCTIONS:\t\t" << display_bool(ITERATE_FUNCTIONS)  << std::endl;
	std::cout << " MUTATE_NODE_PERCENT:\t\t" << MUTATE_NODE_PERCENT  << std::endl;
	std::cout << " MUTATE_TREE_PERCENT:\t\t" << MUTATE_TREE_PERCENT  << std::endl;
	std::cout << " CUT_TREE_PERCENT:\t\t" << CUT_TREE_PERCENT  << std::endl;
	std::cout << " CROSSOVER_PERCENT:\t\t" << CROSSOVER_PERCENT  << std::endl;
	std::cout << " MUTATE_TREE_MAX_DEPTH:\t\t" << MUTATE_TREE_MAX_DEPTH  << std::endl;
	std::cout << " CROSSOVER_NEW_ROOT_PERCENT:\t" << CROSSOVER_NEW_ROOT_PERCENT  << std::endl;
	std::cout << " SHOW_HEADINGS_EVERY:\t\t" << SHOW_HEADINGS_EVERY  << std::endl;
	std::cout << " FITNESS_CASE_FILE:\t\t" << FITNESS_CASE_FILE  << std::endl;
	std::cout << std::endl;
}
