#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>

#include <cstdlib>

#include "fetch_input.h"

int main() {
    std::string url = "https://adventofcode.com/2024/day/1/input";
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

    // Separate lists for left and right values
    std::vector<int> leftList, rightList;

    // Use a stringstream to split the input by lines
    std::istringstream stream(input);
    std::string line;

    // Read each line from the input string and split it into two integers
    while (std::getline(stream, line)) {
        int num1, num2;
        std::istringstream line_stream(line);

        // Read two integers from the line and store them in the respective lists
        if (line_stream >> num1 >> num2) {
            leftList.push_back(num1);
            rightList.push_back(num2);
        }
    }

    //********************** Algorithm **********************//
    // Sort both lists
    std::sort(leftList.begin(), leftList.end());
    std::sort(rightList.begin(), rightList.end());

    // Calculate the total distance
    int totalDistance = 0;
    for (size_t i = 0; i < leftList.size(); ++i) {
        totalDistance += std::abs(leftList[i] - rightList[i]);
    }

    // Output the total distance
    std::cout << "Total distance: " << totalDistance << std::endl;

    return 0;
}