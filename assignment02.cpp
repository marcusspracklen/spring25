#include <cctype>
#include <iostream>
#include <string>
void counter(std::string &data) {

  int char_counter = 0;
  int word_counter = 0;
  int sent_coutner = 0;

  bool seen_space = false;
  bool in_word = false;
 

  for (int i = 0; i < data.length(); ++i) {

    if(std::isalpha(data[i])) {
      ++char_counter;
      in_word = true;
    }
    else if(data[i] == ' ' || data[i] == '\n') {
      seen_space = true;
      if(in_word) {
      ++word_counter;
      in_word = false;
      }
    }
    else if(data[i] == '.' || data[i] == '!' || data[i] == '?') {
      if(in_word && seen_space) {
        ++sent_coutner;
        seen_space = false;
      }
    }
  }

  std::cout << char_counter << " Characters" << "\n";
  std::cout << word_counter << " Words" << "\n";
  std::cout << sent_coutner << " Sentances" << "\n";
;}

int main() {
std::string text;
std::string token;

 while (std::getline(std::cin, token)) {
    text += token + " ";
  }

  counter(text);
 
}