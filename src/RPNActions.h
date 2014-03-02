/*
 * RPNActions.h
 *
 *  Created on: 1 Mar 2014
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

#ifndef RPNACTIONS_H_
#define RPNACTIONS_H_

#include "Globals.h"

inline void rpnAdd(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -=2;
	rpnStack[highest] =  rpnStack[highest+1] + rpnStack[highest];
}

inline void rpnSubtract(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -=2;
	rpnStack[highest] =  rpnStack[highest+1] - rpnStack[highest];
}

inline void rpnMultiply(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -=2;
	rpnStack[highest] =  rpnStack[highest+1] * rpnStack[highest];
}

inline void rpnDivide(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -=2;
	if (rpnStack[highest] == 0.0) { rpnStack[highest] = rpnStack[highest+1]; }
	else { rpnStack[highest] =  rpnStack[highest+1] / rpnStack[highest]; }
}

inline void rpnSquare(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest --;
	rpnStack[highest] =  rpnStack[highest] * rpnStack[highest];
}

inline void rpnPercentMe(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest --;
	rpnStack[highest] =  rpnStack[highest] / 100.0;
}

inline void rpnPercentChange(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -=2;
	if (rpnStack[highest+1] == 0.0 ) { rpnStack[highest] =  0.0; }
	else { rpnStack[highest] =  ((rpnStack[highest] - rpnStack[highest+1]) / rpnStack[highest+1])  * 100.0; }
}

inline void rpnPercentOf(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -=2;
	if (rpnStack[highest+1] == 0.0 or rpnStack[highest] == 0.0) { rpnStack[highest] =  0.0; }
	else { rpnStack[highest] =  (rpnStack[highest+1] / rpnStack[highest]) * 100.0; }
}

inline void rpnAvgOf2(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -=2;
	rpnStack[highest] =  ( rpnStack[highest+1] + rpnStack[highest]) / 2.0;
}

inline void rpnMinOf2(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -=2;
	if (rpnStack[highest+1] < rpnStack[highest]) {
		rpnStack[highest] =  rpnStack[highest+1];
	}
}

inline void rpnMaxOf2(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -=2;
	if (rpnStack[highest+1] > rpnStack[highest]) {
		rpnStack[highest] =  rpnStack[highest+1];
	}
}

inline void rpnAvgOf4(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -=4;
	rpnStack[highest] =  (rpnStack[highest+3] + rpnStack[highest+2] + rpnStack[highest+1] + rpnStack[highest]) / 4.0;
}

inline void rpnMinOf4(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -=4;
	if (rpnStack[highest+3] >rpnStack[highest+2]) {
		// v1 smaller
		if (rpnStack[highest+1] > rpnStack[highest]) {
			// v3 smaller
			if (rpnStack[highest] > rpnStack[highest+2]) { rpnStack[highest] =  rpnStack[highest+2]; }
		} else {
			// v2 smaller
			if (rpnStack[highest+1] > rpnStack[highest+2]) { rpnStack[highest] =  rpnStack[highest+2]; }
			else { rpnStack[highest] =  rpnStack[highest+1]; }
		}
	} else {
		// v0 smaller
		if (rpnStack[highest+1] > rpnStack[highest]) {
			// v3 smaller
			if (rpnStack[highest] > rpnStack[highest+3]) { rpnStack[highest] =  rpnStack[highest+3]; }
		} else {
			// v2 smaller
			if (rpnStack[highest+1] > rpnStack[highest+3]) { rpnStack[highest] =  rpnStack[highest+3]; }
			else { rpnStack[highest] =  rpnStack[highest+1]; }
		}
	}
}

inline void rpnMaxOf4(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -=4;
	if (rpnStack[highest+3] > rpnStack[highest+2]) {
		// v0 bigger
		if (rpnStack[highest+1] > rpnStack[highest]) {
			// v2 bigger
			if (rpnStack[highest+1] > rpnStack[highest+3]) { rpnStack[highest] =  rpnStack[highest+1]; }
			else { rpnStack[highest] =  rpnStack[highest+3]; }
		} else {
			// v3 bigger
			if (rpnStack[highest] < rpnStack[highest+3]) { rpnStack[highest] =  rpnStack[highest+3]; }
		}
	} else {
		// v1 bigger
		if (rpnStack[highest+1] > rpnStack[highest]) {
			// v2 bigger
			if (rpnStack[highest+1] > rpnStack[highest+2]) { rpnStack[highest] =  rpnStack[highest+1]; }
			else { rpnStack[highest] =  rpnStack[highest+2]; }
		} else {
			// v3 bigger
			if (rpnStack[highest] < rpnStack[highest+2]) { rpnStack[highest] =  rpnStack[highest+2]; }
		}
	}
}

inline void rpnToInt(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest --;
	rpnStack[highest] =  round(rpnStack[highest]);
}

inline void rpnSquareRoot(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest --;
	if (rpnStack[highest] < 0.0) {
		rpnStack[highest] = 0 - rpnStack[highest];
	}
	rpnStack[highest] =  sqrt(rpnStack[highest]);
}

inline void rpnIfV1(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -=4;
	if ( rpnStack[highest+3] > rpnStack[highest+2]) { rpnStack[highest] =  rpnStack[highest+1]; }
}

inline void rpnIfV2(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -=4;
	if (rpnStack[highest+1] >  rpnStack[highest+3]) { 	rpnStack[highest] =  rpnStack[highest+2];	}
}

inline void rpnUnPercentMe(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest --;
	rpnStack[highest] =  rpnStack[highest] * 100.0;
}

inline void rpnSum4(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -=4;
	rpnStack[highest] = rpnStack[highest+3] + rpnStack[highest+2] + rpnStack[highest+1] + rpnStack[highest];
}

inline void rpnAbsSum2(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -= 2;
	rpnStack[highest] = fabs(rpnStack[highest+1]) + fabs(rpnStack[highest]);
}

inline void rpnAbsSum4(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -=4;
	rpnStack[highest] = fabs(rpnStack[highest+3]) + fabs(rpnStack[highest+2]) + fabs(rpnStack[highest+1]) + fabs(rpnStack[highest]);
}

inline void rpnAbsMax2(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -= 2;
	if (fabs(rpnStack[highest+1]) > fabs(rpnStack[highest])) { rpnStack[highest] =  fabs(rpnStack[highest+1]); }
	else {	rpnStack[highest] =  fabs(rpnStack[highest]); }
}

inline void rpnAbsMax4(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest -=4;
	if (fabs(rpnStack[highest+3]) > fabs(rpnStack[highest+2])) {
		// v0 bigger
		if (fabs(rpnStack[highest+1]) > fabs(rpnStack[highest])) {
			// v2 bigger
			if (fabs(rpnStack[highest+1]) > fabs(rpnStack[highest+3])) { rpnStack[highest] =  fabs(rpnStack[highest+1]); }
			else { rpnStack[highest] =  fabs(rpnStack[highest+3]); }
		} else {
			// v3 bigger
			if (fabs(rpnStack[highest]) > fabs(rpnStack[highest+3])) { rpnStack[highest] =  fabs(rpnStack[highest]); }
			else { rpnStack[highest] =  fabs(rpnStack[highest+3]); }
		}
	} else {
		// v1 bigger
		if (fabs(rpnStack[highest+1]) > fabs(rpnStack[highest])) {
			// v2 bigger
			if (fabs(rpnStack[highest+1]) > fabs(rpnStack[highest+2])) { rpnStack[highest] =  fabs(rpnStack[highest+1]); }
			else { rpnStack[highest] =  fabs(rpnStack[highest+2]); }
		} else {
			// v3 bigger
			if (fabs(rpnStack[highest]) > fabs(rpnStack[highest+2])) { rpnStack[highest] =  fabs(rpnStack[highest]); }
			else { rpnStack[highest] =  fabs(rpnStack[highest+2]); }
		}
	}
}

inline void rpnNegate(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest --;
	rpnStack[highest] = 0 -  rpnStack[highest];
}

inline void rpnRaiseE(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest --;
	if ( rpnStack[highest] != 0.0) {
		if ( rpnStack[highest] < 0) {
			rpnStack[highest] = 0 - pow(0- rpnStack[highest],EULER);
		} else {
			rpnStack[highest] = pow( rpnStack[highest],EULER);
		}
	}
}

inline void rpnLnE(double rpnStack[RPN_STACK_LIMIT],int & highest) {
	highest --;
	if(rpnStack[highest] != 0.0) {
		if(rpnStack[highest] < 0) {  rpnStack[highest] = 0 - log(0 - rpnStack[highest]); }
		else { rpnStack[highest] = log(rpnStack[highest]);	}
	}
}




#endif /* RPNACTIONS_H_ */
