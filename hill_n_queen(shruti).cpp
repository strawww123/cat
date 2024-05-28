#include <iostream>
#include <vector>
#include <random>
#include <ctime>
using namespace std;

// Function to print the board
void printBoard(const vector<int>& queens) {
    int n = queens.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (queens[i] == j) cout << "Q ";
            else cout << ". ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to count the number of attacking pairs of queens
int countAttacks(const vector<int>& queens) {
    int n = queens.size();
    int attacks = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (queens[i] == queens[j] || abs(i - j) == abs(queens[i] - queens[j])) {
                ++attacks;
            }
        }
    }
    return attacks;
}

// Function to find the best neighbor
vector<int> findBestNeighbor(const vector<int>& queens) {
    vector<int> bestNeighbor = queens;
    int n = queens.size();
    int minAttacks = countAttacks(queens);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (queens[i] != j) {
                vector<int> neighbor = queens;
                neighbor[i] = j;
                int attacks = countAttacks(neighbor);
                if (attacks < minAttacks) {
                    minAttacks = attacks;
                    bestNeighbor = neighbor;
                }
            }
        }
    }
    return bestNeighbor;
}

// Function to solve N-Queens problem using hill climbing
void solveNQueens(int n) {
    // Initialize random number generator
    mt19937 rng(time(nullptr));

    // Generate a random initial state
    vector<int> queens(n);
    for (int i = 0; i < n; ++i) {
        queens[i] = rng() % n;
    }

    // Keep track of the number of iterations
    int iterations = 0;

    // Main loop of hill climbing
    while (true) {
        int attacks = countAttacks(queens);
        if (attacks == 0) {
            cout << "Solution found:" << endl;
            printBoard(queens);
            cout << "Iterations: " << iterations << endl;
            return;
        }

        vector<int> bestNeighbor = findBestNeighbor(queens);
        if (countAttacks(bestNeighbor) >= attacks) {
            cout << "Local optimum reached. Restarting..." << endl;
            // Restart with a new random initial state
            for (int i = 0; i < n; ++i) {
                queens[i] = rng() % n;
            }
        } else {
            queens = bestNeighbor;
        }

        iterations++;
    }
}

int main() {
    int n;
    cout << "Enter the number of queens: ";
    cin >> n;

    solveNQueens(n);

    return 0;
}
