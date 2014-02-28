
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

class TestJsonConfigLoader : public CppUnit::TestFixture {
public:
	TestJsonConfigLoader(){}
	virtual ~TestJsonConfigLoader(){}

	static CppUnit::Test *suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestJsonConfigLoader");

		suiteOfTests->addTest(new CppUnit::TestCaller<TestJsonConfigLoader>("Test testDefultConstructor",&TestJsonConfigLoader::testDefultConstructor));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestJsonConfigLoader>("Test testLoadArgsSolver",&TestJsonConfigLoader::testLoadFile));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestJsonConfigLoader>("Test testLoadArgsCli",&TestJsonConfigLoader::testUpdateSettings));
		return suiteOfTests;
	}
protected:
	void testDefultConstructor() {
		std::cerr << "JsonConfigLoader:\t\t\t" <<  __func__ << std::endl;

		CPPUNIT_ASSERT(false);
	}

	void testLoadFile() {
		std::cerr << "JsonConfigLoader:\t\t\t" <<  __func__ << std::endl;

		CPPUNIT_ASSERT(false);
	}

	void testUpdateSettings() {
		std::cerr << "JsonConfigLoader:\t\t\t" <<  __func__ << std::endl;

		CPPUNIT_ASSERT(false);
	}

};


#endif
