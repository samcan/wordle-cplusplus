#ifndef _WORDLIST_H_
#define _WORDLIST_H_

#include <vector>
#include <string>
#include <algorithm>

class wordlist {
    public:
        int length();

        void add(std::string word);
        void set_done_loading();

        std::string pop_last_word();
        virtual bool find(std::string w) = 0;

        virtual ~wordlist() = default;
    protected:
        std::vector<std::string> words;
        virtual void set_done_loading_hook() = 0;
};



void wordlist::set_done_loading() {
    set_done_loading_hook();
}

void wordlist::add(std::string word) {
    strtolower(word);
    words.push_back(word);
}

int wordlist::length() {
    return words.size();
}

std::string wordlist::pop_last_word() {
    std::string w = words.back();
    words.pop_back();
    return w;
}

#endif