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
    // Step 1: Count occurrences of each number in the right list
    std::unordered_map<int, int> rightCount;
    for (int num : rightList) {
        rightCount[num]++;
    }

    // Step 2: Calculate the similarity score
    int similarityScore = 0;
    for (int num : leftList) {
        similarityScore += num * rightCount[num];
    }

    // Output the similarity score
    std::cout << "Similarity Score: " << similarityScore << std::endl;

    return 0;
}