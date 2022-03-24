#ifndef _UNSORTED_WORDLIST_H_
#define _UNSORTED_WORDLIST_H_

#include <algorithm>
#include <string>
#include "wordlist.h"

class unsorted_wordlist : public wordlist {
    public:
        bool find(std::string w);
        void set_done_loading_hook();

        ~unsorted_wordlist() {
            
        }
    private:
        void sort();
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
    ;
}

#endif