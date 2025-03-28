#ifndef CS19_INTEGER_H
#define CS19_INTEGER_H

#include <string>
#include <vector>
#include <algorithm>
#include <sstream> 

namespace cs19s25 {

struct Integer {
  std::vector<int> digits;

  Integer(const std::string& input_string) {
    digits.resize(input_string.size());
    for (size_t index = 0; index < input_string.size(); ++index) {
        digits[input_string.size() - 1 - index] = input_string[index] - '0';
    }
  }

  operator double() const {
    double value = 0.0;
    double base_ten = 1.0;
    for (int digit : digits) {
      value += digit * base_ten;
      base_ten *= 10.0;
    }
    return value;
  }

  operator std::string() const {
    if (digits.empty()) {
      return "0";
    }

    std::stringstream result;
    for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
      result << *it;
    }
    return result.str();
  }

  Integer operator+(const Integer& other_integer) const {
    std::vector<int> result_digits;
    int carry = 0;
    size_t current_index = 0;
    while (current_index < digits.size() || current_index < other_integer.digits.size() || carry) {

      int digit_one;
      if (current_index < digits.size()) {
        digit_one = digits[current_index];
      }
      else {
        digit_one = 0;
      }

      int digit_two;
      if (current_index < other_integer.digits.size()) {
        digit_two = other_integer.digits[current_index];
      }
      else {
        digit_two = 0;
      }

      int sum = digit_one + digit_two + carry;
      result_digits.push_back(sum % 10);
      carry = sum / 10;
      ++current_index;
    }
    return Integer(result_digits);
  }

  bool operator==(const Integer& comparison_integer) const {
    return digits == comparison_integer.digits;
  }

  Integer(const std::vector<int>& digit_vector) {
    digits = digit_vector;
  }

};

}

#endif