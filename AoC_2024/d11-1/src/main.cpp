#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <unordered_map>

#include "fetch_input.h"

// Function to perform the transformation for one blink
std::unordered_map<uint64_t, uint64_t> blink(const std::unordered_map<uint64_t, uint64_t>& stones) {
    std::unordered_map<uint64_t, uint64_t> new_stones;

    for (const auto& [stone, count] : stones) {
        // Rule 1: If stone is "0", replace with "1"
        if (stone == 0) {
            new_stones[1] += count;
        }
        // Rule 2: If the number of digits is even, split it
        else {
            std::string stone_str = std::to_string(stone);
            if (stone_str.size() % 2 == 0) {
                int half = stone_str.size() / 2;
                uint64_t left = std::stoull(stone_str.substr(0, half));
                uint64_t right = std::stoull(stone_str.substr(half));
                new_stones[left] += count;
                new_stones[right] += count;
            }
            // Rule 3: Otherwise, multiply the stone by 2024
            else {
                new_stones[stone * 2024] += count;
            }
        }
    }

    return new_stones;
}

int main() {
    std::string url = "https://adventofcode.com/2024/day/11/input";
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
    // Split the input into individual stone numbers
    std::unordered_map<uint64_t, uint64_t> stones;

    std::istringstream stream(input);
    std::string stone_str;
    while (stream >> stone_str) {
        uint64_t stone = std::stoull(stone_str);
        stones[stone] += 1;  // Count occurrences of each stone
    }

    // Simulate the transformation process for 25 blinks
    for (int i = 0; i < 25; ++i) {
        stones = blink(stones);
    }

    // After 25 blinks, output the number of stones
    uint64_t total_stones = 0;
    for (const auto& [stone, count] : stones) {
        total_stones += count;
    }

    std::cout << "Number of stones after 25 blinks: " << total_stones << std::endl;

    return 0;
}