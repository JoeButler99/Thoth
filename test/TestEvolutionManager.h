/*
 * TestEvolutionManager.h
 *
 *  Created on: 26 Aug 2013
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

#ifndef TESTEVOLUTIONMANAGER_H_
#define TESTEVOLUTIONMANAGER_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include "../src/Function.h"
#include "../src/EvolutionManager.h"
#include "../src/PopulationMember.h"
//FILE * stdOutPtr2;

//
std::string testMethod;
bool memberMethodEqual(PopulationMember obj) {
	return obj.method == testMethod;
}


class TestEvolutionManager : public CppUnit::TestFixture {
public:
	TestEvolutionManager(){}
	virtual ~TestEvolutionManager(){ }


	static CppUnit::Test *suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestEvolutionManager");
		suiteOfTests->addTest(new CppUnit::TestCaller<TestEvolutionManager>("Test Default Constructor",&TestEvolutionManager::testDefaultConstructor));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestEvolutionManager>("Test Copy Node Tree",&TestEvolutionManager::testCopyNodeTree));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestEvolutionManager>("Test Crossover",&TestEvolutionManager::testCrossover));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestEvolutionManager>("Test Crossover New Root",&TestEvolutionManager::testCrossoverNewRoot));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestEvolutionManager>("Test Cut node tree",&TestEvolutionManager::testCutNodeTree));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestEvolutionManager>("Test delete tree branch",&TestEvolutionManager::testDeleteTreeBranch));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestEvolutionManager>("Test make node tree",&TestEvolutionManager::testMakeNodeTree));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestEvolutionManager>("Test mutate node tree",&TestEvolutionManager::testMutateNodeTree));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestEvolutionManager>("Test mutate single node",&TestEvolutionManager::testMutateSingleNode));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestEvolutionManager>("Test run generations",&TestEvolutionManager::testRunGenerations));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestEvolutionManager>("Test tournament",&TestEvolutionManager::testTornament));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestEvolutionManager>("Test new generation members",&TestEvolutionManager::testNewGenerationMembers));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestEvolutionManager>("Test exit score",&TestEvolutionManager::testExitScore));

		return suiteOfTests;
	}

protected:
	void testDefaultConstructor() {
		std::cerr << "EvolutionManager:\t" <<  __func__ << std::endl;
		EvolutionManager em;
		CPPUNIT_ASSERT(true);
	}

	void testTornament() {
		std::cerr << "EvolutionManager:\t" <<  __func__ << std::endl;
		EvolutionManager em;
		int one , two , three , four;
		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/testSinx"));
		gm.populationManager->generateRequired();
		gm.populationManager->scoreAllVecRpn();
		gm.populationManager->sortByScore();

		one   = em.tournament(40);
		two   = em.tournament(40);
		three = em.tournament(100);
		four  = em.tournament(200);
		CPPUNIT_ASSERT(one >= 0);
		CPPUNIT_ASSERT(one < 40);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(one).score < gm.populationManager->populationlist.v.at(81).score);
		CPPUNIT_ASSERT(two >= 0);
		CPPUNIT_ASSERT(two < 40);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(two).score < gm.populationManager->populationlist.v.at(81).score);
		CPPUNIT_ASSERT(three >=0);
		CPPUNIT_ASSERT(three < 100);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(three).score < gm.populationManager->populationlist.v.at(201).score);
		CPPUNIT_ASSERT(four >= 0);
		CPPUNIT_ASSERT(four <200);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(four).score < gm.populationManager->populationlist.v.at(501).score);
	}

	void testMutateSingleNode() {
		std::cerr << "EvolutionManager:\t" <<  __func__ << std::endl;
		EvolutionManager em;
		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/medium_test_case"));
		PopulationMember p;
		p.createSelf("TestCase",3);
		for (int x = 0; x < 10; ++x) {
			gm.populationManager->populationlist.add(p);
			gm.populationManager->scoreOneMember(x);

		}
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 10);
		gm.populationManager->sortByScore();
		for (int x = 0; x < 10; ++x) {
			em.mutateSingleNode(5,10);
			gm.populationManager->scoreOneMember(gm.populationManager->populationlist.v.size()-1);
		}
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 60);
		// Score the new members
		for (int x = 0; x < 60; ++x) {
			gm.populationManager->scoreOneMember(x);
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(x).score != 0);
			// No Size change should have been possible so we can check that too
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(x).rpnNodeVec.size() == p.rpnNodeVec.size());
		}
		gm.populationManager->sortByScore();

	}

	void testMutateNodeTree() {
		std::cerr << "EvolutionManager:\t" <<  __func__ << std::endl;
		EvolutionManager em;
		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/medium_test_case"));
		PopulationMember p;
		p.createSelf("TestCase",3);
		for (int x = 0; x < 10; ++x) {
			gm.populationManager->populationlist.add(p);
			gm.populationManager->scoreOneMember(x);

		}
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 10);
		gm.populationManager->sortByScore();
		for (int x = 0; x < 10; ++x) {
			em.mutateNodeTree(5,10);
			gm.populationManager->scoreOneMember(gm.populationManager->populationlist.v.size()-1);
		}
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 60);
		// Score the new members
		for (int x = 0; x < 60; ++x) {
			gm.populationManager->scoreOneMember(x);
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(x).score != 0);
			// No Size change should have been possible so we can check that too
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(x).rpnNodeVec.size() >= 2);
		}
		gm.populationManager->sortByScore();
	}

	void testCutNodeTree() {
		std::cerr << "EvolutionManager:\t" <<  __func__ << std::endl;

		EvolutionManager em;
		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/medium_test_case"));
		PopulationMember p;
		p.createSelf("TestCase",3);
		for (int x = 0; x < 10; ++x) {
			gm.populationManager->populationlist.add(p);
			gm.populationManager->scoreOneMember(x);

		}
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 10);
		gm.populationManager->sortByScore();
		for (int x = 0; x < 10; ++x) {
			em.cutNodeTree(5,10);
			gm.populationManager->scoreOneMember(gm.populationManager->populationlist.v.size()-1);
		}
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 60);
		// Score the new members
		for (int x = 0; x < 60; ++x) {
			gm.populationManager->scoreOneMember(x);
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(x).score != 0);
			// No Size change should have been possible so we can check that too
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(x).rpnNodeVec.size() >= 2);
		}
		gm.populationManager->sortByScore();
	}

	void testCrossover() {
		std::cerr << "EvolutionManager:\t" <<  __func__ << std::endl;

		EvolutionManager em;
		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/medium_test_case"));
		PopulationMember p;
		p.createSelf("TestCase",3);
		for (int x = 0; x < 10; ++x) {
			gm.populationManager->populationlist.add(p);
			gm.populationManager->scoreOneMember(x);

		}
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 10);
		gm.populationManager->sortByScore();
		for (int x = 0; x < 10; ++x) {
			em.crossover(5,10);
			gm.populationManager->scoreOneMember(gm.populationManager->populationlist.v.size()-1);
		}
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 60);
		// Score the new members
		for (int x = 0; x < 60; ++x) {
			gm.populationManager->scoreOneMember(x);
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(x).score != 0);
			// No Size change should have been possible so we can check that too
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(x).rpnNodeVec.size() >= 2);
		}
		gm.populationManager->sortByScore();
	}

	void testCrossoverNewRoot() {
		std::cerr << "EvolutionManager:\t" <<  __func__ << std::endl;
		EvolutionManager em;
		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/medium_test_case"));
		for (int x = 0; x < 10; ++x) {
			PopulationMember p;
			p.createSelf("TestCase",3);
			gm.populationManager->populationlist.add(p);
			gm.populationManager->scoreOneMember(x);
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(x).rpnNodeVec.size() >= 3);
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(x).score != 0);

		}
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 10);
		em.crossoverNewRoot(10,10);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 20);
		// Now check our new members
		for (int x = 10; x < 20; ++x) {
			gm.populationManager->scoreOneMember(x);
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(x).rpnNodeVec.size() >= 3);
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(x).score != 0);
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(x).method == "CrossNewR");

		}

	}

	void testDeleteTreeBranch() {
		std::cerr << "EvolutionManager:\t" <<  __func__ << std::endl;
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/medium_test_case"));
		// Check we can cleanly delete a whole node tree
		PopulationMember p;
		p.createSelf("TestCase",4);
		CPPUNIT_ASSERT(p.rpnNodeVec.size() > 1);
		gm.evolutionManager->deleteTreeBranch(0,p.rpnNodeVec);
		CPPUNIT_ASSERT(p.rpnNodeVec.size() == 0);
	}

	void testMakeNodeTree() {
		std::cerr << "EvolutionManager:\t" <<  __func__ << std::endl;
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/medium_test_case"));
		PopulationMember p;

		CPPUNIT_ASSERT(p.rpnNodeVec.size() == 0);
		gm.evolutionManager->makeNodeTree(2,false,p.rpnNodeVec);
		CPPUNIT_ASSERT(p.rpnNodeVec.size() >= 1);
		gm.populationManager->populationlist.v.clear();
		gm.populationManager->populationlist.add(p);
		gm.populationManager->scoreOneMember(0);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).score > 0);

	}

	void testCopyNodeTree() {
		std::cerr << "EvolutionManager:\t" <<  __func__ << std::endl;
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/medium_test_case"));
		PopulationMember p;
		p.createSelf("TestCase",3);
		PopulationMember p2;
		gm.evolutionManager->copyNodeTree(0,0,p2.rpnNodeVec,p.rpnNodeVec);
		CPPUNIT_ASSERT(p.rpnNodeVec.size() > 1);
		CPPUNIT_ASSERT(p.rpnNodeVec.size() == p2.rpnNodeVec.size());
		for (unsigned x = 0; x < p.rpnNodeVec.size(); x++) {
			CPPUNIT_ASSERT(p.rpnNodeVec.at(x).isTerminal == p2.rpnNodeVec.at(x).isTerminal);
			if(p.rpnNodeVec.at(x).isTerminal ) {
				CPPUNIT_ASSERT(p.rpnNodeVec.at(x).tNo == p2.rpnNodeVec.at(x).tNo);
			} else {
				CPPUNIT_ASSERT(p.rpnNodeVec.at(x).fNo == p2.rpnNodeVec.at(x).fNo );
				CPPUNIT_ASSERT(p.rpnNodeVec.at(x).fInputs == p2.rpnNodeVec.at(x).fInputs );
			}
		}
	}

	void testRunGenerations() {
		std::cerr << "EvolutionManager:\t" <<  __func__ << std::endl;
		gm.populationManager->populationlist.v.clear();
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/medium_test_case"));
		gm.settings->FITNESS_CASE_FILE = "fitness_cases/medium_test_case";
		gm.populationManager->removeMembersFromDisk();

		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		gm.evolutionManager->runGenerations(10);

		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == gm.settings->POPULATION);
		gm.populationManager->scoreAllVecRpn(); // Score what falls off the end
		for (unsigned x = 0; x < gm.settings->POPULATION; x++) {

			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(x).score > 0);
			if (gm.populationManager->populationlist.v.at(x).rpnNodeVec.size() < 2) {
				std::cout << x << std::endl;
				std::cout << gm.populationManager->populationlist.v.at(x).method << std::endl;
			}
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(x).rpnNodeVec.size() > 1);
		}
		gm.populationManager->removeMembersFromDisk();
		gm.jsonConfig->updateSettings(gm.settings);
	}



	void testNewGenerationMembers() {
		std::cerr << "EvolutionManager:\t" <<  __func__ << std::endl;
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/medium_test_case"));


		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/medium_test_case"));

		gm.evolutionManager->runGenerations(1);

		// Delete the keep percent we have at the top
		unsigned keep  = (gm.settings->POPULATION - (gm.settings->POPULATION * (gm.settings->KEEP_TOP_PERCENT / 100.0)));
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == gm.settings->POPULATION);
		gm.populationManager->populationlist.v.erase(gm.populationManager->populationlist.v.begin(),gm.populationManager->populationlist.v.begin() + gm.settings->POPULATION-keep);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == keep);


		testMethod = "Crossover";
		int crossoverCreated   = std::count_if(gm.populationManager->populationlist.v.begin(),gm.populationManager->populationlist.v.end(),memberMethodEqual );
		testMethod = "Mut Node";
		int mutNodeCreated	   = std::count_if(gm.populationManager->populationlist.v.begin(),gm.populationManager->populationlist.v.end(),memberMethodEqual );
		testMethod = "Mut Tree";
		int mutTreeCreated	   = std::count_if(gm.populationManager->populationlist.v.begin(),gm.populationManager->populationlist.v.end(),memberMethodEqual );
		testMethod = "Cut Tree";
		int cutTreeCreated	   = std::count_if(gm.populationManager->populationlist.v.begin(),gm.populationManager->populationlist.v.end(),memberMethodEqual );
		testMethod = "CrossNewR";
		int crossoverBrCreated = std::count_if(gm.populationManager->populationlist.v.begin(),gm.populationManager->populationlist.v.end(),memberMethodEqual );
		testMethod = "grow";
		int growMembers        = std::count_if(gm.populationManager->populationlist.v.begin(),gm.populationManager->populationlist.v.end(),memberMethodEqual );
		testMethod = "fill";
		int fillMembers        = std::count_if(gm.populationManager->populationlist.v.begin(),gm.populationManager->populationlist.v.end(),memberMethodEqual );

		CPPUNIT_ASSERT(growMembers == 0);
		CPPUNIT_ASSERT(fillMembers == 0);

		CPPUNIT_ASSERT(crossoverCreated == (int)(keep * ( gm.settings->CROSSOVER_PERCENT / 100.0)));
		CPPUNIT_ASSERT(mutNodeCreated == (int)(keep * ( gm.settings->MUTATE_NODE_PERCENT / 100.0)));
		CPPUNIT_ASSERT(mutTreeCreated == (int)(keep * ( gm.settings->MUTATE_TREE_PERCENT / 100.0)));
		CPPUNIT_ASSERT(cutTreeCreated == (int)(keep * ( gm.settings->CUT_TREE_PERCENT / 100.0)));
		CPPUNIT_ASSERT(crossoverBrCreated == (int)(keep * (gm.settings-> CROSSOVER_NEW_ROOT_PERCENT / 100.0)));
		CPPUNIT_ASSERT((unsigned)(crossoverCreated + crossoverBrCreated + mutNodeCreated + mutTreeCreated + cutTreeCreated) == keep);


	}

	void testExitScore() {
		std::cerr << "EvolutionManager:\t" <<  __func__ << std::endl;

		gm.populationManager->populationlist.v.clear();
		gm.fitnessCases->clear();
		gm.settings->FITNESS_CASE_FILE = "fitness_cases/testSinx_20c";
		gm.populationManager->removeMembersFromDisk();
		CPPUNIT_ASSERT(remove( "unit-test-nodetree.0" ) != 0);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/testSinx_20c"));
		CPPUNIT_ASSERT(gm.settings->EXIT_SCORE == 0);
		gm.settings->EXIT_SCORE = 30;
		CPPUNIT_ASSERT(gm.settings->EXIT_SCORE == 30);
		gm.evolutionManager->runGenerations(20);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).score < gm.settings->EXIT_SCORE);
		gm.populationManager->removeMembersFromDisk();
	}

};


#endif
