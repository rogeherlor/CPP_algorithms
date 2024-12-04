#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>

#include <cstdlib>

#include "fetch_input.h"

int main() {
    std::string url = "https://adventofcode.com/2024/day/2/input";
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

    // Parse the input string to extract the matrix
    std::vector<std::vector<int>> matrix;

    // Use a stringstream to split the input by lines
    std::istringstream stream(input);
    std::string line;

    while (std::getline(stream, line)) {
        std::vector<int> row;
        std::istringstream line_stream(line);
        int num;
        while (line_stream >> num) {
            row.push_back(num);
        }
        if (!row.empty()) {
            matrix.push_back(row);
        }
    }

    //********************** Algorithm **********************//
    // Variable to count safe reports
    int safeCount = 0;

    // Iterate through each report
    for (const auto& report : matrix) {
        bool isIncreasing = true, isDecreasing = true, isValid = true;

        // Check the trend and validity
        for (size_t j = 1; j < report.size(); ++j) {
            int diff = report[j] - report[j - 1];
            if (std::abs(diff) > 3 || diff == 0) {
                isValid = false;
                break;
            }
            if (diff > 0) {
                isDecreasing = false; // Not decreasing
            }
            if (diff < 0) {
                isIncreasing = false; // Not increasing
            }
        }

        // Check if the report is safe
        if (isValid && (isIncreasing || isDecreasing)) {
            ++safeCount;
        }
    }

    // Output the number of safe reports
    std::cout << "Number of safe reports: " << safeCount << std::endl;

    return 0;
}