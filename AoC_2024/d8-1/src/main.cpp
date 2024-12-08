#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <cmath>

#include <cstdlib>

#include "fetch_input.h"


// Helper function to check if a point lies within the map bounds
bool withinBounds(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}


int main() {
    std::string url = "https://adventofcode.com/2024/day/8/input";
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
    // Parse the input into a grid
    std::vector<std::string> grid;
    std::string line;
    for (char c : input) {
        if (c == '\n') {
            grid.push_back(line);
            line.clear();
        } else {
            line += c;
        }
    }
    if (!line.empty()) {
        grid.push_back(line); // Add the last line if it doesn't end with '\n'
    }

    int rows = grid.size();
    int cols = grid[0].size();

    // Collect antenna positions by frequency
    std::unordered_map<char, std::vector<std::pair<int, int>>> antennas;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            char freq = grid[r][c];
            if (std::isalnum(freq)) {
                antennas[freq].emplace_back(r, c);
            }
        }
    }

    // Set to track unique antinode positions
    std::set<std::pair<int, int>> uniqueAntinodes;

    // Calculate antinodes for each frequency group
    for (const auto& [freq, positions] : antennas) {
        int n = positions.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;

                // Get positions of the two antennas
                auto [x1, y1] = positions[i];
                auto [x2, y2] = positions[j];

                // Midpoint and vector difference
                int dx = x2 - x1;
                int dy = y2 - y1;

                // Antinode positions: one before x1 and one after x2
                int ax1 = x1 - dx, ay1 = y1 - dy;
                int ax2 = x2 + dx, ay2 = y2 + dy;

                if (withinBounds(ax1, ay1, rows, cols)) {
                    uniqueAntinodes.emplace(ax1, ay1);
                }
                if (withinBounds(ax2, ay2, rows, cols)) {
                    uniqueAntinodes.emplace(ax2, ay2);
                }
            }
        }
    }

    // Output the number of unique antinode positions
    std::cout << "Total unique antinode locations: " << uniqueAntinodes.size() << std::endl;

    return 0;
}