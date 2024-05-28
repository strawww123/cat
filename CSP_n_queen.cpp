#include <iostream>
#include <vector>

using namespace std;

bool isSafe(const vector<int> &board, int row, int col, int n)
{
    
    for (int i = 0; i < col; i++)
    {
        if (board[i] == row)
        {
            return false;
        }
    }

    
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[j] == i)
        {
            return false;
        }
    }

    
    for (int i = row, j = col; i < n && j >= 0; i++, j--)
    {
        if (board[j] == i)
        {
            return false;
        }
    }

    return true;
}

// Recursive function to solve N-queens problem
void solveNQueens(vector<int> &board, int col, int n, vector<vector<int>> &solutions)
{
    if (col == n)
    {
       
        solutions.push_back(board);
        return;
    }

 
    for (int i = 0; i < n; i++)
    {
        // Check if queen can be placed safely in this row
        if (isSafe(board, i, col, n))
        {
            board[col] = i; 

            // Recursively check if placing queen here leads to a solution
            solveNQueens(board, col + 1, n, solutions);

            // Backtrack
            board[col] = -1; // Remove queen
        }
    }
}


void printSolution(const vector<vector<int>> &solutions, int n)
{
    int numSolutions = solutions.size();
    cout << "Total Solutions: " << numSolutions << endl;
    for (int k = 0; k < numSolutions; k++)
    {
        cout << "Solution " << k + 1 << ":" << endl;
        const vector<int> &board = solutions[k];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[j] == i)
                {
                    cout << " Q ";
                }
                else
                {
                    cout << " . ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }
}

int main()
{
    int n = 5;                
    vector<int> board(n, -1); 
    vector<vector<int>> solutions;

    solveNQueens(board, 0, n, solutions);

    if (!solutions.empty())
    {
        cout << "Solutions exist:" << endl;
        printSolution(solutions, n);
    }
    else
    {
        cout << "No solution exists" << endl;
    }

    return 0;
}