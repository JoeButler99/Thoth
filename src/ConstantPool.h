/*
 * ConstantPool.h
 *
 *  Created on: 7 Feb 2014
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

#ifndef CONSTANTPOOL_H_
#define CONSTANTPOOL_H_

#include <vector>
#include "Globals.h"
#include "RNG.h"


class ConstantPool {
public:
	std::vector<double> constantSet;
	double initialMax;
	double initialMin;
	ConstantPool();
	ConstantPool(double max, double min,int numConstants);
	ConstantPool(std::vector<double> startVals);
	ConstantPool(double max, double min, std::vector<double> startVals);
	~ConstantPool();

	void randomlyInitialise(int numConstants);

	void setFromVector(std::vector<double> inputSet);
};

#endif /* CONSTANTPOOL_H_ */
