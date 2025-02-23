#include <cctype>
#include <iostream>
#include <string>

int character_counter(std::string &data) {
  int count = 0;
  for (char c : data) {
    if (std::isalpha(c)) {
      count++;
    }
  }

  return count;
}

int sentance_counter(std::string &data) {
  int count = 0;
  bool is_word = false;
  for (size_t i = 0; i < data.length(); i++) {
    if(isalpha(data[i])) {
      is_word = true;
    }
    else if ((data[i] == '!' || data[i] == '.' || data[i] == '?') && is_word) {
        count++;
      is_word = false;
    }
  }

  return count;
}

int word_count(std::string &data) {
  int count = 0;
  bool in_word = false;

  for (char c : data) {
    if (isspace(c)) {
      in_word = false;
    } else if (!in_word && std::isalpha(c)) {
      in_word = true;
      count++;
    }
  }

  return count;
}

int main() {
  std::string text, token;

  while (std::cin >> token) {
    if (!text.empty()) {
      text += " ";
    }
    text += token;
  }

  std::cout << "Characters: " << character_counter(text) << "\n";
  std::cout << "Words: " << word_count(text) << "\n";
  std::cout << "Sentances: " << sentance_counter(text) << "\n";
}