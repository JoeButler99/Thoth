/*
 * GlobalManager.h
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

#ifndef GLOBALMANAGER_H_
#define GLOBALMANAGER_H_


#include "GuiFunctions.h"
#include "Globals.h"
#include "ArgParser.h"
#include "JsonConfigLoader.h"
#include "Settings.h"
#include "NodeManager.h"
//#include "PopulationMember.h"


// Forward Declarations
class FitnessCases;
class PopulationManager;
class Optimiser;
class EvolutionManager;
class PopulationMember;


// Global manager exists to hold together what were previously held in single global objects
class GlobalManager {
public:
	ArgParser 		  & argParser;
	JsonConfigLoader  & jsonConfig;
	Settings		  & settings;
	FitnessCases	  & fitnessCases;
	NodeManager       & nodeManager;
	PopulationManager & populationManager;
	Optimiser		  & optimiser;
	EvolutionManager  & evolutionManager;
	GlobalManager(ArgParser & argParser,JsonConfigLoader & jsonConfig,Settings & settings,
				  FitnessCases & fitnessCases,NodeManager & nodeManager,PopulationManager & populationManager,
				  Optimiser & optimiser,EvolutionManager & evolutionManager );
	~GlobalManager();
	 void loadSettings(int argc, char* argv[],bool profiling = false);
};

extern GlobalManager gm;

#endif /* GLOBALMANAGER_H_ */
