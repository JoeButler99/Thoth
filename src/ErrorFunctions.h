/*
 * ErrorFunctions.h
 *
 *  Created on: 15 Sep 2015
 *      Author: joe
 */

#ifndef SRC_ERRORFUNCTIONS_H_
#define SRC_ERRORFUNCTIONS_H_
#include <map>
#include <math.h>       /* fabs */

typedef double (*FnPtr)(double);

// TODO - at the moment this class is just a switch between
// an error function
class ErrorFunction {
public:


	static inline double ABS_ERROR(double error) {
		return fabs(error);
	}

	static inline double ERROR_SQUARED(double error) {
		return error * error;
	}

	static std::map<std::string, FnPtr > functions;
};


#endif /* SRC_ERRORFUNCTIONS_H_ */
