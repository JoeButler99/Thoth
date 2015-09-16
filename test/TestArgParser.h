/*
 * TestArgParser.h
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

#ifndef TESTARGPARSER_H_
#define TESTARGPARSER_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>
#include "../src/ArgParser.h"

class TestArgParser : public CppUnit::TestFixture {
public:
	TestArgParser(){}
	virtual ~TestArgParser(){}

	static CppUnit::Test *suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestArgParser");

		suiteOfTests->addTest(new CppUnit::TestCaller<TestArgParser>("Test testDefultConstructor",&TestArgParser::testDefultConstructor));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestArgParser>("Test testLoadArgsSolver",&TestArgParser::testLoadArgsSolver));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestArgParser>("Test testLoadArgsFail",&TestArgParser::testLoadArgsFail));

		return suiteOfTests;
	}
protected:
	void testDefultConstructor() {
		std::cerr << "ArgParser:\t\t\t" <<  __func__ << std::endl;
		ArgParser argparser;

		CPPUNIT_ASSERT(argparser.numVars == 0);
		CPPUNIT_ASSERT(argparser.isValid(false) == false); // Fails on no input params
	}

	void testLoadArgsSolver() {
		std::cerr << "ArgParser:\t\t\t" <<  __func__ << std::endl;
		ArgParser argparser;

		// The weird casts are used to create an arrgay live char * argv[] in main
		char* args[] = {(char *)"dummy",
						(char *)"--action",
						(char *)"solve",
						(char *)"--num-vars",
						(char *)"13",
						(char *)"--nodetree",
						(char *)"nodetree.0",
						(char *)"--case-variables",
						(char *)"'0.61 -0.09 4 2 4 3 4 -0.4 1 2 0 2 1'"};
        int argc = 9;
        argparser.loadArgs(argc,args);


        CPPUNIT_ASSERT(argparser.numVars == 13);
        CPPUNIT_ASSERT(argparser.isValid(false));
        CPPUNIT_ASSERT(argparser.action == "solve");
        CPPUNIT_ASSERT(argparser.nodetree == "nodetree.0");
        CPPUNIT_ASSERT(argparser.fitnessCases == "");
        CPPUNIT_ASSERT(argparser.configFile == "conf/config.json");
        CPPUNIT_ASSERT(argparser.caseVars == "'0.61 -0.09 4 2 4 3 4 -0.4 1 2 0 2 1'" );
	}

	void testLoadArgsFail() {
		std::cerr << "ArgParser:\t\t\t" <<  __func__ << std::endl;

		ArgParser argparser;
		// The weird casts are used to create an arrgay live char * argv[] in main
		char* args[] = {(char *)"dummy",
						(char *)"--action",
						(char *)"badaction",
						(char *)"--num-vars",
						(char *)"13",
						(char *)"--nodetree",
						(char *)"nodetree.0",
						(char *)"--case-variables",
						(char *)"'0.61 -0.09 4 2 4 3 4 -0.4 1 2 0 2 1'"};
        int argc = 9;
        argparser.loadArgs(argc,args,false);
        CPPUNIT_ASSERT(argparser.isValid(false) == false);

	}

};


#endif
