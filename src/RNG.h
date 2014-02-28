/*
 * RNG.h
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

#ifndef RNG_H_
#define RNG_H_

#include <vector>		// Variable length arrays
#include <omp.h>		// Paralellisation functions (CPU)
#include <time.h>
#include <iostream>
#include <fstream>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/lagged_fibonacci.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

//typedef boost::mt19937 ENG;    // 44ms 2M rand ints    // Mersenne Twister
//typedef boost::mt11213b ENG;   // 42ms 2M rand ints
typedef boost::rand48 ENG;       // 23ms 2M rand ints

typedef boost::uniform_real<double> D_DIST;   // Double Distribution
typedef boost::uniform_int<int> I_DIST;   	  // Int Distribution
typedef boost::variate_generator<ENG,D_DIST> D_GEN;    // Double generator
typedef boost::variate_generator<ENG,I_DIST> I_GEN;    // Int generator

struct RandStore {
	unsigned short storage[3];
};

class RNG {
public:
	double dMin;
	double dMax;
	int iMin;
	int iMax;

	RNG();
	RNG(double dmin, double dmax);
	~RNG();

	// TODO - Should everything move inline here
	bool bRand();

	double dRand();
	double dRand(double min, double max);

	inline int iRand() {
		return (int_generator.at(omp_get_thread_num())() % iMax) + iMin;
	}

	inline int iRand(int max) {
		return (int_generator.at(omp_get_thread_num())() % max);
	}

	inline int iRand(int min,int max) {
		return (int_generator.at(omp_get_thread_num())() % (max - min)) + min;
	}

protected:
    std::vector<ENG> engines;
    std::vector<I_DIST> int_distribution;
    std::vector<D_DIST> double_distribution;
    std::vector<I_GEN> int_generator;
    std::vector<D_GEN> double_generator;
};


#endif /* RNG_H_ */
