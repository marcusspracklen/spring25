#include <iostream>
#include <string>
#include <cctype>

int character_counter(std::string &data) {
    int count = 0;
    for (char c : data) {
        if(std::isalpha(c)) {
            count++;
        }
    }

    return count;
}

int sentance_counter(std::string &data) {
    int count = 0;
    for (char c : data) {
    if(c == '!' || c == '.' || c == '?') {
            count++;
        }
    }
    return count;
}

int word_count(std::string &data) {
    int count = 0;
    bool in_word = true;

    for(char c : data) {
        if(isspace(c)) {
            in_word = false;
        } 
        else if(!in_word) {
            in_word = true;
            count++;
        }

    }

    return count;
}

int main() {

    std::string text, token;

    while (std::cin >> token) {
        if(!text.empty()) {
            text += " ";
        }
        text += token;
    }

    std::cout << "Characters: " << character_counter(text) << "\n";
    std::cout << "Words: " << word_count(text) << "\n";
    std::cout << "Sentances: " << sentance_counter(text) << "\n";
}