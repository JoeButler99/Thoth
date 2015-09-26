/*

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


#include <iostream>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <stdio.h>

// Get the test classes
#include "TestArgParser.h"
#include "TestJsonConfigLoader.h"
#include "TestSettings.h"
#include "TestRNG.h"
#include "TestFitnessCases.h"
#include "TestFunction.h"
#include "TestNode.h"
#include "TestNodeManager.h"
#include "TestPopulationMember.h"
#include "TestPopulationManager.h"
#include "TestOptimiser.h"
#include "TestEvolutionManager.h"
#include "TestConstantPool.h"
#include "TestFunctionSets.h"
#include "TestErrorFunction.h"

// Get the new feature tests
#include "TestDistinctPopulation.h"

// Program src includes
#include "../src/RNG.h"
#include "../src/Globals.h"
#include "../src/GlobalManager.h"



ArgParser ap;
JsonConfigLoader jcl;
Settings settings;
FitnessCases fc;
NodeManager nm;
PopulationManager pm;
Optimiser o;
EvolutionManager em;



int main(int argc, char **argv) {
    std::cout << "Configuring Global Manager:" << std::endl;
    gm.initialise(&ap,&jcl,&settings,&fc,&nm,&pm,&o,&em);
    gm.argParser->configFile = "conf/unit-test-config.json";
    gm.argParser->action     = "improve";
    gm.jsonConfig->loadFile(gm.argParser->configFile);
    gm.jsonConfig->updateSettings(gm.settings);
    gm.nodeManager->setupSelf();
    gm.optimiser->silence = true;
    gm.evolutionManager->silence = true;

    std::cout << "Creating Test Suites:" << std::endl;
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestResultCollector result;

//    runner.addTest(TestArgParser::suite());
//    runner.addTest(TestJsonConfigLoader::suite());
//    runner.addTest(TestSettings::suite());
//    runner.addTest(TestRNG::suite());
//    runner.addTest(TestFitnessCases::suite());
//    runner.addTest(TestFunction::suite());
//    runner.addTest(TestFunctionSets::suite());
//    runner.addTest(TestNode::suite());
//    runner.addTest(TestNodeManager::suite());
//    runner.addTest(TestErrorFunctions::suite());
//    runner.addTest(TestPopulationMember::suite());
//    runner.addTest(TestPopulationManager::suite());
//    runner.addTest(TestOptimiser::suite());
//    runner.addTest(TestEvolutionManager::suite());
//    runner.addTest(TestConstantPool::suite());
    runner.addTest(TestDistinctPopulation::suite());

    std::cout<< "Running the unit tests.\n"<< std::endl;
    runner.run("",false,true,false);

    remove(gm.settings->GUESSES_FILE.c_str());

    return runner.result().wasSuccessful() ? 0 : 1;
}
