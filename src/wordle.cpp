#include <iostream>
#include <string>
#include <fstream>
#include <vector>
/* #include <ncurses/ncurses.h> */

#include "wordle.h"
#include "wordlist.h"
#include "unsorted_wordlist.h"
#include "sorted_wordlist.h"
#include "puzzle.h"
#include "key.h"



void load_words(wordlist *list);
void update_keyboard(std::vector<key> result, keyboard &kbd);
void prompt_for_guess(std::ostream& os, int current_guess, int number_of_guesses);
void output_guess_result(std::ostream& os, std::string guess, std::vector<key> result);

int main() {
    // load words into wordlist
    std::cout << "Loading wordlist... ";
    wordlist* puzzle_answers = new unsorted_wordlist();
    wordlist* valid_guesses = new sorted_wordlist();
    load_words(puzzle_answers);
    load_words(valid_guesses);
    std::cout << "done" << std::endl;

    // build keyboard
    keyboard kbd;

    // create puzzle
    puzzle* puz = new puzzle(puzzle_answers->pop_last_word());

    // get guesses
    std::string guess;
    for (int i=0; i<max_num_of_guesses; i++) {
        // display keyboard with keys remaining
        std::cout << kbd << std::endl;

        bool valid_guess_entered = false;
        while (!valid_guess_entered) {
            prompt_for_guess(std::cout, i, max_num_of_guesses);
            std::cin >> guess;

            if (guess.length() != wordlength) {
                std::cout << "Enter a valid 5-letter word." << std::endl;
            } else {
                if (valid_guesses->find(guess)) {
                    // confirmed that guess is a valid word from wordlist
                    valid_guess_entered = !valid_guess_entered;
                } else {
                    std::cout << "You must enter a valid 5-letter word." << std::endl;
                }
            }
        }

        // transform guess to lowercase
        strtolower(guess);

        // check guess
        std::vector<key> result = puz->check_answer(guess);
        
        // display guess and its result
        output_guess_result(std::cout, guess, result);
        
        // update keyboard
        update_keyboard(result, kbd);

    }

    // free up memory before quitting
    delete(puz);
    delete(puzzle_answers);
    delete(valid_guesses);

    return 0;
}

void prompt_for_guess(std::ostream& os, int current_guess, int number_of_guesses) {
    os << current_guess+1 << "/" << number_of_guesses << " > ";
}

void output_guess_result(std::ostream& os, std::string guess, std::vector<key> result) {
    std::cout << guess << std::endl;
    for(auto k : result) {
        os << k.status;
    }
    os << std::endl;
}

void update_keyboard(std::vector<key> result, keyboard& kbd) {
    for (int i=0; i<wordlength; i++) {
        int j = static_cast<int>(result[i].name) - 'a';
        kbd.keys[j].status = result[i].status;
    }
}

void load_words(wordlist *list) {
    std::string filename = "words.txt";
    std::ifstream f;
    f.open(filename.c_str());

    // each word is only 5 chars long plus the \n char
    char word[wordlength+1];
    while (f.getline(word, wordlength+1)) {
        list->add(word);
    }
    list->set_done_loading();

    f.close();
}