#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>
#include <utility>
#include <functional>

#include <cstdlib>

#include "fetch_input.h"

using namespace std;

// Function to parse the input and extract the grid, guard's position, and initial direction
pair<pair<int, int>, pair<int, int>> parseInput(const string& input, vector<string>& grid) {
    pair<int, int> startPos;
    pair<int, int> startDir;

    int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // Up, Right, Down, Left
    char directionSymbols[4] = {'^', '>', 'v', '<'};

    istringstream ss(input);
    string line;
    int row = 0;
    while (getline(ss, line)) {
        for (int col = 0; col < line.size(); ++col) {
            for (int d = 0; d < 4; ++d) {
                if (line[col] == directionSymbols[d]) {
                    startPos = {row, col};
                    startDir = {directions[d][0], directions[d][1]};
                }
            }
        }
        grid.push_back(line);
        ++row;
    }

    return {startPos, startDir};
}

// Custom hash functor for pair<int, int>
struct pair_hash {
    template <typename T1, typename T2>
    size_t operator ()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);  // Hash the first element
        auto h2 = hash<T2>{}(p.second); // Hash the second element
        return h1 ^ (h2 << 1);          // Combine the two hashes
    }
};

// Function to simulate the guard's movement and return the number of distinct positions visited
int simulateGuard(const vector<string>& grid, pair<int, int> startPos, pair<int, int> startDir) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Declare the unordered_set to track visited positions with the custom hash functor
    unordered_set<pair<int, int>, pair_hash> visited;

    // Lambda to check if a position is within bounds of the grid
    auto inBounds = [&](int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    };

    // Initialize guard's position and direction
    pair<int, int> pos = startPos;
    pair<int, int> direction = startDir;
    visited.insert(pos);  // Insert the starting position into the visited set

    // Loop to simulate the guard's movement
    while (true) {
        int nextX = pos.first + direction.first;
        int nextY = pos.second + direction.second;

        // Exit condition: If the guard is about to leave the grid
        if (!inBounds(nextX, nextY)) {
            break;
        }

        if (grid[nextX][nextY] == '#') {
            // If an obstacle is encountered, turn right 90 degrees
            direction = {direction.second, -direction.first};
        } else {
            // Move to the next position if it's not an obstacle
            pos = {nextX, nextY};
            visited.insert(pos);  // Add the new position to the visited set
        }
    }

    // Return the number of distinct positions visited by the guard
    return visited.size();
}

int main() {
    std::string url = "https://adventofcode.com/2024/day/6/input";
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
    // Parse the input to extract the map, guard's position, and initial direction
    vector<string> grid;
    auto[startPos, startDir] = parseInput(input, grid);

    // Simulate the guard's movement and calculate the result
    int visitedCount = simulateGuard(grid, startPos, startDir);

    // Output the result
    cout << "Distinct positions visited: " << visitedCount << endl;

    return 0;
}