#ifndef _SORTED_WORDLIST_H_
#define _SORTED_WORDLIST_H_

#include <algorithm>
#include <string>
#include "wordlist.h"

class sorted_wordlist : public wordlist {
    public:
        bool find(std::string w);
        void set_done_loading_hook();

        ~sorted_wordlist() {
            
        }
    private:
        void sort();
};

void sorted_wordlist::set_done_loading_hook() {
    // mark that we're done loading all the words so we can
    // sort
    sort();
}

void sorted_wordlist::sort() {
    std::sort(words.begin(), words.end());
}

bool sorted_wordlist::find(std::string w) {
    return std::binary_search(words.begin(), words.end(), w);
}

#endif