#include <iostream>
#include <string>
#include <fstream>
#include <vector>
/* #include <ncurses/ncurses.h> */

#include "wordlist.h"


void load_words(wordlist *list);

int main() {
    // load words into wordlist
    wordlist* words = new wordlist();
    load_words(words);






    // free up memory before quitting
    delete(words);
    return 0;
}

void load_words(wordlist *list) {
    std::string filename = "words.txt";
    std::ifstream f;

    std::cout << "Loading wordlist... ";


    f.open(filename.c_str());

    char word[6];
    while (f) {
        f.getline(word, 6);
        list->add(word);
    }

    f.close();

    std::cout << "done" << std::endl;
}