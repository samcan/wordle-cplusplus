#include <iostream>
#include <string>
#include <fstream>
#include <vector>
/* #include <ncurses/ncurses.h> */

#include "wordle.h"
#include "wordlist.h"
#include "puzzle.h"



void load_words(wordlist *list);

int main() {
    // load words into wordlist
    wordlist* words = new wordlist();
    load_words(words);

    // create puzzle
    puzzle* puz = new puzzle(words->pop_last_word());

    // get guesses
    std::string guess;
    for (int i=0; i<max_num_of_guesses; i++) {
        std::cout << "Guesses remaining: " << max_num_of_guesses-i << std::endl;
        bool valid_guess_entered = false;
        while (!valid_guess_entered) {
            std::cout << "> ";
            std::cin >> guess;

            if (guess.length() != wordlength) {
                std::cout << "Enter a valid 5-letter word." << std::endl;
            } else {
                valid_guess_entered = !valid_guess_entered;
            }
        }

        // check guess
        std::string result = puz->check_answer(guess);
        std::cout << guess << std::endl;
        std::cout << result << std::endl;
    }

    // free up memory before quitting
    delete(puz);
    delete(words);

    return 0;
}

void load_words(wordlist *list) {
    std::string filename = "words.txt";
    std::ifstream f;

    std::cout << "Loading wordlist... ";


    f.open(filename.c_str());

    // each word is only 5 chars long plus the \n char
    char word[wordlength+1];
    while (f.getline(word, wordlength+1)) {
        list->add(word);
    }

    f.close();

    std::cout << "done" << std::endl;
}