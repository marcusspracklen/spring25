#include <cctype>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
std::vector<int> counter(std::string &data) {
  int char_counter = 0;
  int word_counter = 0;
  int sent_coutner = 0;

  bool seen_space = false;
  bool in_word = false;

  for (int i = 0; i < data.length(); ++i) {
    if (std::isalpha(data[i])) {
      ++char_counter;
      in_word = true;
    } else if (data[i] == ' ' || data[i] == '\n') {
      seen_space = true;
      if (in_word) {
        ++word_counter;
        in_word = false;
      }
    } else if (data[i] == '.' || data[i] == '!' || data[i] == '?') {
      if (in_word && seen_space) {
        ++sent_coutner;
        seen_space = false;
      }
    }
  }

  return {char_counter, word_counter, sent_coutner};
}

void ARI_calc(std::vector<int> data) {
  int ARI_value = 0;

  std::string ARI_score[14]{"Kindergarten",  "First Grade",    "Second Grade", "Third Grade",
                            "Fourth Grade",  "Fifth Grade",    "Sixth Grade",  "Seventh Grade",
                            "Eighth Grade",  "Ninth Grade",    "Tenth Grade",  "Eleventh Grade",
                            "Twelfth Grade", "College Student"};

  ARI_value =
      std::ceil(4.71 * (static_cast<double>(data[0]) / static_cast<double>(data[1])) +
                0.5 * (static_cast<double>(data[1]) / static_cast<double>(data[2])) - 21.43);

    if(ARI_value > 14) {
      std::cout << "ARI: " << ARI_value << " (Smarty-pants)"
            << "\n";
    }
    else {
  std::cout << "ARI: " << ARI_value << " (" << ARI_score[static_cast<int>(ARI_value) - 1] << ")"
            << "\n";
    }
}

int main() {
  std::string text;
  std::string token;
  std::vector<int> ARI_helper = {0, 0, 0};

  while (std::getline(std::cin, token)) {
    text += token + " ";
  }

  ARI_helper = counter(text);

  std::cout << ARI_helper[0] << " Characters" << "\n";
  std::cout << ARI_helper[1] << " Words" << "\n";
  std::cout << ARI_helper[2] << " Sentances" << "\n";

  ARI_calc(ARI_helper);
}