/*
 * NodeManager.cpp
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

#include "NodeManager.h"


NodeManager::NodeManager() { }

NodeManager::~NodeManager() {}

void NodeManager::setupSelf() {
	initFunctions();
}


void NodeManager::initFunctions() {
	// Try to find the function set from the settings and load it into the function list

	bool found = false;
	FunctionSet::buildFunctionSets();
	for (unsigned x = 0; x < FunctionSet::functionSets.size(); x++) {
		if (FunctionSet::functionSets.at(x).name == gm.settings->FUNCTION_SET) {
			functionlist = FunctionSet::functionSets.at(x).functionList;
			found = true;
			break;
		}
	}

	if (!found) {
		std::cout << "Could not find FUNCTION_SET named: " << gm.settings->FUNCTION_SET << std::endl;
		exit(6);
	}

}

