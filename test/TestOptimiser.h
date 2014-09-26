/*
 * TestOptimiser.h
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

#ifndef TESTOPTIMISER_H_
#define TESTOPTIMISER_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include "../src/Optimiser.h"

class TestOptimiser : public CppUnit::TestFixture {
public:
	TestOptimiser(){}
	virtual ~TestOptimiser(){ }

	static CppUnit::Test *suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestOptimiser");

		suiteOfTests->addTest(new CppUnit::TestCaller<TestOptimiser>("Test testDefault Constructor",&TestOptimiser::testDefaultConstructor));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestOptimiser>("Test Branch Cutter",&TestOptimiser::testBranchCutter));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestOptimiser>("Test Function Swapper",&TestOptimiser::testFunctionSwapper));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestOptimiser>("Test Terminal Swapper",&TestOptimiser::testTerminalSwapper));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestOptimiser>("Test scoreRpnVec",&TestOptimiser::testScoreRpnVec));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestOptimiser>("Test Optimise",&TestOptimiser::testOptimise));


		return suiteOfTests;
	}

//	void setUp() {
//		freopen("/dev/null","r",stdout);//redirects standard input
//	}
//
//	void tearDown() {
//		freopen ("/dev/tty", "a", stdout);
//	}

protected:
	void testDefaultConstructor() {
		std::cerr << "Optimiser:\t\t" <<  __func__ << std::endl;
		Optimiser o;
		CPPUNIT_ASSERT(true);
	}

	void testBranchCutter() {
		std::cerr << "Optimiser:\t\t" <<  __func__ << std::endl;
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/testSinx"));
		gm.populationManager->populationlist.v.clear();

		PopulationMember p;
		int startSize, finalSize;
		double startScore, finalScore;
		bool improvement = false;
		int loops = 1;
		while(!improvement) {
			p.createSelf("TestCase",3);
			gm.populationManager->populationlist.add(p);
			gm.populationManager->scoreOneMember(0);
			startScore = gm.populationManager->populationlist.v.at(0).score;
			startSize  = gm.populationManager->populationlist.v.at(0).rpnNodeVec.size();
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).rpnNodeVec.size() > 0);

			gm.optimiser->branchCutter(gm.populationManager->populationlist.v.at(0));

			finalScore = gm.populationManager->populationlist.v.at(0).score;
			finalSize  = gm.populationManager->populationlist.v.at(0).rpnNodeVec.size();

			CPPUNIT_ASSERT(finalScore <= startScore);
			CPPUNIT_ASSERT(finalSize <= startSize);
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).score != 0);
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).rpnNodeVec.size() > 1);
			if(finalScore < startScore) {
				improvement = true;
			} else {
				loops++;
				gm.populationManager->populationlist.v.clear();
				std::cerr << "\t\t\t * Improve Attempt: " <<  loops << std::endl;
			}
		}

	}

	void testTerminalSwapper() {
		std::cerr << "Optimiser:\t\t" <<  __func__ << std::endl;
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/medium_test_case"));
		gm.populationManager->populationlist.v.clear();
		PopulationMember p;
		int startSize, finalSize;
		double startScore, finalScore;
		bool improvement = false;
		int loops = 1;
		while(!improvement) {
			p.createSelf("TestCase",3);
			gm.populationManager->populationlist.add(p);
			gm.populationManager->scoreOneMember(0);
			startScore = gm.populationManager->populationlist.v.at(0).score;
			startSize  = gm.populationManager->populationlist.v.at(0).rpnNodeVec.size();
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).rpnNodeVec.size() > 0);

			gm.optimiser->terminalSwapper(gm.populationManager->populationlist.v.at(0));

			finalScore = gm.populationManager->populationlist.v.at(0).score;
			finalSize  = gm.populationManager->populationlist.v.at(0).rpnNodeVec.size();
			CPPUNIT_ASSERT(finalScore <= startScore);
			CPPUNIT_ASSERT(finalSize == startSize);
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).score != 0);
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).rpnNodeVec.size() > 1);
			if(finalScore < startScore) {
				improvement = true;
			} else {
				loops++;
				gm.populationManager->populationlist.v.clear();
				std::cerr << "\t\t\t * Improve Attempt: " <<  loops << std::endl;
			}
			break;
		}
	}

	void testFunctionSwapper() {
		std::cerr << "Optimiser:\t\t" <<  __func__ << std::endl;
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/large_test_case"));
		gm.populationManager->populationlist.v.clear();

		PopulationMember p;
		int startSize, finalSize;
		double startScore, finalScore;
		bool improvement = false;
		int loops = 1;
		while(!improvement) {
			p.createSelf("TestCase",3);
			gm.populationManager->populationlist.add(p);
			gm.populationManager->scoreOneMember(0);
			startScore = gm.populationManager->populationlist.v.at(0).score;
			startSize  = gm.populationManager->populationlist.v.at(0).rpnNodeVec.size();
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).rpnNodeVec.size() > 0);

			gm.optimiser->functionSwapper(gm.populationManager->populationlist.v.at(0));

			finalScore = gm.populationManager->populationlist.v.at(0).score;
			finalSize  = gm.populationManager->populationlist.v.at(0).rpnNodeVec.size();

			CPPUNIT_ASSERT(finalScore <= startScore);
			CPPUNIT_ASSERT(finalSize == startSize);
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).score != 0);
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).rpnNodeVec.size() > 1);
			if(finalScore < startScore) {
				improvement = true;
			} else {
				loops++;
				gm.populationManager->populationlist.v.clear();
				std::cerr << "\t\t\t * Improve Attempt: " <<  loops << std::endl;
			}
		}
	}

	void testScoreRpnVec() {
		std::cerr << "Optimiser:\t\t" <<  __func__ << std::endl;
		gm.fitnessCases->clear();
		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/testSinx"));
		PopulationMember p;
		p.createSelf("TestCase",3);
		CPPUNIT_ASSERT(p.rpnNodeVec.size() > 0);
		gm.populationManager->populationlist.v.clear();
		gm.populationManager->populationlist.add(p);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 1);
		gm.populationManager->scoreOneMember(0);
		double score = gm.populationManager->populationlist.v.at(0).score;
		CPPUNIT_ASSERT(score != 0);
		double newScore = gm.optimiser->scoreRpnVec(p.rpnNodeVec,score);
		CPPUNIT_ASSERT(fabs(score -newScore) < 0.000001);
	}

	void testOptimise() {
		std::cerr << "Optimiser:\t\t" <<  __func__ << std::endl;

		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/medium_test_case"));
		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		PopulationMember p;
		int startSize, finalSize;
		double startScore, finalScore;
		bool improvement = false;
		int loops = 1;
		while(!improvement) {
			p.createSelf("TestCase",3);
			gm.populationManager->populationlist.add(p);
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 1);
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).rpnNodeVec.size() > 0);
			gm.populationManager->scoreOneMember(0);
			startScore = gm.populationManager->populationlist.v.at(0).score;
			startSize  = gm.populationManager->populationlist.v.at(0).rpnNodeVec.size();

			gm.optimiser->optimise(gm.settings->OPTIMISE_CUTTER_EVERY * gm.settings->OPTIMISE_FUNCTIONS_EVERY * gm.settings->OPTIMISE_TERMINALS_EVERY,false);

			finalScore = gm.populationManager->populationlist.v.at(0).score;
			finalSize  = gm.populationManager->populationlist.v.at(0).rpnNodeVec.size();
			CPPUNIT_ASSERT(finalScore <= startScore);
			CPPUNIT_ASSERT(finalSize <= startSize);
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).score != 0);
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).rpnNodeVec.size() > 1);
			if(finalScore < startScore) {
				improvement = true;
			} else {
				loops++;
				gm.populationManager->populationlist.v.clear();
				std::cerr << "\t\t\t * Improve Attempt: " <<  loops << std::endl;
			}
			break;
		}
	}
};


#endif
