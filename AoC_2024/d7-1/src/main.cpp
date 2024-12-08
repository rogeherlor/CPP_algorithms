#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <boost/multiprecision/cpp_int.hpp>

#include <cstdlib>

#include "fetch_input.h"

using namespace std;
using namespace boost::multiprecision;

// Function to evaluate the expression
cpp_int evaluate_expression(const vector<cpp_int>& numbers, const vector<char>& operators) {
    cpp_int result = numbers[0];  // Start with the first number
    
    // Iterate over the operators and apply them left-to-right
    for (size_t i = 0; i < operators.size(); ++i) {
        if (operators[i] == '+') {
            result += numbers[i + 1];  // Add the next number to result
        }
        else if (operators[i] == '*') {
            result *= numbers[i + 1];  // Multiply the next number with result
        }
    }
    
    return result;
}

// Function to check if any combination of operators can produce the test value
bool is_valid_equation(const cpp_int& test_value, const vector<cpp_int>& numbers) {
    size_t n = numbers.size();
    if (n == 1) {
        return numbers[0] == test_value;
    }
    
    // Generate all combinations of operators (+, *) for the positions
    int total_combinations = 1 << (n - 1);  // 2^(n-1) possible combinations
    for (int i = 0; i < total_combinations; ++i) {
        vector<char> operators;
        for (int j = 0; j < n - 1; ++j) {
            operators.push_back((i & (1LL << j)) ? '*' : '+');
        }
        if (evaluate_expression(numbers, operators) == test_value) {
            return true;
        }
    }
    return false;
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