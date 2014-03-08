/*
 * GuiFunctions.h
 *
 *  Created on: 19 Oct 2013
 *      Author: joe
 *

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


#endif /* GUIFUNCTIONS_H_ */
