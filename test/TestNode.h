/*
 * TestNode.h
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

#ifndef TESTNODE_H_
#define TESTNODE_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>
#include <math.h>
#include "../src/Function.h"
#include "../src/Node.h"
#include "../src/RPNActions.h"

class TestNode : public CppUnit::TestFixture {
public:
	TestNode(){}
	virtual ~TestNode(){}

	static CppUnit::Test *suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestNode");

		suiteOfTests->addTest(new CppUnit::TestCaller<TestNode>("Test testCustomConstructor1",&TestNode::testCustomConstructor1));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestNode>("Test testCustomConstructor2",&TestNode::testCustomConstructor2));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestNode>("Test testCustomConstructor3",&TestNode::testCustomConstructor3));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestNode>("Test SetFromFunc)",&TestNode::testSetFromFunc));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestNode>("Test SetTerminal",&TestNode::testSetTerminal));

		return suiteOfTests;
	}
protected:
	void testCustomConstructor1() {
		std::cerr << "Node:\t\t\t" <<  __func__ << std::endl;
		Function f("Merp",2,10,rpnAdd);
		Node n(f);

		CPPUNIT_ASSERT(n.fInputs ==2);
		CPPUNIT_ASSERT(n.fNo == 10);
		CPPUNIT_ASSERT(n.isTerminal == false);
	}

	void testCustomConstructor2() {
		Node n(5);
		CPPUNIT_ASSERT(n.tNo == 5);
		CPPUNIT_ASSERT(n.isTerminal == true);
	}


	void testCustomConstructor3() {
		Node n(3,true);
		CPPUNIT_ASSERT(n.fNo == -1);
		CPPUNIT_ASSERT(n.isTerminal == false);
		CPPUNIT_ASSERT(n.fInputs == 3);
	}

	void testSetFromFunc() {
		std::cerr << "Node:\t\t\t" <<  __func__ << std::endl;
		Node n(5);
		CPPUNIT_ASSERT(n.tNo == 5);
		CPPUNIT_ASSERT(n.isTerminal == true);
		Function f("Merp",2,10,rpnAdd);
		n.setFromFunc(f);

		CPPUNIT_ASSERT(n.fInputs ==2);
		CPPUNIT_ASSERT(n.fNo == 10);
		CPPUNIT_ASSERT(n.isTerminal == false);

	}

	void testSetTerminal() {
		std::cerr << "Node:\t\t\t" <<  __func__ << std::endl;
		Function f("Merp",2,10,rpnAdd);
		Node n(f);

		CPPUNIT_ASSERT(n.fInputs ==2);
		CPPUNIT_ASSERT(n.fNo == 10);
		CPPUNIT_ASSERT(n.isTerminal == false);

		n.setTerminal(7);
		CPPUNIT_ASSERT(n.tNo == 7);
		CPPUNIT_ASSERT(n.isTerminal == true);
	}
};


#endif
