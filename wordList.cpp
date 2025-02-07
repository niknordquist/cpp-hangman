//
// Created by Nik Nordquist on 2/7/25.
//

#include "wordList.h"
#include "random.h"
#include <iostream>

namespace wordList {
    std::vector<std::string> wordBank = {"mystery", "broccoli", "account", "almost", "spaghetti"
    , "opinion", "beautiful", "distance", "luggage"};

    std::string& generateRandomWord() {
        return wordList::wordBank[Random::get<std::size_t>(0,(wordList::wordBank.size() - 1))];
    }
}