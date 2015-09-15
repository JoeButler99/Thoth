/*
 * ErrorFunctions.h
 *
 *  Created on: 15 Sep 2015
 *      Author: joe
 */

#ifndef SRC_ERRORFUNCTIONS_H_
#define SRC_ERRORFUNCTIONS_H_

// TODO - at the moment this class is just a switch between
// an error function
class ErrorFunction {
public:
	static inline double ABS_ERROR(double error) {
		return error;
	}

	static inline double ERROR_SQUARED(double error) {
		return error * error;
	}
};


#endif /* SRC_ERRORFUNCTIONS_H_ */
