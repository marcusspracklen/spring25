#include <gmp.h>
#include <gmpxx.h>
#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include "cs19_integer.h"
 
int main() {
  std::string left_str, right_str, op;
  while (std::cin >> left_str >> op >> right_str) {

    std::cout << cs19::Integer("-101713657699297453207081186099992326985") * cs19::Integer("11") << "\n";

    try {
      cs19::Integer cs19_left(left_str), cs19_right(right_str);
      mpz_class mpz_left(left_str), mpz_right(right_str);
      if (op == "+") {
        cs19::Integer cs19_result = cs19_left + cs19_right;
        mpz_class mpz_result = mpz_left + mpz_right;
        std::cout << cs19_result << '\n';
        assert(std::string(cs19_result) == mpz_result.get_str());
      } else if (op == "-") {
        cs19::Integer cs19_result = cs19_left - cs19_right;
        mpz_class mpz_result = mpz_left - mpz_right;
        std::cout << cs19_result << '\n';
        assert(std::string(cs19_result) == mpz_result.get_str());
      } else if (op == "*") {
        cs19::Integer cs19_result = cs19_left * cs19_right;
        mpz_class mpz_result = mpz_left * mpz_right;
        std::cout << cs19_result << '\n';
        assert(std::string(cs19_result) == mpz_result.get_str());
      } else if (op == "==") {
        bool cs19_result = cs19_left == cs19_right;
        bool mpz_result = mpz_left == mpz_right;
        std::cout << cs19_result << '\n';
        assert(cs19_result == mpz_result);
      } else if (op == "!=") {
        bool cs19_result = cs19_left != cs19_right;
        bool mpz_result = mpz_left != mpz_right;
        std::cout << cs19_result << '\n';
        assert(cs19_result == mpz_result);
      } else if (op == "<") {
        bool cs19_result = cs19_left < cs19_right;
        bool mpz_result = mpz_left < mpz_right;
        std::cout << cs19_result << '\n';
        assert(cs19_result == mpz_result);
      } else if (op == "<=") {
        bool cs19_result = cs19_left <= cs19_right;
        bool mpz_result = mpz_left <= mpz_right;
        std::cout << cs19_result << '\n';
        assert(cs19_result == mpz_result);
      } else if (op == ">") {
        bool cs19_result = cs19_left > cs19_right;
        bool mpz_result = mpz_left > mpz_right;
        std::cout << cs19_result << '\n';
        assert(cs19_result == mpz_result);
      } else if (op == ">=") {
        bool cs19_result = cs19_left >= cs19_right;
        bool mpz_result = mpz_left >= mpz_right;
        std::cout << cs19_result << '\n';
        assert(cs19_result == mpz_result);
      }
    } catch (std::exception &error) {
      std::cerr << error.what() << '\n';
    }
  }
}