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
		suiteOfTests->addTest(new CppUnit::TestCaller<TestArgParser>("Test testLoadArgsCli",&TestArgParser::testLoadArgsCli));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestArgParser>("Test testLoadArgsFail",&TestArgParser::testLoadArgsFail));

		return suiteOfTests;
	}
protected:
	void testDefultConstructor() {
		std::cerr << "ArgParser:\t\t\t" <<  __func__ << std::endl;
		ArgParser argparser;

		CPPUNIT_ASSERT(argparser.numVars == 0);
		CPPUNIT_ASSERT(argparser.isValid());
	}

	void testLoadArgsSolver() {
		std::cerr << "ArgParser:\t\t\t" <<  __func__ << std::endl;
		ArgParser argparser;


		CPPUNIT_ASSERT(false);
	}

	void testLoadArgsCli() {
		std::cerr << "ArgParser:\t\t\t" <<  __func__ << std::endl;

		CPPUNIT_ASSERT(false);
	}

	void testLoadArgsFail() {
		std::cerr << "ArgParser:\t\t\t" <<  __func__ << std::endl;

		CPPUNIT_ASSERT(false);

	}



};


#endif
