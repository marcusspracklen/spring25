#ifndef cs19_integer
#define cs19_integer

#include <algorithm>
#include <vector>
#include <string>

namespace cs19 {
struct Integer {
std::vector<int> nums;
mutable bool is_negative = false;


    Integer() {
        nums.push_back(0);
        is_negative = false;
    }

    Integer(const Integer &that) {
        nums = that.nums;
        is_negative = that.is_negative;
    }

    Integer(const std::string &input){
        for (int i = input.size() - 1; i >= 0; i--) {
            if(!std::isdigit(input[i])) {
                if(input[i] == '-') {
                    is_negative = true;
                }
            } else{
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
        bool gonna_be_neg = false;

        if(this->is_negative && that.is_negative) {
            gonna_be_neg = true;
        }

        if(this->is_negative && !that.is_negative) {
            is_negative = false;
            std::string result = that - *this;
            return Integer(result);
        }

        if(!this->is_negative && that.is_negative) {
            that.is_negative = false;
            std::string result = *this - that;
            return Integer(result);
        }

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

        if(gonna_be_neg) {
            result.push_back('-');
        }

        return Integer(result);
    }

    Integer operator-(const Integer &that) const {
        std::vector<int> minus_result;
        int borrow = 0;
        std::string result;
        int biggest_num = std::max(nums.size(), that.nums.size());
        bool gonna_be_neg = false;
        bool invert = false;

        if(*this < that) {
            invert = true;
        }

        if (this->is_negative && !that.is_negative) {
            is_negative = false;
            auto abs_this = *this;
            auto abs_that = that;
            std::string result = abs_this + abs_that;

            result.push_back('-');
            return Integer(result);
        }

        if(that.is_negative) {
            that.is_negative = false;
            auto abs_this = *this;
            auto abs_that = that;
            std::string result = abs_this + abs_that;

            return Integer(result);
        }


        for (int i = 0; i < biggest_num; ++i) {
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

            int difference;

            if(invert) {
                gonna_be_neg = true;
                difference = num1 - num0 - borrow;
            } else {
                difference = num0 - num1 - borrow;
            }

            // Checks to see if num1 was bigger than num0 and if so "borrows" a 10 from the next place
            if(difference < 0) {
                difference += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }

            minus_result.push_back(difference);
        }

        // Add any extra borrowing we had left over
        if(borrow != 0) {
            minus_result.push_back(borrow);
        }

        if(gonna_be_neg) {
            result.push_back('-');
        }

        // The vector minus_result is backwards so we have to iterate across it in reverse to get the right number
        for(int i = minus_result.size() - 1; i >= 0; i--) {
            result.push_back(minus_result[i] + '0');
        }

        return Integer(result);
    }

    Integer operator-() const {
        Integer result = *this;
        if(!(nums.size() == 1 && nums[0] == 0)) {
            result.is_negative = !is_negative;
        }
        return result;
    }

    Integer operator*(const Integer &that) const {
        // Makes sure neither number is 0
        if ((nums.size() == 1 && nums[0] == 0) || (that.nums.size() == 1 && that.nums[0] == 0)) {
            return Integer("0");
        }

        int result_size = nums.size() + that.nums.size();
        std::vector<int> times_result(result_size, 0);

        // Loop multiplies every digit of this to every digit of that
        for (size_t i = 0; i < nums.size(); ++i) {
            int carry = 0;
            for (size_t j = 0; j < that.nums.size(); ++j) {
                // Adds the current sum to the new product
                int product = times_result[i + j] + nums[i] * that.nums[j] + carry;
                times_result[i + j] = product % 10;
                carry = product / 10;
            }

            // If there is any remaining carry value add it to the result
                if(carry > 0) {
                    times_result[i + that.nums.size()] += (carry % 10);
            }
        }

        // Checks for and removes any leading zeros
        while (times_result.size() > 1 && times_result.back() == 0) {
            times_result.pop_back();
        }

        // Converts digits to a string
        std::string result;
        for (int i = times_result.size() - 1; i >= 0; --i) {
            result.push_back(times_result[i] + '0');
        }

        // Handles negatives, the result can only be negative if only one of the nums is negative
        Integer final_result(result);
        final_result.is_negative = (is_negative != that.is_negative);
        return Integer(final_result);
    }

    friend std::ostream& operator<<(std::ostream& os, const Integer& value) {
        os << static_cast<std::string>(value);
        return os;
    }

    bool operator==(const Integer &that) const {
        bool is_equal;
        if(this->is_negative != that.is_negative) {
            return false;
        }

        is_equal = nums == that.nums;

        return is_equal;
    }

    bool operator!=(const Integer &that) {
        bool not_equal;
        if(this->is_negative != that.is_negative) {
            return true;
        }

        if(nums == that.nums) {
            return false;
        } else {
            return true;
        }

    }

    bool operator<(const Integer &that) {
        bool is_less;

        if(this->is_negative != that.is_negative) {
            if(this->is_negative && !that.is_negative) {
                return true;
            }
            else if(!this->is_negative && that.is_negative) {
                return false;
            }
        } 

        if(nums.size() > that.nums.size()) {
            return false;
        }
        if(nums.size() < that.nums.size()) {
            return true;
        }

        if(this->is_negative == that.is_negative) {
            for(int i = nums.size() - 1; i >= 0; i--) {
                if(nums[i] != that.nums[i]) {
                    is_less = nums[i] > that.nums[i];
                }
            }

        } else {

        for(int i = nums.size() - 1; i >= 0; i--) {
            if(nums[i] != that.nums[i]) {
                is_less = nums[i] < that.nums[i];
            }
        }
    }

        return is_less;
    }

    bool operator<=(const Integer &that) {
        bool is_less_or;
        if(this->operator==(that)) {
            return true;
        } else {
            is_less_or = this->operator<(that);
        }
        return is_less_or;
    }

    bool operator>(const Integer &that) {
        bool is_greater;

        if(this->is_negative != that.is_negative) {
            if(this->is_negative && !that.is_negative) {
                return false;
            }
            else if(!this->is_negative && that.is_negative) {
                return true;
            }
        } 

        if(nums.size() < that.nums.size()) {
            return false;
        }
        if(nums.size() > that.nums.size()) {
            return true;
        }

        if(this->is_negative == that.is_negative) {

            for(int i = nums.size() - 1; i >= 0; i--) {
                if(nums[i] != that.nums[i]) {
                    is_greater = nums[i] < that.nums[i];
                }
            }

        }else {

        for(int i = nums.size() - 1; i >= 0; i--) {
            if(nums[i] != that.nums[i]) {
                is_greater = nums[i] > that.nums[i];
            }
        }

    }

        return is_greater;
    }

    bool operator>=(const Integer &that) {
        bool is_greater_or;
        if(this->operator==(that)) {
            return true;
        } else {
            is_greater_or = this->operator>(that);
        }
        return is_greater_or;
    }
};

}  // namespace cs19
#endif
