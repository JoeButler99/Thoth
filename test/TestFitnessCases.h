/*
 * TestFitnessCases.h
 *
 *  Created on: 25 Nov 2013
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


#ifndef TESTFITNESSCASES_H_
#define TESTFITNESSCASES_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>
#include <math.h>
#include "../src/FitnessCases.h"
#include "../src/GlobalManager.h"


class TestFitnessCases : public CppUnit::TestFixture {
public:
	TestFitnessCases(){}
	virtual ~TestFitnessCases(){}

	void setUp() {
		gm.jsonConfig->loadFile("conf/unit-test-config.json");
	}

	static CppUnit::Test *suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestFitnessCases");

		suiteOfTests->addTest(new CppUnit::TestCaller<TestFitnessCases>("Test custom constructor",&TestFitnessCases::testDefaultConstructor));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFitnessCases>("Test LoadFile",&TestFitnessCases::testLoadFile));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFitnessCases>("Test LoadString",&TestFitnessCases::testLoadString));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFitnessCases>("Test LoadFileConstants",&TestFitnessCases::testLoadFileConstants));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFitnessCases>("Test ConstantsAppend",&TestFitnessCases::testConstantsAppend));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFitnessCases>("Test UpdateConstants",&TestFitnessCases::testUpdateConstants));


		return suiteOfTests;
	}
protected:
	 void testDefaultConstructor() {
		std::cerr << "FitnessCases:\t\t" <<  __func__ << std::endl;
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->targets.size() == 0);
		CPPUNIT_ASSERT(gm.fitnessCases->cases.size() == 0);
	 }

	 void testLoadFileConstants() {
			std::cerr << "FitnessCases:\t\t" <<  __func__ << std::endl;
			gm.fitnessCases->clear();

			CPPUNIT_ASSERT(gm.fitnessCases->targets.size() == 0);
			CPPUNIT_ASSERT(gm.fitnessCases->cases.size() == 0);
			CPPUNIT_ASSERT(gm.fitnessCases->multipliers.size() == 0);
			CPPUNIT_ASSERT(gm.fitnessCases->SCALING_ENABLED == false);
			CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/large_test_case_20c"));
			CPPUNIT_ASSERT(gm.fitnessCases->SCALING_ENABLED == true);
			CPPUNIT_ASSERT(gm.fitnessCases->TERMINALS == 294);
			CPPUNIT_ASSERT(gm.fitnessCases->TOTAL_CASES == 3000);
			CPPUNIT_ASSERT(gm.fitnessCases->NUM_VARS == 274);
			CPPUNIT_ASSERT(gm.fitnessCases->NUM_CONSTS == 20);
			CPPUNIT_ASSERT(gm.fitnessCases->CONST_LOWER == -1000);
			CPPUNIT_ASSERT(gm.fitnessCases->CONST_UPPER == 1000);
			CPPUNIT_ASSERT(gm.fitnessCases->TARGET_SCORE == 0);
			CPPUNIT_ASSERT(gm.fitnessCases->SCALING_LOWER == 0.5);
			CPPUNIT_ASSERT(gm.fitnessCases->SCALING_UPPER == 1.5);
			CPPUNIT_ASSERT(gm.fitnessCases->cp.initialMax == 1000);
			CPPUNIT_ASSERT(gm.fitnessCases->cp.initialMin == -1000);
			CPPUNIT_ASSERT(gm.fitnessCases->cp.constantSet.size() == 20);

			bool variance = false;
			double temp = 0;
			for (int x = 0; x < 20; ++x) {
				if (x == 0 ) { temp = gm.fitnessCases->cp.constantSet.at(x); }
				else {
					if (gm.fitnessCases->cp.constantSet.at(x) != temp) {
						variance = true; break;
					}
				}
			}
			CPPUNIT_ASSERT(variance);
	 }

	 void testConstantsAppend() {
			gm.fitnessCases->clear();

			CPPUNIT_ASSERT(gm.fitnessCases->targets.size() == 0);
			CPPUNIT_ASSERT(gm.fitnessCases->cases.size() == 0);
			CPPUNIT_ASSERT(gm.fitnessCases->multipliers.size() == 0);
			CPPUNIT_ASSERT(gm.fitnessCases->SCALING_ENABLED == false);
			CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/large_test_case_20c"));
			CPPUNIT_ASSERT(gm.fitnessCases->SCALING_ENABLED == true);
			CPPUNIT_ASSERT(gm.fitnessCases->TERMINALS == 294);
			CPPUNIT_ASSERT(gm.fitnessCases->TOTAL_CASES == 3000);
			CPPUNIT_ASSERT(gm.fitnessCases->NUM_VARS == 274);
			CPPUNIT_ASSERT(gm.fitnessCases->NUM_CONSTS == 20);
			CPPUNIT_ASSERT(gm.fitnessCases->CONST_LOWER == -1000);
			CPPUNIT_ASSERT(gm.fitnessCases->CONST_UPPER == 1000);
			CPPUNIT_ASSERT(gm.fitnessCases->TARGET_SCORE == 0);
			CPPUNIT_ASSERT(gm.fitnessCases->SCALING_LOWER == 0.5);
			CPPUNIT_ASSERT(gm.fitnessCases->SCALING_UPPER == 1.5);
			CPPUNIT_ASSERT(gm.fitnessCases->cp.initialMax == 1000);
			CPPUNIT_ASSERT(gm.fitnessCases->cp.initialMin == -1000);
			CPPUNIT_ASSERT(gm.fitnessCases->cp.constantSet.size() == 20);


			CPPUNIT_ASSERT(gm.fitnessCases->cases[0].size() == 294);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[50].size() == 294);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[550].size() == 294);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[0][290] != 0);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[0][291] != 0);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[0][292] != 0);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[0][290] == gm.fitnessCases->cases[30][290]);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[0][291] == gm.fitnessCases->cases[30][291]);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[0][292] == gm.fitnessCases->cases[30][292]);
	 }

	 void testUpdateConstants() {
			gm.fitnessCases->clear();

			CPPUNIT_ASSERT(gm.fitnessCases->targets.size() == 0);
			CPPUNIT_ASSERT(gm.fitnessCases->cases.size() == 0);
			CPPUNIT_ASSERT(gm.fitnessCases->multipliers.size() == 0);
			CPPUNIT_ASSERT(gm.fitnessCases->SCALING_ENABLED == false);
			CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/large_test_case_20c"));
			CPPUNIT_ASSERT(gm.fitnessCases->SCALING_ENABLED == true);
			CPPUNIT_ASSERT(gm.fitnessCases->TERMINALS == 294);
			CPPUNIT_ASSERT(gm.fitnessCases->TOTAL_CASES == 3000);
			CPPUNIT_ASSERT(gm.fitnessCases->NUM_VARS == 274);
			CPPUNIT_ASSERT(gm.fitnessCases->NUM_CONSTS == 20);
			CPPUNIT_ASSERT(gm.fitnessCases->CONST_LOWER == -1000);
			CPPUNIT_ASSERT(gm.fitnessCases->CONST_UPPER == 1000);
			CPPUNIT_ASSERT(gm.fitnessCases->TARGET_SCORE == 0);
			CPPUNIT_ASSERT(gm.fitnessCases->SCALING_LOWER == 0.5);
			CPPUNIT_ASSERT(gm.fitnessCases->SCALING_UPPER == 1.5);
			CPPUNIT_ASSERT(gm.fitnessCases->cp.initialMax == 1000);
			CPPUNIT_ASSERT(gm.fitnessCases->cp.initialMin == -1000);
			CPPUNIT_ASSERT(gm.fitnessCases->cp.constantSet.size() == 20);

			CPPUNIT_ASSERT(gm.fitnessCases->cases[0].size() == 294);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[50].size() == 294);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[550].size() == 294);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[0][290] != 0);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[0][291] != 0);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[0][292] != 0);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[0][290] == gm.fitnessCases->cases[30][290]);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[0][291] == gm.fitnessCases->cases[30][291]);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[0][292] == gm.fitnessCases->cases[30][292]);

			double original1 = gm.fitnessCases->cases[10][277];
			double original2 = gm.fitnessCases->cases[13][279];
			double original3 = gm.fitnessCases->cases[17][281];

			ConstantPool cp(1000,-1000,20);
			CPPUNIT_ASSERT(cp.constantSet.size() == 20);
			CPPUNIT_ASSERT(cp.constantSet.at(0) != 0);
			gm.fitnessCases->updateConstantSet(cp);

			CPPUNIT_ASSERT(fabs(gm.fitnessCases->cases[10][277] - original1) > 0.00001);
			CPPUNIT_ASSERT(fabs(gm.fitnessCases->cases[13][279] - original2) > 0.00001);
			CPPUNIT_ASSERT(fabs(gm.fitnessCases->cases[17][281] - original3) > 0.00001);

			CPPUNIT_ASSERT(gm.fitnessCases->cases[0].size() == 294);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[50].size() == 294);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[550].size() == 294);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[0][290] != 0);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[0][291] != 0);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[0][292] != 0);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[0][290] == gm.fitnessCases->cases[30][290]);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[0][291] == gm.fitnessCases->cases[30][291]);
			CPPUNIT_ASSERT(gm.fitnessCases->cases[0][292] == gm.fitnessCases->cases[30][292]);
	 }


	 void testLoadFile() {
		std::cerr << "FitnessCases:\t\t" <<  __func__ << std::endl;
		gm.fitnessCases->clear();

		CPPUNIT_ASSERT(gm.fitnessCases->targets.size() == 0);
		CPPUNIT_ASSERT(gm.fitnessCases->cases.size() == 0);
		CPPUNIT_ASSERT(gm.fitnessCases->SCALING_ENABLED == false);
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/medium_test_case"));
		CPPUNIT_ASSERT(gm.fitnessCases->SCALING_ENABLED == false);

		CPPUNIT_ASSERT(gm.fitnessCases->TERMINALS == 93);
		CPPUNIT_ASSERT(gm.fitnessCases->TOTAL_CASES == 1000);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_VARS == 93);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_CONSTS == 0);
		CPPUNIT_ASSERT(gm.fitnessCases->CONST_LOWER == 0);
		CPPUNIT_ASSERT(gm.fitnessCases->CONST_UPPER == 0);
		CPPUNIT_ASSERT(gm.fitnessCases->TARGET_SCORE == 0);
		CPPUNIT_ASSERT(gm.fitnessCases->SCALING_LOWER == 1);
		CPPUNIT_ASSERT(gm.fitnessCases->SCALING_UPPER == 1);
		CPPUNIT_ASSERT(gm.fitnessCases->targets.size() == 1000);
		CPPUNIT_ASSERT(gm.fitnessCases->cases.size() == 1000);
		CPPUNIT_ASSERT(gm.fitnessCases->multipliers.size() == 1000);
		CPPUNIT_ASSERT(gm.fitnessCases->cases.at(0).size() == 93);


		CPPUNIT_ASSERT(gm.fitnessCases->SCALING_ENABLED == false);
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/testSinx"));
		CPPUNIT_ASSERT(gm.fitnessCases->SCALING_ENABLED == false);
		CPPUNIT_ASSERT(gm.fitnessCases->TERMINALS == 1);
		CPPUNIT_ASSERT(gm.fitnessCases->TOTAL_CASES == 63);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_VARS == 1);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_CONSTS == 0);
		CPPUNIT_ASSERT(gm.fitnessCases->CONST_LOWER == 0);
		CPPUNIT_ASSERT(gm.fitnessCases->CONST_UPPER == 0);
		CPPUNIT_ASSERT(gm.fitnessCases->TARGET_SCORE == 0);
		CPPUNIT_ASSERT(gm.fitnessCases->SCALING_LOWER == 1);
		CPPUNIT_ASSERT(gm.fitnessCases->SCALING_UPPER == 1);
		CPPUNIT_ASSERT(gm.fitnessCases->targets.size() == 63);
		CPPUNIT_ASSERT(gm.fitnessCases->cases.size() == 63);
		CPPUNIT_ASSERT(gm.fitnessCases->multipliers.size() == 63);
		CPPUNIT_ASSERT(gm.fitnessCases->multipliers.at(0) == 1);
		CPPUNIT_ASSERT(gm.fitnessCases->multipliers.at(1) == 1);
		CPPUNIT_ASSERT(gm.fitnessCases->cases.at(0).size() == 1);


		CPPUNIT_ASSERT(gm.fitnessCases->SCALING_ENABLED == false);
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/large_test_case"));
		CPPUNIT_ASSERT(gm.fitnessCases->SCALING_ENABLED == true);
		CPPUNIT_ASSERT(gm.fitnessCases->TERMINALS == 274);
		CPPUNIT_ASSERT(gm.fitnessCases->TOTAL_CASES == 3000);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_VARS == 274);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_CONSTS == 0);
		CPPUNIT_ASSERT(gm.fitnessCases->CONST_LOWER == 0);
		CPPUNIT_ASSERT(gm.fitnessCases->CONST_UPPER == 0);
		CPPUNIT_ASSERT(gm.fitnessCases->TARGET_SCORE == 0);
		CPPUNIT_ASSERT(gm.fitnessCases->SCALING_LOWER == 0.5);
		CPPUNIT_ASSERT(gm.fitnessCases->SCALING_UPPER == 1.5);
		CPPUNIT_ASSERT(gm.fitnessCases->targets.size() == 3000);
		CPPUNIT_ASSERT(gm.fitnessCases->cases.size() == 3000);
		CPPUNIT_ASSERT(gm.fitnessCases->multipliers.size() == 3000);
		CPPUNIT_ASSERT(gm.fitnessCases->multipliers.at(0) == 0.5);
		CPPUNIT_ASSERT(gm.fitnessCases->multipliers.at(1) != 0.5);
		CPPUNIT_ASSERT(gm.fitnessCases->cases.at(0).size() == 274);

	 }

	 void testLoadString() {
		std::cerr << "FitnessCases:\t\t" <<  __func__ << std::endl;
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/large_test_case"));
		CPPUNIT_ASSERT(gm.fitnessCases->TERMINALS == 274);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_VARS == 274);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_CONSTS == 0);
		gm.fitnessCases->TERMINALS  = 0;
		gm.fitnessCases->NUM_VARS   = 0;

		std::ostringstream oss;
		std::copy(gm.fitnessCases->cases.at(0).begin(), gm.fitnessCases->cases.at(0).end()-1, std::ostream_iterator<double>(oss, " "));
		oss << gm.fitnessCases->cases.at(0).back();

		gm.fitnessCases->loadString((char*)oss.str().c_str(),274);
		CPPUNIT_ASSERT(gm.fitnessCases->TERMINALS == 274);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_VARS == 274);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_CONSTS == 0);

	 }


};


#endif

