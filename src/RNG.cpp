/*
 * RNG.cpp
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

#include "RNG.h"

// Globals I initialise
RNG rng;

unsigned int good_seed()
{
    unsigned int random_seed, random_seed_a, random_seed_b;
    std::ifstream file ("/dev/urandom", std::ios::binary);
    if (file.is_open())
    {
        char * memblock;
        int size = sizeof(int);
        memblock = new char [size];
        file.read (memblock, size);
        file.close();
        random_seed_a = *reinterpret_cast<int*>(memblock);
        delete[] memblock;
    }// end if
    else
    {
        random_seed_a = 0;
    }
    random_seed_b = time(0);
    random_seed = random_seed_a xor random_seed_b;
    return random_seed;
} // end good_seed()


// Now we build up the vectors with an int and double generator per thread
RNG::RNG() : dMin(0.0), dMax(1000000), iMin(0), iMax(1000000000){
	srand(time(0));
	int threads = std::max(1,omp_get_max_threads());
	for (int x = 0; x < threads; ++x) {
		engines.push_back(ENG(good_seed()));
		double_distribution.push_back(D_DIST(dMin,dMax));
		int_distribution.push_back(I_DIST(iMin,iMax));
		double_generator.push_back(D_GEN(engines.at(x),double_distribution.at(x)));
		int_generator.push_back(I_GEN(engines.at(x),int_distribution.at(x)));
	}
}
RNG::RNG(double dmin, double dmax) : dMin(dmin), dMax(dmax), iMin(0), iMax(1000000000) {
	int threads = std::max(1,omp_get_max_threads());
	for (int x = 0; x < threads; ++x) {
		engines.push_back(ENG(good_seed()));
		double_distribution.push_back(D_DIST(dMin,dMax));
		int_distribution.push_back(I_DIST(iMin,iMax));
		double_generator.push_back(D_GEN(engines.at(x),double_distribution.at(x)));
		int_generator.push_back(I_GEN(engines.at(x),int_distribution.at(x)));
	}
}

RNG::~RNG() { }






