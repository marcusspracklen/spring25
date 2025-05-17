#ifndef CS19_CASE_INSENSITIVE_STRING_H
#define CS19_CASE_INSENSITIVE_STRING_H

#include <string>
#include <iostream>
#include <cctype>
#include <compare>

namespace cs19 {

class CaseInsensitiveString {
public:

    // Constructors
    CaseInsensitiveString() = default;
    CaseInsensitiveString(const std::string& str);

    // Conversion operator
    operator std::string() const;

    const std::string& str() const;

    // Comparison operators
    friend bool operator==(const CaseInsensitiveString& lhs, const CaseInsensitiveString& rhs);
    friend bool operator==(const CaseInsensitiveString& lhs, const std::string& rhs);
    friend bool operator==(const std::string& lhs, const CaseInsensitiveString& rhs);

    friend std::strong_ordering operator<=>(const CaseInsensitiveString& lhs, const CaseInsensitiveString& rhs);

    friend std::istream& operator>>(std::istream& in, CaseInsensitiveString& s);
    friend std::ostream& operator<<(std::ostream& out, const CaseInsensitiveString& s);

    friend std::string::iterator begin();
    friend std::string::iterator end();

private:
    std::string original_;

    static std::string to_lower(const std::string& s);
};

} // namespace cs19
#endif