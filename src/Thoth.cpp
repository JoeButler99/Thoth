//============================================================================
// Name        : Thoth.cpp
// Author      : Joe Butler
// Version     : 0.1.1
// Copyright   : Lovingly coded by HRH
// Description : Genetic Programing in C++ using an RPN solver loop. Aims to be
//               fast.
// Contact     : joe_butler99@hotmail.com
//============================================================================

/*

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


#include <iostream>
#include <vector>		// Variable length arrays
#include <string>
#include <map>
#include <omp.h>		// Paralisation functions
#include <sys/time.h>   // Timer funcions
#include <ctime>
#include <cstring>
#include "Settings.h"
#include "JsonConfigLoader.h"
#include "PopulationManager.h"
#include "Optimiser.h"
#include "EvolutionManager.h"
#include "GlobalManager.h"
#include "ConfigException.h"





const char *welcome_text = "\033[92m\n"
"\n"
		"\n"
		"  _____ _           _   _     \n"
		" |_   _| |__   ___ | |_| |__  \n"
		"   | | | '_ \\ / _ \\| __| '_ \\ \n"
		"   | | | | | | (_) | |_| | | | \n"
		"   |_| |_| |_|\\___/ \\__|_| |_| \n"
"\n"
"\n"
"   ____    \n"
"  / ___|   _     _                        \n"
" | |     _| |_ _| |_                      \n"
" | |___ |_   _|_   _|                     \n"
"  \\____|  |_|   |_|                       \n"
"   ____                 _   _                                       \n"
"  / ___| ___ _ __   ___| |_(_) ___                                  \n"
" | |  _ / _ \\ '_ \\ / _ \\ __| |/ __|                                 \n"
" | |_| |  __/ | | |  __/ |_| | (__                                  \n"
"  \\____|\\___|_| |_|\\___|\\__|_|\\___|                                 \n"
"  ____                                                _             \n"
" |  _ \\ _ __ ___   __ _ _ __ __ _ _ __ ___  _ __ ___ (_)_ __   __ _ \n"
" | |_) | '__/ _ \\ / _` | '__/ _` | '_ ` _ \\| '_ ` _ \\| | '_ \\ / _` |\n"
" |  __/| | | ( ) | ( | | | | ( | | | | | | | | | | | | | | | | ( | |\n"
" |_|   |_|  \\___/ \\__, |_|  \\__,_|_| |_| |_|_| |_| |_|_|_| |_|\\__, |\n"
"                  |___/                                       |___/\n"
"\n"
"\n"
"\n"
" _.-/|o_0|\\-._  Copyright (C) 2013-2014 Joe Butler _.-/|0_o|\\-._\n Contact: joe_butler99@hotmail.com\n"
"\033[0m";


/*
 * 		Setup the Global Manager
 */

// Setup the gm
ArgParser ap;
JsonConfigLoader jcl;
Settings settings;
FitnessCases fc;
NodeManager nm;
PopulationManager pm;
Optimiser o;
EvolutionManager em;


int main(int argc, char* argv[]) {
	try {
		gm.initialise(&ap,&jcl,&settings,&fc,&nm,&pm,&o,&em);
		gm.loadSettings(argc,argv);


		if (gm.argParser->action == "solve") {

			gm.fitnessCases->loadString(gm.argParser->caseVars.c_str(),gm.argParser->numVars);
			gm.nodeManager->setupSelf();
			gm.populationManager->loadMemberFromFilename(gm.argParser->nodetree.c_str());
			gm.fitnessCases->addConstantsToCliCase(); // Does nothing if no constants

			double result = gm.populationManager->solveVecCaseSet(0);
			std::cout << result << std::endl;
			return 0;

		} else if(gm.argParser->action == "improve") {
			//
			//		Main Improver loop
			//
			std::cout << welcome_text <<std::endl;
			gm.argParser->displayArgs();
			gm.settings->displaySettings();

			// Try to load the fitness cases
			if (!gm.fitnessCases->loadFile(gm.settings->FITNESS_CASE_FILE)) {
				std::cout << "Unable to load fitness cases: " << gm.settings->FITNESS_CASE_FILE << std::endl;
				exit(2);
			}
			gm.fitnessCases->displayFitnessCases();

			gm.nodeManager->setupSelf();
			gm.evolutionManager->runGenerations();
		}
	} catch (ConfigException &e) {
		std::cout << "\033[31m\n";
		std::cout << e.errorMessage << "\033[0m\n\n" << std::endl;

		exit(3);
	}


	return 0;
}

