/*
 * TestFunction.h
 *
 *  Created on: 25 Nov 2013
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

/*
 * TestRNG.h
 *
 *  Created on: 26 Aug 2013
 *      Author: joe
 */

#ifndef TESTFUNCTION_H_
#define TESTFUNCTION_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>
#include <math.h>
#include "../src/Function.h"

class TestFunction : public CppUnit::TestFixture {
public:
	TestFunction() : stackLevel(0) {}
	virtual ~TestFunction(){}
	int stackLevel;
	double rpnStack[RPN_STACK_LIMIT];

	void setUp() {
		stackLevel = 0;
		rpnStack = {0};

	}

	static CppUnit::Test *suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestFunction");

		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test custom constructor",&TestFunction::testCustomConstructor));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test DisplaySelf",&TestFunction::testDisplaySelf));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test Action",&TestFunction::testAction));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test Fadd",&TestFunction::testFadd));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test Fsubtract",&TestFunction::testFsubtract));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test Fmultiply",&TestFunction::testFmultiply));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test Fdivide",&TestFunction::testFdivide));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test Fpercentme",&TestFunction::testFpercentme));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test Funpercentme",&TestFunction::testFunpercentme));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test Fsquared",&TestFunction::testFsquared));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test FPC_change",&TestFunction::testFPC_change));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test FPC_of",&TestFunction::testFPC_of));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test FAVG_2",&TestFunction::testFAVG_2));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test Fmin_2",&TestFunction::testFmin_2));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test Fmax_2",&TestFunction::testFmax_2));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test FAVG_4",&TestFunction::testFAVG_4));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test Fmin_4",&TestFunction::testFmin_4));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test Fmax_4",&TestFunction::testFmax_4));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test FInt_Me",&TestFunction::testFInt_Me));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test Fsquare_rt",&TestFunction::testFsquare_rt));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test Fif_4_1",&TestFunction::testFif_4_1));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test Fif_4_2",&TestFunction::testFif_4_2));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test Fsum",&TestFunction::testFSum));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test FAbsSum2",&TestFunction::testFAbsSum2));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test FAbsSum4",&TestFunction::testFAbsSum4));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test FAbsMax2",&TestFunction::testFAbsMax2));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test FAbsMax4",&TestFunction::testFAbsMax4));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test FlipDouble",&TestFunction::testFlipDouble));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test FRaiseE",&TestFunction::testFRaiseE));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestFunction>("Test FLnE",&TestFunction::testFLnE));


		return suiteOfTests;
	}
