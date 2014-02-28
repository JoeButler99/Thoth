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

#ifndef TESTRNG_H_
#define TESTRNG_H_


#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>
#include "../src/RNG.h"

extern RNG rng;

class TestRNG : public CppUnit::TestFixture {
public:
	TestRNG(){}
	virtual ~TestRNG(){}

	static CppUnit::Test *suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestRNG");
		suiteOfTests->addTest(new CppUnit::TestCaller<TestRNG>("Test default constructor",&TestRNG::testDefaultConstructor));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestRNG>("Test default constructor",&TestRNG::testCustomConstructor));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestRNG>("Test default constructor",&TestRNG::testFRand));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestRNG>("Test default constructor",&TestRNG::testDRand));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestRNG>("Test default constructor",&TestRNG::testBRand));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestRNG>("Test Int generator",&TestRNG::testIRand));


		return suiteOfTests;
	}
protected:
	void testDefaultConstructor() {
		std::cerr << "RNG:\t\t\t" <<  __func__ << std::endl;
		CPPUNIT_ASSERT(rng.dMin == 0);
		CPPUNIT_ASSERT(rng.dMax == 1000000);
		//CPPUNIT_ASSERT(rng.e)

	};
	void testCustomConstructor() {
		RNG newRNG(-5.0,3.0);
		std::cerr << "RNG:\t\t\t" <<  __func__ << std::endl;
		CPPUNIT_ASSERT(newRNG.dMin == -5.0);
		CPPUNIT_ASSERT(newRNG.dMax == 3.0);
		double testVal = newRNG.dRand();
		CPPUNIT_ASSERT( (testVal >= -5.0 && testVal <= 3.0 ));

	};

	void testBRand() {
		std::cerr << "RNG:\t\t\t" <<  __func__ << std::endl;
		int trues = 0;
		int falses = 0;
		// Here we just generate loads and check we got some of each
		for (int x = 0; x < 50; ++x) {
			if(rng.bRand()) {
				trues ++;
			} else {
				falses ++;
			}
		}
		CPPUNIT_ASSERT( trues > 0 );
		CPPUNIT_ASSERT( falses > 0 );

	}

	void testFRand() {
		std::cerr << "RNG:\t\t\t" <<  __func__ << std::endl;

		int testVal;
		int x = 0;
		while (x < 50) {
			testVal = rng.iRand(0,20);
			CPPUNIT_ASSERT( (testVal >= 0 && testVal < 20 ));

			testVal = rng.iRand(0,30);
			CPPUNIT_ASSERT( (testVal >= 0 && testVal < 30 ));

			testVal = rng.iRand(0,5);
			CPPUNIT_ASSERT( (testVal >= 0 && testVal < 5 ));
			x++;
		}
	};

	void testDRand() {
		std::cerr << "RNG:\t\t\t" <<  __func__ << std::endl;
		double testVal = rng.dRand(-1,1);
		CPPUNIT_ASSERT( (testVal >= -1 && testVal <= 1 ));

		testVal = rng.dRand(-1,1);
		CPPUNIT_ASSERT( (testVal >= -1 && testVal <= 1 ));

		testVal = rng.dRand(-1,1);
		CPPUNIT_ASSERT( (testVal >= -1 && testVal <= 1 ));

		testVal = rng.dRand(-1,1);
		CPPUNIT_ASSERT( (testVal >= -1 && testVal <= 1 ));

		testVal = rng.dRand(3,5);
		CPPUNIT_ASSERT( (testVal >= 3 && testVal <= 5 ));

		testVal = rng.dRand(3,5);
		CPPUNIT_ASSERT( (testVal >= 3 && testVal <= 5 ));

		testVal = rng.dRand(3,5);
		CPPUNIT_ASSERT( (testVal >= 3 && testVal <= 5 ));

		testVal = rng.dRand(3,5);
		CPPUNIT_ASSERT( (testVal >= 3 && testVal <= 5 ));

		testVal = rng.dRand(3,5);
		CPPUNIT_ASSERT( (testVal >= 3 && testVal <= 5 ));

	};


	void testIRand() {
		std::cerr << "RNG:\t\t\t" <<  __func__ << std::endl;
		int value;
		for (int x = 0; x < 50; ++x) {
			value = rng.iRand();
			CPPUNIT_ASSERT(value >= 0);
		}

		for (int x = 0; x < 50; ++x) {
			value = rng.iRand(20);
			CPPUNIT_ASSERT(value >= 0 && value < 20);
		}

		for (int x = 0; x < 50; ++x) {
			value = rng.iRand(5,20);
			CPPUNIT_ASSERT(value >= 5 && value < 20);
		}
	}
};


#endif /* TESTRNG_H_ */

