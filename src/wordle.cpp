#include <iostream>
#include <string>
#include <fstream>
#include <vector>
/* #include <ncurses/ncurses.h> */

#include "wordle.h"
#include "wordlist.h"
#include "shuffled_wordlist.h"
#include "sorted_wordlist.h"
#include "puzzle.h"
#include "key.h"

using std::cout;
using std::cin;
using std::endl;

std::string get_valid_guess(int cur_guess_num, wordlist* l);
void load_words(wordlist *list);
void update_keyboard(std::vector<key> result, keyboard *kbd);
void prompt_for_guess(std::ostream& os, int current_guess, int number_of_guesses);
void output_guess_result(std::ostream& os, std::string guess, std::vector<key> result);
void output_instructions(std::ostream& os);
bool is_result_winning(std::vector<key> result);

int main() {
    // load words into wordlist
    cout << "Loading wordlist... ";
    wordlist* puzzle_answers = new shuffled_wordlist();
    wordlist* valid_guesses = new sorted_wordlist();
    load_words(puzzle_answers);
    load_words(valid_guesses);
    cout << "done" << endl;

    // build keyboard
    keyboard* kbd = new keyboard();

    // create puzzle
    puzzle* puz = new puzzle(puzzle_answers->pop_last_word());

    output_instructions(cout);

    // get guesses
    bool quitting = false;
    bool winning = false;
    int i;
    std::string guess;
    for (i=0; i<max_num_of_guesses; i++) {
        // display keyboard with keys remaining
        cout << *kbd << endl;
        // will return either a valid 5-letter word or "quit"
        guess = get_valid_guess(i, valid_guesses);

        if (guess == word_quit) {
            quitting = true;
            break;
        }

        // check guess
        std::vector<key> result = puz->check_answer(guess);
        
        // display guess and its result
        output_guess_result(cout, guess, result);
        winning = is_result_winning(result);
        
        // update keyboard
        update_keyboard(result, kbd);

        if (winning) {
            break;
        }

    }

    if (!winning && !quitting) {
        // lost the game
        cout << endl << "Sorry, but you lost! You ran out of guesses." << endl;
        cout << "The word was " << puz->answer() << "." << endl;
    } else if (quitting) {
        cout << "The word was " << puz->answer() << "." << endl;
    } else {
        cout << endl << "Congratulations; you won in " << i+1 << " guesses." << endl;
    }
    // TODO display guess results

    // free up memory before quitting
    delete(puz);
    delete(puzzle_answers);
    delete(valid_guesses);
    delete(kbd);

    return 0;
}

std::string get_valid_guess(int cur_guess_num, wordlist* wordl) {
    std::string guess = "";
    bool valid_guess_entered = false;
    while (!valid_guess_entered) {
        prompt_for_guess(cout, cur_guess_num, max_num_of_guesses);
        cin >> guess;
        
        // transform guess to lowercase
        strtolower(guess);

        if (guess == word_quit) {
            return guess;
        } else if (guess.length() != wordlength) {
            cout << "Enter a valid 5-letter word." << endl;
        } else {
            if (wordl->find(guess)) {
                // confirmed that guess is a valid word from wordlist
                valid_guess_entered = true;
            } else {
                cout << "You must enter a valid 5-letter word." << endl;
            }
        }
    }
    return guess;
}

bool is_result_winning(std::vector<key> result) {
    for (auto k : result) {
        if (k.status != guess_status::Correct) {
            return false;
        }
    }
    return true;
}

void prompt_for_guess(std::ostream& os, int current_guess, int number_of_guesses) {
    os << current_guess+1 << "/" << number_of_guesses << " > ";
}

void output_guess_result(std::ostream& os, std::string guess, std::vector<key> result) {
    cout << guess << endl;
    for(auto k : result) {
        os << k.status;
    }
    os << endl;
}

void update_keyboard(std::vector<key> result, keyboard *kbd) {
    for (int i=0; i<wordlength; i++) {
        int j = static_cast<int>(result[i].name) - 'a';
        kbd->keys[j].status = result[i].status;
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

void output_instructions(std::ostream& os) {
    os << endl;
    os << "You have " << max_num_of_guesses << " guesses to guess the five-letter word." << endl << endl;
    os << "Legend:" << endl;
    os << guess_status::Correct << " Correct letter, correct location" << endl;
    os << guess_status::Incorrect << " Incorrect, not in puzzle" << endl;
    os << guess_status::Wrong_Location << " Correct letter, wrong location" << endl;
    os << endl;
}