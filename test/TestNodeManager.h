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

#ifndef TESTNODEMANAGER_H_
#define TESTNODEMANAGER_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>
#include <math.h>
#include "../src/Function.h"
#include "../src/Node.h"
#include "../src/NodeManager.h"


class TestNodeManager : public CppUnit::TestFixture {
public:
	TestNodeManager(){}
	virtual ~TestNodeManager(){}

	static CppUnit::Test *suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestNodeManager");

		suiteOfTests->addTest(new CppUnit::TestCaller<TestNodeManager>("Test Default Constructor",&TestNodeManager::testDefaultConstructor));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestNodeManager>("Test SetupSelf",&TestNodeManager::testSetupSelf));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestNodeManager>("Test InitFunctions",&TestNodeManager::testInitFunctions));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestNodeManager>("Test GiveRandFunctionVoid",&TestNodeManager::testGiveRandFunctionVoid));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestNodeManager>("Test GiveRandFunctionInt",&TestNodeManager::testGiveRandFunctionInt));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestNodeManager>("Test GetFunctionByNum",&TestNodeManager::testGetFunctionByNum));

		return suiteOfTests;
	}
protected:
	void testDefaultConstructor() {
		std::cerr << "NodeManager:\t\t" <<  __func__ << std::endl;
		NodeManager nm;
		CPPUNIT_ASSERT(nm.functionlist.size() == 0);
	}

	void testSetupSelf() {
		std::cerr << "NodeManager:\t\t" <<  __func__ << std::endl;
		NodeManager nm;
		CPPUNIT_ASSERT(nm.functionlist.size() == 0);
		nm.setupSelf();
		CPPUNIT_ASSERT(nm.functionlist.size() > 0);
	}

	void testInitFunctions() {
		std::cerr << "NodeManager:\t\t" <<  __func__ << std::endl;
		NodeManager nm;
		CPPUNIT_ASSERT(nm.functionlist.size() == 0);
		nm.initFunctions();
		CPPUNIT_ASSERT(nm.functionlist.size() > 0);
	}


	void testGiveRandFunctionVoid() {
		std::cerr << "NodeManager:\t\t" <<  __func__ << std::endl;
		NodeManager nm;
		CPPUNIT_ASSERT(nm.functionlist.size() == 0);
		nm.setupSelf();

		Function & f = nm.giveRandFunction();
		CPPUNIT_ASSERT(f._inputs != 0);

	}

	void testGiveRandFunctionInt() {
		std::cerr << "NodeManager:\t\t" <<  __func__ << std::endl;
		NodeManager nm;
		CPPUNIT_ASSERT(nm.functionlist.size() == 0);
		nm.setupSelf();

		Function & f = nm.giveRandFunction(2);
		CPPUNIT_ASSERT(f._inputs == 2);

		f = nm.giveRandFunction(1);
		CPPUNIT_ASSERT(f._inputs == 1);

		f = nm.giveRandFunction(4);
		CPPUNIT_ASSERT(f._inputs == 4);

	}

	void testGetFunctionByNum() {
		std::cerr << "NodeManager:\t\t" <<  __func__ << std::endl;
		NodeManager nm;
		CPPUNIT_ASSERT(nm.functionlist.size() == 0);
		nm.setupSelf();

		Function & f = nm.getFunctionByNum(3);
		CPPUNIT_ASSERT(f._inputs == 2);
		CPPUNIT_ASSERT(f._name == "Divide");

		f = nm.getFunctionByNum(4);
		CPPUNIT_ASSERT(f._inputs == 1);
		CPPUNIT_ASSERT(f._name == "Square");

		f = nm.getFunctionByNum(12);
		CPPUNIT_ASSERT(f._inputs == 4);
		CPPUNIT_ASSERT(f._name == "Min 4");
	}
};


#endif
