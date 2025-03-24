#ifndef CS19_INTEGER_H_
#define CS19_INTEGER_H_

#include <string>
#include <algorithm>

namespace cs19s25 {


struct Integer {

    std::string value;

    Integer(const std::string& str) : value(str) {}

    operator double() const {
        return std::stod(value);
    }

    operator std::string() const {
        return value;
    }

    Integer operator+(const Integer &that) const {
        std::string result = "";
        int carry = 0;
        int i = value.size();
        int j = that.value.size() - 1;

        while (i >= 0 || j >=0 || carry) {
            int term1 = (i >= 0) ? value[i--] - '0' : 0;
            int term2 = (j >= 0) ? that.value[j--] - '0' : 0;

            int sum = term1 + term2 + carry; 
            carry = sum / 10;
            result.push_back((sum % 10) + '0');
        }

        std::reverse(result.begin(), result.end());
        return Integer(result);

    }



};
}

#endif
