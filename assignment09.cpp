#include <iostream>
#include <string> 
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <sstream>

std::string string_to_char(const std::string& hex_string) {
    // Create a string stream so the hex can be treated as a stream of words
    std::stringstream stream(hex_string);
    std::string result;
    std::string temp_hex;

    // Read in each white space seperated word from out stream
    while (stream >> temp_hex) {
        // Convert the hex to an int then cast to a char
        char ch = static_cast<char>(std::stoi(temp_hex, nullptr, 16));
        // Then add that char to the final result
        result += ch;
    }
    return result;
}

std::string to_upper_case(const std::string& input) {
    std::string upper_str = "";
    for (char i : input) {
        if (std::isalpha(i)) {
        upper_str += toupper(i);
        } else {
            upper_str += i;
        }
    }
    return upper_str;
}

int main() {
    std::unordered_map<std::string, std::string> table;
    std::string key_code_point = "";
    std::string key_name = "";
    std::string value = "";
    std::string input = "";

    std::ifstream file("/srv/datasets/utf8.txt");
    std::string file_line = "";

    while (std::getline(file, file_line)) {

        // Find the tabs that seperate data values in the line that has just been read in
        auto tab1 = file_line.find('\t');
        auto tab2 = file_line.find('\t', tab1 + 1);

        // Use the tabs to find that data I need for each of map keys and vaules
        key_code_point = file_line.substr(0, tab1);
        key_name = file_line.substr(tab1 + 1, tab2 - (tab1 + 1));
        value = file_line.substr(tab2 + 1, file_line.size());

        // Remove the U+ from the original key code point in case I get a code point without it in the input
        key_code_point.erase(0, 2);

        // Remove any leading zeros from the code point
        key_code_point.erase(0, key_code_point.find_first_not_of('0'));

        // Set up my map by setting keys and values from the file I am reading from
        table.emplace(key_code_point, value);
        table.emplace(key_name, value);

        // Make sure file_line is empty before reading more into it
        file_line = "";
    }
    file.close();

    // Reads in the user input checks it against the map that was just set up to find the correct hex value
    while (std::getline(std::cin, input)) {
        // Make all letters uppercase
        input = to_upper_case(input);

        // Erase the U+ so all its working with is the code
        if (input.substr(0, 2) == "U+") {
            input.erase(0, 2);
        }
        // Erase any leading 0's
        input.erase(0, input.find_first_not_of('0'));

        auto key = table.find(input);
        
        // Checks to make sure that the input key is a value in our map
        if (key != table.end()) {
            // Get the value associated with the key
            auto output_value = key->second;
            auto output = string_to_char(output_value);
            std::cout << output;
        } else {
            std::string output = input;
            char leading_str1 = '0';
            char leading_str2 = 'x';
            output.push_back(leading_str1 + leading_str2);
            std::cout << string_to_char(output);
        }
    }
}