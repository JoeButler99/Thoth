/*
 * TestRNG.h
 *
 *  Created on: 26 Aug 2013
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

#ifndef TESTPOPULATIONMEMBER_H_
#define TESTPOPULATIONMEMBER_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>
#include <math.h>
#include "../src/PopulationMember.h"
#include "../src/FitnessCases.h"

class TestPopulationMember : public CppUnit::TestFixture {
public:
	TestPopulationMember(){}
	virtual ~TestPopulationMember(){}
	PopulationMember simpleP;
	double testVars[5];

	void setUp() {
		Node n(1,true);
		simpleP.rpnNodeVec.push_back(n);
		for (int x = 0; x < 5; ++x) {
			testVars[x] = x+1;
		}

	}

	static CppUnit::Test *suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestPopulationMember");

		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test default constructor",&TestPopulationMember::testDefaultConstructor));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test Create Self",&TestPopulationMember::testCreateSelf));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test Fill Random Nodes",&TestPopulationMember::testFillRandomNodes));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test Set score",&TestPopulationMember::testSetScore));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test RpnVecSolveSelf",&TestPopulationMember::testRpnVecSolveSelf));
		//suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test RpnVecSolveSelfAll",&TestPopulationMember::testRpnVecSolveSelfAll));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test Fadd",&TestPopulationMember::testFadd));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test Fsubtract",&TestPopulationMember::testFsubtract));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test Fmultiply",&TestPopulationMember::testFmultiply));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test Fdivide",&TestPopulationMember::testFdivide));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test Fpercentme",&TestPopulationMember::testFpercentme));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test Funpercentme",&TestPopulationMember::testFunpercentme));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test Fsquared",&TestPopulationMember::testFsquared));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test FPC_change",&TestPopulationMember::testFPC_change));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test FPC_of",&TestPopulationMember::testFPC_of));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test FAVG_2",&TestPopulationMember::testFAVG_2));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test Fmin_2",&TestPopulationMember::testFmin_2));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test Fmax_2",&TestPopulationMember::testFmax_2));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test FAVG_4",&TestPopulationMember::testFAVG_4));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test Fmin_4",&TestPopulationMember::testFmin_4));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test Fmax_4",&TestPopulationMember::testFmax_4));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test FInt_Me",&TestPopulationMember::testFInt_Me));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test Fsquare_rt",&TestPopulationMember::testFsquare_rt));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test Fif_4_1",&TestPopulationMember::testFif_4_1));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test Fif_4_2",&TestPopulationMember::testFif_4_2));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test Fsum",&TestPopulationMember::testFSum));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test FAbsSum2",&TestPopulationMember::testFAbsSum2));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test FAbsSum4",&TestPopulationMember::testFAbsSum4));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test FAbsMax2",&TestPopulationMember::testFAbsMax2));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test FAbsMax4",&TestPopulationMember::testFAbsMax4));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test FlipDouble",&TestPopulationMember::testFlipDouble));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test FRaiseE",&TestPopulationMember::testFRaiseE));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationMember>("Test FLnE",&TestPopulationMember::testFLnE));

		return suiteOfTests;
	}
protected:

	void loadFitness() {
		gm.fitnessCases.clear();
		CPPUNIT_ASSERT(gm.fitnessCases.loadFile("fitness_cases/medium_test_case"));
	}

	void testDefaultConstructor() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		PopulationMember p;
		CPPUNIT_ASSERT(true);
	}

	void testCreateSelf() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		loadFitness();
		PopulationMember p;
		gm.nodeManager.initFunctions();
		p.createSelf("TestCase",3);
		CPPUNIT_ASSERT(p.rpnNodeVec.size() >= 4);
	}

	void testFillRandomNodes() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		loadFitness();
		PopulationMember p;
		gm.nodeManager.initFunctions();
		p.fillRandomNodes(2);
		CPPUNIT_ASSERT(p.rpnNodeVec.size() >= 2);
	}

	void testSetScore() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		PopulationMember p;
		p.setScore(50.698);
		CPPUNIT_ASSERT(p.score == 50.698);
		p.setScore(-10002.7);
		CPPUNIT_ASSERT(p.score == -10002.7);
	}

	void testRpnVecSolveSelf() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		loadFitness();
		PopulationMember p;
		gm.nodeManager.initFunctions();

		// Create a smaller subset before we create this member
		gm.fitnessCases.NUM_CONSTS = 0;
		gm.fitnessCases.NUM_VARS   = 5;
		gm.fitnessCases.TERMINALS  = 5;

		p.createSelf("TestCase",2);
		double result = 9999999;
		result = p.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result != 9999999);
		result = 9999999;

		PopulationMember p2;
		p2.createSelf("TestCase2",3);
		result = p2.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result != 9999999);
	}







	void testFadd() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		gm.nodeManager.initFunctions();
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(0));


		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 3 );
	}

	void testFsubtract() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(1));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == -1 );
	}

	void testFmultiply() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(2));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 2 );
	}

	void testFdivide() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(3));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 0.5 );
	}

	void testFsquared() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(4));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 1 );
	}

	void testFpercentme() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(5));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 0.01 );
	}




	void testFPC_change() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(6));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 100 );
	}

	void testFPC_of() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(7));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 50 );
	}

	void testFAVG_2() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(8));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 1.5 );
	}

	void testFmin_2() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(9));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 1 );
	}

	void testFmax_2() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(10));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 2 );
	}

	void testFAVG_4() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(11));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT((result - 3.3333333333) < 0.00001 );
	}

	void testFmin_4() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(12));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 1 );
	}

	void testFmax_4() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(13));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 4 );
	}

	void testFInt_Me() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(14));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 1 );
	}

	void testFsquare_rt() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(15));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 1 );
	}

	void testFif_4_1() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(16));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 4 );

	}

	void testFif_4_2() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(17));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 2 );
	}

	void testFunpercentme() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(18));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 100 );
	}


	void testFSum() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(19));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 10 );
	}

	void testFAbsSum2() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(20));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 3 );
	}

	void testFAbsSum4() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(21));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 10 );
	}

	void testFAbsMax2() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(22));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 2 );
	}

	void testFAbsMax4() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(23));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 4 );
	}

	void testFlipDouble() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(24));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == -1 );
	}

	void testFRaiseE() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(25));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 1 );

	}

	void testFLnE() {
		std::cerr << "PopulationMember:\t" <<  __func__ << std::endl;
		simpleP.rpnNodeVec.push_back(gm.nodeManager.getFunctionByNum(26));

		// Add the number inputs

		for (unsigned x = 0; x < simpleP.rpnNodeVec.at(1).fInputs; x++) {
			simpleP.rpnNodeVec.push_back(Node(x));
		}
		double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result == 0 );
		for(double x = 0; x < 6.3; x+= 0.1) {
			testVars[0] = x;
			double result = 99999;
		result = simpleP.rpnVecSolveSelf(testVars);
		CPPUNIT_ASSERT(result != 99999);
		}
	}


};


#endif
