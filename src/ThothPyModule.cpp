#include <boost/python.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <omp.h>
#include <sys/time.h>
#include <ctime>
#include <cstring>


// Prepare the Thoth Imports Module
#include "Settings.h"
#include "JsonConfigLoader.h"
#include "PopulationManager.h"
#include "Optimiser.h"
#include "EvolutionManager.h"
#include "GlobalManager.h"


double solver(const int num_vars,const std::string &nodetree, boost::python::list &case_vars) {
	// Setup the gm
	ArgParser ap;
    JsonConfigLoader jcl;
	Settings settings;
	FitnessCases fc;
	NodeManager nm;
	PopulationManager pm;
	Optimiser o;
	EvolutionManager em;
	gm.initialise(&ap,&jcl,&settings,&fc,&nm,&pm,&o,&em);

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

	// Prepare the solver to run
	gm.fitnessCases->loadString(oss.str().c_str(),num_vars);
	gm.populationManager->loadMemberFromFilename(nodetree.c_str());
	gm.fitnessCases->addConstantsToCliCase(); // Does nothing if no constants
	return gm.populationManager->solveVecCaseSet(0);
}

using namespace boost::python;
BOOST_PYTHON_MODULE(PyThoth) {
	boost::python::def("solver", solver);
}
