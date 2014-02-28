/*
 * Node.cpp
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

#include "Node.h"



Node::Node(Function & f) :  fNo(f._mynum), fInputs(f._inputs), tNo(0) , isTerminal(false){}

Node::Node(int t) : fNo(-2), fInputs(1), tNo(t), isTerminal(true) {}

Node::Node(int inputs, bool headnode) : fNo(-1), fInputs(inputs), tNo(0), isTerminal(false) {}

//void Node::setFromFunc (Function & f) {
//	is_terminal = false;
//	fNo 	= f._mynum;
//	fInputs = f._inputs;
//}
//
//void Node::setTerminal (int t) {
//	is_terminal = true;
//	tNo = t;
//}
