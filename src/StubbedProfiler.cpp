#include <boost/timer/timer.hpp>
#include <cmath>


int dummyInt;       // Used to stop some functions thinking we do nothing
double dummyDouble; // Used to stop some functions thinking we do nothing

int main(int argc, char **argv) {
	boost::timer::auto_cpu_timer t;

	for (long i = 0; i < 100000000; ++i)
		dummyDouble = std::sqrt(1234.456L); // burn some time

	std::cout << dummyDouble << std::endl;
	return 0;

}
