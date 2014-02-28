/*
 * Function.h
 *
 *  Created on: 3 May 2013
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

#ifndef FUNCTION_H_
#define FUNCTION_H_
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>		// abs math function
#include "Globals.h"



class Function {
public:
	std::string _name;
	unsigned int _inputs, _mynum;
	Function(const std::string & n, int i, int mynum);
	//~Function();
	std::string displaySelf();
	double action (double aa , double bb = 0.0, double cc = 0.0, double dd = 0.0);
	double Fadd(double a, double b);
	double Fsubtract(double a, double b);
	double Fmultiply(double a, double b);
	double Fdivide(double a, double b);
	double Fpercentme(double a);
	double Funpercentme(double a);
	double Fsquared(double a);
	double FPC_change(double a, double b);
	double FPC_of(double a, double b);
	double FAVG_2(double a, double b);
	double Fmin_2(double a, double b);
	double Fmax_2(double a, double b);
	double FAVG_4(double a, double b,double c, double d);
	double Fmin_4(double a, double b,double c, double d);
	double Fmax_4(double a, double b,double c, double d);
	double FInt_Me(double a) ;
	double Fsquare_rt(double a) ;
	double Fif_4_1(double a,double b,double c,double d);
	double Fif_4_2(double a,double b,double c,double d);
	double FSum(double a,double b,double c,double d);
	double FAbsSum2(double a, double b);
	double FAbsSum4(double a,double b,double c,double d);
	double FAbsMax2(double a, double b);
	double FAbsMax4(double a,double b,double c,double d);
	double FlipDouble(double a);
	double FRaiseE(double a);
	double FLnE(double a);

};

#endif /* FUNCTION_H_ */
