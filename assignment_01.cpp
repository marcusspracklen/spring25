#include <iostream>
#include <cmath>

int main() {
  constexpr int BUFFER_SIZE = 8192;
  constexpr int ASCII_VAL_A = 'A';
  constexpr int ASCII_VAL_a = 'a';
  constexpr int ASCII_VAL_Z = 'Z';
  constexpr int ASCII_VAL_z = 'z';

  int counter[26] = {0};
  char input[BUFFER_SIZE];
  double total_chars = 0;

  // Reads into the array "input", the for loop is here if the input exceeds the maximum value of
  // the data type.
  for (std::cin.read(input, BUFFER_SIZE); std::cin.gcount(); std::cin.read(input, BUFFER_SIZE)) {
    // Iterates an amount of times equal to the number of characters that were input.
    // This loop's job is to count up the total number of characters and what letter they were by
    // putting them into array and storing them there so we can access them later.
    for (int i = 0; i < std::cin.gcount(); ++i) {
      // Checks to makes sure that the input was part of the alphabet and does not have another
      // ASCII value outside of A-Z.
      if ((input[i] >= ASCII_VAL_A && input[i] <= ASCII_VAL_Z) || (input[i] >= ASCII_VAL_a && input[i] <= ASCII_VAL_z)) {
        // Passes placeholder the value of the array at "i".
        int index = (input[i] >= ASCII_VAL_a) ? (input[i] - ASCII_VAL_a) : (input[i] - ASCII_VAL_A);
        // Adds one to the value at "i".
        counter[index]++;
        total_chars++;
      }
    }
  }

  // For loop to iterate through the array that counted up all the indivdual letters.
  // It has three variables i iterates through the uppercase letters, n iterates through the
  // lowercase letters, and j iterates through the values of the ASCII values from "A" to "z" so we
  // can label our outputs.
  for (int i = 0, j = ASCII_VAL_A ; i < 26; ++i, ++j) {
    char letter_label = j;
    int letter_count = counter[i];
    // Calculates the percent that each letter appears in the whole input.
    //int percent = static_cast<int>(std::ceil((static_cast<double>(letter_count) / total_chars) * 100));
    int percent = (static_cast<double>(letter_count) / total_chars) * 100;
    // Checks to make sure that in the input the letter we are currently checking appeared.
    if (letter_count != 0) {
      std::cout << letter_label << " " << letter_count << " ";
      // Prints out the percentange in "*""
      for (int star_count = 0; star_count < percent; ++star_count) {
        std::cout << "*";
      }
      std::cout << "\n";
    }
  }
}
