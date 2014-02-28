/*
 * Optimiser.cpp
 *
 *  Created on: 20 May 2013
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

#include "Optimiser.h"

Optimiser::Optimiser() : silence(false) { }
Optimiser::~Optimiser() {}


std::string timeNow() {
	char mbstr[100];
	time_t tim;  //create variable of time_t
	time(&tim); //pass variable tim to time function
	strftime(mbstr, 100, "%H:%M:%S", localtime(&tim));
	std::string timestr(mbstr);
	return timestr;
}


// This struct creates a set of variables and their mutexes to protect them during threaded optimisation.
struct Optimiser_mutex_stats {
	// TODO - This could be tidied up a bit, we no longer check as much
	double curr_score, start_score;
	int best_term;
	int best_func;
	bool improvement;
	std::vector<Node> tmp_rpn_tree;
	pthread_mutex_t m_tmp_rpn_tree;
	pthread_mutex_t m_curr_score;
	pthread_mutex_t m_best_term;
	pthread_mutex_t m_best_func;
	pthread_mutex_t m_improvement;

	Optimiser_mutex_stats() : curr_score(0), start_score(0), best_term(0), best_func(0), improvement(false) {
		if (pthread_mutex_init(&m_curr_score, NULL) != 0) { printf("\n mutex init failed\n"); }
		if (pthread_mutex_init(&m_best_term, NULL) != 0) { printf("\n mutex init failed\n"); }
		if (pthread_mutex_init(&m_best_func, NULL) != 0) { printf("\n mutex init failed\n"); }
		if (pthread_mutex_init(&m_improvement, NULL) != 0) { printf("\n mutex init failed\n"); }
		if (pthread_mutex_init(&m_tmp_rpn_tree, NULL) != 0) { printf("\n mutex init failed\n"); }
	}

	void update(double score,int term, int func) {
		pthread_mutex_lock(&m_curr_score);
		if (score < curr_score) {
			curr_score = score;
			best_term = term;
			best_func = func;
			improvement = true;
		}
		pthread_mutex_unlock(&m_curr_score);
	}


	void update(double score,std::vector<Node> & trt, int bestTerm ){
		pthread_mutex_lock(&m_curr_score);
		pthread_mutex_lock(&m_tmp_rpn_tree);
		pthread_mutex_lock(&m_best_term);
		if (score < curr_score) {
			curr_score = score;
			improvement = true;
			tmp_rpn_tree = trt;
			best_term = bestTerm;
		}
		pthread_mutex_unlock(&m_best_term);
		pthread_mutex_unlock(&m_tmp_rpn_tree);
		pthread_mutex_unlock(&m_curr_score);
	}
};


void delete_tree_branch(int node_index,std::vector<Node> * node_tree ) {
	int members = node_tree->at(node_index).fInputs;
	node_tree->erase(node_tree->begin() + node_index);
	while (members > 0) {
		if (! node_tree->at(node_index).isTerminal ) {
			members += node_tree->at(node_index).fInputs;
		}
		node_tree->erase(node_tree->begin() + node_index);
		members --;
	}
}


bool Optimiser::branchCutter(PopulationMember & p) {
	Optimiser_mutex_stats oms;
	bool madeImprovement = false;
	if (!silence) {
		printf("\e[1;34m\nStarting Branch Cutter\e[0m - Tree size %lu - Started at: %s\n",p.rpnNodeVec.size(),timeNow().c_str());
	}

	// Work through the list of nodes
	for (unsigned int x = 0; x < p.rpnNodeVec.size(); x++ ) {
		std::vector<Node> orig_rpn_vec(p.rpnNodeVec);
		oms.start_score = p.score;
		oms.curr_score  = p.score;
		oms.improvement = false;

		// If we hit a function, try replacing it with all available terminals
		if (! p.rpnNodeVec.at(x).isTerminal && p.rpnNodeVec.at(x).fNo != -1 ) {
			int fid = p.rpnNodeVec.at(x).fNo;
#pragma omp parallel
			{
#pragma omp for schedule(static)
				for (unsigned int y = 0; y < gm.fitnessCases.TERMINALS; y ++) {
					// Copy and edit the vector
					std::vector<Node> tmp_rpn_vec(p.rpnNodeVec);

					// Clear down the function tree
					delete_tree_branch(x,&tmp_rpn_vec);

					// Put a terminal in its place
					tmp_rpn_vec.insert(tmp_rpn_vec.begin()+x,Node(y));

					// Check out how this scores
					double tmp_score = scoreRpnVec(tmp_rpn_vec,oms.curr_score);
					if (tmp_score < oms.curr_score) {
						oms.update(tmp_score,tmp_rpn_vec,y);
					}
				}
			}
			// If we made an improvement, share the news
			if(oms.improvement) {
				if (!silence) {
					if (! madeImprovement) {
						printf("%-9s %-8s %-8s %-11s %-11s\n","Position","Was Func","Now Term","Old Score","New Score");
					}
				}
				madeImprovement = true;

				if (!silence) {
					printf("%-9d %-8d %-8d %-11f %-11f\n",x,fid,oms.best_term,oms.start_score,oms.curr_score);
				}
				// Fix the node and the rpn tree on the population member with the new information.
				p.rpnNodeVec = oms.tmp_rpn_tree;	// This is where we update the change quickly for this loop
				p.score = oms.curr_score;
			}
		}
	}
	if (!silence) {
		printf("\e[1;34mFinished Branch Cutter\e[0m - Tree size %lu\n",p.rpnNodeVec.size());
	}
	return madeImprovement;
}


bool Optimiser::terminalSwapper(PopulationMember & p) {
	Optimiser_mutex_stats oms;
	bool madeImprovement = false;
	if(!silence) {
		printf("\e[1;34m\nStarting Terminal Swapper \e[0m - Started at: %s\n",timeNow().c_str());
	}

	// Work through the list of nodes
	for (unsigned int x = 0; x < p.rpnNodeVec.size(); x++ ) {
		// If we hit a terminal, try all versions of it
		if (p.rpnNodeVec.at(x).isTerminal ) {
			oms.start_score = p.score;
			oms.curr_score  = p.score;
			oms.improvement = false;
			unsigned int tid = p.rpnNodeVec.at(x).tNo;
#pragma omp parallel
		    {
#pragma omp for schedule(static)
				for (unsigned int y = 0; y < gm.fitnessCases.TERMINALS; y ++) {
					if (y != tid) { // Don't score ourself!
						// Copy and edit the vector
						std::vector<Node> tmp_rpn_vec(p.rpnNodeVec);
						tmp_rpn_vec.at(x).tNo = y;
						double tmp_score = scoreRpnVec(tmp_rpn_vec,oms.curr_score);
						// If we have an improvement, add it
						if (tmp_score < oms.curr_score) {
							oms.update(tmp_score,y,0);

						}
					}
				}
			}
			// If we made an improvement, share the news
			if(oms.improvement) {
				if (!silence) {
					if (! madeImprovement) {
						printf("%-9s %-8s %-8s %-11s %-11s\n","Position","Was Term","Now Term","Old Score","New Score");
					}
				}
				madeImprovement = true;

				if (!silence) {
					printf("%-9d %-8d %-8d %-11f %-11f\n",x,tid,oms.best_term,oms.start_score,oms.curr_score);
				}

				// Fix the node and the rpn tree on the population member with the new information.
				p.rpnNodeVec.at(x).tNo = oms.best_term;					   // This is where we update the change quickly for this loop
				p.score = oms.curr_score;
			}
		}
	}
	return madeImprovement;
}


bool Optimiser::functionSwapper(PopulationMember & p) {
	Optimiser_mutex_stats oms;
	bool madeImprovement = false;
	if (!silence) {
		printf("\e[1;34m\nStarting Function Swapper %s\e[0m - Started at:\n",timeNow().c_str());
	}

	// Work through the list of nodes
	for (unsigned int x = 0; x < p.rpnNodeVec.size(); x++ ) {
		std::vector<Node> orig_rpn_vec(p.rpnNodeVec);
		oms.start_score = p.score;
		oms.curr_score  = p.score;
		oms.improvement = false;

		// If we hit a function, try all versions of it
		if (! p.rpnNodeVec.at(x).isTerminal && p.rpnNodeVec.at(x).fNo != -1 ) {
			int fid = p.rpnNodeVec.at(x).fNo;
			std::vector<Node> tmp_rpn_vec(orig_rpn_vec);
#pragma omp parallel
		    {
#pragma omp for schedule(dynamic)
				for (unsigned int y = 0; y < gm.nodeManager.functionlist.size(); y ++) {
					if ((int)gm.nodeManager.functionlist.at(y)._mynum != fid) {
						// Only swap functions with the same number of inputs
						if (gm.nodeManager.functionlist.at(y)._inputs == gm.nodeManager.functionlist.at(fid)._inputs ) {
							tmp_rpn_vec.at(x).fNo  = gm.nodeManager.functionlist.at(y)._mynum;
							double tmp_score = scoreRpnVec(tmp_rpn_vec,oms.curr_score);
							// If we have an improvement, add it
							if (tmp_score < oms.curr_score) {
								oms.update(tmp_score,0,y);
							}
						}
					}
				}
		    }

			// If we made an improvement, share the news
			if(oms.improvement) {
				if (!silence) {
					if (! madeImprovement) {
						printf("%-9s %-8s %-8s %-11s %-11s\n","Position","Was Func","Now Func","Old Score","New Score");
					}
				}

				madeImprovement = true;
				if (!silence) {
					printf("%-9d %-8d %-8d %-11f %-11f\n",x,fid,oms.best_func,oms.start_score,oms.curr_score);
				}

				// Fix the node and the rpn tree on the population member with the new information.
				p.rpnNodeVec.at(x).fNo  = oms.best_func;
				p.score = oms.curr_score;
			}
		}
	}
	return madeImprovement;
}


// Run all optimisation loops in sequence
void Optimiser::optimise(int generation, bool save) {

	if (generation % gm.settings.OPTIMISE_CUTTER_EVERY == 0) {
		if (gm.settings.ITERATE_CUTTER) {
			bool improve_tree = true;
			while(improve_tree) {
				improve_tree = branchCutter(gm.populationManager.populationlist.v.at(0));
			}
		} else {
			branchCutter(gm.populationManager.populationlist.v.at(0));
		}
		if (save) { gm.populationManager.writeMembersToDisk();}
	}

	if (generation % gm.settings.OPTIMISE_TERMINALS_EVERY == 0) {
		if (gm.settings.ITERATE_TERMINALS) {
			bool improve_terminals = true;
			while(improve_terminals) {
				improve_terminals = terminalSwapper(gm.populationManager.populationlist.v.at(0));
			}
		} else {
			terminalSwapper(gm.populationManager.populationlist.v.at(0));
		}
		if (save) { gm.populationManager.writeMembersToDisk();}
	}

	if (generation % gm.settings.OPTIMISE_FUNCTIONS_EVERY == 0) {
		if (gm.settings.ITERATE_FUNCTIONS) {
			bool improve_functions = true;
			while(improve_functions) {
				improve_functions = functionSwapper(gm.populationManager.populationlist.v.at(0));
			}
		} else {
			functionSwapper(gm.populationManager.populationlist.v.at(0));
		}
		if (save) { gm.populationManager.writeMembersToDisk();}
	}
}


