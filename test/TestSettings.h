/*
 * TestSettings.h
 *
 *  Created on: 15 Sep 2015
 *      Author: joe
 */

#ifndef TEST_TESTSETTINGS_H_
#define TEST_TESTSETTINGS_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>
#include "../src/Settings.h"

class TestSettings : public CppUnit::TestFixture {
public:
	TestSettings(){}
	virtual ~TestSettings(){}

	static CppUnit::Test *suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestSettings");

		suiteOfTests->addTest(new CppUnit::TestCaller<TestSettings>("Test testConstructor", &TestSettings::testConstructor));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestSettings>("Test testDisplaySettings", &TestSettings::testDisplaySettings));
		return suiteOfTests;
	}
protected:
	void testConstructor() {
		// Test good options
		Settings settings;

		// Test the default constructor settings
		CPPUNIT_ASSERT(settings.SAVE_FILE_PREFIX == "nodetree");
		CPPUNIT_ASSERT(settings.POPULATION == 8000);
		CPPUNIT_ASSERT(settings.LOAD_SAVED == true);


		// Now just test one item of each type.
		settings.POPULATION = 4000;
		CPPUNIT_ASSERT(settings.POPULATION == 4000);

	}

	void testDisplaySettings() {
		CPPUNIT_ASSERT(false);
	}
};



#endif /* TEST_TESTSETTINGS_H_ */
