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

  // Reads into the array "input", the for loop is here if the input exceeds the maximum value of
  // the data type.
  for (std::cin.read(input, VAR_SIZE); std::cin.gcount(); std::cin.read(input, VAR_SIZE)) {
    // Iterates an amount of times equal to the number of characters that were input.
    // This loop's job is to count up the total number of characters and what letter they were by
    // putting them into array and storing them there so we can access them later.
    for (int i = 0; i < std::cin.gcount(); ++i) {
      // Checks to makes sure that the input was part of the alphabet and does not have another
      // ASCII value outside of A-Z.
      if (input[i] > ASCII_VAL_A && input[i] < ASCII_VAL_z) {
        int place_holder = 0;
        // Passes placeholder the value of the array at "i".
        place_holder = input[i];
        // Adds one to the value at "i".
        counter[place_holder - ASCII_VAL_A] += ADD_ONE;
        total_chars += ADD_ONE;
      }
    }
  }

  // For loop to iterate through the array that counted up all the indivdual letters.
  // It has three variables i iterates through the uppercase letters, n iterates through the
  // lowercase letters, and j iterates through the values of the ASCII values from "A" to "z" so we
  // can label our outputs.
  for (int i = (ASCII_VAL_A - ASCII_VAL_A), n = (ASCII_VAL_a - ASCII_VAL_A), j = ASCII_VAL_A;
       i <= (ASCII_VAL_Z - ASCII_VAL_A); ++i, ++n, ++j) {
    char letter_label = j;
    int letter_count = 0;
    // Adds together the upper and lowercase letters so we know the total number
    letter_count = counter[i] + counter[n];

    // Calculates the percent that each letter appears in the whole input.
    percent = (letter_count / total_chars) * 100;

    // Checks to make sure that in the input the letter we are currently checking appeared.
    if (letter_count != 0) {
      std::cout << letter_label << " " << letter_count << " ";
      // Prints out the percentange in "*""
      for (int i = 0; i < percent; ++i) {
        std::cout << "*";
      }
      std::cout << "\n";
    }
  }
}
