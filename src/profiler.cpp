/*
 * profiler.cpp
 *
 *  Created on: 8 Dec 2013
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
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <ostream>
#include <math.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctime>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string>
#include <cstdio>


#include "PopulationManager.h"
#include "Optimiser.h"
#include "Globals.h"
#include "GuiFunctions.h"
#include "EvolutionManager.h"
#include "GlobalManager.h"

int reps;
int totalMicroSeconds;
int dummyInt; // Use this to stop some functions thinking we do nothing
Function gFunc("Fadd",2,0,rpnAdd);
PopulationMember standardPopMem;
FILE * stdOutPtr;


// Setup the gm
ArgParser ap;
JsonConfigLoader jcl;
Settings settings;
FitnessCases fc;
NodeManager nm;
PopulationManager pm;
Optimiser o;
EvolutionManager em;
GlobalManager gm = GlobalManager(ap,jcl,settings,fc,nm,pm,o,em);



void usage() {
	question_msg("\nUsage:");
	question_msg( "\nbin/profiler <num of reps>\n\n");
}


void setup(int argc, char **argv){
	gm.argParser.configFile = "conf/profiler-original-config.json";
	gm.loadSettings(argc,argv,true);


	gm.fitnessCases.loadFile(gm.settings.FITNESS_CASE_FILE);
	gm.nodeManager.setupSelf();
	std::cout << "Working with " << gm.nodeManager.functionlist.size() << " functions." << std::endl;
	standardPopMem.method = "fill";
	standardPopMem.rpnNodeVec.push_back(Node(1,true));
	standardPopMem.rpnNodeVec.push_back(Node(gm.nodeManager.getFunctionByNum(0)));
	standardPopMem.rpnNodeVec.push_back(Node(gm.nodeManager.getFunctionByNum(1)));
	standardPopMem.rpnNodeVec.push_back(Node(gm.nodeManager.getFunctionByNum(2)));
	standardPopMem.rpnNodeVec.push_back(Node(gm.nodeManager.getFunctionByNum(3)));
	standardPopMem.rpnNodeVec.push_back(Node(gm.nodeManager.getFunctionByNum(1)));
	standardPopMem.rpnNodeVec.push_back(Node(4));
	standardPopMem.rpnNodeVec.push_back(Node(7));
	standardPopMem.rpnNodeVec.push_back(Node(10));
	standardPopMem.rpnNodeVec.push_back(Node(13));
	standardPopMem.rpnNodeVec.push_back(Node(gm.nodeManager.getFunctionByNum(3)));
	standardPopMem.rpnNodeVec.push_back(Node(16));
	standardPopMem.rpnNodeVec.push_back(Node(19));
	standardPopMem.rpnNodeVec.push_back(Node(gm.nodeManager.getFunctionByNum(0)));
	standardPopMem.rpnNodeVec.push_back(Node(22));
	standardPopMem.rpnNodeVec.push_back(Node(gm.nodeManager.getFunctionByNum(2)));
	standardPopMem.rpnNodeVec.push_back(Node(25));
	standardPopMem.rpnNodeVec.push_back(Node(28));
	standardPopMem.hasChanged = true;
	gm.populationManager.populationlist.add(standardPopMem);
	gm.populationManager.scoreOneMember(0);
	standardPopMem.score = gm.populationManager.populationlist.v.at(0).score;
	std::cout << "Standard Pop Mem scores: "<< gm.populationManager.populationlist.v.at(0).score << std::endl;
	gm.populationManager.populationlist.v.clear();
}

void testNodeCreation(unsigned reps) {
	for (unsigned x = 0; x < reps; ++x) {
		Node nT(rng.iRand(gm.fitnessCases.TERMINALS));
		Node nF(gm.nodeManager.giveRandFunction());
	}
}

void testPopulationMemberCreation(unsigned reps) {
	for (unsigned x = 0; x < reps; ++x) {
		PopulationMember p;
		p.createSelf("Profiler",3);
	}
}

void testIRand(unsigned reps) {
	int result = 0;
	for (unsigned x = 0; x < reps; ++x) {
		result = rng.iRand(gm.settings.POPULATION);
	}
	dummyInt = result;
}

void testIRandThreaded(unsigned reps) {
	int result = 0;
#pragma omp parallel
	{
#pragma omp for schedule(static) nowait
		for (unsigned x = 0; x < reps; ++x) {
			result = rng.iRand(gm.settings.POPULATION);
		}
	}
	dummyInt = result;
}


void testNodeReassign(unsigned reps) {
	for (unsigned x = 0; x < reps; ++x) {
		Node nT(rng.iRand(gm.fitnessCases.TERMINALS));
		Node nF(gm.nodeManager.giveRandFunction());
		nF.setTerminal(rng.iRand(gm.fitnessCases.TERMINALS));
		nT.setFromFunc(gm.nodeManager.giveRandFunction());
	}
}


void testPopulationManagerPopulationCreation(unsigned reps) {
	for (unsigned x = 0; x < reps; ++x) {
		gm.populationManager.generateRequired();
		gm.populationManager.populationlist.v.clear();
	}
}


void testPopulationManagerPopulationSort(unsigned reps) {
	gm.populationManager.generateRequired();
	gm.populationManager.scoreAllVecRpn();
	TvectorPM test = gm.populationManager.populationlist;

	for (unsigned x = 0; x < reps; ++x) {
		gm.populationManager.sortByScore();
		gm.populationManager.populationlist = test;
	}
	gm.populationManager.populationlist.v.clear();
}

void testPopulationManagerPopulationCull(unsigned reps) {
	gm.populationManager.generateRequired();
	TvectorPM test = gm.populationManager.populationlist;
	for (unsigned x = 0; x < reps; ++x) {
		gm.populationManager.sortByScore();
		gm.populationManager.cullWeak();
		gm.populationManager.populationlist = test;
	}
	gm.populationManager.populationlist.v.clear();
}

void testPopulationManagerScoreOne(unsigned reps) {
	gm.populationManager.generateRequired();
	int member;
	for (unsigned x = 0; x < reps; ++x) {
		member = rng.iRand(gm.settings.POPULATION);
		gm.populationManager.scoreOneMember(member);
		gm.populationManager.populationlist.v.at(member).hasChanged = true; // Score again if we get it
	}
	gm.populationManager.populationlist.v.clear();
}


void testPopulationManagerScoreAll(unsigned reps) {
	gm.populationManager.generateRequired();
	TvectorPM test = gm.populationManager.populationlist;
	for (unsigned x = 0; x < reps; ++x) {
		gm.populationManager.scoreAllVecRpn();
		gm.populationManager.populationlist = test;
	}
	gm.populationManager.populationlist.v.clear();
}


void testOptimiserTerminalSwapper(unsigned reps) {

	for (unsigned x = 0; x < reps; ++x) {
		PopulationMember oP = standardPopMem;
		gm.optimiser.terminalSwapper(oP);
	}
}

void testOptimiserFunctionSwapper(unsigned reps) {

	for (unsigned x = 0; x < reps; ++x) {
		PopulationMember oP = standardPopMem;
		gm.optimiser.functionSwapper(oP);
	}
}

void testOptimiserBranchCutter(unsigned reps) {

	for (unsigned x = 0; x < reps; ++x) {
		PopulationMember oP = standardPopMem;
		gm.optimiser.branchCutter(oP);
	}
}

void testOptimiserOptimise(unsigned reps) {
	for (unsigned x = 0; x < reps; ++x) {
		gm.populationManager.populationlist.add(standardPopMem);
		gm.optimiser.optimise(gm.settings.OPTIMISE_CUTTER_EVERY* gm.settings.OPTIMISE_FUNCTIONS_EVERY * gm.settings.OPTIMISE_TERMINALS_EVERY,false);
		gm.populationManager.populationlist.v.clear();
	}
}

void testEvolutionCopyNodeTree(unsigned reps) {
	std::vector<Node> testRPNTree;
	for (unsigned x = 0; x < reps; ++x) {
		testRPNTree.clear();
		gm.evolutionManager.copyNodeTree(0,0,testRPNTree,standardPopMem.rpnNodeVec);
	}
}

void testEvolutionTournament(unsigned reps) {
	gm.populationManager.generateRequired();
	gm.populationManager.scoreAllVecRpn();
	gm.populationManager.sortByScore();
	int result = 0;
	for (unsigned x = 0; x < reps; ++x) {
		result = gm.evolutionManager.tournament(gm.settings.POPULATION);
	}
	gm.populationManager.populationlist.v.clear();
	dummyInt = result;
}

void testEvolutionCrossover(unsigned reps) {
	gm.populationManager.generateRequired();
	gm.populationManager.scoreAllVecRpn();
	gm.populationManager.sortByScore();
	for (unsigned x = 0; x < reps; ++x) {
		gm.evolutionManager.crossover(8,100);
	}
	gm.populationManager.populationlist.v.clear();
}

void testEvolutionCrossoverBranch(unsigned reps) {
	gm.populationManager.generateRequired();
	gm.populationManager.scoreAllVecRpn();
	gm.populationManager.sortByScore();
	for (unsigned x = 0; x < reps; ++x) {
		gm.evolutionManager.crossoverNewRoot(8,100);
	}
	gm.populationManager.populationlist.v.clear();
}

void testEvolutionCutNodeTree(unsigned reps) {
	gm.populationManager.generateRequired();
	gm.populationManager.scoreAllVecRpn();
	gm.populationManager.sortByScore();
	for (unsigned x = 0; x < reps; ++x) {
		gm.evolutionManager.crossover(8,100);
	}
	gm.populationManager.populationlist.v.clear();
}

void testEvolutionMutTree(unsigned reps) {
	gm.populationManager.generateRequired();
	gm.populationManager.scoreAllVecRpn();
	gm.populationManager.sortByScore();
	for (unsigned x = 0; x < reps; ++x) {
		gm.evolutionManager.mutateNodeTree(8,100);
	}
	gm.populationManager.populationlist.v.clear();
}

void testEvolutionMutNode(unsigned reps) {
	gm.populationManager.generateRequired();
	gm.populationManager.scoreAllVecRpn();
	gm.populationManager.sortByScore();
	for (unsigned x = 0; x < reps; ++x) {
		gm.evolutionManager.mutateSingleNode(8,100);
	}
	gm.populationManager.populationlist.v.clear();
}




void timeAndDisplay(std::string name,function_ptr_uint f_ptr,int multiplier = 1) {
	totalMicroSeconds = 0;
	struct timeval start, end;
	long mtime, seconds, useconds;
	int total_reps = reps * multiplier;

	// Stop any stdout getting in the way
	stdOutPtr = freopen("/de/null","r",stdout);//redirects standard input

	gettimeofday(&start, NULL);
	// Run the code
	f_ptr(total_reps);

	gettimeofday(&end, NULL);
	//reset to standard output again
	stdOutPtr = freopen ("/dev/tty", "a", stdout);

	seconds  = end.tv_sec  - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	mtime = ((seconds) * 1000000 + useconds/1.0) + 0.0005;
	totalMicroSeconds += mtime;
	printf(" %-11d %-11d %-11d %-29s %-11d μs\n",reps,multiplier,total_reps,name.c_str(),totalMicroSeconds);
}


int main(int argc, char **argv) {
	if (argc != 2) {
		usage();
		return 1;
	}

	setup(argc,argv);
	std::cout << "Thoth Profiler" << std::endl;
	gm.settings.displaySettings();
	gm.fitnessCases.displayFitnessCases();

	reps = atoi(argv[1]);

	printf("\n\e[1;34m%-12s%-12s%-12s%-30s%-12s\e[0m\n\n","User Reps","Multipler","Total Reps","Block Name","Time Taken");
	timeAndDisplay("Random Int Generation",testIRand,100000);
	timeAndDisplay("Threaded Rnd Int Gen",testIRandThreaded,100000);
	timeAndDisplay("Node Creation",testNodeCreation,500);
	timeAndDisplay("Node Create & Reassign",testNodeReassign,500);
	timeAndDisplay("Population Member Creation",testPopulationMemberCreation,500);
	timeAndDisplay("Population Init",testPopulationManagerPopulationCreation);
	timeAndDisplay("Population Sort",testPopulationManagerPopulationSort);
	timeAndDisplay("Population Cull",testPopulationManagerPopulationCull);
	timeAndDisplay("Population Score One",testPopulationManagerScoreOne);
	timeAndDisplay("Population Score All",testPopulationManagerScoreAll);
	timeAndDisplay("Optimiser Terminal Swap",testOptimiserTerminalSwapper);
	timeAndDisplay("Optimiser Function Swap",testOptimiserFunctionSwapper);
	timeAndDisplay("Optimiser Branch Cutter",testOptimiserBranchCutter);
	timeAndDisplay("Optimiser Optimise",testOptimiserOptimise);
	timeAndDisplay("Evolution CopyNodeTree",testEvolutionCopyNodeTree,5000);
	timeAndDisplay("Evolution Tournament",testEvolutionTournament,5000);
	timeAndDisplay("Evolution Crossover",testEvolutionCrossover,20);
	timeAndDisplay("Evolution Crossover New",testEvolutionCrossoverBranch,20);
	timeAndDisplay("Evolution CutNodeTree",testEvolutionCutNodeTree,20);
	timeAndDisplay("Evolution Mutate Node",testEvolutionMutNode,20);
	timeAndDisplay("Evolution Mutate Tree",testEvolutionMutTree,20);

	std::cout << "\n" << std::endl;
}
