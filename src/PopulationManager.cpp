/*
 * PopulationManager.cpp
 *
 *  Created on: 4 May 2013
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


#include <omp.h>
#include "PopulationManager.h"


// This is what sorts the populationlist array by their scores
struct sort_pop_member_by_score
{
    inline bool operator() (PopulationMember struct1,PopulationMember struct2)
    {
    	return (struct1.score < struct2.score);
    }
};

PopulationManager::PopulationManager() : pos(0), cutScore(-1), missedCut(0) {}

PopulationManager::~PopulationManager() { }


// Generate population members up to the required number
void PopulationManager::generateRequired() {
	int missing = gm.settings->POPULATION - populationlist.v.size();
#pragma omp parallel
	{
#pragma omp for schedule(dynamic) nowait
		for (int x = 0; x < missing; x++) {
			if (x < (missing / 2)) {
				populationlist.add(PopulationMember("fill",gm.settings->INITIAL_MAX_DEPTH));
			} else {
				populationlist.add(PopulationMember("grow",gm.settings->INITIAL_MAX_DEPTH));
			}
		}
		if (missing > 0 ) {
			//printf(" * Generated %d new population members. \n",missing);
		}
	}
}


// Ask the population member at position (memberid) to solve a single caseset
// Used to get the program to give its solution to a single input
double PopulationManager::solveVecCaseSet(int memberid) {
	return populationlist.v.at(memberid).rpnVecSolveSelf(&gm.fitnessCases->cliCase[0]);

}


// Score the member of the population at position x
void PopulationManager::scoreOneMember(int memberid) {
	double total_away = 0.0;
	bool scaling = gm.fitnessCases->SCALING_ENABLED;
	if ( populationlist.v.at(memberid).hasChanged ) {
		// Loop all fitness cases
		for (unsigned int y = 0; y < gm.fitnessCases->TOTAL_CASES; y++) {
			double score = gm.errorFunction( populationlist.v[memberid].rpnVecSolveSelf( &gm.fitnessCases->cases[y][0]) - gm.fitnessCases->targets[y]);
			if (scaling) {
				score *= gm.fitnessCases->multipliers[y];
			}
			total_away += score;
		}
		// Assign the score to the population member
		populationlist.v.at(memberid).setScore(total_away);
	}
}


// Score the entire population
void PopulationManager::scoreAllVecRpn() {
	if (gm.settings->USE_CUT_SCORING) {
		missedCut = 0;
	}
	bool scaling = gm.fitnessCases->SCALING_ENABLED;
#pragma omp parallel
	{
#pragma omp for schedule(dynamic) nowait
		for ( unsigned int x = 0; x < gm.settings->POPULATION; x ++) {
			if ( populationlist.v.at(x).hasChanged ) {
				double total_away = 0.0;
				// Loop all fitness cases
				for (unsigned int y = 0; y < gm.fitnessCases->TOTAL_CASES; y++) {
					double score = gm.errorFunction(populationlist.v[x].rpnVecSolveSelf( &gm.fitnessCases->cases[y][0]) - gm.fitnessCases->targets[y]);

					if (scaling) {
						score *= gm.fitnessCases->multipliers[y];
					}
					total_away += score;

					if (gm.settings->USE_CUT_SCORING && cutScore > 0) { // Every 25 loops check if we can bin
						if (total_away > cutScore) {
							missedCut += 1;
							break;
						}
					}
				}
				// Assign the score to the population member
				populationlist.v.at(x).setScore(total_away);
			}
		}
	}
}


void PopulationManager::sortByScore() {
	// Have overloaded operator< to make this fast
	std::sort(populationlist.v.begin(),populationlist.v.end());
}


// Remove the worst score members from the populatuion
void PopulationManager::cullWeak(){
	int num_to_murder = gm.settings->POPULATION * ((100 - gm.settings->KEEP_TOP_PERCENT) / 100.0);
	populationlist.v.resize(gm.settings->POPULATION - num_to_murder);

	// The last members score is the 'cut' mark
	if (gm.settings->USE_CUT_SCORING) {
		cutScore = populationlist.v.back().score;
	}
}


// Add the programs constants into the save file
void PopulationManager::addConstantsToFile(std::ofstream * writefile) {
	if (gm.fitnessCases->NUM_CONSTS != 0 ) {
		writefile->precision(20);
		*writefile << "CONSTANTS ";
		for (unsigned x = 0; x < gm.fitnessCases->NUM_CONSTS; ++x) {
			*writefile << "+" << gm.fitnessCases->cp.constantSet.at(x);
		}
		*writefile << "|" << std::endl;
	}
}


// Add the nodes from the tree into the file
void PopulationManager::addNodesToFile(int population_member_id, std::ofstream * writefile, int depth) {
	for(int x = 0; x < depth; x ++ ) {
		*writefile<<".";
	}
	pos ++;
	Node n = populationlist.v.at(population_member_id).rpnNodeVec.at(pos);
	// Write this node to file and go through it children
	if(n.isTerminal) {
		*writefile<<"T:"<<n.tNo<<"|"<<std::endl;
		if(n.tNo > gm.fitnessCases->TERMINALS) {
			std::cout << "FOUND BAD TERMINAL NUMBER: " << n.tNo << std::endl;
			std::cout << "CREATED BY: " << populationlist.v.at(population_member_id).method << std::endl;
			exit(10);
		}
	} else {
		if (n.fNo == -1) {
			*writefile<<"F:"<<n.fNo<<"| ROOT WITH("<< n.fInputs << ") inputs" <<std::endl;
		} else {
			*writefile<<"F:"<<n.fNo<<"| "<< gm.nodeManager->functionlist.at(n.fNo).name  <<std::endl;
		}
		for(unsigned int x = 0; x < n.fInputs;x++) {
			addNodesToFile(population_member_id,writefile,depth +1);
		}
	}
}


// Takes a population member and writes its node tree to disk.
void PopulationManager::writeMembersToDisk() {
	for (unsigned int x = 0; x < gm.settings->SAVE_TOTAL; x++) {
		char filename[100];
		std::ofstream writefile;
		sprintf(filename,"%s.%d",gm.settings->SAVE_FILE_PREFIX.c_str(),x);
		writefile.open(filename);
		writefile << "#\n# Generated Node Tree from " << gm.settings->FITNESS_CASE_FILE << "\n";
		writefile << "# This Tree scored: " << populationlist.v.at(x).score << "\n";
		writefile << "# Total Nodes: " << populationlist.v.at(x).rpnNodeVec.size() << "\n";
		writefile << "FUNCTION_SET: " << gm.settings->FUNCTION_SET << "\n";
		pos = -1;
		addConstantsToFile(&writefile);
		addNodesToFile(x,&writefile,0);
		writefile.close();
	}
}

void PopulationManager::removeMembersFromDisk() {
	for (unsigned int x = 0; x < gm.settings->SAVE_TOTAL; x++) {
			char filename[100];
			std::ofstream writefile;
			sprintf(filename,"%s.%d",gm.settings->SAVE_FILE_PREFIX.c_str(),x);
			remove(filename);
		}
}


// Save the current programs estimates to file
void PopulationManager::writeGuesses() {
    std::ofstream guesses_out;
    guesses_out.open(gm.settings->GUESSES_FILE.c_str());
	guesses_out<<"#\n# Generated Node tree from " << gm.settings->FITNESS_CASE_FILE << ".\n";
	guesses_out<<"# This tree scored: "<< populationlist.v.at(0).score << std::endl;
	guesses_out<<"# Total Nodes: "<< populationlist.v.at(0).rpnNodeVec.size()<< std::endl;
	char line[100];
	for (unsigned int x = 0; x < gm.fitnessCases->TOTAL_CASES; x++) {
		double result = populationlist.v[0].rpnVecSolveSelf( &gm.fitnessCases->cases[x][0]);
		sprintf(line,"Case: %-4d ",x);
		guesses_out << line;
		sprintf(line,"\tTarget: %-6f \tResult: %-6f",gm.fitnessCases->targets[x],result);
		guesses_out << line;
		guesses_out << std::endl;
	}
}


void PopulationManager::loadMemberFromFilename(const char * filename) throw(ConfigException) {
	std::ifstream loadfile(filename);
	std::vector<Node> rpn_node_vec;
	if (loadfile) {
		// read the file by line and build nodes:
		for( std::string line; getline( loadfile, line ); ) {
			std::string nodedef;
			std::stringstream stream(line);
			int part = 0;
			int depth;
			// Split the lines by the '|' which I chose as a delimiter between node definition and notes
			while( getline(stream, nodedef, '|') ) {
				// We only need the node side section
				if (part == 0) {
					// If we are not at a comment line, we need to make a node!
					if ( nodedef.at(0) != '#' ) {
						if (nodedef.at(0) == 'C' ) {
							std::string constants = nodedef.replace(0,11,"");
							std::string c;
							std::vector<double> savedConstants;
							std::istringstream constantStream(constants);
							while ( getline(constantStream,c,'+')) {
								double tmp = atof(c.c_str());
								savedConstants.push_back(tmp);
							}

							ConstantPool cp(savedConstants);
							gm.fitnessCases->updateConstantSet(cp);
						} else if (nodedef.at(0) == 'F' && nodedef.at(1) == 'U') {
							// We just need to check this function set is the same as the one the config loaded
							// This must quietly change to the correct function set, so if we are solving
							// we do not pollute the output with a message
							std::string functionSet = nodedef.replace(0,14,"");
							functionSet.erase(std::remove(functionSet.begin(), functionSet.end(), '\n'), functionSet.end());
							if (functionSet != gm.settings->FUNCTION_SET) {
								gm.settings->FUNCTION_SET.assign(functionSet);
								gm.nodeManager->initFunctions();
							}

						} else {
							// Now delete the '.'s
							depth = std::count(nodedef.begin(), nodedef.end(), '.');
							if (depth > 0) { for (int y =0; y < depth; y ++) { nodedef.erase(0,1); } }
							int number = atoi(nodedef.substr(2,3).c_str());
							if (nodedef.at(0) == 'F') {
								if (number == -1) {
									rpn_node_vec.push_back(Node(1,true));
								} else {
									rpn_node_vec.push_back(Node(gm.nodeManager->getFunctionByNum(number)));
								}
							} else {
								rpn_node_vec.push_back(Node(number));
							}
						}
					}
				}
				part ++;
			}
		}

		// Make this into a populatiom member and put it on the pile
		PopulationMember p;
		p.rpnNodeVec = rpn_node_vec;
		p.method = "Saved";
		p.hasChanged = true;
		populationlist.add(p);
	}
}

void PopulationManager::loadMembersFromDisk() throw(ConfigException) {
	for (unsigned int x = 0; x < gm.settings->LOAD_TOTAL; x++) {
		char filename[100];
		sprintf(filename,"%s.%d",gm.settings->SAVE_FILE_PREFIX.c_str(),x);
		std::ifstream loadfile(filename);
		std::vector<Node> rpn_node_vec;
		if (loadfile) {
			loadMemberFromFilename(filename);
		}
	}
}


