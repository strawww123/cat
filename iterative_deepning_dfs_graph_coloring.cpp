#include <bits/stdc++.h>
using namespace std;

#define V 4

void printSolution(int color[]);

bool isSafe(int v, bool graph[V][V], int color[], int c) {
    for (int i = 0; i < V; i++)
        if (graph[v][i] && c == color[i])
            return false;
    return true;
}

// Recursive utility function implementing DFS and backtracking with depth limit
bool DLSUtil(bool graph[V][V], int m, int color[], int v, int depth, int limit) {
    if (v == V) // Base case: all vertices are colored
        return true;
    if (depth > limit) // Depth limit reached
        return false;

    for (int c = 1; c <= m; c++) { // Try different colors
        if (isSafe(v, graph, color, c)) {
            color[v] = c; // Assign color

            if (DLSUtil(graph, m, color, v + 1, depth + 1, limit)) // Recur to color the next vertex (DFS)
                return true;

            color[v] = 0; // Backtrack if coloring does not lead to a solution
        }
    }
    return false; // No color can be assigned to this vertex
}

bool IDDFS(bool graph[V][V], int m, int maxDepth) {
    int color[V];

    for (int limit = 0; limit <= maxDepth; limit++) {
        memset(color, 0, sizeof(color)); // Reset color array for each iteration
        if (DLSUtil(graph, m, color, 0, 0, limit)) {
            printSolution(color);
            return true;
        }
    }

    cout << "Solution does not exist within the depth limit\n";
    return false;
}

void printSolution(int color[]) {
    cout << "Solution Exists: Following are the assigned colors\n";
    for (int i = 0; i < V; i++)
        cout << " " << color[i] << " ";
    cout << "\n";
}

int main() {
    bool graph[V][V] = {
        { 0, 1, 1, 1 },
        { 1, 0, 1, 0 },
        { 1, 1, 0, 1 },
        { 1, 0, 1, 0 },
    };

    int m = 3;
    int maxDepth;

    cout << "Enter the maximum depth limit: ";
    cin >> maxDepth;

    IDDFS(graph, m, maxDepth);
    return 0;
}
