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

// Recursive utility function implementing DFS and backtracking
bool graphColoringUtil(bool graph[V][V], int m, int color[], int v) {
    if (v == V) // Base case: all vertices are colored
        return true;

    for (int c = 1; c <= m; c++) { // Try different colors
        if (isSafe(v, graph, color, c)) {
            color[v] = c; // Assign color

            if (graphColoringUtil(graph, m, color, v + 1)) // Recur to color the next vertex (DFS)
                return true;

            color[v] = 0; // Backtrack if coloring does not lead to a solution
        }
    }
    return false; // No color can be assigned to this vertex
}

bool graphColoring(bool graph[V][V], int m) {
    int color[V] = {0};

    if (!graphColoringUtil(graph, m, color, 0)) {
        cout << "Solution does not exist";
        return false;
    }

    printSolution(color);
    return true;
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

    graphColoring(graph, m);
    return 0;
}





