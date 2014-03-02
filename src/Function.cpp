/*
 * Function.cpp
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

#include "Function.h"

Function::Function(const std::string & n, int i, int num,rpn_action_ptr a)
: name(n), inputs(i), mynum(num), action(a) {}

std::string Function::displaySelf(){
	return name;
}


//// Load the function based on the
//double Function::action (double aa , double bb, double cc , double dd ) {
//	//http://stackoverflow.com/questions/4842952/code-optimization-switch-versus-ifs
//
//	switch (_mynum) {
//	case 0 :
//		return Fadd(aa,bb);
//		break;
//	case 1 :
//		return Fsubtract(aa,bb);
//		break;
//	case 2 :
//		return Fmultiply(aa,bb);
//		break;
//	case 3 :
//		return Fdivide(aa,bb);
//		break;
//	case 4 :
//		return Fsquared(aa);
//		break;
//	case 5 :
//		return Fpercentme(aa);
//		break;
//	case 6 :
//		return FPC_change(aa,bb);
//		break;
//	case 7 :
//		return FPC_of(aa,bb);
//		break;
//	case 8 :
//		return FAVG_2(aa,bb);
//		break;
//	case 9 :
//		return Fmin_2(aa,bb);
//		break;
//	case 10 :
//		return Fmax_2(aa,bb);
//		break;
//	case 11 :
//		return FAVG_4(aa,bb,cc,dd);
//		break;
//	case 12 :
//		return Fmin_4(aa,bb,cc,dd);
//		break;
//	case 13 :
//		return Fmax_4(aa,bb,cc,dd);
//		break;
//	case 14:
//		return FInt_Me(aa);
//		break;
//	case 15:
//		return Fsquare_rt(aa);
//		break;
//	case 16:
//		return Fif_4_1(aa,bb,cc,dd);
//		break;
//	case 17:
//		return Fif_4_2(aa,bb,cc,dd);
//		break;
//	case 18:
//		return Funpercentme(aa);
//		break;
//	case 19:
//		return FSum(aa,bb,cc,dd); break;
//	case 20:
//		return FAbsSum2(aa,bb); break;
//	case 21:
//		return FAbsSum4(aa,bb,cc,dd); break;
//	case 22:
//		return FAbsMax2(aa,bb); break;
//	case 23:
//		return FAbsMax4(aa,bb,cc,dd); break;
//	case 24:
//		return FlipDouble(aa); break;
//	case 25:
//		return FRaiseE(aa); break;
//	case 26:
//		return FLnE(aa); break;
//	default:
//		std::cout <<"ERROR: bad function number:"<< _mynum<< std::endl;
//		return 0.0;
//		break;
//	}
//	// We should never get here
//	return 0.0;
//}
//
//double Function::Fadd(double a, double b)   {
//	return a + b;
//};
//
//
//double Function::Fsubtract(double a, double b)   {
//		return a - b;
//};
//
//
//double Function::Fmultiply(double a, double b)   {
//	return a * b;
//};
//
//double Function::Fdivide(double a, double b)  {
//	if (b == 0.0) {
//		return a;
//	} else {
//		return a / b;
//	}
//};
//
//double Function::Fpercentme(double a) {
//	if (a == 0) {
//		return a;
//	} else {
//		return a / 100.0;
//	}
//}
//
//double Function::Funpercentme(double a) {
//	if (a == 0) {
//		return a;
//	} else {
//		return a * 100.0;
//	}
//}
//
//
//double Function::Fsquared(double a)  {
//	if (a == 0.0) {
//		return a;
//	} else {
//		return a * a;
//	}
//};
//
//
//double Function::FPC_change(double a, double b) {
//	if (a == 0.0) {
//		return 0.0;
//	} else {
//		return ((b - a) / a) * 100.0;
//	}
//}
//
//double Function::FPC_of(double a, double b) {
//	if (b == 0) {
//		return a;
//	}
//	if (a == 0 ) { return 0; }
//	return (a / b) * 100.0;
//}
//
//double Function::FAVG_2(double a, double b) {
//	return ( a + b) / 2.0;
//}
//
//double Function::Fmin_2(double a, double b) {
//	if (a > b) {
//		return b;
//	} else {
//		return a;
//	}
//}
//
//double Function::Fmax_2(double a, double b) {
//	if (a > b) {
//		return a;
//	} else {
//		return b;
//	}
//}
//
//double Function::FAVG_4(double a, double b,double c, double d) {
//	return (a + b + c + d) / 4.0;
//}
//
//double Function::Fmin_4(double a, double b,double c, double d) {
//	return Fmin_2(Fmin_2(a,b),Fmin_2(c,d));
//}
//
//double Function::Fmax_4(double a, double b,double c, double d) {
//	return Fmax_2(Fmax_2(a,b),Fmax_2(c,d));
//}
//
//double Function::FInt_Me(double a) {
//	return round(a);
//}
//
//// Be careful not to do negative numbers
//double Function::Fsquare_rt(double a) {
//	if (a < 0.0) {
//		return sqrt(0 -a);
//	} else {
//		return sqrt(a);
//	}
//}
//
//
//double Function::Fif_4_1(double a,double b,double c,double d) {
//    if (a > b) {
//        return c;
//    } else {
//       	return d;
//    }
//}
//
//double Function::Fif_4_2(double a,double b,double c,double d) {
//	if (c > a) {
//		return b;
//	} else {
//		return d;
//	}
//}
//
//double Function::FSum(double a,double b,double c,double d) {
//	return a + b + c + d;
//}
//
//double Function::FAbsSum2(double a, double b) {
//	return fabs(a) + fabs(b);
//}
//
//double Function::FAbsSum4(double a,double b,double c,double d) {
//	return fabs(a) + fabs(b) + fabs(c) + fabs(d);
//}
//
//double Function::FAbsMax2(double a, double b) {
//	return Fmax_2(fabs(a),fabs(b));
//}
//
//double Function::FAbsMax4(double a,double b,double c,double d) {
//	return Fmax_4(fabs(a),fabs(b),fabs(c),fabs(d));
//}
//
//double Function::FlipDouble(double a) {
//	return 0 - a;
//}
//
//double Function::FRaiseE(double a) {
//	if ( a < 0 ) {
//		return 0 - pow(0-a,EULER);
//	} else {
//		return pow(a,EULER);
//	}
//
//}
//
//double Function::FLnE(double a) {
//	if ( a == 0) { return a; }
//	if ( a < 0 ) {
//		return 0 - log(0 -a);
//	} else {
//		return log(a);
//	}
//
//}

