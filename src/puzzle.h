#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include <vector>
#include <string>
#include "wordle.h"
#include "key.h"
// This class will "be" the puzzle. It'll have a word assigned, and then each
// guess will be checked against it.

class puzzle {
    public:
        puzzle() {}
        puzzle(std::string sol): solution(sol) {};

        std::vector<key> check_answer(std::string ans);
        const std::string answer();
    private:
        bool is_char_in_solution(const char c);
        std::string solution;

};

std::vector<key> puzzle::check_answer(std::string ans) {
    std::vector<key> result;
    // we have to determine the exact results of this potential answer
    
    for (int i=0; i<wordlength; i++) {
        key k;
        k.name = ans[i];
        if (ans[i] == solution[i]) {
            // letter is in correct spot
            k.status = guess_status::Correct;
        } else {
            // letter is either in incorrect spot or just not in puzzle
            // solution at all
            if (is_char_in_solution(ans[i])) {
                k.status = guess_status::Wrong_Location;
            } else {
                k.status = guess_status::Incorrect;
            }
        }
        result.push_back(k);
    }

    return result;
}

const std::string puzzle::answer() {
    return solution;
}

bool puzzle::is_char_in_solution(const char c) {
    return solution.find(c) != std::string::npos;
}

#endif