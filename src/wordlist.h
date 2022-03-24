#ifndef _WORDLIST_H_
#define _WORDLIST_H_

#include <vector>
#include <string>

class wordlist {
    public:
        void add(std::string word);
        int length();

    private:
        std::vector<std::string> words;
};

void wordlist::add(std::string word) {
    words.push_back(word);
}

int wordlist::length() {
    return words.size();
}

#endif