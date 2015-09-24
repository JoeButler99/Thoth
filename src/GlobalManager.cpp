/*
 * GlobalManager.cpp
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

#include "GlobalManager.h"

// Create my global object
GlobalManager gm;

GlobalManager::GlobalManager() : argParser(0), jsonConfig(0), settings(0), fitnessCases(0), nodeManager(0), populationManager(0), optimiser(0), evolutionManager(0), errorFunction(ErrorFunction::ABS_ERROR) {}
GlobalManager::~GlobalManager() {}

void GlobalManager::initialise(ArgParser * ap,JsonConfigLoader * jcl,Settings * s,
				  FitnessCases * fc,NodeManager * nm,PopulationManager * pm,
				  Optimiser * o,EvolutionManager * em) {
	argParser         = ap;
	jsonConfig        = jcl;
	settings          = s;
	fitnessCases      = fc;
	nodeManager       = nm;
	populationManager = pm;
	optimiser         = o;
	evolutionManager  = em;
	errorFunction     = ErrorFunction::ABS_ERROR;
}

// TODO - maybe something better
void GlobalManager::updateErrorFunction() throw(ConfigException) {
	if (settings->ERROR_FUNCTION == "ERROR_SQUARED") {
		errorFunction = ErrorFunction::ERROR_SQUARED;
	} else if (settings->ERROR_FUNCTION == "ABS_ERROR") {
		errorFunction = ErrorFunction::ABS_ERROR;
	} else {
		throw ConfigException("Unknown error function: " + settings->ERROR_FUNCTION);
	}
}


void GlobalManager::loadSettings(int argc, char* argv[],bool profiling) throw(ConfigException) {
	if (!profiling) { argParser->loadArgs(argc,argv); }


	if (argParser->action == "solve") {
		// Nothing to do here. (for now)
	} else {
		jsonConfig->loadFile(argParser->configFile);
		jsonConfig->updateSettings(settings);

		updateErrorFunction();

		// Args can override some settings from the config
		if (!profiling) {
			if (argParser->fitnessCases != "") {
				settings->FITNESS_CASE_FILE.assign(argParser->fitnessCases);
			}
		}
	}
}
