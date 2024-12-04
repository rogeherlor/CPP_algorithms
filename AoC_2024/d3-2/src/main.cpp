#include <iostream>
#include <string>
#include <regex>

#include <cstdlib>

#include "fetch_input.h"

int calculateSumOfMultiplicationsWithConditions(const std::string& input) {
    // Combined regex pattern to match all instructions (do(), don't(), mul(X, Y))
    std::regex instructionRegex(R"(do\(\)|don't\(\)|mul\((\d+),(\d+)\))");

    std::smatch match;
    int sum = 0;
    bool mulEnabled = true; // Multiplications start enabled by default

    auto begin = input.cbegin();
    auto end = input.cend();

    // Process the string for all instructions in order
    while (std::regex_search(begin, end, match, instructionRegex)) {
        std::string matchedStr = match.str();

        if (matchedStr == "do()") {
            // Enable future mul instructions
            mulEnabled = true;
        } else if (matchedStr == "don't()") {
            // Disable future mul instructions
            mulEnabled = false;
        } else if (match[1].matched && match[2].matched) {
            // Found a mul(X, Y) instruction
            if (mulEnabled) {
                // If enabled, extract numbers and calculate their product
                int x = std::stoi(match[1]);
                int y = std::stoi(match[2]);
                sum += x * y;
            }
        }

        // Move to the next part of the string
        begin = match.suffix().first;
    }

    return sum;
}

int main() {
    std::string url = "https://adventofcode.com/2024/day/3/input";
    const char* sessionEnv = std::getenv("AOC_SESSION"); // Replace with your actual session cookie
    if (!sessionEnv) {
        std::cerr << "Error: AOC_SESSION environment variable is not set." << std::endl;
        return 1; // Exit with an error code
    }
    std::string sessionCookie = sessionEnv;
    
    // Call fetchInput function to get the input text
    std::string input = fetchInput(url, sessionCookie);

    // Print the response from the server
    std::cout << "Response from server:\n" << input << std::endl;


    //********************** Algorithm **********************//
    int result = calculateSumOfMultiplicationsWithConditions(input);

    // Output the result
    std::cout << "Sum of enabled multiplications: " << result << std::endl;

    return 0;
}