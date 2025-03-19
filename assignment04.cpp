#include <cs19_wordle.h>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <unordered_set>
#include <set>
#include <vector>

using namespace cs19_wordle;

auto dictionary_maker() {
  std::unordered_set<std::string> dict;
  std::ifstream wordle_words("wordle_words.txt");
  std::string word;

  while (wordle_words >> word) {
    dict.insert(word);
  }
  wordle_words.close();

  return dict;
}

int main(int argc, char** argv) {
  if (argc < 1) {
    std::cerr << "ERROR: " << argv[0] << " was the only command line input.\n";
    return 1;
  }

  // Create a set that has all the words possible for our wordle game.
  std::unordered_set<std::string> dictionary;

  // Use to check guesses right and wrong letters
  std::map<cs19_wordle::letter_status_t, const std::string> ansi_colors{
      {cs19_wordle::GREEN, "\033[1;30;42m"},
      {cs19_wordle::YELLOW, "\033[1;30;43m"},
      {cs19_wordle::GRAY, "\033[1;30;243m"},
      {cs19_wordle::ERROR, "\033[1;30;41m"}};

  cs19_wordle::Wordle game;
  std::random_device rd;
  std::mt19937 gen(rd());

  bool game_active = true;
  bool game_won = false;

  // First guess
  std::string guess = "AUDIO";

  int win_checker = 0;

  for (int i = 0; i < 1; ++i) {  // TESTING
    // while (game_active) {
    dictionary = dictionary_maker();
    guess = "AUDIO";
    assert(!dictionary.empty());
    int guess_max = 6;
    std::cout << game.wins();

    for (int guess_num = 1; guess_num < guess_max; ++guess_num) {
      auto result = game.guess(guess);

      std::cout << guess_num << " " << guess << std::endl;

      if (game.wins() > win_checker) {
        ++win_checker;
        std::cout << "I won" << std::endl;
        break;
      }

    //   for (int i = 0; i < 5; ++i) {
    //     std::cout << ansi_colors[result[i]] << guess[i];
    //   }
    //   std::cout << "\n";

      std::set<char> gray_letters;
      std::vector<std::pair<char, int>> green_letters;
      std::vector<std::pair<char, int>> yellow_letters;

      // Look at our dictinary set and exclude any words that don't have a green letter
      // Where we want word_in_dict, include a yellow letter, and don't include any of our gray letters.
      for (int i = 0; i < 5; ++i) {
        if (result[i] == GREEN) {
          green_letters.emplace_back(guess[i], i);
        } else if (result[i] == YELLOW) {
          yellow_letters.emplace_back(guess[i], i);
        } else if (result[i] == GRAY) {
          gray_letters.insert(guess[i]);
        }
      }

      for(auto gray : gray_letters) {
        for (auto [ch, pos] : green_letters) {
          if ((gray) == (ch)) {
            gray_letters.erase(gray);
          } else {
            ++gray;
          }
        }
        for (auto [ch, pos] : yellow_letters) {
          if ((gray) == (ch)) {
            gray_letters.erase(gray);
          } else {
            ++gray;
          }
        }
      }

      for (auto word_in_dict = dictionary.begin(); word_in_dict != dictionary.end();) {
        bool valid = true;

        // Remove words that contain any gray letter
        for (auto c : gray_letters) {
          if ((*word_in_dict).find(c) != std::string::npos) {
            valid = false;
            //std::cout << "WIBBKE " << c << " " << *word_in_dict << std::endl;
            break;
          }
        }

        // Remove words that dont contain the green letter at the given position
        for (auto [ch, pos] : green_letters) {
          if ((*word_in_dict)[pos] != ch) {
            std::cout << guess << " " << *word_in_dict << std::endl;
            valid = false;
            break;
          }
        }

        /* Remove words that
           1. Contain the letter at the given position
           2. Dont contain the letter */
        for (auto [ch, pos] : yellow_letters) {
          if ((*word_in_dict)[pos] == ch || (*word_in_dict).find(ch) == std::string::npos) {
            valid = false;
            break;
          }
        }

        //std::cout << *word_in_dict << " " << valid << std::endl;
        if (!valid) {
          word_in_dict = dictionary.erase(word_in_dict);
        } else {
          ++word_in_dict;
        }
      }

      std::uniform_int_distribution<size_t> dis(0, dictionary.size() - 1);
      std::cout << "DICT SIZE " << dictionary.size() << std::endl;
      assert(!dictionary.empty());
      auto next_guess = std::next(dictionary.begin(), dis(gen));
      guess = *next_guess;
    }
  }
}