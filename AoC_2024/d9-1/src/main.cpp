#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <unordered_map>

#include "fetch_input.h"

// Function to calculate the sum for a block
unsigned long long int file_sum(int a, int n, int block_id) {
    unsigned long long int s = (((2 * a) + n - 1) * n) / 2;
    return s * block_id;
}

// Checksum calculation
unsigned long long int calculateChecksum(const std::string& line) {
    int n = line.size();
    int last_block_ptr = n % 2 == 0 ? n - 2 : n - 1;
    int ptr = 0, block_ind = 0;
    unsigned long long int checksum1 = 0;

    std::string mutable_line = line; // Create a mutable copy of the input line

    while (ptr <= last_block_ptr) {
        if (ptr % 2 == 0) { // File block
            checksum1 += file_sum(block_ind, mutable_line[ptr] - '0', ptr / 2);
            block_ind += (mutable_line[ptr] - '0');
            ptr++;
        } else { // Free space
            int t = std::min(mutable_line[ptr] - '0', mutable_line[last_block_ptr] - '0');
            checksum1 += file_sum(block_ind, t, last_block_ptr / 2);

            mutable_line[ptr] -= t;
            mutable_line[last_block_ptr] -= t;
            block_ind += t;

            if (mutable_line[ptr] == '0') ptr++;
            if (mutable_line[last_block_ptr] == '0') last_block_ptr -= 2;
        }
    }

    return checksum1;
}

int main() {
    std::string url = "https://adventofcode.com/2024/day/9/input";
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
    try {
        // Calculate the checksum
        unsigned long long int Checksum = calculateChecksum(input);

        // Output the result for Part 1
        std::cout << "Part 1 Checksum: " << Checksum << std::endl;

        // Additional logic for Part 2 can be added here if required
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}