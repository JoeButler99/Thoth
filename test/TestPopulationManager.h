/*
 * TestPopulationManager.h
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

#ifndef TESTPOPULATIONMANAGER_H_
#define TESTPOPULATIONMANAGER_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>
#include <math.h>
#include <cerrno>
#include "../src/Function.h"
#include "../src/PopulationMember.h"
#include "../src/PopulationManager.h"


class TestPopulationManager : public CppUnit::TestFixture {
public:
	TestPopulationManager(){}
	virtual ~TestPopulationManager(){}

	static CppUnit::Test *suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestPopulationManager");

		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationManager>("Test Default Constructor",&TestPopulationManager::testDefaultConstructor));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationManager>("Test Generate Required",&TestPopulationManager::testGenerateRequired));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationManager>("Test score all rpn vec",&TestPopulationManager::testScoreAllVecRpn));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationManager>("Test score all rpn vec with Scaling",&TestPopulationManager::testScoreAllVecScalingEnabled));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationManager>("Test sort by score",&TestPopulationManager::testSortByScore));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationManager>("Test Cull weak",&TestPopulationManager::testCullWeak));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationManager>("Test write members to disk",&TestPopulationManager::testWriteMembersToDisk));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationManager>("Test write guesses",&TestPopulationManager::testWriteGuesses));
		//suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationManager>("Test add node to file",&TestPopulationManager::testAddNodesToFile));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationManager>("Test AddConstantsToFile",&TestPopulationManager::testAddConstantsToFile));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationManager>("Test load members from disk",&TestPopulationManager::testLoadMembersFromDisk));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationManager>("Test load members from filename",&TestPopulationManager::testLoadMemberFromFilename));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationManager>("Test score one member",&TestPopulationManager::testScoreOneMember));
		suiteOfTests->addTest(new CppUnit::TestCaller<TestPopulationManager>("Test solve vec case set",&TestPopulationManager::testSolveVecCaseSet));

		return suiteOfTests;
	}
protected:
	void testDefaultConstructor() {
		std::cerr << "PopulationManager:\t" <<  __func__ << std::endl;
		PopulationManager pm;
		CPPUNIT_ASSERT(true);
	}

	void testGenerateRequired() {
		std::cerr << "PopulationManager:\t" <<  __func__ << std::endl;
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);


		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/testSinx"));
		gm.populationManager->generateRequired();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == gm.settings->POPULATION);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).rpnNodeVec.at(0).fInputs == 1);

		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/large_test_case"));
		gm.populationManager->populationlist.v.clear();
		gm.populationManager->generateRequired();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == gm.settings->POPULATION);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).rpnNodeVec.at(0).fInputs == 1);


	}

	void testScoreAllVecRpn() {
		std::cerr << "PopulationManager:\t" <<  __func__ << std::endl;
		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/testSinx"));
		gm.populationManager->generateRequired();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == gm.settings->POPULATION);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).rpnNodeVec.at(0).fInputs == 1);
		gm.populationManager->scoreAllVecRpn();

		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).score  != 0.0);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).score  != -1);
	}

	void testScoreAllVecScalingEnabled() {
		std::cerr << "PopulationManager:\t" <<  __func__ << std::endl;

		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/large_test_case"));
		gm.populationManager->generateRequired();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == gm.settings->POPULATION);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).rpnNodeVec.at(0).fInputs == 1);
		gm.populationManager->scoreAllVecRpn();

		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).score  != 0.0);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).score  != -1);
	}


	void testSortByScore() {
		std::cerr << "PopulationManager:\t" <<  __func__ << std::endl;

		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/testSinx"));
		gm.populationManager->generateRequired();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == gm.settings->POPULATION);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).rpnNodeVec.at(0).fInputs == 1);
		gm.populationManager->scoreAllVecRpn();
		double start_score = gm.populationManager->populationlist.v.at(0).score;
		gm.populationManager->sortByScore();
		CPPUNIT_ASSERT( start_score > 0);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == gm.settings->POPULATION);



		// Now test the scores are ascending
		double last = 0;
		for (unsigned x = 0; x < gm.populationManager->populationlist.v.size(); x++) {
			if (x == 0) { last = gm.populationManager->populationlist.v.at(x).score; }
			else {CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(x).score >= last);}
		}
	}

	void testCullWeak() {
		std::cerr << "PopulationManager:\t" <<  __func__ << std::endl;

		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/testSinx"));
		gm.populationManager->generateRequired();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == gm.settings->POPULATION);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).rpnNodeVec.at(0).fInputs == 1);
		gm.populationManager->scoreAllVecRpn();
		double start_score = gm.populationManager->populationlist.v.at(0).score;
		gm.populationManager->sortByScore();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).score  != start_score);

		gm.populationManager->cullWeak();

		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == gm.settings->POPULATION * (gm.settings->KEEP_TOP_PERCENT / 100.0));
	}

	void testAddConstantsToFile() {
		std::cerr << "PopulationManager:\t" <<  __func__ << std::endl;
		std::string saveName = "test/constants.txt";
		std::string contents;

		// Delete the old file
		remove(saveName.c_str());
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/large_test_case_20c"));
		std::ofstream writefile;
		writefile.open(saveName.c_str());
		gm.populationManager->addConstantsToFile(&writefile);

		// Check we can read the file
		std::ifstream ifile(saveName.c_str());
		CPPUNIT_ASSERT(ifile);

		std::string line;
		int lines = 0;
		for (lines = 0; std::getline(ifile, line); ++lines)
		    ;
		CPPUNIT_ASSERT(lines = 1);
		ifile.close();
		writefile.close();
		contents = get_file_contents(saveName.c_str());
		CPPUNIT_ASSERT(contents.substr(0,15) != "CONSTANTS |1|2|");

		// Now check that we can get some of the right constants in place
		double vals[20]  = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
		std::vector<double> testVars(vals,vals+20);
		ConstantPool cp(1000,-1000,testVars);
		gm.fitnessCases->updateConstantSet(cp);
		remove(saveName.c_str());
		writefile.open(saveName.c_str());
		gm.populationManager->addConstantsToFile(&writefile);
		contents = get_file_contents(saveName.c_str());
		CPPUNIT_ASSERT(contents.substr(0,15) == "CONSTANTS +1+2+");

		ifile.close();
		writefile.close();
		remove(saveName.c_str());

	}



	void testWriteMembersToDisk() {
		std::cerr << "PopulationManager:\t" <<  __func__ << std::endl;

		gm.settings->SAVE_FILE_PREFIX = "testCaseMember";
		gm.populationManager->removeMembersFromDisk();

		// Generate members
		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/testSinx"));
		gm.populationManager->generateRequired();
		gm.populationManager->scoreAllVecRpn();
		gm.populationManager->sortByScore();

		// Save and test members
		gm.settings->SAVE_FILE_PREFIX = "testCaseMember";
		gm.populationManager->writeMembersToDisk();
		for (unsigned x = 0; x < 5; x++) {
			char saveName[50];
			sprintf(saveName,"%s.%d","testCaseMember",x);
			std::ifstream ifile(saveName);
			CPPUNIT_ASSERT(ifile);
			unsigned lines = std::count(std::istreambuf_iterator<char>(ifile), std::istreambuf_iterator<char>(), '\n');
			CPPUNIT_ASSERT(lines == gm.populationManager->populationlist.v.at(x).rpnNodeVec.size() + 5);
			CPPUNIT_ASSERT(remove(saveName) == 0);
		}
	}

	void testWriteGuesses() {
		std::cerr << "PopulationManager:\t" <<  __func__ << std::endl;

		gm.populationManager->populationlist.v.clear();
		// First remove anything which may be laying around
		remove(gm.settings->GUESSES_FILE.c_str());
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/testSinx"));
		// Create a member to score
		gm.populationManager->generateRequired();
		gm.populationManager->scoreAllVecRpn();
		gm.populationManager->writeGuesses();

		std::ifstream ifile(gm.settings->GUESSES_FILE.c_str());
		CPPUNIT_ASSERT(ifile);
		unsigned lines = std::count(std::istreambuf_iterator<char>(ifile), std::istreambuf_iterator<char>(), '\n');
		CPPUNIT_ASSERT(lines == gm.fitnessCases->TOTAL_CASES + 4); // One for each case + the program header
		ifile.close();

		CPPUNIT_ASSERT(remove(gm.settings->GUESSES_FILE.c_str()) == 0); // If we can't remove the previous loop didnt work properly
	}


	void testLoadMembersFromDisk() {
		std::cerr << "PopulationManager:\t" <<  __func__ << std::endl;
		// First we need to create and save nodetrees
		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		gm.fitnessCases->clear();

		gm.settings->SAVE_FILE_PREFIX = "testCaseMember";


		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/testSinx"));
		gm.populationManager->generateRequired();
		gm.populationManager->scoreAllVecRpn();
		gm.populationManager->sortByScore();
		gm.populationManager->writeMembersToDisk();
		unsigned sizes[gm.settings->SAVE_TOTAL];
		for (unsigned x = 0; x < gm.settings->SAVE_TOTAL; x++) {
			sizes[x] = gm.populationManager->populationlist.v.at(x).rpnNodeVec.size();
			CPPUNIT_ASSERT(sizes[x] >= 2);
		}
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == gm.settings->POPULATION);
		double scores[5] = {gm.populationManager->populationlist.v.at(0).score, gm.populationManager->populationlist.v.at(1).score,gm.populationManager->populationlist.v.at(2).score,gm.populationManager->populationlist.v.at(3).score,gm.populationManager->populationlist.v.at(4).score};
		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);


		// Now load and test them
		gm.populationManager->loadMembersFromDisk();

		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 5);
		for (unsigned x = 0; x < gm.settings->LOAD_TOTAL; x++) {
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(x).rpnNodeVec.size() >= 2);
			CPPUNIT_ASSERT(sizes[x] == gm.populationManager->populationlist.v.at(x).rpnNodeVec.size());
			gm.populationManager->scoreOneMember(x);
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(x).score == scores[x]);

			char saveName[50];
			sprintf(saveName,"%s.%d","testCaseMember",x);
			CPPUNIT_ASSERT(remove(saveName) == 0);
		}
		gm.populationManager->removeMembersFromDisk();
		gm.jsonConfig->updateSettings(gm.settings);
	}

	void testLoadMemberFromFilename() {
		std::cerr << "PopulationManager:\t" <<  __func__ << std::endl;

		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/testSinx"));

		// Load in the saved test members
		for (unsigned x = 0; x < 5; x++) {
			char saveName[50];
			sprintf(saveName,"%s.%d","test/testCaseMember",x);
			std::ifstream ifile(saveName);
			CPPUNIT_ASSERT(ifile);
			gm.populationManager->loadMemberFromFilename(saveName);
			CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == x +1);
			gm.populationManager->scoreOneMember(x);
		}

		// Score them, we know what they should score when they saved
		CPPUNIT_ASSERT(fabs(gm.populationManager->populationlist.v.at(0).score - 19.2386 - (gm.settings->NODE_WEIGHT * gm.populationManager->populationlist.v.at(0).rpnNodeVec.size()) ) < 0.001);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).rpnNodeVec.size() == 12);
		CPPUNIT_ASSERT(fabs(gm.populationManager->populationlist.v.at(1).score - 33.5557 - (gm.settings->NODE_WEIGHT * gm.populationManager->populationlist.v.at(1).rpnNodeVec.size())) < 0.001);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(1).rpnNodeVec.size() == 5);
		CPPUNIT_ASSERT(fabs(gm.populationManager->populationlist.v.at(2).score - 33.5557 - (gm.settings->NODE_WEIGHT * gm.populationManager->populationlist.v.at(2).rpnNodeVec.size())) < 0.001);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(2).rpnNodeVec.size() == 5);
		CPPUNIT_ASSERT(fabs(gm.populationManager->populationlist.v.at(3).score - 32.5766 - (gm.settings->NODE_WEIGHT * gm.populationManager->populationlist.v.at(3).rpnNodeVec.size())) < 0.001);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(3).rpnNodeVec.size() == 8);
		CPPUNIT_ASSERT(fabs(gm.populationManager->populationlist.v.at(4).score - 35.3952 - (gm.settings->NODE_WEIGHT * gm.populationManager->populationlist.v.at(4).rpnNodeVec.size())) < 0.001);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(4).rpnNodeVec.size() == 8);
	}

	void testScoreOneMember() {
		std::cerr << "PopulationManager:\t" <<  __func__ << std::endl;

		gm.populationManager->populationlist.v.clear();
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/testSinx"));
		// Create a member to score
		PopulationMember p;
		p.createSelf("Test",2);
		CPPUNIT_ASSERT(p.hasChanged == true);
		double initial_score = p.score;
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		gm.populationManager->populationlist.add(p);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).score == initial_score);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).hasChanged == true);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 1);
		gm.populationManager->scoreOneMember(0);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).score != initial_score);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).hasChanged == false);


		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/medium_test_case"));
		PopulationMember p2;
		p2.createSelf("Test",2);
		CPPUNIT_ASSERT(p2.hasChanged == true);
		initial_score = p2.score;
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 1);
		gm.populationManager->populationlist.add(p2);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(1).score == initial_score);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(1).hasChanged == true);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 2);
		gm.populationManager->scoreOneMember(1);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(1).score != initial_score);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(1).hasChanged == false);


		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/large_test_case"));
		PopulationMember p3;
		p3.createSelf("Test",2);
		CPPUNIT_ASSERT(p3.hasChanged == true);
		initial_score = p3.score;
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 2);
		gm.populationManager->populationlist.add(p3);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(2).score == initial_score);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(2).hasChanged == true);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 3);
		gm.populationManager->scoreOneMember(2);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(2).score != initial_score);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(2).hasChanged == false);

	}

	void testSolveVecCaseSet() {
		std::cerr << "PopulationManager:\t" <<  __func__ << std::endl;

		gm.populationManager->populationlist.v.clear();
		gm.fitnessCases->clear();
		CPPUNIT_ASSERT(gm.fitnessCases->loadFile("fitness_cases/testSinx"));
		PopulationMember p;
		p.createSelf("Test",2);
		CPPUNIT_ASSERT(p.hasChanged == true);
		double initial_score = p.score;
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 0);
		gm.populationManager->populationlist.add(p);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).score == initial_score);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.at(0).hasChanged == true);
		CPPUNIT_ASSERT(gm.populationManager->populationlist.v.size() == 1);
		std::vector<double> test_input;
		test_input.push_back(7.5);
		gm.fitnessCases->cliCase	= test_input;
		double result = 99999;
		result = gm.populationManager->solveVecCaseSet(0);
		CPPUNIT_ASSERT(result != 99999);
	}


	std::string get_file_contents(const char *filename)
	{
	  std::ifstream in(filename, std::ios::in | std::ios::binary);
	  if (in)
	  {
	    std::string contents;
	    in.seekg(0, std::ios::end);
	    contents.resize(in.tellg());
	    in.seekg(0, std::ios::beg);
	    in.read(&contents[0], contents.size());
	    in.close();
	    return(contents);
	  }
	  throw(errno);
	}

};


#endif