protected:
	void setStack(double * vars,)


	 void testCustomConstructor() {
		std::cerr << "Function:\t\t" <<  __func__ << std::endl;
		Function f("Fadd",2,0,rpnAdd);
		CPPUNIT_ASSERT(f.name == "Fadd");
		CPPUNIT_ASSERT(f.inputs == 2);
		CPPUNIT_ASSERT(f.mynum == 0);
	 }

	 void testDisplaySelf() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
		Function f("Fadd",2,0,rpnAdd);
		CPPUNIT_ASSERT(f.name == "Fadd");
		CPPUNIT_ASSERT(f.inputs == 2);
		CPPUNIT_ASSERT(f.mynum == 0);
		CPPUNIT_ASSERT(f.displaySelf() == "Fadd");
	 }


	 void testAction() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("Fadd",2,0,rpnAdd);
	 	CPPUNIT_ASSERT(f.action(10,20) == 30);
	 }

	 void testFadd() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
		Function f("Fadd",2,0,rpnAdd);
		CPPUNIT_ASSERT(fabs(f.action(10,12) - 22 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-10,12) - 2 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,0) - -0.5 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,-80) - -80.5 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(0.1,0.1) - 0.2 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.1,-0.1) - -0.2 ) < 0.000001);
	 }

	 void testFsubtract() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
		Function f("Fsubtract",2,1,rpnSubtract);
		CPPUNIT_ASSERT(fabs(f.action(10,12) - -2 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-10,12) - -22 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,0) - -0.5 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,-80) - 79.5) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(0.1,0.1) - 0 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.1,-0.1) - 0 ) < 0.000001);
	 }

	 void testFmultiply() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("Fmultiply",2,2,rpnMultiply);
	 	CPPUNIT_ASSERT(fabs(f.action(10,12) - 120 ) < 0.000001);
	 	CPPUNIT_ASSERT(fabs(f.action(-10,12) - -120 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,0) - 0 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,-80) - 40 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(0.1,0.1) - 0.01 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.1,-0.1) - 0.01 ) < 0.000001);
	 }

	 void testFdivide() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("Fdivide",2,3,rpnDivide);
		CPPUNIT_ASSERT(fabs(f.action(10,12) - 0.83333333 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-10,12) - -0.833333333 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,0) - -0.5 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,-80) - 0.00625 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(0.1,0.1) -1 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.1,-0.1) -1 ) < 0.000001);

	 }

	 void testFpercentme() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
		Function f("Fpercentme",2,3,rpnPercentMe);
		CPPUNIT_ASSERT(fabs(f.Fpercentme(20) - 0.2 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fpercentme(0.01) - 0.0001 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fpercentme(-0.01) - -0.0001 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fpercentme(-20) - -0.2 ) < 0.000001);

	 }

	 void testFunpercentme() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
		Function f("Funpercentme",2,3,rpnUnPercentMe);
		CPPUNIT_ASSERT(fabs(f.Funpercentme(20) - 2000 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Funpercentme(0.01) - 1 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Funpercentme(-0.01) - -1 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Funpercentme(-20) - -2000 ) < 0.000001);

	 }

	 void testFsquared() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("Fpercentme",2,3,rpnSquare);
		CPPUNIT_ASSERT(fabs(f.Fsquared(20) - 400 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fsquared(0.01) - 0.0001 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fsquared(-0.01) - 0.0001 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fsquared(-20) - 400 ) < 0.000001);
	 }

	 void testFPC_change() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("FPC_change",2,6,rpnPercentChange);
		CPPUNIT_ASSERT(fabs(f.action(10,12) - 20 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-10,12) - -220 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,0) - -100 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,-80) - 15900 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(0.1,0.1) - 0 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.1,-0.1) - 0 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(0,0.1)) < 0.000001);
	 }

	 void testFPC_of() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("FPC_of",2,7,rpnPercentOf);
		CPPUNIT_ASSERT(fabs(f.action(10,12) - 83.33333333 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-10,12) - -83.33333333 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,0) - -0.5 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,-80) - 0.625 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(0.1,0.1) - 100 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.1,-0.1) - 100 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(0,0.1)) < 0.0000001);
	 }

	 void testFAVG_2() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("AVG 2",2,8,rpnAvgOf2);
		CPPUNIT_ASSERT(fabs(f.action(10,12) - 11 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-10,12) - 1 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,0) - -0.25 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,-80) - -40.25 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(0.1,0.1) - 0.1 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.1,-0.1) - -0.1 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(0,0.1) - 0.05) < 0.000001);
	 }

	 void testFmin_2() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("min 2",2,9,rpnMinOf2);
		CPPUNIT_ASSERT(fabs(f.action(10,12) - 10 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-10,12) - -10 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,0) - -0.5 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,-80) - -80 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(0.1,0.1) - 0.1 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.1,-0.1) - -0.1 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(0,0.1) - 0) < 0.000001);
	 }

	 void testFmax_2() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("max 2",2,10,rpnMaxOf2);
		CPPUNIT_ASSERT(fabs(f.action(10,12) - 12 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-10,12) - 12 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,0) - -0 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,-80) - -0.5 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(0.1,0.1) - 0.1 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.1,-0.1) - -0.1 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(0,0.1) - 0.1) < 0.000001);
	 }

	 void testFAVG_4() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("max 2",2,10,rpnAvgOf4);
		CPPUNIT_ASSERT(fabs(f.FAVG_4(0,1,2,3) - 1.5) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.FAVG_4(10,-3,0,-7) - 0) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.FAVG_4(20,-30,10,-10) - -2.5) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.FAVG_4(0.2,0.7,0.4,1.6) - 0.725) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.FAVG_4(0.2,-0.7,0.4,-1.6) - -0.425) < 0.000001);
	 }

	 void testFmin_4() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("max 2",2,10,rpnMinOf4);
		CPPUNIT_ASSERT(fabs(f.Fmin_4(0,1,2,3) - 0) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fmin_4(10,-3,0,-7) - -7) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fmin_4(20,-30,10,-10) - -30) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fmin_4(0.2,0.7,0.4,1.6) - 0.2) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fmin_4(0.2,-0.7,0.4,-1.6) - -1.6) < 0.000001);
	 }

	 void testFmax_4() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("max 2",2,10,rpnMaxOf4);
		CPPUNIT_ASSERT(fabs(f.Fmax_4(0,1,2,3) - 3) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fmax_4(10,-3,0,-7) - 10) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fmax_4(20,-30,10,-10) - 20) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fmax_4(0.2,0.7,0.4,1.6) - 1.6) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fmax_4(0.2,-0.7,0.4,-1.6) - 0.4) < 0.000001);
	 }

	 void testFInt_Me() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("max 2",2,10,rpnToInt);
	 	CPPUNIT_ASSERT(fabs(f.FInt_Me(0) - 0) < 0.000001);
	 	CPPUNIT_ASSERT(fabs(f.FInt_Me(0.6) - 1) < 0.000001);
	 	CPPUNIT_ASSERT(fabs(f.FInt_Me(-0.7) - -1) < 0.000001);
	 	CPPUNIT_ASSERT(fabs(f.FInt_Me(-10) - -10) < 0.000001);
	 	CPPUNIT_ASSERT(fabs(f.FInt_Me(27) - 27) < 0.000001);
	 }

	 void testFsquare_rt() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("max 2",2,10,rpnSquareRoot);
	 	CPPUNIT_ASSERT(fabs(f.Fsquare_rt(0) - 0) < 0.000001);
	 	CPPUNIT_ASSERT(fabs(f.Fsquare_rt(0.6) - 0.7745966692) < 0.000001);
	 	CPPUNIT_ASSERT(fabs(f.Fsquare_rt(-0.7) - 0.8366600265) < 0.000001);
	 	CPPUNIT_ASSERT(fabs(f.Fsquare_rt(-10) - 3.16227766) < 0.000001);
	 	CPPUNIT_ASSERT(fabs(f.Fsquare_rt(27) - 5.196152433) < 0.000001);
	 }

	 void testFif_4_1() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("max 2",2,10,rpnIfV1);
		CPPUNIT_ASSERT(fabs(f.Fif_4_1(0,1,2,3) - 3) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fif_4_1(10,-3,0,-7) - 0) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fif_4_1(20,-30,10,-10) - 10) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fif_4_1(0.2,0.7,0.4,1.6) - 1.6) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fif_4_1(0.2,-0.7,0.4,-1.6) - 0.4) < 0.000001);
	 }

	 void testFif_4_2() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("max 2",2,10,rpnIfV2);
		CPPUNIT_ASSERT(fabs(f.Fif_4_2(0,1,2,3) - 1) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fif_4_2(10,-3,0,-7) - -7) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fif_4_2(20,-30,10,-10) - -10) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fif_4_2(0.2,0.7,0.4,1.6) - 0.7) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.Fif_4_2(0.2,-0.7,0.4,-1.6) - -0.7) < 0.000001);
	 }

	 void testFSum() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("max 2",2,10,rpnSum4);
		CPPUNIT_ASSERT(fabs(f.FSum(0,1,2,3) - 6) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.FSum(10,-3,0,-7) - 0) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.FSum(20,-30,10,-10) - -10) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.FSum(0.2,0.7,0.4,1.6) - 2.9) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.FSum(0.2,-0.7,0.4,-1.6) - -1.7) < 0.000001);
	 }

	 void testFAbsSum2() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("max 2",2,20,rpnAbsSum2);
		CPPUNIT_ASSERT(fabs(f.action(10,12) - 22 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-10,12) - 22 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,0) - 0.5 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,-80) - 80.5 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(0.1,0.1) - 0.2 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.1,-0.1) - 0.2 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(0,0.1) - 0.1) < 0.000001);
	 }

	 void testFAbsSum4() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("max 2",2,10,rpnAbsSum4);
		CPPUNIT_ASSERT(fabs(f.FAbsSum4(0,1,2,3) - 6) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.FAbsSum4(10,-3,0,-7) - 20) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.FAbsSum4(20,-30,10,-10) - 70) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.FAbsSum4(0.2,0.7,0.4,1.6) - 2.9) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.FAbsSum4(0.2,-0.7,0.4,-1.6) - 2.9) < 0.000001);
	 }

	 void testFAbsMax2() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("max 2",2,22,rpnAbsMax2);
		CPPUNIT_ASSERT(fabs(f.action(10,12) - 12 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-10,12) - 12 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,0) - 0.5 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.5,-80) - 80 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(0.1,0.1) - 0.1 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(-0.1,-0.1) - 0.1 ) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.action(0,0.1) - 0.1) < 0.000001);
	 }

	 void testFAbsMax4() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("max 2",2,22,rpnAbsMax4);
		CPPUNIT_ASSERT(fabs(f.FAbsMax4(0,1,2,3) - 3) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.FAbsMax4(10,-3,0,-7) - 10) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.FAbsMax4(20,-30,10,-10) - 30) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.FAbsMax4(0.2,0.7,0.4,1.6) - 1.6) < 0.000001);
		CPPUNIT_ASSERT(fabs(f.FAbsMax4(0.2,-0.7,0.4,-1.6) - 1.6) < 0.000001);
	 }

	 void testFlipDouble() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("max 2",2,22,rpnNegate);
	 	CPPUNIT_ASSERT(fabs(f.FlipDouble(0) - 0) < 0.000001);
	 	CPPUNIT_ASSERT(fabs(f.FlipDouble(0.6) - -0.6) < 0.000001);
	 	CPPUNIT_ASSERT(fabs(f.FlipDouble(-0.7) - .7) < 0.000001);
	 	CPPUNIT_ASSERT(fabs(f.FlipDouble(-10) - 10) < 0.000001);
	 	CPPUNIT_ASSERT(fabs(f.FlipDouble(27) - -27) < 0.000001);
	 }

	 void testFRaiseE() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("max 2",2,22,rpnRaiseE);
	 	CPPUNIT_ASSERT(fabs(f.FRaiseE(0) - 0) < 0.000001);
	 	CPPUNIT_ASSERT(fabs(f.FRaiseE(0.6) - 0.2494322333) < 0.000001);
	 	CPPUNIT_ASSERT(fabs(f.FRaiseE(-0.7) - -0.379256312) < 0.000001);
	 	CPPUNIT_ASSERT(fabs(f.FRaiseE(-10) - -522.73529967) < 0.000001);
	 	CPPUNIT_ASSERT(fabs(f.FRaiseE(27) - 7777.680702) < 0.000001);
	 }

	 void testFLnE() {
	 	std::cerr << "Function:\t\t" <<  __func__ << std::endl;
	 	Function f("max 2",2,22,rpnLnE);
	 	CPPUNIT_ASSERT(fabs(f.FLnE(0) - 0) < 0.000001);
	 	CPPUNIT_ASSERT(fabs(f.FLnE(0.6) - -0.510825624) < 0.000001);
	 	CPPUNIT_ASSERT(fabs(f.FLnE(-0.7) - 0.356675) < 0.000001);
	 	CPPUNIT_ASSERT(fabs(f.FLnE(-10) - -2.302585093) < 0.000001);
	 	CPPUNIT_ASSERT(fabs(f.FLnE(27) - 3.295836866) < 0.000001);
	 }

};


#endif
