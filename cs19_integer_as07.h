#ifndef cs19_integer
#define cs19_integer

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

namespace cs19 {
struct Integer {
std::vector<int> nums;
bool is_negative = false;


    Integer(const std::string &input){
        for (int i = input.size() - 1; i >= 0; i--) {
            if(!std::isdigit(input[i])) {
                if(input[i] == '-') {
                    is_negative = true;
                } else {
                    std::cerr << "ERROR: Unkown character entered." << "\n";
                }
            }
            else{
                nums.push_back(input[i] - '0');
            }
        }
    }

    operator double() const {
        double result = 0;
        double column = 1;

        for (int i : nums) {
            result += (i * column);
            column = column * 10;
        }

        if(is_negative) {
            result *= (-1);
        }

        return result;
    }

    operator std::string() const {
        std::string result;

        if(is_negative) {
            result.push_back('-');
        }

        for (int i = nums.size() - 1; i >= 0; i--) {
            result.push_back(nums[i] + '0');
        }

        
        return result;
    }

    Integer operator+(const Integer &that) const {
        std::vector<int> add_result;
        int carry = 0;
        std::string result;
        int biggest_num = std::max(nums.size(), that.nums.size());

        for (int i = 0; i < biggest_num; i++) {
            int num0 = 0;
            int num1 = 0;
            int num0_length = nums.size();
            int num1_length = that.nums.size();
            if (i < num0_length) {
                num0 = nums[i];
            }
            if (i < num1_length) {
                num1 = that.nums[i];
            }
            int sum = num0 + num1 + carry;
            add_result.push_back(sum % 10);
            carry = sum / 10;
        }

        if (carry != 0) {
            add_result.push_back(carry);
        }

        for (int i = add_result.size() - 1; i >= 0; i--) {
            result.push_back(add_result[i] + '0');
        }

        return Integer(result);
    }

    Integer operator-(const Integer &that) const {
        std::vector<int> minus_result;
        int borrow = 0;
        std::string result;
        int biggest_num = std::max(nums.size(), that.nums.size());

        bool first_time = true;
        bool gonna_be_negative = false;

        for(int i = biggest_num - 1; i >= 0; --i) {
            int num0 = nums[i];
            int num1 = that.nums[i];
            int num0_length = nums.size();
            int num1_length = that.nums.size();
            if (i < num0_length) {
                num0 = nums[i];
            }
            if (i < num1_length) {
                num1 = that.nums[i];
            }

            
                int checker = num0 - num1;
            if(checker < 0) {
                num0 = num1;
                num1 = num0;
                first_time = false;
                gonna_be_negative = true;
            }

            int difference = num0 - num1;

                if(num0 - num1 <= 0) {
                    difference += 10;
                    borrow = 1;
             } else {
                    borrow = 0;
             }


            minus_result.push_back(difference);
        }

        if(borrow != 0) {
            minus_result.push_back(borrow);
        }

        // Removes any leading zeros
        for(int i = 0; i < minus_result.size(); i++) {
            if(minus_result[i] == 0) {
                minus_result.erase(minus_result.begin() + i);
            }

        }

        // The vector minus_result is backwards so we have to iterate across it in reverse to get the right number
        for(int i = minus_result.size() - 1; i >= 0; i--) {
            if(i = 0) {
                if(gonna_be_negative) {
                minus_result[i] = minus_result[i] * (-1);
                }
            }
            result.push_back(minus_result[i] + '0');
        }

        return Integer(result);
    }

    Integer operator*(const Integer &that) const {
        std::vector<int> mulpt_result; 
        int carry = 0;
        std::string result;
        int biggest_num = std::max(nums.size(), that.nums.size());


        for(int i = 0; i < biggest_num; i++) {
            int num0 = 0;
            int num1 = 0;
            int num0_length = nums.size();
            int num1_length = that.nums.size();

            if(i < num0_length) {
                num0 = nums[i];
            }
            if(i < num1_length) {
                num1 = that.nums[i];
            }

            int product = (num0 * num1) + carry;
            mulpt_result.push_back(product % 10);
            carry = product / 10;
        }

        if(carry != 0 ) {
            mulpt_result.push_back(carry);
        }

        for(int i = mulpt_result.size() - 1; i >= 0; i--) {
            result.push_back(mulpt_result[i] + '0');
        }


        return Integer(result);
    }

    bool operator==(const Integer &that) {
        bool is_equal;
        is_equal = nums == that.nums;

        return is_equal;
    }

    bool operator!=(const Integer &that) {
        bool is_equal;
        is_equal = nums != that.nums;

        return is_equal;
    }

    bool operator<(const Integer &that) {
        bool is_less;

        is_less = nums < that.nums;

        return is_less;
    }

    bool operator<=(const Integer &that) {
        bool is_less_or;

        if(is_less_or = nums < that.nums) {
            return is_less_or = true;
        }
        if(is_less_or = nums == that.nums) {
            return is_less_or = true;
        } else {
            return is_less_or;
        }
    }

    bool operator>(const Integer &that) {
        bool is_greater;

        is_greater = nums > that.nums;
        return is_greater;
    }

    bool operator>=(const Integer &that) {
        bool is_greater_or;

        if(is_greater_or = nums > that.nums) {
            return is_greater_or = true;
        }
        if(is_greater_or = nums == that.nums) {
            return is_greater_or = true;
        } else {
            return is_greater_or;
        }
    }
};

}  // namespace cs19
#endif