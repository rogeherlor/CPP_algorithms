#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>

#include <cstdlib>

#include "fetch_input.h"

// Function to check if a report is safe
bool isSafeReport(const std::vector<int>& report) {
    if (report.size() < 2) return false;

    bool isIncreasing = true, isDecreasing = true;

    for (size_t i = 1; i < report.size(); ++i) {
        int diff = report[i] - report[i - 1];
        if (std::abs(diff) > 3 || diff == 0) return false;
        if (diff > 0) isDecreasing = false; // Not decreasing
        if (diff < 0) isIncreasing = false; // Not increasing
    }

    return isIncreasing || isDecreasing;
}

// Function to check if a report can be made safe by removing one level
bool canBeMadeSafe(const std::vector<int>& report) {
    for (size_t i = 0; i < report.size(); ++i) {
        std::vector<int> modifiedReport = report;
        modifiedReport.erase(modifiedReport.begin() + i); // Remove the i-th level
        if (isSafeReport(modifiedReport)) {
            return true;
        }
    }
    return false;
}

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

    // Check each report
    for (const auto& report : matrix) {
        if (isSafeReport(report) || canBeMadeSafe(report)) {
            ++safeCount;
        }
    }

    // Output the number of safe reports
    std::cout << "Number of safe reports (with Problem Dampener): " << safeCount << std::endl;

    return 0;
}