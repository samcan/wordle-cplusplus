#ifndef _UNSORTED_WORDLIST_H_
#define _UNSORTED_WORDLIST_H_

#include <algorithm>
#include <string>
#include <random>
#include <ctime>
#include "wordlist.h"

class unsorted_wordlist : public wordlist {
    public:
        bool find(std::string w);
        void set_done_loading_hook();

        ~unsorted_wordlist() {
            
        }
    private:
        void shuffle();
};

bool unsorted_wordlist::find(std::string w) {
    auto it = std::find(words.begin(), words.end(), w);
    if (it != words.end()) {
        return true;
    } else {
        return false;
    }
}

void unsorted_wordlist::set_done_loading_hook() {
    shuffle();
}

void unsorted_wordlist::shuffle() {
    std::mt19937 g(static_cast<uint32_t>(time(0)));
    std::shuffle(words.begin(), words.end(), g);
}

#endif