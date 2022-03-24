#ifndef _WORDLE_H_
#define _WORDLE_H_

const int max_num_of_guesses = 6;
const int wordlength = 5;

#include <iostream>
#include <algorithm>
#include <string>

inline void strtolower(std::string w) {
    std::transform(w.begin(), w.end(), w.begin(), tolower);
}

inline void strtoupper(std::string w) {
    std::transform(w.begin(), w.end(), w.begin(), toupper);
}

#endif