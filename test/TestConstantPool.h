/*
 * TestConstantPool.h
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

#ifndef TESTCONSTANTPOOL_H_
#define TESTCONSTANTPOOL_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>
#include <math.h>
#include "../src/FitnessCases.h"
#include "../src/ConstantPool.h"
#include "../src/PopulationManager.h"
#include "../src/Optimiser.h"
#include "../src/EvolutionManager.h"

//
//		Constants were not a part of the original Thoth, so their
//		fitness cases have been extended to test against a wide selection of the
//		already created elements.
//
class TestConstantPool : public CppUnit::TestFixture {
public:
	TestConstantPool(){}
	virtual ~TestConstantPool(){}


	static CppUnit::Test *suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestConstantPool");

		suiteOfTests->addTest(new CppUnit::TestCaller<TestConstantPool>("Test Default Constructor",&TestConstantPool::testDefaultConstructor));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestConstantPool>("Test Custom Constructor1",&TestConstantPool::testCustomConstructor1));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestConstantPool>("Test Custom Constructor2",&TestConstantPool::testCustomConstructor2));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestConstantPool>("Test Custom Constructor3",&TestConstantPool::testCustomConstructor3));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestConstantPool>("Test LoadFromFitnessCase",&TestConstantPool::testLoadFromFitnessCase));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestConstantPool>("Test ProgramsSelectConstants",&TestConstantPool::testProgramsSelectConstants));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestConstantPool>("Test SolveWithConstants",&TestConstantPool::testSolveWithConstants));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestConstantPool>("Test SaveWithConstants",&TestConstantPool::testSaveWithConstants));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestConstantPool>("Test LoadWithConstants",&TestConstantPool::testLoadWithConstants));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestConstantPool>("Test LoadSaveEquality",&TestConstantPool::testLoadSaveEquality));
		//suiteOfTests->addTest(new CppUnit::TestCaller<TestConstantPool>("Test ConstantOptimisation",&TestConstantPool::testConstantOptimisation));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestConstantPool>("Test CliSolverWithConstants",&TestConstantPool::testCliSolverWithConstants));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestConstantPool>("Test CliSolverWithoutConstants",&TestConstantPool::testCliSolverWithoutConstants));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestConstantPool>("Test RandomlyInitialise",&TestConstantPool::testRandomlyInitialise));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestConstantPool>("Test SetFromVector",&TestConstantPool::testSetFromVector));

		return suiteOfTests;
	}
protected:
	void testDefaultConstructor() {
		std::cerr << "ConstantPool:\t\t" <<  __func__ << std::endl;
		ConstantPool cp;
		CPPUNIT_ASSERT(cp.initialMax == 0);
		CPPUNIT_ASSERT(cp.initialMin == 0);
		CPPUNIT_ASSERT(cp.constantSet.size() == 0);
		CPPUNIT_ASSERT(true);
	}

	void testCustomConstructor1() {
		std::cerr << "ConstantPool:\t\t" <<  __func__ << std::endl;
		ConstantPool cp(10.0,-10.0,20);
		CPPUNIT_ASSERT(cp.initialMax == 10);
		CPPUNIT_ASSERT(cp.initialMin == -10);
		CPPUNIT_ASSERT(cp.constantSet.size() == 20);
	}

	void testCustomConstructor2() {
		std::cerr << "ConstantPool:\t\t" <<  __func__ << std::endl;
		double vals[3] = {0.1,0.5,0.7};
		std::vector<double> testVars(vals,vals+3);
		ConstantPool cp(testVars);
		CPPUNIT_ASSERT(cp.initialMax == 0);
		CPPUNIT_ASSERT(cp.initialMin == 0);
		CPPUNIT_ASSERT(cp.constantSet.size() == 3);
	}

	void testCustomConstructor3() {
		std::cerr << "ConstantPool:\t\t" <<  __func__ << std::endl;
		double vals[5] = {0.1,0.5,0.7,8.5,-5};
		std::vector<double> testVars(vals,vals+5);
		ConstantPool cp(30,-30, testVars);
		CPPUNIT_ASSERT(cp.initialMax == 30);
		CPPUNIT_ASSERT(cp.initialMin == -30);
		CPPUNIT_ASSERT(cp.constantSet.size() == 5);
	}

	void testLoadFromFitnessCase() {
		std::cerr << "ConstantPool:\t\t" <<  __func__ << std::endl;
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/large_test_case_20c"));
		CPPUNIT_ASSERT(gm.fitnessCases->TERMINALS == 294);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_VARS == 274);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_CONSTS == 20);
		CPPUNIT_ASSERT(gm.fitnessCases->cp.constantSet.size() == 20);
		for (unsigned x = 0; x < 20; x++) {
			CPPUNIT_ASSERT(gm.fitnessCases->cp.constantSet.at(x) != 0 );
		}
	}

	// CHeck that some constants are picked when nodetrees are generated
	void testProgramsSelectConstants() {
		std::cerr << "ConstantPool:\t\t" <<  __func__ << std::endl;
		FitnessCases fc;

		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/large_test_case_20c"));
		CPPUNIT_ASSERT(gm.fitnessCases->TERMINALS == 294);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_VARS == 274);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_CONSTS == 20);
		int retries = 5;
		bool found = false;
		while(retries > 0) {
			PopulationMember p;
			p.createSelf("Test",6);
			for (unsigned x = 0; x < p.rpnNodeVec.size(); x++) {
				if (p.rpnNodeVec.at(x).isTerminal) {
					if ( p.rpnNodeVec.at(x).tNo >= gm.fitnessCases->NUM_VARS) {
						found = true; break;
					}
				}
			}
			if (found) { break; }
			retries --;
		}
		CPPUNIT_ASSERT(found);
	}

	// Make sure that the program is able to solve itself when a
	// fitness case with constants is loaded
	void testSolveWithConstants() {
		std::cerr << "ConstantPool:\t\t" <<  __func__ << std::endl;
		FitnessCases fc;
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/large_test_case_20c"));
		CPPUNIT_ASSERT(gm.fitnessCases->TERMINALS == 294);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_VARS == 274);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_CONSTS == 20);

		CPPUNIT_ASSERT(gm.fitnessCases->cases.at(0).size() == 294);
		// Solve the first 10 fitness cases for each of 5 randomly generated
		// large nodetrees.
		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		int retries = 5;
		while(retries > 0) {
			PopulationMember p;
			p.createSelf("Test",6);
			for (unsigned x = 0; x < 10; x++) {

				double result = 99999;

				CPPUNIT_ASSERT(result == 99999);
				result = p.rpnVecSolveSelf(&gm.fitnessCases->cases[x][0]);
				CPPUNIT_ASSERT(result != 99999);
			}
			retries --;
		}
	}

	// Test the writing of a nodetree to disk where the population members have constants
	// enabled
	void testSaveWithConstants() {
		std::cerr << "ConstantPool:\t\t" <<  __func__ << std::endl;
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/large_test_case_20c"));
		CPPUNIT_ASSERT(gm.fitnessCases->TERMINALS == 294);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_VARS == 274);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_CONSTS == 20);

		// Generate a population of 10
		gm.settings->SAVE_FILE_PREFIX = "test/testConsantsSave";
		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		for (int var = 0; var < 10; ++var) {
			PopulationMember p;
			p.createSelf("testSaveWithConstants",4);
			gm.populationManager->populationlist.add(p);
			gm.populationManager->scoreOneMember(var);
		}
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 10);
		gm.populationManager->sortByScore();

		// Save members
		gm.populationManager->writeMembersToDisk();

		// Check that they are all saved in the files
		// Check that the constants are all the same between files
		// Check that all files have the right number of elements
		std::ifstream ifile;
		for (int x = 0; x < 5; ++x) {
			char saveName[50];
			sprintf(saveName,"%s.%d","test/testConsantsSave",x);
			ifile.open(saveName);
			CPPUNIT_ASSERT(ifile.is_open());
			std::string line;
			int lines = 0;
			bool first = true;
			std::string last_consts = "";
			bool found_consts = false;
			for (lines = 0; std::getline(ifile, line); ++lines) {
				if (lines == 6) {
					CPPUNIT_ASSERT(line.substr(0,10) == "CONSTANTS ");
					found_consts = true;
					if (first) {
						last_consts = line; first = false;
					} else {
						CPPUNIT_ASSERT(line == last_consts);
					}
				}
			}
			CPPUNIT_ASSERT(found_consts);
			remove(saveName);
			ifile.close();
		}
		gm.populationManager->removeMembersFromDisk();
		gm.jsonConfig->updateSettings(gm.settings);
	}

	void testLoadWithConstants() {
		std::cerr << "ConstantPool:\t\t" <<  __func__ << std::endl;
		// we need to check that the constant string which we load from file, re-saves to the exact
		// same constant string and the program is valid
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/large_test_case_20c"));
		CPPUNIT_ASSERT(gm.fitnessCases->TERMINALS == 294);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_VARS == 274);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_CONSTS == 20);
		std::vector<double> original = gm.fitnessCases->cp.constantSet;
		CPPUNIT_ASSERT(original == gm.fitnessCases->cp.constantSet);

		PopulationManager pm;
		CPPUNIT_ASSERT(pm.populationlist.v.size() == 0);
		std::string mem0 = "test/constantSaveNodetree.0";
		std::string mem1 = "test/constantSaveNodetree.1";
		pm.loadMemberFromFilename(mem0.c_str());
		pm.loadMemberFromFilename(mem1.c_str());
		CPPUNIT_ASSERT(pm.populationlist.v.size() == 2);


		CPPUNIT_ASSERT(original != gm.fitnessCases->cp.constantSet);
		CPPUNIT_ASSERT(gm.fitnessCases->cp.constantSet.size() == 20);
		CPPUNIT_ASSERT(gm.fitnessCases->cases.at(0).at(274) == gm.fitnessCases->cp.constantSet.at(0));
		CPPUNIT_ASSERT(gm.fitnessCases->cases.at(10).at(275) == gm.fitnessCases->cp.constantSet.at(1));
		CPPUNIT_ASSERT(gm.fitnessCases->cases.at(20).at(276) == gm.fitnessCases->cp.constantSet.at(2));
		CPPUNIT_ASSERT(gm.fitnessCases->cases.at(0).at(274) == 10.5);
	}

	// Check that the constant sets save and load giving the same score
	void testLoadSaveEquality() {
		std::cerr << "ConstantPool:\t\t" <<  __func__ << std::endl;
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/large_test_case_20c"));
		CPPUNIT_ASSERT(gm.fitnessCases->TERMINALS == 294);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_VARS == 274);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_CONSTS == 20);

		gm.settings->SAVE_FILE_PREFIX = "testLoadSaveEquality-nodetree";
		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);

		double scores[5];
		int retries = 5;
		int loop = 0;
		while (retries > loop) {
			PopulationMember p;
			p.createSelf("testLoadSaveEquality",6);
			gm.populationManager->populationlist.add(p);
			gm.populationManager->scoreOneMember(loop);
			scores[loop] = gm.populationManager->populationlist.v.at(loop).score;
			loop++;
		}
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 5);
		gm.populationManager->writeMembersToDisk();
		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);


		gm.populationManager->loadMemberFromFilename("testLoadSaveEquality-nodetree.0"); remove("testLoadSaveEquality-nodetree.0");
		gm.populationManager->loadMemberFromFilename("testLoadSaveEquality-nodetree.1"); remove("testLoadSaveEquality-nodetree.1");
		gm.populationManager->loadMemberFromFilename("testLoadSaveEquality-nodetree.2"); remove("testLoadSaveEquality-nodetree.2");
		gm.populationManager->loadMemberFromFilename("testLoadSaveEquality-nodetree.3"); remove("testLoadSaveEquality-nodetree.3");
		gm.populationManager->loadMemberFromFilename("testLoadSaveEquality-nodetree.4"); remove("testLoadSaveEquality-nodetree.4");
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 5);
		loop = 0;
		while (retries > loop) {
			gm.populationManager->scoreOneMember(loop);
			CPPUNIT_ASSERT(scores[loop] == gm.populationManager->populationlist.v.at(loop).score);
			loop++;
		}
		gm.populationManager->removeMembersFromDisk();
		gm.jsonConfig->updateSettings(gm.settings);
	}

	void testConstantOptimisation() {
		std::cerr << "ConstantPool:\t\t" <<  __func__ << std::endl;
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/testSinx_20c"));
		CPPUNIT_ASSERT(gm.fitnessCases->TERMINALS == 21);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_VARS == 1);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_CONSTS == 20);

		ConstantPool cp = gm.fitnessCases->cp;
		CPPUNIT_ASSERT(cp.constantSet.size() == 20);

		// Run the optimisation

		CPPUNIT_ASSERT(cp.constantSet.size() == 20);



		CPPUNIT_ASSERT(false);
	}

	void testCliSolverWithConstants() {
		std::cerr << "ConstantPool:\t\t" <<  __func__ << std::endl;
		// First load a fitness case, we are going to steal one of the examples
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/large_test_case_20c"));
		CPPUNIT_ASSERT(gm.fitnessCases->TERMINALS == 294);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_VARS == 274);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_CONSTS == 20);
		double first = gm.fitnessCases->cases.at(0).at(274);
		double second = gm.fitnessCases->cases.at(0).at(275);
		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		gm.populationManager->loadMemberFromFilename("test/constantSaveNodetree.0");

		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 1);
		CPPUNIT_ASSERT(first != gm.fitnessCases->cases.at(0).at(274));
		CPPUNIT_ASSERT(second != gm.fitnessCases->cases.at(0).at(275));
		CPPUNIT_ASSERT(gm.fitnessCases->cases.at(0).at(274) == 10.5);
		CPPUNIT_ASSERT(gm.fitnessCases->cases.at(0).size() == 294);
		gm.fitnessCases->SCALING_ENABLED = false;
		// Now load a string fitness case test
		CPPUNIT_ASSERT(gm.fitnessCases->cases.size() == 3000);
		gm.fitnessCases->cliCase = gm.fitnessCases->cases.at(0);
		CPPUNIT_ASSERT(gm.fitnessCases->cliCase.size() == 294);

		double result = 10000;
		CPPUNIT_ASSERT(result == 10000);
		result = gm.populationManager->solveVecCaseSet(0);
		CPPUNIT_ASSERT(result != 10000 );

	}

	void testCliSolverWithoutConstants() {
		std::cerr << "ConstantPool:\t\t" <<  __func__ << std::endl;
		PopulationManager pm;


		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/large_test_case"));
		CPPUNIT_ASSERT(gm.fitnessCases->TERMINALS == 274);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_VARS == 274);
		CPPUNIT_ASSERT(gm.fitnessCases->NUM_CONSTS == 0);
		gm.nodeManager->setupSelf();
		pm.loadMemberFromFilename("test/noconstantSaveNodetree.0");
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 1);
		gm.fitnessCases->cliCase = gm.fitnessCases->cases[0];
		CPPUNIT_ASSERT(gm.fitnessCases->cliCase.size() == 274);

		double result = 10000;
		CPPUNIT_ASSERT(result == 10000);
		result = pm.solveVecCaseSet(0);
		CPPUNIT_ASSERT(result != 10000 );

	}

	void testRandomlyInitialise() {
		std::cerr << "ConstantPool:\t\t" <<  __func__ << std::endl;
		ConstantPool cp;
		cp.initialMin = 0;
		cp.initialMax = 10;
		cp.randomlyInitialise(50);
		CPPUNIT_ASSERT(cp.constantSet.size() == 50);

		bool variance = false;
		double temp = 0;
		for (int x = 0; x < 50; ++x) {
			if (x == 0 ) { temp = cp.constantSet.at(x); }
			else {
				if (cp.constantSet.at(x) != temp) {
					variance = true; break;
				}
			}
		}
		CPPUNIT_ASSERT(variance);
	}

	void testSetFromVector() {
		std::cerr << "ConstantPool:\t\t" <<  __func__ << std::endl;
		ConstantPool cp;
		CPPUNIT_ASSERT(cp.constantSet.size() == 0);
		double vals[8] = {1,2,3,4,5,6,7,8};
		std::vector<double> testVals(vals,vals+8);

		cp.setFromVector(testVals);
		CPPUNIT_ASSERT(cp.constantSet.size() == 8);
		CPPUNIT_ASSERT(cp.constantSet.at(0) == 1);
		CPPUNIT_ASSERT(cp.constantSet.at(4) == 5);
	}

};


#endif


