#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>

#include "fetch_input.h"

// Direction vectors for movement (up, down, left, right)
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

// Function to perform BFS to count all distinct paths from a trailhead
int bfsRating(const std::vector<std::vector<int>>& map, int startX, int startY) {
    int rows = map.size();
    int cols = map[0].size();
    
    // Queue for BFS, storing current position and the number of ways to get there
    std::queue<std::pair<int, int>> q;
    q.push({startX, startY});
    
    // Map to store the number of ways to reach each position
    std::unordered_map<std::string, int> ways;
    ways[std::to_string(startX) + "," + std::to_string(startY)] = 1;  // There's one way to start at the trailhead
    
    int trailsCount = 0;

    // BFS to explore the grid
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        // If we reach a height of 9, count this as a valid trail
        if (map[x][y] == 9) {
            trailsCount += ways[std::to_string(x) + "," + std::to_string(y)];
        }

        // Explore neighbors (up, down, left, right)
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // Check bounds and if the neighbor is valid (height + 1 condition)
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && map[nx][ny] == map[x][y] + 1) {
                std::string key = std::to_string(nx) + "," + std::to_string(ny);

                // If this position has been reached before, increment the number of ways to reach it
                if (ways.find(key) != ways.end()) {
                    ways[key] += ways[std::to_string(x) + "," + std::to_string(y)];
                } else {
                    q.push({nx, ny});
                    ways[key] = ways[std::to_string(x) + "," + std::to_string(y)];
                }
            }
        }
    }

    return trailsCount;
}

// Function to parse input and map it to the grid
std::vector<std::vector<int>> parseInput(const std::string& input) {
    std::vector<std::vector<int>> map;
    std::string line;
    for (char c : input) {
        if (c == '\n') {
            if (!line.empty()) {
                std::vector<int> row;
                for (char ch : line) {
                    row.push_back(ch - '0'); // Convert char to int
                }
                map.push_back(row);
            }
            line.clear();
        } else {
            line += c;
        }
    }
    return map;
}

int main() {
    std::string url = "https://adventofcode.com/2024/day/10/input";
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
    // Parse the input into a 2D map/grid
    std::vector<std::vector<int>> map = parseInput(input);

    int rows = map.size();
    int cols = map[0].size();
    int totalRating = 0;

    // Loop over the map to find trailheads (cells with height 0)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (map[i][j] == 0) {
                // Run BFS from each trailhead and add the rating
                totalRating += bfsRating(map, i, j);
            }
        }
    }

    // Output the total rating
    std::cout << "Total rating of all trailheads: " << totalRating << std::endl;

    return 0;
}