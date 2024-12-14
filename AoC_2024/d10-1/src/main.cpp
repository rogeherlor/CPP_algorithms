#include <iostream>
#include <vector>
#include <queue>
#include <string>

#include "fetch_input.h"

// Direction vectors for movement (up, down, left, right)
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

// BFS function to explore the map and count reachable '9's from a trailhead
int bfs(const std::vector<std::vector<int>>& map, int startX, int startY) {
    int rows = map.size();
    int cols = map[0].size();
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::queue<std::pair<int, int>> q; // Queue for BFS
    q.push({startX, startY});
    visited[startX][startY] = true;
    int score = 0;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        // If we reach a height of 9, increase score
        if (map[x][y] == 9) {
            score++;
        }

        // Explore neighbors (up, down, left, right)
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // Check if the neighbor is within bounds and valid (height + 1 condition)
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && !visited[nx][ny] && map[nx][ny] == map[x][y] + 1) {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }

    return score;
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
    int totalScore = 0;

    // Loop over the map to find trailheads (cells with height 0)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (map[i][j] == 0) {
                // Run BFS from each trailhead and add the score
                totalScore += bfs(map, i, j);
            }
        }
    }

    // Output the total score
    std::cout << "Total score of all trailheads: " << totalScore << std::endl;

    return 0;
}