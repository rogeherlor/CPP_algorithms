#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <cmath>
#include <numeric>

#include <cstdlib>

#include "fetch_input.h"


// Helper function to check if a point lies within the map bounds
bool withinBounds(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

// Hash function for std::pair to use in unordered_set
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ (std::hash<T2>()(pair.second) << 1);
    }
};


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
        grid.push_back(line);
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
    std::unordered_set<std::pair<int, int>, pair_hash> uniqueAntinodes;

    // Calculate antinodes for each frequency group
    for (const auto& [freq, positions] : antennas) {
        int n = positions.size();
        if (n < 2) continue;

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                // Get positions of the two antennas
                auto [x1, y1] = positions[i];
                auto [x2, y2] = positions[j];

                // Add the two antennas as antinodes
                uniqueAntinodes.emplace(x1, y1);
                uniqueAntinodes.emplace(x2, y2);

                // Calculate the direction vector (dx, dy)
                int dx = x2 - x1;
                int dy = y2 - y1;
                int g = std::gcd(std::abs(dx), std::abs(dy));
                dx /= g;
                dy /= g;

                // Walk along the line in both directions until out of bounds
                int cx = x1, cy = y1;

                // Move in the positive direction
                while (withinBounds(cx, cy, rows, cols)) {
                    uniqueAntinodes.emplace(cx, cy);
                    cx += dx;
                    cy += dy;
                }

                // Reset to the starting antenna and move in the negative direction
                cx = x1;
                cy = y1;
                while (withinBounds(cx, cy, rows, cols)) {
                    uniqueAntinodes.emplace(cx, cy);
                    cx -= dx;
                    cy -= dy;
                }
            }
        }
    }

    // Output the number of unique antinode positions
    std::cout << "Total unique antinode locations: " << uniqueAntinodes.size() << std::endl;

    return 0;
}