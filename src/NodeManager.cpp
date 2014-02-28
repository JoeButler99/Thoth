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
	//initTerminals();
	initFunctions();
}

//void NodeManager::setLastFunctionLocation() {
//	unsigned loc = functionlist.size() -1;
//	functionlist.at(loc).location = loc;
//}

void NodeManager::initFunctions() {
	Function cpfadd 		= Function("Add",2,0) ;
	Function cpfsubtract	= Function("Subtract",2,1) ;
	Function cpfdivide   	= Function("Multiply",2,2) ;
	Function cpfmultiply 	= Function("Divide",2,3) ;
	Function cpfsquared 	= Function("Square",1,4) ;
	Function cpfpercentme	= Function("PercentMe",1,5) ;
	Function cpfpcchange	= Function("PercentChg",2,6);
	Function cpfpcof		= Function("PercentOf",2,7);
	Function cpfavg2 		= Function("AVG 2",2,8);
	Function cpfmin2		= Function("Min 2",2,9);
	Function cpfmax2		= Function("Max 2",2,10);
	Function cpfavg4		= Function("AVG 4",4,11);
	Function cpfmin4		= Function("Min 4",4,12);
	Function cpfmax4		= Function("Max 4",4,13);
	Function cpfintme		= Function("Int Me",1,14);
	Function cpfsquarert	= Function("Square RT",1,15);
	Function cpfif41		= Function("IF v1",4,16);
	Function cpfif42		= Function("IF v2",4,17);
	Function cpfunpercentme = Function("* 100",1,18);
	Function cpfsum			= Function("Sum4",4,19);
	Function cpfabssum2		= Function("AbsSum2",2,20);
	Function cpfabssum4		= Function("AbsSum4",4,21);
	Function cpfabsmax2		= Function("AbsMax2",2,22);
	Function cpfabsmax4		= Function("AbsMax4",4,23);
	Function cpfflipdouble	= Function("Flip",1,24);
	Function cpfraisee		= Function("raise e",1,25);
	Function cpflne			= Function("ln e",1,26);


	functionlist.push_back(cpfadd); //setLastFunctionLocation();
	functionlist.push_back(cpfsubtract); //setLastFunctionLocation();
	functionlist.push_back(cpfdivide); //setLastFunctionLocation();
	functionlist.push_back(cpfmultiply); //setLastFunctionLocation();
	functionlist.push_back(cpfsquared); //setLastFunctionLocation();
	functionlist.push_back(cpfpercentme); //setLastFunctionLocation();
	functionlist.push_back(cpfpcchange); //setLastFunctionLocation();
	functionlist.push_back(cpfpcof); //setLastFunctionLocation();
	functionlist.push_back(cpfavg2); //setLastFunctionLocation();
	functionlist.push_back(cpfmin2); //setLastFunctionLocation();
	functionlist.push_back(cpfmax2); //setLastFunctionLocation();
	functionlist.push_back(cpfavg4); //setLastFunctionLocation();
	functionlist.push_back(cpfmin4); //setLastFunctionLocation();
	functionlist.push_back(cpfmax4); //setLastFunctionLocation();
	functionlist.push_back(cpfintme); //setLastFunctionLocation();
	functionlist.push_back(cpfsquarert); //setLastFunctionLocation();
	functionlist.push_back(cpfif41); //setLastFunctionLocation();
	functionlist.push_back(cpfif42); //setLastFunctionLocation();
	functionlist.push_back(cpfunpercentme); //setLastFunctionLocation();
	functionlist.push_back(cpfsum);
	functionlist.push_back(cpfabssum2);
	functionlist.push_back(cpfabssum4);
	functionlist.push_back(cpfabsmax2);
	functionlist.push_back(cpfabsmax4);
	functionlist.push_back(cpfflipdouble);
	functionlist.push_back(cpfraisee);
	functionlist.push_back(cpflne);

}

