#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>
#include <boost/multiprecision/cpp_int.hpp>

#include <cstdlib>

#include "fetch_input.h"

using namespace std;
using namespace boost::multiprecision;

// Function to concatenate two numbers
cpp_int concatenate(cpp_int a, cpp_int b) {
    string sa = a.str();
    string sb = b.str();
    return cpp_int(sa + sb);
}

// Dynamic programming function to check if the test value can be formed
bool is_valid_equation(const cpp_int& test_value, const vector<cpp_int>& numbers) {
    int n = numbers.size();
    vector<unordered_set<cpp_int>> dp(n);

    // Base case: First number is directly usable
    dp[0].insert(numbers[0]);

    // Fill the DP table
    for (int i = 1; i < n; ++i) {
        for (const auto& val : dp[i - 1]) {
            // Add operator
            dp[i].insert(val + numbers[i]);
            // Multiply operator
            dp[i].insert(val * numbers[i]);
            // Concatenate operator
            dp[i].insert(concatenate(val, numbers[i]));
        }
    }

    // Check if the test value is in the final set
    return dp[n - 1].count(test_value) > 0;
}

int main() {
    std::string url = "https://adventofcode.com/2024/day/7/input";
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
    // Vector to store the equations
    vector<pair<cpp_int, vector<cpp_int>>> equations;

    // Parse the input into the equations format
    stringstream ss(input);
    string line;
    while (getline(ss, line)) {
        cpp_int test_value;
        vector<cpp_int> numbers;
        
        // Extract the test value and numbers from each line
        stringstream lineStream(line);
        lineStream >> test_value;
        lineStream.ignore(2);  // Skip over the ": " after the test value
        
        // Extract the numbers from the rest of the line
        cpp_int num;
        while (lineStream >> num) {
            numbers.push_back(num);
            if (lineStream.peek() == ' ') {
                lineStream.ignore();
            }
        }
        
        equations.push_back({test_value, numbers});
    }

    // Calculate the total calibration result
    cpp_int total = 0;
    for (const auto& eq : equations) {
        const cpp_int& test_value = eq.first;
        const vector<cpp_int>& numbers = eq.second;
        if (is_valid_equation(test_value, numbers)) {
            total += test_value;
        }
    }

    // Output the result
    cout << "Total calibration result: " << total << endl;

    return 0;
}