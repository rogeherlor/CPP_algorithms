#include <iostream>
#include <vector>
#include <string>

#include <cstdlib>

#include "fetch_input.h"

// Function to parse the input string into a 2D grid
std::vector<std::vector<char>> parseGrid(const std::string& input) {
    std::vector<std::vector<char>> grid;
    std::string line;
    for (char c : input) {
        if (c == '\n') {
            if (!line.empty()) {
                grid.push_back(std::vector<char>(line.begin(), line.end()));
                line.clear();
            }
        } else {
            line += c;
        }
    }
    if (!line.empty()) {
        grid.push_back(std::vector<char>(line.begin(), line.end()));
    }
    return grid;
}

// Check if the 'X-MAS' pattern exists centered at (x, y)
bool isXMAS(const std::vector<std::vector<char>>& grid, int x, int y) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Coordinates for the X-MAS diagonals
    std::vector<std::pair<int, int>> diag1 = {{-1, -1}, {0, 0}, {1, 1}}; // Top-left to bottom-right
    std::vector<std::pair<int, int>> diag2 = {{1, -1}, {0, 0}, {-1, 1}}; // Bottom-left to top-right

    // Check both diagonals for "MAS" or "SAM"
    auto matchesPattern = [&](const std::vector<std::pair<int, int>>& diagonal) {
        std::string diagStr;
        for (const auto& [dx, dy] : diagonal) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx < 0 || nx >= rows || ny < 0 || ny >= cols) return false; // Out of bounds
            diagStr += grid[nx][ny];
        }
        return (diagStr == "MAS" || diagStr == "SAM");
    };

    return matchesPattern(diag1) && matchesPattern(diag2);
}

// Count all occurrences of 'X-MAS' in the grid
int countXMAS(const std::vector<std::vector<char>>& grid) {
    int count = 0;
    int rows = grid.size();
    int cols = grid[0].size();

    // Check every possible center position
    for (int x = 0; x < rows; ++x) {
        for (int y = 0; y < cols; ++y) {
            if (isXMAS(grid, x, y)) {
                ++count;
            }
        }
    }

    return count;
}


int main() {
    std::string url = "https://adventofcode.com/2024/day/4/input";
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
    // Parse input into a grid
    auto grid = parseGrid(input);

    // Find and count all occurrences of "XMAS"
    int result = countXMAS(grid);

    // Output the result
    std::cout << "Total occurrences of 'XMAS': " << result << std::endl;

    return 0;
}