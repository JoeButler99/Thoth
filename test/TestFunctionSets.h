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
		std::cerr << "FunctionSets:\t\t" <<  __func__ << std::endl;
		std::string name("TestFunctionSet");

		FunctionSet::functionSets.clear();
		FunctionSet fs(name);
		CPPUNIT_ASSERT(fs.name == "TestFunctionSet");
		CPPUNIT_ASSERT(fs.functionList.size() == 0);
		CPPUNIT_ASSERT(FunctionSet::functionSets.size() == 0);
	}

	void testBuildFunctionSets() {
		std::cerr << "FunctionSets:\t\t" <<  __func__ << std::endl;
		std::string name("TestFunctionSet");
		FunctionSet::functionSets.clear();
		FunctionSet fs(name);
		CPPUNIT_ASSERT(fs.name == "TestFunctionSet");
		CPPUNIT_ASSERT(fs.functionList.size() == 0);
		CPPUNIT_ASSERT(FunctionSet::functionSets.size() == 0);

		FunctionSet::buildFunctionSets();
		CPPUNIT_ASSERT(FunctionSet::functionSets.size() > 0);
		CPPUNIT_ASSERT(FunctionSet::functionSets.at(0).name == "Basic");
		CPPUNIT_ASSERT(FunctionSet::functionSets.at(0).functionList.size() == 4);
	}
};



#endif /* TEST_TESTFUNCTIONSETS_H_ */
