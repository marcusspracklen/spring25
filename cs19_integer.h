#ifndef cs19_integer
#define cs19_integer

#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include <iostream>

namespace cs19 {

struct Integer {
    // Construct from string with error checking
    Integer(const std::string& input) {
        if (input.empty()) {
            throw std::invalid_argument("Input string cannot be empty.");
        }

        // Remove leading zeros 
        size_t first_non_zero = input.find_first_not_of('0');
        if (first_non_zero == std::string::npos) { 
            digits = {0}; // If all zeros, store zero
            return;
        }

        // Validate digits
        if (!std::all_of(input.begin(), input.end(), ::isdigit)) {
            throw std::invalid_argument("Input must only contain digits.");
        }

        // Store digits in reverse for easier arithmetic
        digits.reserve(input.size());
        for (auto it = input.rbegin(); it != input.rend(); ++it) {
            digits.push_back(*it - '0');
        }
    }

    // Convert to double (approximation with overflow check)
    operator double() const {
        double value = 0.0;
        double place_value = 1.0;

        for (int digit : digits) {
            value += digit * place_value;
            if (value > std::numeric_limits<double>::max() / 10) { 
                // Overflow check
                std::cerr << "Warning: Double overflow detected!" << std::endl;
                return std::numeric_limits<double>::infinity(); 
            }
            place_value *= 10.0;
        }
        return value;
    }

    // Convert to string
    operator std::string() const {
        if (digits.empty()) return "0";

        std::string result;
        result.reserve(digits.size());
        for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
            result += static_cast<char>(*it + '0');
        }
        return result;
    }

    // Addition operator
    Integer operator+(const Integer& other) const {
        std::vector<int> sum_digits;
        int carry = 0;
        size_t i = 0;

        // Loop until both vectors are empty and no carry
        while (i < digits.size() || i < other.digits.size() || carry) {

            int left_digit;
            if (i < digits.size()){
                left_digit = digits[i];
            }
            else {
                left_digit = 0;
            }

            int right_digit;
            if (i < other.digits.size()) {
                right_digit = other.digits[i];
            } 
            else {
                right_digit = 0;
            }

            int total = left_digit + right_digit + carry;
            sum_digits.push_back(total % 10);
            carry = total / 10;
            ++i;
        }

        return Integer(std::move(sum_digits));
    }

    // Equality operator
    bool operator==(const Integer& other) const {
        return digits == other.digits;
    }

    std::vector<int> digits;

    // Avoid duplication
    Integer(std::vector<int>&& digit_vector) : digits(std::move(digit_vector)) {}
};

} // namespace cs19

#endif
