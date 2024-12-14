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
unsigned long long int calculateChecksum(const std::string& input) {
    std::string cline = input; // Create a mutable copy of the input
    int n = input.size();
    int last_block_ptr = (n % 2 == 0) ? n - 2 : n - 1;
    unsigned long long checksum2 = 0;
    std::vector<std::queue<int>> files_by_size(10); // Tracks file blocks by size
    std::unordered_map<int, char> moved;           // Tracks moved blocks
    int block_ind = 0;

    // Populate files_by_size with file blocks indexed by size
    for (int i = last_block_ptr; i >= 0; i -= 2) {
        files_by_size[cline[i] - '0'].push(i);
    }

    // Process the input to calculate the checksum
    for (int ptr = 0; ptr < n;) {
        if (ptr % 2 == 0) { // File block
            if (moved.find(ptr) == moved.end()) {
                checksum2 += file_sum(block_ind, cline[ptr] - '0', ptr / 2);
                block_ind += (cline[ptr] - '0');
            } else {
                block_ind += (moved[ptr] - '0');
            }
            ++ptr;
        } else { // Free space
            int cur_space = cline[ptr] - '0';
            int max_ind = -1; // Tracks the best file block index to move
            int vec_ind = -1; // Tracks the corresponding file size

            // Find the largest file that fits into the current free space
            for (int j = 1; j <= cur_space; ++j) {
                std::queue<int>& temp = files_by_size[j];
                if (!temp.empty() && (max_ind < temp.front()) && temp.front() > ptr) {
                    max_ind = temp.front();
                    vec_ind = j;
                }
            }

            if (max_ind == -1) { // No suitable file block found
                block_ind += cur_space;
                ++ptr;
                continue;
            }

            // Move the file block to the free space
            cur_space = cline[max_ind] - '0';
            checksum2 += file_sum(block_ind, cur_space, max_ind / 2);
            files_by_size[vec_ind].pop();

            moved[max_ind] = cline[max_ind]; // Mark the block as moved
            block_ind += cur_space;

            // Update the input representation
            cline[max_ind] = '0';
            cline[ptr] -= cur_space;

            if (cline[ptr] == '0') {
                ++ptr; // Move to the next free space
            }
        }
    }

    return checksum2;
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
        std::cout << "Part 2 Checksum: " << Checksum << std::endl;

        // Additional logic for Part 2 can be added here if required
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}