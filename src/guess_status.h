#ifndef _GUESS_STATUS_H_
#define _GUESS_STATUS_H_

#include <iostream>
#include <string>

enum class guess_status { Unknown, Correct, Wrong_Location, Incorrect} ;

std::ostream& operator<<(std::ostream& os, const guess_status& gs) {
    std::string s = "";
    switch(gs) {
        case guess_status::Unknown:
            s += " ";
            break;
        case guess_status::Correct:
            s += "*";
            break;
        case guess_status::Wrong_Location:
            s += "^";
            break;
        case guess_status::Incorrect:
            s += ".";
            break;
    }

    os << s;
    return os;
}

#endif