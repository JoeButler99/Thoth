#include <boost/python.hpp>
#include <iostream>
#include <vector>		// Variable length arrays
#include <string>
#include <sstream>
#include <map>
#include <omp.h>		// Paralisation functions
#include <sys/time.h>   // Timer funcions
#include <ctime>
#include <cstring>


// Prepare the Thoth Imports Module
#include "Settings.h"
#include "JsonConfigLoader.h"
#include "ArgParser.h"
#include "FitnessCases.h"
//#include "NodeManager.h"
//#include "Optimiser.h"
//#include "EvolutionManager.h"
//#


double solver(const int num_vars,const std::string &nodetree, boost::python::list &case_vars) {
	// Setup the gm
	ArgParser ap;
    JsonConfigLoader jcl;
	Settings settings;
	FitnessCases fc;
//	NodeManager nm;
//	PopulationManager pm;
//	Optimiser o;
//	EvolutionManager em;
//	GlobalManager gm = GlobalManager(ap,jcl,settings,fc,nm,pm,o,em);

	// Prepare the variables
	std::vector<double> vCaseVars;
	std::ostringstream oss;
	double v;
	for (int x = 0; x < len(case_vars); x++) {
		v = boost::python::extract<double>(case_vars[x]);
		vCaseVars.push_back(v);
	}
	std::copy(vCaseVars.begin(),vCaseVars.end()-1,std::ostream_iterator<int>(oss, " "));
	oss << vCaseVars.back();

	std::cout << display_bool(true) << std::endl;
	// Debug Output
	std::cout << num_vars << std::endl;
	std::cout << nodetree << std::endl;
	std::cout << oss.str() << std::endl;

	return 42.0;
}

using namespace boost::python;
BOOST_PYTHON_MODULE(PyThoth) {
	boost::python::def("solver", solver);
}
