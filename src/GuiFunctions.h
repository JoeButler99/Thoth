/*
 * GuiFunctions.h
 *
 *  Created on: 19 Oct 2013
 *      Author: joe
 *
 * 		* TODO - Many functions from here can be removed

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

#ifndef GUIFUNCTIONS_H_
#define GUIFUNCTIONS_H_
#include <ostream>
#include <iostream>

namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_CYAN		= 36,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}

static Color::Modifier red(Color::FG_RED);
static Color::Modifier blue(Color::FG_CYAN);
static Color::Modifier def(Color::FG_DEFAULT);

//
//		 Static stuff! - keeps it out of main
//

inline void error_msg(const std::string & msg) {
	std::cout << red << msg << def << std::endl;
}

inline void question_msg(const std::string & msg) {
	std::cout << blue << msg << def << " ";
}

inline std::string display_bool(bool input) {
	if (input) {
		return "true";
	} else {
		return "false";
	}
}


//inline bool askYesNo(const std::string& question) {
//	//std::cout << question << std::endl;
//	question_msg(question);
//	std::string input;
//	question_msg("(yes / no): ");
//	while (true) {
//		std::getline(std::cin,input);
//		std::transform(input.begin(),input.end(),input.begin(),::tolower);
//		if ( input == "yes" || input == "y") {
//			std::cout << std::endl << std::endl;
//			return true;
//		}
//		if ( input == "no" || input == "n") {
//			std::cout << std::endl << std::endl;
//			return false;
//		}
//	}
//	return false;
//}
//
//
//inline bool askDefaultOther(const std::string& question,const std::string& defaultAction) {
//	//std::cout << question << std::endl;
//	question_msg(question);
//	std::string input;
//
//	question_msg("("+defaultAction +"): ");
//	std::cin.ignore();
//	std::getline(std::cin,input);
//	std::transform(input.begin(),input.end(),input.begin(),::tolower);
//	if ( input == "") {
//		std::cout << std::endl << std::endl;
//		return true;
//	} else {
//		return false;
//	}
//}
//
//inline int getIntFromUser(const std::string& question) {
//	question_msg(question);
//	int result;
//	std::cin >> result;
//	std::cout << std::endl;
//	return result;
//}
//
//
//inline void setFileName(const std::string & prompt,const std::string & prefix,std::string & filename) {
//	std::string temp;
//	std::cout << prompt << std::endl;
//	std::cin >> temp;
//	filename = prefix + temp;
//}
//
//
//inline std::string pickFile(std::vector<fs::path> files) {
//	while (true) {
//		// Make a temporary 'menu' for the user to select a file
//		std::cout << "\n\nChoose File: " << std::endl;
//		for (unsigned x = 0; x < files.size(); x++) {
//			std::cout << x+1 << ") " << files.at(x).string() << std::endl;
//		}
//
//		std::cout << "\n( Enter 0 to Abort )" << std::endl;
//		// Now wait for the user selection
//		unsigned choice;
//		question_msg("\n\nSelect Choice: ");
//		std::cin >> choice;
//		std::cout << std::endl;
//
//		if (choice == 0) {
//			return "";
//		} else if(choice -1 >= files.size() || choice < 0) {
//			std::cout << "INVALID SELECTION" << std::endl;
//		} else {
//			return files.at(choice-1).string();
//		}
//	}
//	return "";
//}


#endif /* GUIFUNCTIONS_H_ */
