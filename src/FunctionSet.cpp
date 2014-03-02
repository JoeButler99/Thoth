/*
 * FunctionSet.cpp
 *
 *  Created on: 1 Mar 2014
 *      Author: joe
 */

#include "FunctionSet.h"

FunctionSet::FunctionSet(std::string n) : name(n) {}
FunctionSet::~FunctionSet() {}

std::vector<FunctionSet> FunctionSet::functionSets;
