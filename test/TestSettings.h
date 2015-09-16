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
		//suiteOfTests->addTest(new CppUnit::TestCaller<TestSettings>("Test testDisplaySettings", &TestSettings::testDisplaySettings));
		return suiteOfTests;
	}
protected:
	void testConstructor() {
		std::cerr << "Settings:\t\t" <<  __func__ << std::endl;
		// Test good options
		Settings settings;

		// Test the default constructor settings
		CPPUNIT_ASSERT(settings.SAVE_FILE_PREFIX == "nodetree");
		CPPUNIT_ASSERT(settings.POPULATION == 8000);
		CPPUNIT_ASSERT(settings.LOAD_SAVED == true);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(settings.NODE_WEIGHT,1.0,0.001);


		// Now just test one item of each type.
		// This is actually tested fully in TestJsonConfigLoader.h
		settings.SAVE_FILE_PREFIX = "test";
		settings.POPULATION = 4000;
		settings.LOAD_SAVED = false;
		settings.NODE_WEIGHT = 0.76;

		CPPUNIT_ASSERT(settings.SAVE_FILE_PREFIX == "test");
		CPPUNIT_ASSERT(settings.POPULATION == 4000);
		CPPUNIT_ASSERT(settings.LOAD_SAVED == false);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(settings.NODE_WEIGHT,0.76,0.001);

	}

	void testDisplaySettings() {
		// TODO - This just dumps class properties to the terminal. Might be a better way of doing that
		// If so then test it.
	}
};



#endif /* TEST_TESTSETTINGS_H_ */
