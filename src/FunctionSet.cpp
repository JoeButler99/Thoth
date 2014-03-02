/*
 * FunctionSet.cpp
 *
 *  Created on: 1 Mar 2014
 *      Author: joe
 *

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

#include "FunctionSet.h"

FunctionSet::FunctionSet(std::string n) : name(n) {}
FunctionSet::~FunctionSet() {}

std::vector<FunctionSet> FunctionSet::functionSets;
