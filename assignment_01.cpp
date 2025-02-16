#include <iostream>

int main() {
  constexpr int ADD_ONE = 1;
  constexpr int VAR_SIZE = 8192;
  constexpr int ASCII_VAL_A = 65;
  constexpr int ASCII_VAL_a = 97;
  constexpr int ASCII_VAL_Z = 90;
  constexpr int ASCII_VAL_z = 122;

  int counter[ASCII_VAL_z - ASCII_VAL_A] = {0};
  char input[VAR_SIZE];
  double total_chars = 0;
  double percent = 0;

  for (std::cin.read(input, VAR_SIZE); std::cin.gcount(); std::cin.read(input, VAR_SIZE)) {
    for (int i = 0; i < std::cin.gcount(); ++i) {
      if (input[i] > ASCII_VAL_A && input[i] < ASCII_VAL_z) {
        int place_holder = 0;
        place_holder = input[i];
        counter[place_holder - ASCII_VAL_A] += ADD_ONE;
        total_chars += ADD_ONE;
      }
    }
  }

  for (int i = (ASCII_VAL_A - ASCII_VAL_A), n = (ASCII_VAL_a - ASCII_VAL_A), j = ASCII_VAL_A;
       i <= (ASCII_VAL_Z - ASCII_VAL_A); ++i, ++n, ++j) {
    char test = j;
    int letter_count = 0;
    letter_count = counter[i] + counter[n];

    percent = (letter_count / total_chars) * 100;

    if (letter_count != 0) {
      std::cout << test << " " << letter_count << " ";
      for (int i = 0; i < percent; ++i) {
        std::cout << "*";
      }
      std::cout << "\n";
    }
  }
}
