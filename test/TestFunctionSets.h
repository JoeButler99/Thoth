/*
 * TestFunctionSets.h
 *
 *  Created on: 16 Sep 2015
 *      Author: joe
 */

#ifndef TEST_TESTFUNCTIONSETS_H_
#define TEST_TESTFUNCTIONSETS_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>
#include "../src/FunctionSet.h"


class TestFunctionSets : public CppUnit::TestFixture {
public:
	TestFunctionSets(){}
	virtual ~TestFunctionSets(){}

	static CppUnit::Test *suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestFunctionSets");

		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunctionSets>("Test testConstructor", &TestFunctionSets::testConstructor));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunctionSets>("Test testBuildFunctionSets", &TestFunctionSets::testBuildFunctionSets));
		return suiteOfTests;
	}
protected:
	void testConstructor() {
		std::cerr << "Settings:\t\t" <<  __func__ << std::endl;
		CPPUNIT_ASSERT(false);
	}

	void testBuildFunctionSets() {
		std::cerr << "Settings:\t\t" <<  __func__ << std::endl;
		CPPUNIT_ASSERT(false);
	}
};



#endif /* TEST_TESTFUNCTIONSETS_H_ */
