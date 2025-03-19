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
  std::vector<std::string> dict;
  std::ifstream wordle_words("wordle_words.txt");
  std::string word;

  while (wordle_words >> word) {
    dict.push_back(word);
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
  std::vector<std::string> master_dictionary;

  // Use to check guesses right and wrong letters
  std::map<cs19_wordle::letter_status_t, const std::string> ansi_colors{
      {cs19_wordle::GREEN, "\033[1;30;42m"},
      {cs19_wordle::YELLOW, "\033[1;30;43m"},
      {cs19_wordle::GRAY, "\033[1;30;243m"},
      {cs19_wordle::ERROR, "\033[1;30;41m"}};

  std::random_device rd;
  std::mt19937 gen(rd());

  bool game_active = true;
  bool game_won = false;


  int win_checker = 0;

  int games_count = 100;

  master_dictionary = dictionary_maker();

  for (int i = 0; i < games_count; ++i) {  // TESTING
    // while (game_active) {
    std::vector<std::string> dictionary = master_dictionary;
    cs19_wordle::Wordle game;
    std::string guess = "";
    assert(!dictionary.empty());
    int guess_max = 6;
    //std::cout << "WON " << game.wins() << " " << dictionary.size() << std::endl;

    

    for (int guess_num = 1; guess_num < guess_max; ++guess_num) {

      if(guess_num == 1)
        guess = "AUDIO";

      if(guess_num == 2) {
        guess = "SLEPT";
      }

      auto result = game.guess(guess);


      if (game.wins() != 0) {
        ++win_checker;
        //std::cout << "I won" << std::endl;
        break;
      }

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

        // Looks to see if a letter has already appeared as a yellow or green
        // and removes it from the gray letter vector if it has.      
        for (auto [ch, pos] : green_letters) {
            gray_letters.erase(ch);
          
        }
        for (auto [ch, pos] : yellow_letters) {
            gray_letters.erase(ch);
      }

      std::vector<std::string> new_vector;

      int count = 0;
      for (auto word_in_dict = dictionary.begin(); word_in_dict != dictionary.end(); word_in_dict++) {
        bool valid = true;

        count += 1;

        std::string current_word = *word_in_dict;

        //std::cout << count << std::endl;
        // Remove words that dont contain the green letter at the given position
          for (auto [ch, pos] : green_letters) {
            if (current_word[pos] != ch) {
              valid = false;
              break;
            }
          }
          
        if (valid == false){
          continue;
        }

        // Remove words that contain any gray letter
        for (auto c : gray_letters) {
           if (current_word.find(c) != std::string::npos) {
             valid = false;
             break;
           }
         }

        if (valid == false) {
          continue;
        }

        /* Remove words that
           1. Contain the letter at the given position
           2. Dont contain the letter */
        for (auto [ch, pos] : yellow_letters) {
          if (current_word[pos] == ch || current_word.find(ch) == std::string::npos) {
            valid = false;
            break;
          }
        }

        if (valid == false) {
          continue;
        }

        //std::cout << *word_in_dict << " " << valid << std::endl;
        new_vector.push_back(current_word);
      }

      dictionary = new_vector;

      std::uniform_int_distribution<size_t> dis(0, dictionary.size() - 1);
      //std::cout << "DICT SIZE " << dictionary.size() << std::endl;
      assert(!dictionary.empty());
      auto next_guess = std::next(dictionary.begin(), dis(gen));
      guess = *next_guess;
    }
  }
  std::cout << win_checker << " " << games_count << std::endl;
}