/*
 * JsonConfigLoader.cpp
 *
 *  Created on: 17 Feb 2014
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

#include "JsonConfigLoader.h"

JsonConfigLoader::JsonConfigLoader() :loaded(false) {}

JsonConfigLoader::~JsonConfigLoader() {}


bool JsonConfigLoader::loadFile(std::string inputfile) {

	root.clear();

	std::fstream jsonFile(inputfile.c_str());
	if (!jsonFile.is_open()) {
		std::cout << "Unable to open: " << inputfile << std::endl;
		return false;
	}
	std::string jsonContent( (std::istreambuf_iterator<char>(jsonFile) ),
						   (std::istreambuf_iterator<char>()    ) );

	bool parsingSuccessful = reader.parse( jsonContent, root );
	if (!parsingSuccessful) {
	    // report to the user the failure and their locations in the document.
	    std::cout  << "Failed to parse configuration\n"
	               << reader.getFormattedErrorMessages();
		return false;
	}
	jsonFile.close();

	loaded = true;
	return true;
}


// Look to update the settings with any values provided by the json
bool JsonConfigLoader::updateSettings(Settings & settings) {
	if (!loaded) { return false; }

	// Update the unsigned Ints
	settings.POPULATION = root.get("POPULATION",settings.POPULATION).asInt();
	settings.KEEP_TOP_PERCENT = root.get("KEEP_TOP_PERCENT",settings.KEEP_TOP_PERCENT).asInt();
	settings.GENERATIONS = root.get("GENERATIONS",settings.GENERATIONS).asInt();
	settings.INITIAL_MAX_DEPTH = root.get("INITIAL_MAX_DEPTH",settings.INITIAL_MAX_DEPTH).asInt();
	settings.SAVE_EVERY = root.get("SAVE_EVERY",settings.SAVE_EVERY).asInt();
	settings.SAVE_TOTAL = root.get("SAVE_TOTAL",settings.SAVE_TOTAL).asInt();
	settings.LOAD_TOTAL = root.get("LOAD_TOTAL",settings.LOAD_TOTAL).asInt();
	settings.GUESSES_EVERY = root.get("GUESSES_EVERY",settings.GUESSES_EVERY).asInt();
	settings.OPTIMISE_CUTTER_EVERY = root.get("OPTIMISE_CUTTER_EVERY",settings.OPTIMISE_CUTTER_EVERY).asInt();
	settings.OPTIMISE_TERMINALS_EVERY = root.get("OPTIMISE_TERMINALS_EVERY",settings.OPTIMISE_TERMINALS_EVERY).asInt();
	settings.OPTIMISE_FUNCTIONS_EVERY = root.get("OPTIMISE_FUNCTIONS_EVERY",settings.OPTIMISE_FUNCTIONS_EVERY).asInt();
	settings.MUTATE_NODE_PERCENT = root.get("MUTATE_NODE_PERCENT",settings.MUTATE_NODE_PERCENT).asInt();
	settings.MUTATE_TREE_PERCENT = root.get("MUTATE_TREE_PERCENT",settings.MUTATE_TREE_PERCENT).asInt();
	settings.CUT_TREE_PERCENT = root.get("CUT_TREE_PERCENT",settings.CUT_TREE_PERCENT).asInt();
	settings.CROSSOVER_PERCENT = root.get("CROSSOVER_PERCENT",settings.CROSSOVER_PERCENT).asInt();
	settings.MUTATE_TREE_MAX_DEPTH = root.get("MUTATE_TREE_MAX_DEPTH",settings.MUTATE_TREE_MAX_DEPTH).asInt();
	settings.CROSSOVER_NEW_ROOT_PERCENT = root.get("CROSSOVER_NEW_ROOT_PERCENT",settings.CROSSOVER_NEW_ROOT_PERCENT).asInt();
	settings.SHOW_HEADINGS_EVERY = root.get("SHOW_HEADINGS_EVERY",settings.SHOW_HEADINGS_EVERY).asInt();

	// Update the doubles
	settings.NODE_WEIGHT = root.get("NODE_WEIGHT",settings.NODE_WEIGHT).asDouble();
	settings.EXIT_SCORE = root.get("EXIT_SCORE",settings.EXIT_SCORE).asDouble();

	// Update the bools
	settings.USE_CUT_SCORING = root.get("USE_CUT_SCORING",settings.USE_CUT_SCORING).asBool();
	settings.SAVE_AFTER_EACH_OPTIMISE = root.get("SAVE_AFTER_EACH_OPTIMISE",settings.SAVE_AFTER_EACH_OPTIMISE).asBool();
	settings.LOAD_SAVED = root.get("LOAD_SAVED",settings.LOAD_SAVED).asBool();
	settings.SHOW_GUESSES = root.get("SHOW_GUESSES",settings.SHOW_GUESSES).asBool();
	settings.ITERATE_CUTTER = root.get("ITERATE_CUTTER",settings.ITERATE_CUTTER).asBool();
	settings.ITERATE_TERMINALS = root.get("ITERATE_TERMINALS",settings.ITERATE_TERMINALS).asBool();
	settings.ITERATE_FUNCTIONS = root.get("ITERATE_FUNCTIONS",settings.ITERATE_FUNCTIONS).asBool();

	// Update the strings
	settings.FUNCTION_SET     = root.get("FUNCTION_SET",settings.FUNCTION_SET).asString();
	settings.SAVE_FILE_PREFIX = root.get("SAVE_FILE_PREFIX",settings.SAVE_FILE_PREFIX).asString();
	settings.GUESSES_FILE     = root.get("GUESSES_FILE",settings.GUESSES_FILE).asString();
	if (settings.FITNESS_CASE_FILE == "") {
		settings.FITNESS_CASE_FILE = root.get("FITNESS_CASE_FILE",settings.FITNESS_CASE_FILE).asString();
	}

	return true;
}
