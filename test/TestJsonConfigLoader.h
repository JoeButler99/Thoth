
/*
 * TestJsonConfigLoader.h
 *
 *  Created on: 20 Feb 2014
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

#ifndef TESTJSONCONFIGLOADER_H_
#define TESTJSONCONFIGLOADER_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>
#include "../src/JsonConfigLoader.h"
#include "../src/Settings.h"

class TestJsonConfigLoader : public CppUnit::TestFixture {
public:
	TestJsonConfigLoader(){}
	virtual ~TestJsonConfigLoader(){}

	static CppUnit::Test *suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestJsonConfigLoader");

		suiteOfTests->addTest(new CppUnit::TestCaller<TestJsonConfigLoader>("Test testDefultConstructor",&TestJsonConfigLoader::testDefultConstructor));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestJsonConfigLoader>("Test testLoadFile",&TestJsonConfigLoader::testLoadFile));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestJsonConfigLoader>("Test testUpdateSettings",&TestJsonConfigLoader::testUpdateSettings));
		return suiteOfTests;
	}
protected:
	void testDefultConstructor() {
		std::cerr << "JsonConfigLoader:\t" <<  __func__ << std::endl;
		JsonConfigLoader jcl;
		CPPUNIT_ASSERT(jcl.loaded == false);

	}

	void testLoadFile() {
		std::cerr << "JsonConfigLoader:\t" <<  __func__ << std::endl;
		JsonConfigLoader jcl;
		std::string testJsonFile = "conf/unit-test-config.json";

		CPPUNIT_ASSERT(jcl.loaded == false);
		CPPUNIT_ASSERT(jcl.loadFile(testJsonFile));
		CPPUNIT_ASSERT(jcl.loaded);
	}

	void testUpdateSettings() {
		std::cerr << "JsonConfigLoader:\t" <<  __func__ << std::endl;

		Settings settings;

		// Test the default constructor settings

		CPPUNIT_ASSERT(settings.FUNCTION_SET == "Basic");
		CPPUNIT_ASSERT(settings.ERROR_FUNCTION == "ERROR_SQUARED");
		CPPUNIT_ASSERT(settings.POPULATION == 8000);
		CPPUNIT_ASSERT(settings.KEEP_TOP_PERCENT == 25);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(settings.NODE_WEIGHT,1.0,0.001);
		CPPUNIT_ASSERT(settings.GENERATIONS == 4000);
		CPPUNIT_ASSERT(settings.INITIAL_MAX_DEPTH == 3);
		CPPUNIT_ASSERT(settings.USE_CUT_SCORING == true);
		CPPUNIT_ASSERT(settings.EXIT_SCORE == 0);
		CPPUNIT_ASSERT(settings.SAVE_EVERY == 2);
		CPPUNIT_ASSERT(settings.SAVE_TOTAL == 5);
		CPPUNIT_ASSERT(settings.SAVE_FILE_PREFIX == "nodetree");
		CPPUNIT_ASSERT(settings.LOAD_SAVED == true);
		CPPUNIT_ASSERT(settings.LOAD_TOTAL == 5);
		CPPUNIT_ASSERT(settings.SHOW_GUESSES == true);
		CPPUNIT_ASSERT(settings.GUESSES_FILE == "program_guesses");
		CPPUNIT_ASSERT(settings.GUESSES_EVERY == 5);
		CPPUNIT_ASSERT(settings.OPTIMISE_CUTTER_EVERY == 20);
		CPPUNIT_ASSERT(settings.OPTIMISE_TERMINALS_EVERY == 40);
		CPPUNIT_ASSERT(settings.OPTIMISE_FUNCTIONS_EVERY == 30);
		CPPUNIT_ASSERT(settings.ITERATE_CUTTER == false);
		CPPUNIT_ASSERT(settings.ITERATE_TERMINALS == false);
		CPPUNIT_ASSERT(settings.ITERATE_FUNCTIONS == false);
		CPPUNIT_ASSERT(settings.MUTATE_NODE_PERCENT == 5);
		CPPUNIT_ASSERT(settings.MUTATE_TREE_PERCENT == 30);
		CPPUNIT_ASSERT(settings.CUT_TREE_PERCENT == 35);
		CPPUNIT_ASSERT(settings.CROSSOVER_PERCENT == 30);
		CPPUNIT_ASSERT(settings.MUTATE_TREE_MAX_DEPTH == 2);
		CPPUNIT_ASSERT(settings.CROSSOVER_NEW_ROOT_PERCENT == 0);
		CPPUNIT_ASSERT(settings.SHOW_HEADINGS_EVERY == 30);
		CPPUNIT_ASSERT(settings.FITNESS_CASE_FILE == "");

		JsonConfigLoader jcl;
		std::string testJsonFile = "conf/unit-test-config.json";
		CPPUNIT_ASSERT(jcl.loadFile(testJsonFile));
		CPPUNIT_ASSERT(jcl.updateSettings(&settings));

		CPPUNIT_ASSERT(settings.FUNCTION_SET == "FinanceFull");
		CPPUNIT_ASSERT(settings.ERROR_FUNCTION == "ABS_ERROR");
		CPPUNIT_ASSERT(settings.POPULATION == 800);
		CPPUNIT_ASSERT(settings.KEEP_TOP_PERCENT == 25);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(settings.NODE_WEIGHT,0.05,0.001);
		CPPUNIT_ASSERT(settings.GENERATIONS == 200);
		CPPUNIT_ASSERT(settings.INITIAL_MAX_DEPTH == 3);
		CPPUNIT_ASSERT(settings.USE_CUT_SCORING == true);
		CPPUNIT_ASSERT(settings.EXIT_SCORE == 0);
		CPPUNIT_ASSERT(settings.SAVE_EVERY == 2);
		CPPUNIT_ASSERT(settings.SAVE_TOTAL == 5);
		CPPUNIT_ASSERT(settings.SAVE_FILE_PREFIX == "unit-test-nodetree");
		CPPUNIT_ASSERT(settings.LOAD_SAVED == true);
		CPPUNIT_ASSERT(settings.LOAD_TOTAL == 5);
		CPPUNIT_ASSERT(settings.SHOW_GUESSES == true);
		CPPUNIT_ASSERT(settings.GUESSES_FILE == "unit-test-program_guesses");
		CPPUNIT_ASSERT(settings.GUESSES_EVERY == 5);
		CPPUNIT_ASSERT(settings.OPTIMISE_CUTTER_EVERY == 20);
		CPPUNIT_ASSERT(settings.OPTIMISE_TERMINALS_EVERY == 40);
		CPPUNIT_ASSERT(settings.OPTIMISE_FUNCTIONS_EVERY == 30);
		CPPUNIT_ASSERT(settings.ITERATE_CUTTER == false);
		CPPUNIT_ASSERT(settings.ITERATE_TERMINALS == false);
		CPPUNIT_ASSERT(settings.ITERATE_FUNCTIONS == false);
		CPPUNIT_ASSERT(settings.MUTATE_NODE_PERCENT == 5);
		CPPUNIT_ASSERT(settings.MUTATE_TREE_PERCENT == 20);
		CPPUNIT_ASSERT(settings.CUT_TREE_PERCENT == 25);
		CPPUNIT_ASSERT(settings.CROSSOVER_PERCENT == 40);
		CPPUNIT_ASSERT(settings.MUTATE_TREE_MAX_DEPTH == 2);
		CPPUNIT_ASSERT(settings.CROSSOVER_NEW_ROOT_PERCENT == 10);
		CPPUNIT_ASSERT(settings.SHOW_HEADINGS_EVERY == 30);
		CPPUNIT_ASSERT(settings.FITNESS_CASE_FILE == "fitness_cases/testSinx_20c");

	}

};


#endif
