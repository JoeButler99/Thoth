/*
 * FunctionSet.h
 *
 *  Created on: 1 Mar 2014
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

#ifndef FUNCTIONSET_H_
#define FUNCTIONSET_H_

#include "Function.h"
#include "RPNActions.h"

class FunctionSet {
public:
	std::string name;
	std::vector<Function> functionList;
	FunctionSet(std::string n);
	virtual ~FunctionSet();

	static std::vector<FunctionSet> functionSets;

	// Build Functionsets is the current way to get new combinations of available functions into Thoth
	// This system may be improved in future so that they may be dynamic instead of compiled
	static void buildFunctionSets() {
		functionSets.clear();

		FunctionSet basic("Basic");
		basic.functionList.push_back(Function("Add",2,0,rpnAdd));
		basic.functionList.push_back(Function("Subtract",2,1,rpnSubtract));
		basic.functionList.push_back(Function("Multiply",2,2,rpnMultiply));
		basic.functionList.push_back(Function("Divide",2,3,rpnDivide));
		functionSets.push_back(basic);

		FunctionSet basicP("Basic+");
		basicP.functionList.push_back(Function("Add",2,0,rpnAdd));
		basicP.functionList.push_back(Function("Subtract",2,1,rpnSubtract));
		basicP.functionList.push_back(Function("Multiply",2,2,rpnMultiply));
		basicP.functionList.push_back(Function("Divide",2,3,rpnDivide));
		basicP.functionList.push_back(Function("SquareRoot",1,4,rpnSquareRoot));
		basicP.functionList.push_back(Function("IFv1",4,5,rpnIfV1));
		basicP.functionList.push_back(Function("AVG4",4,6,rpnAvgOf4));
		basicP.functionList.push_back(Function("PercentChg",2,7,rpnPercentChange));
		basicP.functionList.push_back(Function("Flip",1,8,rpnNegate));
		functionSets.push_back(basicP);

		FunctionSet basicPP("Basic++");
		basicPP.functionList.push_back(Function("Add",2,0,rpnAdd));
		basicPP.functionList.push_back(Function("Subtract",2,1,rpnSubtract));
		basicPP.functionList.push_back(Function("Multiply",2,2,rpnMultiply));
		basicPP.functionList.push_back(Function("Divide",2,3,rpnDivide));
		basicPP.functionList.push_back(Function("IFv1",4,4,rpnIfV1));
		basicPP.functionList.push_back(Function("AVG4",4,5,rpnAvgOf4));
		basicPP.functionList.push_back(Function("PercentChg",2,6,rpnPercentChange));
		basicPP.functionList.push_back(Function("Flip",1,7,rpnNegate));
		basicPP.functionList.push_back(Function("Min2",2,8,rpnMinOf2));
		basicPP.functionList.push_back(Function("AVG2",2,9,rpnAvgOf2));
		basicPP.functionList.push_back(Function("AbsSum2",2,10,rpnAbsSum2));
		basicPP.functionList.push_back(Function("AbsMax4",4,11,rpnAbsMax4));
		basicPP.functionList.push_back(Function("IntMe",1,12,rpnToInt));
		functionSets.push_back(basicPP);


		FunctionSet financeFull("FinanceFull");
		financeFull.functionList.push_back(Function("Add",2,0,rpnAdd));
		financeFull.functionList.push_back(Function("Subtract",2,1,rpnSubtract));
		financeFull.functionList.push_back(Function("Multiply",2,2,rpnMultiply));
		financeFull.functionList.push_back(Function("Divide",2,3,rpnDivide));
		financeFull.functionList.push_back(Function("Square",1,4,rpnSquare));
		financeFull.functionList.push_back(Function("PercentMe",1,5,rpnPercentMe));
		financeFull.functionList.push_back(Function("PercentChg",2,6,rpnPercentChange));
		financeFull.functionList.push_back(Function("PercentOf",2,7,rpnPercentOf));
		financeFull.functionList.push_back(Function("AVG2",2,8,rpnAvgOf2));
		financeFull.functionList.push_back(Function("Min2",2,9,rpnMinOf2));
		financeFull.functionList.push_back(Function("Max2",2,10,rpnMaxOf2));
		financeFull.functionList.push_back(Function("AVG4",4,11,rpnAvgOf4));
		financeFull.functionList.push_back(Function("Min4",4,12,rpnMinOf4));
		financeFull.functionList.push_back(Function("Max4",4,13,rpnMaxOf4));
		financeFull.functionList.push_back(Function("IntMe",1,14,rpnToInt));
		financeFull.functionList.push_back(Function("SquareRoot",1,15,rpnSquareRoot));
		financeFull.functionList.push_back(Function("IFv1",4,16,rpnIfV1));
		financeFull.functionList.push_back(Function("IFv2",4,17,rpnIfV2));
		financeFull.functionList.push_back(Function("UnPercent",1,18,rpnUnPercentMe));
		financeFull.functionList.push_back(Function("Sum4",4,19,rpnSum4));
		financeFull.functionList.push_back(Function("AbsSum2",2,20,rpnAbsSum2));
		financeFull.functionList.push_back(Function("AbsSum4",4,21,rpnAbsSum4));
		financeFull.functionList.push_back(Function("AbsMax2",2,22,rpnAbsMax2));
		financeFull.functionList.push_back(Function("AbsMax4",4,23,rpnAbsMax4));
		financeFull.functionList.push_back(Function("Flip",1,24,rpnNegate));
		financeFull.functionList.push_back(Function("RaiseE",1,25,rpnRaiseE));
		financeFull.functionList.push_back(Function("LnE",1,26,rpnLnE));
		functionSets.push_back(financeFull);

	}
};


#endif /* FUNCTIONSET_H_ */
