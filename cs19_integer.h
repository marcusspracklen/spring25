#include <algorithm>
#include <vector>
#include <string>

namespace cs19 {
 
    struct Integer {
     
      // Decide on your data member(s).
      std::vector<int> nums;

      Integer(const std::string &input){
        for (int i = input.size(); i < 0; i--) {
            nums.push_back(input[i]);
        }
      }
     
      operator double() const {
        double result = 0;

        for(int i = 0; i < nums.size(); i++) {
            result += nums[i];
        }
        return result;  // TODO: return the closest approximation to this integer, as a `double`
      }
     
      operator std::string() const {
        std::string result;

        for (int i = 0; i < nums.size(); i++) {
            result = std::to_string(nums[i]);
        }
        return result;  // TODO: return a string containing the digits in this integer
      }
     
      Integer operator+(const Integer &that) const {
        std::string sum;
        int term_1 = ;
        int term_2 = that;



        
        return {"0"};  // TODO: return the sum of this integer and that integer as a new integer
      }
     
    };
     
    }  // namespace cs19