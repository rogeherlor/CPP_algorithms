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

// Check if the word "XMAS" exists starting from (x, y) in a specific direction
bool checkWord(const std::vector<std::vector<char>>& grid, int x, int y, int dx, int dy, const std::string& word) {
    int rows = grid.size();
    int cols = grid[0].size();
    for (int i = 0; i < word.size(); ++i) {
        int nx = x + i * dx;
        int ny = y + i * dy;
        if (nx < 0 || nx >= rows || ny < 0 || ny >= cols || grid[nx][ny] != word[i]) {
            return false;
        }
    }
    return true;
}

// Function to count all occurrences of "XMAS" in the grid
int countXMAS(const std::vector<std::vector<char>>& grid) {
    const std::string word = "XMAS";
    int count = 0;
    int rows = grid.size();
    int cols = grid[0].size();

    // Directions: {dx, dy}
    std::vector<std::pair<int, int>> directions = {
        {0, 1}, {1, 0}, {1, 1}, {-1, 1}, // Right, Down, Diagonal Down-Right, Diagonal Up-Right
        {0, -1}, {-1, 0}, {-1, -1}, {1, -1} // Left, Up, Diagonal Up-Left, Diagonal Down-Left
    };

    for (int x = 0; x < rows; ++x) {
        for (int y = 0; y < cols; ++y) {
            for (const auto& [dx, dy] : directions) {
                if (checkWord(grid, x, y, dx, dy, word)) {
                    ++count;
                }
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