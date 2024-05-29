#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Structure to represent a node in the grid
struct Node
{
    int x, y;     // Coordinates
    int g, h, f;  // Costs
    Node *parent; // Parent node pointer

    Node(int _x, int _y)
    {
        x = _x;
        y = _y;
        g = 0;
        h = 0;
        f = 0;
        parent = nullptr;
    }
};

// Function to calculate Manhattan distance heuristic
int heuristic(Node *current, Node *goal)
{
    return abs(current->x - goal->x) + abs(current->y - goal->y);
}

// Function to check if a node is within the grid bounds and is traversable
bool isValid(int x, int y, int grid_width, int grid_height, vector<vector<int>> &grid)
{
    return x >= 0 && x < grid_width && y >= 0 && y < grid_height && grid[x][y] == 0;
}

// Function to reconstruct path from goal to start
vector<pair<int, int>> reconstructPath(Node *current)
{
    vector<pair<int, int>> path;
    while (current != nullptr)
    {
        path.emplace_back(current->x, current->y);
        current = current->parent;
    }
    reverse(path.begin(), path.end());
    return path;
}

// AO* algorithm
vector<pair<int, int>> ao_star(vector<vector<int>> &grid, pair<int, int> start, pair<int, int> goal)
{
    int grid_width = grid.size();
    int grid_height = grid[0].size();

    priority_queue<Node *> open_list;
    unordered_set<Node *> closed_set;

    Node *start_node = new Node(start.first, start.second);
    start_node->h = heuristic(start_node, new Node(goal.first, goal.second));
    start_node->f = start_node->g + start_node->h;
    open_list.push(start_node);

    while (!open_list.empty())
    {
        Node *current = open_list.top();
        open_list.pop();

        if (current->x == goal.first && current->y == goal.second)
        {
            return reconstructPath(current);
        }

        closed_set.insert(current);

        // Explore neighbors
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                if (dx == 0 && dy == 0)
                    continue;
                int next_x = current->x + dx;
                int next_y = current->y + dy;

                if (!isValid(next_x, next_y, grid_width, grid_height, grid))
                    continue;

                Node *neighbor = new Node(next_x, next_y);
                neighbor->g = current->g + 1;
                neighbor->h = heuristic(neighbor, new Node(goal.first, goal.second));
                neighbor->f = neighbor->g + neighbor->h;
                neighbor->parent = current;

                if (closed_set.find(neighbor) != closed_set.end())
                    continue;

                open_list.push(neighbor);
            }
        }
    }

    // No path found
    return {};
}

int main()
{
    // Example grid: 0 represents an empty cell, 1 represents an obstacle
    vector<vector<int>> grid = {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0}};

    pair<int, int> start = {0, 0};
    pair<int, int> goal = {3, 3};

    vector<pair<int, int>> path = ao_star(grid, start, goal);

    if (!path.empty())
    {
        cout << "Path found: ";
        for (const auto &p : path)
        {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    }
    else
    {
        cout << "No path found!" << endl;
    }

    return 0;
}