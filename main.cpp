#include "random.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

namespace WordList {
    std::vector<std::string> wordBank = {"mystery", "broccoli", "account", "almost", "spaghetti"
    , "opinion", "beautiful", "distance", "luggage"};

    std::string& generateRandomWord() {
        return WordList::wordBank[Random::get<std::size_t>(0,(WordList::wordBank.size() - 1))];
    }
}

class Session {
private:
    std::string_view m_word {WordList::generateRandomWord() };
    std::vector<char> guessedLetters = std::vector<char>(26);
    std::vector<char> misses = {'+', '+', '+', '+', '+', '+'};
    int lives {6};
    int attempts {0};
    int score {0};
    bool winner {false};
public:
    std::vector<char> getGuessedLetters() { return guessedLetters; }
    char getMiss(int miss) const {
        assert(miss >= 0);
        assert(miss < 6);
        return misses[miss];
    }
    std::string_view getWord() const { return m_word; }
    int getLives() const { return lives; }
    int getScore() const{ return score; }
    bool getWinner() const { return winner; }

    void loseLife() { --lives; }
    void setScore(const int points) { score += points;}
    void setWinner() { winner = true; }
    void incAttempts() { ++attempts; }
    void addGuessedLetters(const char letter) { guessedLetters[attempts] = letter; }
    void addMiss(const char miss) { misses[lives] = miss; }

};

void printGameState(Session& game) {
    std::cout << "The word: ";
    for (int i = 0; i < game.getWord().length(); i++) {
        if (std::count(game.getGuessedLetters().begin(), game.getGuessedLetters().end(), game.getWord()[i]) > 0) {
            std::cout << game.getWord()[i];
        } else {
            std::cout << "_";
        }
    }
    std::cout << "  Wrong guesses: ";
    for (int i = 0; i < 6; i++) {
        std::cout << game.getMiss(i);
    }
    std::cout << std::endl;
    if (game.getScore() == game.getWord().size()) {
        game.setWinner();
        std::cout << "Congratulations! You've beat C++man! The word was: " << game.getWord();
    }
    if (game.getLives() < 1) {
        std::cout << "You lost! The word was: " << game.getWord();
    }
}

void getGuess(Session& game) {
    char guess{};
    bool validGuess = false;
    while (!validGuess) {

        std::cout << "Enter your next letter: ";
        std::cin >> guess;

        if (!std::cin || (guess < 'a' || guess > 'z')) {
            std::cout << "That wasn't a valid input. Try again\n";
            std::cin.clear();
        } else if (std::count(game.getGuessedLetters().begin(), game.getGuessedLetters().end(), guess) > 0) {
            std::cout << "You already guessed that. Try again.\n";
        }
        else {
            validGuess = true;
            game.addGuessedLetters(guess);
            const int appearances = static_cast<int>(
                std::count(game.getWord().begin(), game.getWord().end(), guess));
            game.incAttempts();
            if (appearances == 0) {
                std::cout << "No, '" << guess << "' is not in the word!\n";
                game.loseLife();
                game.addMiss(guess);
            } else {
                std::cout << "Yes, '" << guess << "' is in the word!\n";
                game.setScore(appearances);
            }
            printGameState(game);
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    std::cout << "Welcome to C++man (a variant of hangman)\nTo win: guess the word."
                 " To lose: run out of pluses.\n\n";
    Session newGame;
    printGameState(newGame);
    while (newGame.getLives() > 0 && !newGame.getWinner()) {
        getGuess(newGame);
    }
    return 0;
}