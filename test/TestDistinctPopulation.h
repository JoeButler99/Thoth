/*
 * TestDistinctPopulation.h
 *
 *  Created on: 26 Sept 2015
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

#ifndef TESTDISTINCTPOPULATION_H_
#define TESTDISTINCTPOPULATION_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>
#include "../src/JsonConfigLoader.h"


class TestDistinctPopulation : public CppUnit::TestFixture {
public:
	TestDistinctPopulation(){}
	virtual ~TestDistinctPopulation(){}

	static CppUnit::Test *suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestDistinctPopulation");

		suiteOfTests->addTest(new CppUnit::TestCaller<TestDistinctPopulation>("Test testDistinctPopulationConfig",&TestDistinctPopulation::testDistinctPopulationConfig));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestDistinctPopulation>("Test testDistinctPopulationLargePopulation",&TestDistinctPopulation::testDistinctPopulationLargePopulation));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestDistinctPopulation>("Test testDistinctPopulationNodeEquality",&TestDistinctPopulation::testDistinctPopulationNodeEquality));
                suiteOfTests->addTest(new CppUnit::TestCaller<TestDistinctPopulation>("Test testDistinctPopulationVectorLengths",&TestDistinctPopulation::testDistinctPopulationVectorLengths));
                suiteOfTests->addTest(new CppUnit::TestCaller<TestDistinctPopulation>("Test testDistinctPopulationPopulationManger",&TestDistinctPopulation::testDistinctPopulationPopulationManger));
                suiteOfTests->addTest(new CppUnit::TestCaller<TestDistinctPopulation>("Test testDistinctPopulationConsoleOutput",&TestDistinctPopulation::testDistinctPopulationConsoleOutput));
                suiteOfTests->addTest(new CppUnit::TestCaller<TestDistinctPopulation>("Test testDistinctPopulationUniqueFromProgramStart",&TestDistinctPopulation::testDistinctPopulationUniqueFromProgramStart));
                suiteOfTests->addTest(new CppUnit::TestCaller<TestDistinctPopulation>("Test testDistinctPopulationEvolutionManager",&TestDistinctPopulation::testDistinctPopulationEvolutionManager));
                suiteOfTests->addTest(new CppUnit::TestCaller<TestDistinctPopulation>("Test testDistinctPopulationRuntimeException",&TestDistinctPopulation::testDistinctPopulationRuntimeException));
                //suiteOfTests->addTest(new CppUnit::TestCaller<TestDistinctPopulation>("Test testLoadA",&TestDistinctPopulation::testLoadA));
                //suiteOfTests->addTest(new CppUnit::TestCaller<TestDistinctPopulation>("Test testLoad",&TestDistinctPopulation::testLoad));
		return suiteOfTests;
	}
protected:
	void testDistinctPopulationConfig() {
		std::cerr << "DistinctPopulation:\t" <<  __func__ << std::endl;
		Settings settings;
		JsonConfigLoader jcl;
		std::string testJsonFile = "conf/unit-test-config.json";

		jcl.loadFile(testJsonFile);
		CPPUNIT_ASSERT(jcl.loaded);
		CPPUNIT_ASSERT(jcl.updateSettings(&settings));
		CPPUNIT_ASSERT(settings.DISCARD_DUPLICATES == false);
		CPPUNIT_ASSERT(settings.MAX_DUPLICATE_RETRIES == 0);

		CPPUNIT_ASSERT(false);
	}

	void testDistinctPopulationLargePopulation() {
		std::cerr << "DistinctPopulation:\t" <<  __func__ << std::endl;
		CPPUNIT_ASSERT(false);
	}

	void testDistinctPopulationNodeEquality() {
		std::cerr << "DistinctPopulation:\t\t" <<  __func__ << std::endl;
                CPPUNIT_ASSERT(false);
	}

    void testDistinctPopulationVectorLengths() {
		std::cerr << "DistinctPopulation:\t\t" <<  __func__ << std::endl;
                CPPUNIT_ASSERT(false);
	}

	void testDistinctPopulationPopulationManger() {
		std::cerr << "DistinctPopulation:\t\t" <<  __func__ << std::endl;
                CPPUNIT_ASSERT(false);
	}

	void testDistinctPopulationConsoleOutput() {
		std::cerr << "DistinctPopulation:\t\t" <<  __func__ << std::endl;
                CPPUNIT_ASSERT(false);
	}

	void testDistinctPopulationUniqueFromProgramStart() {
		std::cerr << "DistinctPopulation:\t\t" <<  __func__ << std::endl;
                CPPUNIT_ASSERT(false);
	}

	void testDistinctPopulationEvolutionManager() {
		std::cerr << "DistinctPopulation:\t\t" <<  __func__ << std::endl;
                CPPUNIT_ASSERT(false);
	}

	void testDistinctPopulationRuntimeException() {
		std::cerr << "DistinctPopulation:\t\t" <<  __func__ << std::endl;
                CPPUNIT_ASSERT(false);
	}

//	void testLoadA() {
//		std::cerr << "DistinctPopulation:\t\t" <<  __func__ << std::endl;
//                CPPUNIT_ASSERT(false);
//	}
//
//	void testLoad() {
//		std::cerr << "DistinctPopulation:\t\t" <<  __func__ << std::endl;
//                CPPUNIT_ASSERT(false);
//	}

};


#endif
