#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

#include <cstdlib>

#include "fetch_input.h"

using namespace std;

// Helper function to split a string by a delimiter
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    stringstream ss(s);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to parse the rules
vector<pair<int, int>> parseRules(const vector<string>& rules) {
    vector<pair<int, int>> parsedRules;
    for (const string& rule : rules) {
        auto parts = split(rule, '|');
        parsedRules.emplace_back(stoi(parts[0]), stoi(parts[1]));
    }
    return parsedRules;
}

// Function to parse updates
vector<vector<int>> parseUpdates(const vector<string>& updates) {
    vector<vector<int>> parsedUpdates;
    for (const string& update : updates) {
        auto parts = split(update, ',');
        vector<int> pages;
        for (const string& page : parts) {
            pages.push_back(stoi(page));
        }
        parsedUpdates.push_back(pages);
    }
    return parsedUpdates;
}

// Function to check if an update is in the correct order
bool isValidUpdate(const vector<int>& update, const vector<pair<int, int>>& rules) {
    unordered_map<int, int> pagePositions;
    for (int i = 0; i < update.size(); ++i) {
        pagePositions[update[i]] = i;
    }
    for (const auto& rule : rules) {
        int x = rule.first, y = rule.second;
        if (pagePositions.count(x) && pagePositions.count(y)) {
            if (pagePositions[x] >= pagePositions[y]) {
                return false; // Rule violated
            }
        }
    }
    return true;
}

// Function to calculate the middle page
int getMiddlePage(const vector<int>& update) {
    return update[update.size() / 2];
}


int main() {
    std::string url = "https://adventofcode.com/2024/day/5/input";
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
    // Parse the input
    auto sections = split(input, '\n');
    auto it = find(sections.begin(), sections.end(), "");
    vector<string> ruleStrings(sections.begin(), it);
    vector<string> updateStrings(it + 1, sections.end());

    // Parse rules and updates
    auto rules = parseRules(ruleStrings);
    auto updates = parseUpdates(updateStrings);

    // Validate updates and calculate the sum of middle pages
    int sumOfMiddlePages = 0;
    for (const auto& update : updates) {
        if (isValidUpdate(update, rules)) {
            sumOfMiddlePages += getMiddlePage(update);
        }
    }

    // Output the result
    cout << "Sum of middle pages: " << sumOfMiddlePages << endl;

    return 0;
}