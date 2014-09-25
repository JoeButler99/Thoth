/*
 * EvolutionManager.cpp
 *
 *  Created on: 19 May 2013
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

#include "EvolutionManager.h"


EvolutionManager::EvolutionManager() : silence(false) {}
EvolutionManager::~EvolutionManager() {}

void EvolutionManager::deleteTreeBranch(int node_index,std::vector<Node> & node_tree ) {
	int members = node_tree.at(node_index).fInputs;
	node_tree.erase(node_tree.begin() + node_index);
	while (members > 0) {
		if (! node_tree.at(node_index).isTerminal ) {
			members += node_tree.at(node_index).fInputs;
		}
		node_tree.erase(node_tree.begin() + node_index);
		members --;
	}
}

// This adds to the node_tree. It cannot make a complete tree
void EvolutionManager::makeNodeTree(int depth,bool fill,std::vector<Node> & node_tree) {
	if (( depth == 0 ) || (!fill && (rng.iRand(100) % 5 == 0))){
		node_tree.push_back(Node(rng.iRand(gm.fitnessCases->TERMINALS)));
	} else {
		Node n(gm.nodeManager->giveRandFunction());
		node_tree.push_back(n);
		for (unsigned int x = 0; x < n.fInputs; x++) {
			makeNodeTree(depth -1,fill,node_tree);
		}
	}
}


// Copy a sub-nodetree from one tree into another
void EvolutionManager::copyNodeTree(int insert_index,int get_index,std::vector<Node> & into_node_tree,std::vector<Node> & from_node_tree ) {
	int members = from_node_tree.at(get_index).fInputs;
	into_node_tree.insert(into_node_tree.begin()+insert_index,from_node_tree.at(get_index));
	// increment the indexes
	insert_index ++; get_index ++;
	while (members > 0) {
		if (! from_node_tree.at(get_index).isTerminal ) {
			members += from_node_tree.at(get_index).fInputs;
		}
		// insert and increment the indexes
		into_node_tree.insert(into_node_tree.begin()+insert_index,from_node_tree.at(get_index));
		insert_index ++; get_index ++;
		members --; // one less member to add.
	}
}


// Crossover method to produce the next generation
void EvolutionManager::crossover(int num_needed, int pool_size) {
	gm.populationManager->populationlist.v.reserve(gm.populationManager->populationlist.v.size() + num_needed);
#pragma omp parallel
	{
#pragma omp for schedule(dynamic) nowait
		for (int x = 0; x < num_needed; x ++) {
			int parenta = tournament(pool_size);
			int parentb = tournament(pool_size);
			int nodea    = rng.iRand(1,gm.populationManager->populationlist.v.at(parenta).rpnNodeVec.size());
			int nodeb    = rng.iRand(1,gm.populationManager->populationlist.v.at(parentb).rpnNodeVec.size());

			// Start building the new RPN Vec
			std::vector<Node> new_rpn_vec(gm.populationManager->populationlist.v.at(parenta).rpnNodeVec);

			// Make the space for the new tree to be inserted
			if (! new_rpn_vec.at(nodea).isTerminal) {
				deleteTreeBranch(nodea,new_rpn_vec);
			} else {
				new_rpn_vec.erase(new_rpn_vec.begin() + nodea);
			}

			// Insert the tree from the other member into the space
			if (gm.populationManager->populationlist.v.at(parentb).rpnNodeVec.at(nodeb).isTerminal) {
				new_rpn_vec.insert(new_rpn_vec.begin() +nodea,gm.populationManager->populationlist.v.at(parentb).rpnNodeVec.at(nodeb) );
			} else {
				copyNodeTree(nodea,nodeb,new_rpn_vec,gm.populationManager->populationlist.v.at(parentb).rpnNodeVec);
			}

			// Assign the new member and put it into the population
			PopulationMember p(new_rpn_vec);
			p.hasChanged = true;
			p.method = "Crossover";
			gm.populationManager->populationlist.add(p);
		}
	}
}



// Creating a new root node, take a subtrees from chosen members to create a new member
// It is hoped that this method will encourage diverse members as it's an extra way to grow from the top of the tree
void EvolutionManager::crossoverNewRoot(int num_needed, int pool_size) {
	gm.populationManager->populationlist.v.reserve(gm.populationManager->populationlist.v.size() + num_needed);
#pragma omp parallel
	{
#pragma omp for schedule(dynamic) nowait
		for (int x = 0; x < num_needed; x ++) {
			// Create a new node vector
			std::vector<Node> new_rpn_vec;
			new_rpn_vec.push_back(Node(1,true));
			Node rootFunc(gm.nodeManager->giveRandFunction());
			new_rpn_vec.push_back(rootFunc);
			for (unsigned f = 0; f < rootFunc.fInputs; f++) {
				// Now we copy in a tree to fill each of this root functions inputs
				int parent = tournament(pool_size);
				int nodeId   = rng.iRand(1,gm.populationManager->populationlist.v.at(parent).rpnNodeVec.size());

				// Insert the tree from the other member into the space
				if (gm.populationManager->populationlist.v.at(parent).rpnNodeVec.at(nodeId).isTerminal) {
					new_rpn_vec.push_back(gm.populationManager->populationlist.v.at(parent).rpnNodeVec.at(nodeId));
				} else {
					copyNodeTree(new_rpn_vec.size(),nodeId,new_rpn_vec,gm.populationManager->populationlist.v.at(parent).rpnNodeVec);
				}
			}

			// Assign the new member and put it into the population
			PopulationMember p(new_rpn_vec);
			p.hasChanged = true;
			p.method = "CrossNewR";
			gm.populationManager->populationlist.add(p);
		}
	}
}



void EvolutionManager::cutNodeTree(int num_needed, int pool_size) {
	gm.populationManager->populationlist.v.reserve(gm.populationManager->populationlist.v.size() + num_needed);
	const unsigned minSize = 2;
#pragma omp parallel
	{
#pragma omp for schedule(dynamic) nowait
		for (int x = 0; x < num_needed; x ++) {
			std::vector<Node> new_rpn_vec(gm.populationManager->populationlist.v.at(tournament(pool_size)).rpnNodeVec);

			int edit_node;
			while (true) {
				if (new_rpn_vec.size() == minSize) {
					break;
				}
				edit_node = rng.iRand(1,new_rpn_vec.size());
				if (! new_rpn_vec.at(edit_node).isTerminal) { // Loop till we  get a function node
					// Delete the whole tree that exists for that function
					deleteTreeBranch(edit_node,new_rpn_vec);

					// insert a terminal node in that space
					Node n(rng.iRand(gm.fitnessCases->TERMINALS));
					new_rpn_vec.insert(new_rpn_vec.begin() + edit_node,n);
					break;
				}
			}
			// Assign the new member and put it into the population
			PopulationMember p(new_rpn_vec);
			p.hasChanged = true;
			p.method = "Cut Tree";
			gm.populationManager->populationlist.add(p);

		}
	}
}

void EvolutionManager::mutateNodeTree(int num_needed, int pool_size) {
	gm.populationManager->populationlist.v.reserve(gm.populationManager->populationlist.v.size() + num_needed);
#pragma omp parallel
	{
#pragma omp for schedule(dynamic) nowait
		for (int x = 0; x < num_needed; x ++) {
			// Copy the original RPN Vec, create a new member
			std::vector<Node> new_rpn_vec(gm.populationManager->populationlist.v.at(tournament(pool_size)).rpnNodeVec);
			int edit_node = rng.iRand(1,new_rpn_vec.size());

			// Now we generate a mini node tree which will be stitched into the new member
			std::vector<Node> new_tree;
			if (x < (num_needed / 2)) {
				makeNodeTree(gm.settings->MUTATE_TREE_MAX_DEPTH,true,new_tree);
			} else {
				makeNodeTree(gm.settings->MUTATE_TREE_MAX_DEPTH,false,new_tree);
			}

			// Now we build in the tree to the existing tree
			if (new_rpn_vec.at(edit_node).isTerminal) {
				new_rpn_vec.erase(new_rpn_vec.begin() + edit_node);
				for ( unsigned int y = 0; y < new_tree.size(); y ++) {
					new_rpn_vec.insert(new_rpn_vec.begin() + edit_node + y,new_tree.at(y));
				}
			} else {
				// If we start with a function we need to delete the tree that exists with it first.
				deleteTreeBranch(edit_node,new_rpn_vec);

				// Now we have removed any old tree, we can insert the new one
				for ( unsigned int y = 0; y < new_tree.size(); y ++) {
					new_rpn_vec.insert(new_rpn_vec.begin() + edit_node + y,new_tree.at(y));
				}
			}

			// Assign the new member and put it into the population
			PopulationMember p(new_rpn_vec);
			p.hasChanged = true;
			p.method = "Mut Tree";
			gm.populationManager->populationlist.add(p);
		}
	}
}

void EvolutionManager::mutateSingleNode(int num_needed, int pool_size) {
	// Make sure we have enough space in the population list vector
	gm.populationManager->populationlist.v.reserve(gm.populationManager->populationlist.v.size() + num_needed);

#pragma omp parallel
	{
#pragma omp for schedule(dynamic) nowait
		for (int x = 0; x < num_needed; x ++) {
			// Copy the original RPN Vec, create a new member
			PopulationMember p(gm.populationManager->populationlist.v.at(tournament(pool_size)).rpnNodeVec);
			int edit_node = rng.iRand(1,p.rpnNodeVec.size());

			// Make the change, depending on what we have
			if (p.rpnNodeVec.at(edit_node).isTerminal) {
				unsigned int new_t;
				while (true) {
					new_t = rng.iRand(gm.fitnessCases->TERMINALS);
					if (new_t != p.rpnNodeVec.at(edit_node).tNo) {
						break;
					}
				}
				p.rpnNodeVec.at(edit_node).tNo = new_t;
			} else {
				int new_f;
				while (true) {
					new_f = rng.iRand(gm.nodeManager->functionlist.size());
					if (new_f != p.rpnNodeVec.at(edit_node).fNo && gm.nodeManager->functionlist.at(new_f).inputs == p.rpnNodeVec.at(edit_node).fInputs) {
						break;
					}
				}
				p.rpnNodeVec.at(edit_node).fNo = gm.nodeManager->functionlist.at(new_f).mynum;
			}

			// Assign the new member and put it into the population
			p.hasChanged = true;
			p.method = "Mut Node";
			gm.populationManager->populationlist.add(p);

		}
	}
}

int EvolutionManager::tournament(int tornament_size) {
	//RNG - replaced below
	int a = rng.iRand(tornament_size);
	int b = rng.iRand(tornament_size);
	if(gm.populationManager->populationlist.v.at(a).score < gm.populationManager->populationlist.v.at(b).score) {
		return a;
	} else { return b; }
}


void EvolutionManager::runGenerations(unsigned gens) {
	// Do we need to try and load previous members
	if(gm.settings->LOAD_SAVED) {
		gm.populationManager->loadMembersFromDisk();
	}
	// Reset any cut score for the new generations - THis is really to help the test cases
	gm.populationManager->cutScore = 0;
	for (unsigned int x = 1; x <= gens; x++) {
		// Generate any missing and score the group
		gm.populationManager->generateRequired();
		gm.populationManager->scoreAllVecRpn();
		gm.populationManager->sortByScore();
		if (gm.populationManager->populationlist.v.at(0).score < gm.settings->EXIT_SCORE) {
			if (!silence) {
				std::cout << "EXIT SCORE REACHED! ( " << gm.settings->EXIT_SCORE << " )" << std::endl;
			}
			break;
		}
		gm.populationManager->cullWeak();
		// Check if we are to save any members this loop
		if(x % gm.settings->SAVE_EVERY == 0) {
			gm.populationManager->writeMembersToDisk();
		}
		// Create the new generation
		int missing   = gm.settings->POPULATION - gm.populationManager->populationlist.v.size();
		int pool_size = gm.populationManager->populationlist.v.size();
		mutateSingleNode((int)((missing / 100.0) * gm.settings->MUTATE_NODE_PERCENT),pool_size);
		mutateNodeTree((int)((missing / 100.0) * gm.settings->MUTATE_TREE_PERCENT),pool_size);
		cutNodeTree((int)((missing / 100.0) * gm.settings->CUT_TREE_PERCENT),pool_size);
		crossover((int)((missing / 100.0) * gm.settings->CROSSOVER_PERCENT),pool_size);
		crossoverNewRoot((int)((missing / 100.0) * gm.settings->CROSSOVER_NEW_ROOT_PERCENT),pool_size);

		// Generation Update
		if (!silence) {
			if (x % gm.settings->SHOW_HEADINGS_EVERY == 0 || x == 1) {
				printf("\n\e[1;34m%-10s%-8s%-8s%-14s%-12s%-12s%-14s%-12s\e[0m\n\n","Time","Gen","Pop","BestScore","CreatedBy","Tree Size", "Cut Score", "Total Cut");
			}
		}
		time_t tim;  //create variable of time_t
		time(&tim); //pass variable tim to time function
		char mbstr[100];
		strftime(mbstr, 100, "%H:%M:%S", localtime(&tim));

		if (!silence) {
			printf("%-10s%-8d%-8lu%-14f%-12s%-12lu%-14f%-12d\n",mbstr,x,gm.populationManager->populationlist.v.size(),gm.populationManager->populationlist.v.at(0).score,gm.populationManager->populationlist.v.at(0).method.c_str(),gm.populationManager->populationlist.v.at(0).rpnNodeVec.size(),gm.populationManager->cutScore,gm.populationManager->missedCut);
		}

		// Guesses Output
		if (x % gm.settings->GUESSES_EVERY == 0) {
			gm.populationManager->writeGuesses();
		}

		// Optimiser Loop - Ask the optimiser if it wants to do anything
		gm.optimiser->optimise(x,gm.settings->SAVE_AFTER_EACH_OPTIMISE);
	}

	// After exiting the generation loop we can write the members to disk
	gm.populationManager->writeMembersToDisk();

}
