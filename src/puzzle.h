#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include <string>

// This class will "be" the puzzle. It'll have a word assigned, and then each
// guess will be checked against it.

class puzzle {
    public:
        puzzle() {}
        puzzle(std::string sol): solution(sol) {};
    
        std::string check_answer(std::string ans);
    private:
        bool is_char_in_solution(const char c);
        std::string solution;

};

std::string puzzle::check_answer(std::string ans) {
    // TODO confirm that answer is in wordlist.

    // we'll check for whether the answer exactly matches the solution right
    // off. If it doesn't, then we have to check each char in our potential
    // answer and see how it compares to the puzzle solution.

    if(ans == solution) {
        return "* * * * *";
    }
    

    // we have to determine the exact results of this potential answer
    std::string result;
    for (int i=0; i<5; i++) {
        if (ans[i] == solution[i]) {
            // letter is in correct spot
            result += "* ";
        } else {
            // letter is either in incorrect spot or just not in puzzle
            // solution at all
            if (is_char_in_solution(ans[i])) {
                result += "^ ";
            } else {
                result += ". ";
            }
        }
    }

    return result;
}

bool puzzle::is_char_in_solution(const char c) {
    return solution.find(c) != std::string::npos;
}

#endif