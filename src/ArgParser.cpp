/*
 * ArgParser.cpp
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

#include "ArgParser.h"

ArgParser::ArgParser() : numVars(0) {}

ArgParser::~ArgParser() {}


void ArgParser::usage(bool exitAfter, int exitcode) {
	std::cout << "\nUsage:" << std::endl;

	std::cout << "--action\t\t" << "Which action to perform." << std::endl;
	std::cout << "\t\t\t  'solve' - Solves a set of inputs from the CLI with a nodetree and a given number of variables. Requires: --nodetree"  << std::endl;
	std::cout << "\t\t\t  'improve' - (Default) loads the fitnesscases and configfile, which can also be default, and try to improve the program\n"  << std::endl;
	std::cout << "--nodetree\t\t" << "- Which nodetree to use when solving the program\n"<< std::endl;
	std::cout << "--case-variables:\t" << "- Takes a string with the variables surounded by quotes. Eg. \"1 2 7.5 99.34 ... \"\n" << std::endl;
	std::cout << "--fitness-cases:\t" << "- Method to override fitness cases. Can also be set in the config file\n" << std::endl;
	std::cout << "--config-file\t\t" << "- (Default: conf/config.json) Optional way to specify a config file.\n" << std::endl;
	std::cout << "-h\t\t\t" << "- Display usage.\n" << std::endl;
	std::cout << std::endl;
	std::cout << "See README.md for more information.\n" << std::endl;
	if (exitAfter) {
		exit(exitcode);
	}
}

// isValid checks that the arguments are suitable to continue
bool ArgParser::isValid(bool dieOnError) {
	if (action == "solve") {
		if (numVars == 0) {
			error_msg("\nERROR: --num-vars is required to solve a case");
			usage(true,1);
		} else if (nodetree == "") {
			error_msg("\nERROR: --nodetree is required to solve a case");
			usage(true,1);
		} else if (caseVars == "") {
			error_msg("\nERROR: --case-variables are required to solve a case");
			usage(true,1);
		}
	} else if (action == "improve") {
		// Should be fine with defaults. This might change in the future.
	} else {
		if (dieOnError) {
			error_msg("\nERROR: Unknown action. Unable to continue.");
			usage(true,1);
		} else {
			return false;
		}
	}
	return true;
}

void ArgParser::loadArgs(int argc, char * argv[],bool dieOnError) {
	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			if (i + 1 != argc)  { // Check that we haven't finished parsing already
                if ( strcmp(argv[i],"--action") == 0 ) {
                    action = argv[i + 1];
                    i++;
                } else if (strcmp(argv[i],"--case-variables") == 0 ) {
                	caseVars = argv[i + 1];
                    i++;
                } else if (strcmp(argv[i],"--num-vars") == 0 ) {
                    numVars = atoi(argv[i + 1]);
                    i++;
                } else if (strcmp(argv[i],"--fitness-cases") == 0 ) {
                    fitnessCases = argv[i + 1];
                    i++;
                } else if (strcmp(argv[i],"--config-file") == 0 ) {
                    configFile = argv[i + 1];
                    i++;
                } else if (strcmp(argv[i],"--nodetree") == 0 ) {
                	nodetree =  argv[i + 1];
                	i++;
    			} else if (strcmp(argv[i],"-h") == 0 ) {
                	usage(true,0);
                } else {
                	std::cout << "ERROR WITH CLI ARGUMENTS" <<std::endl;
                	std::cout << argv[i] << std::endl;
                    exit(2);
                }
			} else if (strcmp(argv[i],"-h") == 0 ) {
            	usage(true,0);
			}
			// Set the default action to improve if not specified.
			if (action == "") {	action = "improve"; }

			// Set the default config if not specified.
			if (configFile == "") { configFile   = "conf/config.json"; }

		}
	} else {
		// TODO - move these defaults to another more easily testable place. See Settings class too.
		// When no arguments are passed in, we setup defaults to
		// let a default config file handle things
		action       = "improve";
		nodetree     = "";
		caseVars     = "";
		fitnessCases = "";
		configFile   = "conf/config.json";
	}
	isValid(dieOnError);
}

void ArgParser::displayArgs() {
	question_msg("Thoth CLI Settings:\n\n");
	std::cout << "Action:\t\t" << action << std::endl;
	std::cout << " Nodetree:\t\t" << nodetree << std::endl;
	std::cout << " Case Vars:\t\t" << caseVars << std::endl;
	std::cout << " Fitness Cases:\t\t" << fitnessCases << std::endl;
	std::cout << " Config File:\t\t" << configFile << std::endl;
	std::cout << " Num Vars:\t\t" << numVars<< std::endl;
	std::cout  << std::endl;
}




