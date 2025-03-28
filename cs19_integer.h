#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

namespace cs19 {
 
    struct Integer {
     
      // Decide on your data member(s).
      std::vector<int> nums;

      Integer(const std::string &input){
        for (int i = input.size() - 1; i != 0; i--) {
            nums.push_back(input[i]);
        }
      }
     
      operator double() const {
        double result = 0;
        int column = 1;

        for(auto i = nums.rbegin(); i != nums.rend(); i--) {
            result += (*i * column);
            column = column * 10;
        }
        return {result};  // TODO: return the closest approximation to this integer, as a `double`
      }

      operator std::string() const {
        std::string result;

        for (int i = 0; i != nums.size(); i++) {
            result.push_back(nums[i]);
        }
        return result;  // TODO: return a string containing the digits in this integer
      }
     
    //   Integer operator+(const Integer &that) const {
    //     std::string sum;
    //    // Integer term_1;
    //     int term_2 = that;



        
    //     //return {"0"};  // TODO: return the sum of this integer and that integer as a new integer
    //   }

    //   Integer operator==(const Integer &that) {

    //   }
     
    };
     
    }  // namespace cs19