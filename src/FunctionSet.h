/*
 * FunctionSet.h
 *
 *  Created on: 1 Mar 2014
 *      Author: joe
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

	// Build Functionsets is the current way to
	static void buildFunctionSets() {
		functionSets.clear();

		FunctionSet basic("Basic");
		basic.functionList.push_back(Function("Add",2,0,rpnAdd));
		basic.functionList.push_back(Function("Subtract",2,1,rpnSubtract));
		basic.functionList.push_back(Function("Multiply",2,2,rpnMultiply));
		basic.functionList.push_back(Function("Divide",2,3,rpnDivide));
		functionSets.push_back(basic);

	}
};


#endif /* FUNCTIONSET_H_ */
