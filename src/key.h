#ifndef _KEY_H_
#define _KEY_H_

#include <iostream>
#include <string>
#include <vector>
#include "guess_status.h"

struct key {
    char name;
    guess_status status = guess_status::Unknown;
};

class keyboard {
    public:
        keyboard() {
            for (int i=0; i<26; i++) {
                key k;
                k.name = i + 'a';
                k.status = guess_status::Unknown;

                keys.push_back(k);
            }
        }
    
    public:
        std::vector<key> keys;
};

std::ostream& operator<<(std::ostream& os, const keyboard& ks) {
    for (auto k : ks.keys) {
        os << k.status << (char)toupper(k.name) << " ";
    }
    return os;
}


#endif