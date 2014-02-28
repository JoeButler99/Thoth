/*
 * PopulationMember.h
 *
 *  Created on: 4 May 2013
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

#ifndef POPULATIONMEMBER_H_
#define POPULATIONMEMBER_H_
#include <vector>
#include <string>
#include "Node.h"
#include "Function.h"
#include "RNG.h"
#include "GlobalManager.h"
#include "FitnessCases.h"


class PopulationMember {
public:
	std::string method;
	bool hasChanged;
	double score;
	std::vector<Node> rpnNodeVec;

	PopulationMember();
	PopulationMember(std::vector<Node> inputVec);

	void createSelf(std::string m,int depth);
	void fillRandomNodes(int max_depth);
	void displaySelf();
	void setScore(double s);

	inline bool operator< (const PopulationMember& rhs) const{
		return this->score < rhs.score;
	}

	// This function is only here to stop the optimiser having to create lots of temporary population members when
	// It scores it improvement attempts
	inline static double solveVecCaseSet(double * var_set, std::vector<Node> & rpnNodeVec) {
		double rpnStack[RPN_STACK_LIMIT] = {0};
		int highest = 0;
		for (int x = rpnNodeVec.size()-1; x > -1; x -- ) {
			if (rpnNodeVec[x].isTerminal) {
				// Add to stack
				rpnStack[highest] = var_set[rpnNodeVec[x].tNo];
				highest ++;
			} else {
				// Solve requested - onto stack
				switch (rpnNodeVec[x].fNo) {
				case -1:
					highest -= rpnNodeVec[x].fInputs;
					break;
				case 0 :
					highest -=2;
					//stack[highest] =  values[0] + values[1]; break;
					rpnStack[highest] =  rpnStack[highest+1] + rpnStack[highest]; break;
				case 1 :
					highest -=2;
					rpnStack[highest] =  rpnStack[highest+1] - rpnStack[highest]; break;
				case 2 :
					highest -=2;
					rpnStack[highest] =  rpnStack[highest+1] * rpnStack[highest]; break;
				case 3 :
					highest -=2;
					if (rpnStack[highest] == 0.0) { rpnStack[highest] = rpnStack[highest+1]; }
					else { rpnStack[highest] =  rpnStack[highest+1] / rpnStack[highest]; }
					break;
				case 4 :
					highest --;
					rpnStack[highest] =  rpnStack[highest] * rpnStack[highest];  break;
				case 5 :
					highest --;
					if (rpnStack[highest] != 0) {
						rpnStack[highest] =  rpnStack[highest] / 100.0;
					}  break;
				case 6 :
					highest -=2;
					if (rpnStack[highest+1] == 0.0 ) { rpnStack[highest] =  0.0; }
					else { rpnStack[highest] =  ((rpnStack[highest] - rpnStack[highest+1]) / rpnStack[highest+1])  * 100.0; } break;
				case 7 :
					highest -=2;
					if (rpnStack[highest+1] == 0.0 or rpnStack[highest] == 0.0) { rpnStack[highest] =  0.0; }
					else { rpnStack[highest] =  (rpnStack[highest+1] / rpnStack[highest]) * 100.0; } break;
				case 8 :
					highest -=2;
					rpnStack[highest] =  ( rpnStack[highest+1] + rpnStack[highest]) / 2.0; break;
				case 9 :
					highest -=2;
					if (rpnStack[highest+1] < rpnStack[highest]) {
						rpnStack[highest] =  rpnStack[highest+1];
					} break;
				case 10 :
					highest -=2;
					if (rpnStack[highest+1] > rpnStack[highest]) {
						rpnStack[highest] =  rpnStack[highest+1];
					} break;
				case 11 :
					highest -=4;
					rpnStack[highest] =  (rpnStack[highest+3] + rpnStack[highest+2] + rpnStack[highest+1] + rpnStack[highest]) / 4.0; break;
				case 12 :
					highest -=4;
					if (rpnStack[highest+3] >rpnStack[highest+2]) {
						// v1 smaller
						if (rpnStack[highest+1] > rpnStack[highest]) {
							// v3 smaller
							if (rpnStack[highest] > rpnStack[highest+2]) { rpnStack[highest] =  rpnStack[highest+2]; }
							//else { stack[highest] =  stack[highest]; }
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
							//else { stack[highest] =  stack[highest]; }
						} else {
							// v2 smaller
							if (rpnStack[highest+1] > rpnStack[highest+3]) { rpnStack[highest] =  rpnStack[highest+3]; }
							else { rpnStack[highest] =  rpnStack[highest+1]; }
						}
					} break;
				case 13 :
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
					} break;
				case 14:
					highest --;
					rpnStack[highest] =  round(rpnStack[highest]); break;
				case 15:
					highest --;
					if (rpnStack[highest] > 0.0) {
						rpnStack[highest] =  sqrt(rpnStack[highest]);
					} break;
				case 16:
					highest -=4;
				    if ( rpnStack[highest+3] > rpnStack[highest+2]) { rpnStack[highest] =  rpnStack[highest+1]; }
				    break;
				case 17:
					highest -=4;
					if (rpnStack[highest+1] >  rpnStack[highest+3]) { 	rpnStack[highest] =  rpnStack[highest+2];	}
					break;
				case 18:
					highest --;
					if (rpnStack[highest] != 0) {
						rpnStack[highest] =  rpnStack[highest] * 100.0;
					} break;
				case 19:
					highest -=4;
					rpnStack[highest] = rpnStack[highest+3] + rpnStack[highest+2] + rpnStack[highest+1] + rpnStack[highest]; break;
				case 20:
					highest -= 2;
					rpnStack[highest] = fabs(rpnStack[highest+1]) + fabs(rpnStack[highest]); break;
				case 21:
					highest -=4;
					rpnStack[highest] = fabs(rpnStack[highest+3]) + fabs(rpnStack[highest+2]) + fabs(rpnStack[highest+1]) + fabs(rpnStack[highest]); break;
				case 22:
					highest -= 2;
					if (fabs(rpnStack[highest+1]) > fabs(rpnStack[highest])) { rpnStack[highest] =  fabs(rpnStack[highest+1]); }
					else {	rpnStack[highest] =  fabs(rpnStack[highest]); } break;
				case 23:
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
					} break;
				case 24:
					highest --;
					rpnStack[highest] = 0 -  rpnStack[highest]; break;
				case 25:
					highest --;
					if ( rpnStack[highest] == 0.0) { break;}
					if ( rpnStack[highest] < 0) {
						rpnStack[highest] = 0 - pow(0- rpnStack[highest],EULER);
					} else {
						rpnStack[highest] = pow( rpnStack[highest],EULER);
					} break;
				case 26:
					highest --;
					if(rpnStack[highest] == 0.0) { rpnStack[highest] = 0; break;}
					if(rpnStack[highest] < 0) {  rpnStack[highest] = 0 - log(0 - rpnStack[highest]); }
					else { rpnStack[highest] = log(rpnStack[highest]);	}
					break;
				default:
					rpnStack[highest] =  0.0; break;
				}
				highest ++;
			}
		}

		return rpnStack[0];
	}

	// Main Solver class
	inline double rpnVecSolveSelf(double * var_set) const {
		double rpnStack[RPN_STACK_LIMIT] = {0};
		int highest = 0;
		for (int x = rpnNodeVec.size()-1; x > -1; x -- ) {
			if (rpnNodeVec[x].isTerminal) {
				// Add to stack
				rpnStack[highest] = var_set[rpnNodeVec[x].tNo];
				highest ++;
			} else {
				// Solve requested - onto stack
				switch (rpnNodeVec[x].fNo) {
				case -1:
					highest -= rpnNodeVec[x].fInputs;
					break;
				case 0 :
					highest -=2;
					//stack[highest] =  values[0] + values[1]; break;
					rpnStack[highest] =  rpnStack[highest+1] + rpnStack[highest]; break;
				case 1 :
					highest -=2;
					rpnStack[highest] =  rpnStack[highest+1] - rpnStack[highest]; break;
				case 2 :
					highest -=2;
					rpnStack[highest] =  rpnStack[highest+1] * rpnStack[highest]; break;
				case 3 :
					highest -=2;
					if (rpnStack[highest] == 0.0) { rpnStack[highest] = rpnStack[highest+1]; }
					else { rpnStack[highest] =  rpnStack[highest+1] / rpnStack[highest]; }
					break;
				case 4 :
					highest --;
					rpnStack[highest] =  rpnStack[highest] * rpnStack[highest];  break;
				case 5 :
					highest --;
					if (rpnStack[highest] != 0) {
						rpnStack[highest] =  rpnStack[highest] / 100.0;
					}  break;
				case 6 :
					highest -=2;
					if (rpnStack[highest+1] == 0.0 ) { rpnStack[highest] =  0.0; }
					else { rpnStack[highest] =  ((rpnStack[highest] - rpnStack[highest+1]) / rpnStack[highest+1])  * 100.0; } break;
				case 7 :
					highest -=2;
					if (rpnStack[highest+1] == 0.0 or rpnStack[highest] == 0.0) { rpnStack[highest] =  0.0; }
					else { rpnStack[highest] =  (rpnStack[highest+1] / rpnStack[highest]) * 100.0; } break;
				case 8 :
					highest -=2;
					rpnStack[highest] =  ( rpnStack[highest+1] + rpnStack[highest]) / 2.0; break;
				case 9 :
					highest -=2;
					if (rpnStack[highest+1] < rpnStack[highest]) {
						rpnStack[highest] =  rpnStack[highest+1];
					} break;
				case 10 :
					highest -=2;
					if (rpnStack[highest+1] > rpnStack[highest]) {
						rpnStack[highest] =  rpnStack[highest+1];
					} break;
				case 11 :
					highest -=4;
					rpnStack[highest] =  (rpnStack[highest+3] + rpnStack[highest+2] + rpnStack[highest+1] + rpnStack[highest]) / 4.0; break;
				case 12 :
					highest -=4;
					if (rpnStack[highest+3] >rpnStack[highest+2]) {
						// v1 smaller
						if (rpnStack[highest+1] > rpnStack[highest]) {
							// v3 smaller
							if (rpnStack[highest] > rpnStack[highest+2]) { rpnStack[highest] =  rpnStack[highest+2]; }
							//else { stack[highest] =  stack[highest]; }
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
							//else { stack[highest] =  stack[highest]; }
						} else {
							// v2 smaller
							if (rpnStack[highest+1] > rpnStack[highest+3]) { rpnStack[highest] =  rpnStack[highest+3]; }
							else { rpnStack[highest] =  rpnStack[highest+1]; }
						}
					} break;
				case 13 :
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
					} break;
				case 14:
					highest --;
					rpnStack[highest] =  round(rpnStack[highest]); break;
				case 15:
					highest --;
					if (rpnStack[highest] > 0.0) {
						rpnStack[highest] =  sqrt(rpnStack[highest]);
					} break;
				case 16:
					highest -=4;
				    if ( rpnStack[highest+3] > rpnStack[highest+2]) { rpnStack[highest] =  rpnStack[highest+1]; }
				    break;
				case 17:
					highest -=4;
					if (rpnStack[highest+1] >  rpnStack[highest+3]) { 	rpnStack[highest] =  rpnStack[highest+2];	}
					break;
				case 18:
					highest --;
					if (rpnStack[highest] != 0) {
						rpnStack[highest] =  rpnStack[highest] * 100.0;
					} break;
				case 19:
					highest -=4;
					rpnStack[highest] = rpnStack[highest+3] + rpnStack[highest+2] + rpnStack[highest+1] + rpnStack[highest]; break;
				case 20:
					highest -= 2;
					rpnStack[highest] = fabs(rpnStack[highest+1]) + fabs(rpnStack[highest]); break;
				case 21:
					highest -=4;
					rpnStack[highest] = fabs(rpnStack[highest+3]) + fabs(rpnStack[highest+2]) + fabs(rpnStack[highest+1]) + fabs(rpnStack[highest]); break;
				case 22:
					highest -= 2;
					if (fabs(rpnStack[highest+1]) > fabs(rpnStack[highest])) { rpnStack[highest] =  fabs(rpnStack[highest+1]); }
					else {	rpnStack[highest] =  fabs(rpnStack[highest]); } break;
				case 23:
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
					} break;
				case 24:
					highest --;
					rpnStack[highest] = 0 -  rpnStack[highest]; break;
				case 25:
					highest --;
					if ( rpnStack[highest] == 0.0) { break;}
					if ( rpnStack[highest] < 0) {
						rpnStack[highest] = 0 - pow(0- rpnStack[highest],EULER);
					} else {
						rpnStack[highest] = pow( rpnStack[highest],EULER);
					} break;
				case 26:
					highest --;
					if(rpnStack[highest] == 0.0) { rpnStack[highest] = 0; break;}
					if(rpnStack[highest] < 0) {  rpnStack[highest] = 0 - log(0 - rpnStack[highest]); }
					else { rpnStack[highest] = log(rpnStack[highest]);	}
					break;
				default:
					rpnStack[highest] =  0.0; break;
				}
				highest ++;
			}
		}

		return rpnStack[0];
	}


};

#endif /* POPULATIONMEMBER_H_ */
