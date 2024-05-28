#include <bits/stdc++.h>
using namespace std;

#define N 9

// Utility function to print the Sudoku board with separators
void printBoard(int board[N][N]) {
    for (int row = 0; row < N; row++) {
        if (row % 3 == 0 && row != 0) {
            cout << "---------------------" << endl;
        }
        for (int col = 0; col < N; col++) {
            if (col % 3 == 0 && col != 0) {
                cout << " |";
            }
            cout << " " << board[row][col];
        }
        cout << endl;
    }
    cout << endl;
}

// Check if placing num in board[row][col] is valid
bool isValid(int board[N][N], int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (board[row][x] == num || board[x][col] == num)
            return false;
    }
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num)
                return false;
        }
    }
    return true;
}

// Find the next empty cell
bool findEmptyCell(int board[N][N], int &row, int &col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (board[row][col] == 0)
                return true;
        }
    }
    return false;
}

// Heuristic function: count the number of empty cells
int heuristic(int board[N][N]) {
    int count = 0;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (board[row][col] == 0)
                count++;
        }
    }
    return count;
}

struct Node {
    int board[N][N];
    int cost; // g(n)
    int heuristicCost; // h(n)
    int totalCost; // f(n) = g(n) + h(n)

    Node(int b[N][N], int c, int h)
        : cost(c), heuristicCost(h), totalCost(c + h) {
        memcpy(board, b, sizeof(board));
    }

    bool operator>(const Node &other) const {
        return totalCost > other.totalCost;
    }
};

void aStar(int board[N][N]) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(Node(board, 0, heuristic(board)));

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (heuristic(current.board) == 0) {
            printBoard(current.board);
            return;
        }

        int row, col;
        if (!findEmptyCell(current.board, row, col))
            continue;

        for (int num = 1; num <= 9; num++) {
            if (isValid(current.board, row, col, num)) {
                int newBoard[N][N];
                memcpy(newBoard, current.board, sizeof(newBoard));
                newBoard[row][col] = num;

                int newCost = current.cost + 1;
                int newHeuristicCost = heuristic(newBoard);
                pq.push(Node(newBoard, newCost, newHeuristicCost));
            }
        }
    }

    cout << "No solution exists" << endl;
}

int main() {
    int board[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    aStar(board);
    return 0;
}
