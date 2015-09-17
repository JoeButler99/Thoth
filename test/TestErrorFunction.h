/*
 * TestErrorFunction.h
 *
 *  Created on: 17 Sep 2015
 *      Author: joe
 */

#ifndef TEST_TESTERRORFUNCTION_H_
#define TEST_TESTERRORFUNCTION_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>
#include "../src/ErrorFunctions.h"

class TestErrorFunctions : public CppUnit::TestFixture {

public:
	TestErrorFunctions(){}
	virtual ~TestErrorFunctions(){}
	static CppUnit::Test *suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestFunctionSets");

		suiteOfTests->addTest(new CppUnit::TestCaller<TestErrorFunctions>("Test testABS_ERROR", &TestErrorFunctions::testABS_ERROR));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestErrorFunctions>("Test testBuildFunctionSets", &TestErrorFunctions::testERROR_SQUARED));
		return suiteOfTests;
	}
protected:
	void testABS_ERROR() {
		std::cerr << "ErrorFunctions:\t\t" <<  __func__ << std::endl;
		CPPUNIT_ASSERT(ErrorFunction::ABS_ERROR(-10) == 10);
		CPPUNIT_ASSERT(ErrorFunction::ABS_ERROR(-0.5) == 0.5);
		CPPUNIT_ASSERT(ErrorFunction::ABS_ERROR(0.5) == 0.5);

	}

	void testERROR_SQUARED() {
		std::cerr << "ErrorFunctions:\t\t" <<  __func__ << std::endl;
		CPPUNIT_ASSERT(ErrorFunction::ERROR_SQUARED(-10) == 100);
		CPPUNIT_ASSERT(ErrorFunction::ERROR_SQUARED(-0.5) == 0.25);
		CPPUNIT_ASSERT(ErrorFunction::ERROR_SQUARED(0.5) == 0.25);
	}
};



#endif /* TEST_TESTERRORFUNCTION_H_ */
