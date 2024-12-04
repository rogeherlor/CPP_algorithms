#include <iostream>
#include <string>
#include <regex>

#include <cstdlib>

#include "fetch_input.h"

// Algorithm to process valid mul instructions
int calculateSumOfMultiplications(const std::string& input) {
    // Regular expression to match valid mul(X,Y) instructions
    std::regex mulRegex(R"(mul\((\d{1,3}),(\d{1,3})\))");
    std::smatch match;

    int sum = 0;
    auto begin = input.cbegin();
    auto end = input.cend();

    // Find all matches of valid mul instructions
    while (std::regex_search(begin, end, match, mulRegex)) {
        int x = std::stoi(match[1]);
        int y = std::stoi(match[2]);
        sum += x * y;
        begin = match.suffix().first; // Move to the next part of the string
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
    // Use the algorithm to compute the sum of valid multiplications
    int result = calculateSumOfMultiplications(input);

    // Output the final result
    std::cout << "Sum of all valid multiplications: " << result << std::endl;

    return 0;
}