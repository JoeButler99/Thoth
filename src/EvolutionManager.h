/*
 * EvolutionManager.h
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

#ifndef EVOLUTIONMANAGER_H_
#define EVOLUTIONMANAGER_H_
#include <sys/time.h>
#include "Globals.h"
#include "PopulationManager.h"
#include "Optimiser.h"



class EvolutionManager {
public:
	EvolutionManager();
	~EvolutionManager();
	bool silence;
	int tournament(int tornament_size);

	void mutateSingleNode(int num_needed, int pool_size);
	void mutateNodeTree(int num_needed, int pool_size);
	void cutNodeTree(int num_needed, int pool_size);
	void crossover(int num_needed, int pool_size);
	void crossoverNewRoot(int num_needed, int pool_size);
	void runGenerations(unsigned gens = gm.settings->GENERATIONS);

	void deleteTreeBranch(int node_index,std::vector<Node> & node_tree );
	void makeNodeTree(int depth,bool fill,std::vector<Node> & node_tree);
	void copyNodeTree(int insert_index,int get_index,std::vector<Node> & into_node_tree,std::vector<Node> & from_node_tree );
};


#endif /* EVOLUTIONMANAGER_H_ */
