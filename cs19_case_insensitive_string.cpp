#include "cs19_case_insensitive_string.h"

namespace cs19 {

// Constructor
CaseInsensitiveString::CaseInsensitiveString(const std::string& str) : original_(str) {}

// Conversion Operator
CaseInsensitiveString::operator std::string() const {
    return original_;
}

// Accessor
const std::string& CaseInsensitiveString::str() const {
    return original_;
}

std::string CaseInsensitiveString::to_lower(const std::string& s) {
    std::string result = s;
    for (char& c: result) {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    return result;
}

// Equality operator
bool operator==(const CaseInsensitiveString& lhs, const CaseInsensitiveString& rhs) {
    return CaseInsensitiveString::to_lower(lhs.original_) == CaseInsensitiveString::to_lower(rhs.original_);
}

bool operator==(const CaseInsensitiveString& lhs, const std::string& rhs) {
    return CaseInsensitiveString::to_lower(lhs.original_) == CaseInsensitiveString::to_lower(rhs);
}

bool operator==(const std::string& lhs, const CaseInsensitiveString& rhs) {
    return lhs == rhs;
}

// Comparison operator
std::strong_ordering operator<=>(const CaseInsensitiveString& lhs, const CaseInsensitiveString& rhs) {
    return CaseInsensitiveString::to_lower(lhs.original_) <=> CaseInsensitiveString::to_lower(rhs.original_);
}

std::string begin() {
    return original_.begin();
}

std::string end() {
    return orignal_.end();
}

// Stream input
std::istream& operator>>(std::istream& in, CaseInsensitiveString& s) {
    in >> s.original_;
    return in;
}

// Stream output
std:: ostream& operator<<(std::ostream& out, const CaseInsensitiveString& s) {
    out << s.original_;
    return out;
}

}; // namespace cs19