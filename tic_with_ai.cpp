
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

struct Move
{
    int row, col;
};

void printBoard(const vector<vector<char>> &board)
{
    for (const auto &row : board)
    {
        for (char cell : row)
        {
            cout << cell << " | ";
        }
        cout << endl
             << "-------------" << endl;
    }
}

bool isBoardFull(const vector<vector<char>> &board)
{
    for (const auto &row : board)
    {
        for (char cell : row)
        {
            if (cell == EMPTY)
            {
                return false;
            }
        }
    }
    return true;
}

bool checkWinner(const vector<vector<char>> &board, char player)
{
    // Check rows and columns
    for (int i = 0; i < 3; ++i)
    {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
        {
            return true;
        }
    }

    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
    {
        return true;
    }

    return false;
}

bool isMoveValid(const vector<vector<char>> &board, int row, int col)
{
    return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == EMPTY;
}

int evaluateBoard(const vector<vector<char>> &board)
{
    if (checkWinner(board, PLAYER_X))
    {
        return -1;
    }
    else if (checkWinner(board, PLAYER_O))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int minimax(vector<vector<char>> &board, int depth, bool isMaximizing)
{
    int score = evaluateBoard(board);

    if (score == 1 || score == -1)
    {
        return score;
    }

    if (isBoardFull(board))
    {
        return 0;
    }

    if (isMaximizing)
    {
        int maxScore = INT_MIN;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (board[i][j] == EMPTY)
                {
                    board[i][j] = PLAYER_O;
                    maxScore = max(maxScore, minimax(board, depth + 1, false));
                    board[i][j] = EMPTY;
                }
            }
        }
        return maxScore;
    }
    else
    {
        int minScore = INT_MAX;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (board[i][j] == EMPTY)
                {
                    board[i][j] = PLAYER_X;
                    minScore = min(minScore, minimax(board, depth + 1, true));
                    board[i][j] = EMPTY;
                }
            }
        }
        return minScore;
    }
}

Move findBestMove(vector<vector<char>> &board)
{
    int bestScore = INT_MIN;
    Move bestMove;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == EMPTY)
            {
                board[i][j] = PLAYER_O;
                int moveScore = minimax(board, 0, false);
                board[i][j] = EMPTY;

                if (moveScore > bestScore)
                {
                    bestScore = moveScore;
                    bestMove.row = i;
                    bestMove.col = j;
                }
            }
        }
    }

    return bestMove;
}

int main()
{
    vector<vector<char>> board(3, vector<char>(3, EMPTY));
    bool playerTurn = true;

    while (true)
    {
        printBoard(board);

        if (playerTurn)
        {
            int row, col;
            cout << "Enter your move (row and column, starting from 1): ";
            cin >> row >> col;
            row--; // Convert to zero-based index
            col--;

            if (isMoveValid(board, row, col))
            {
                board[row][col] = PLAYER_X;
            }
            else
            {
                cout << "Invalid move. Try again." << endl;
                // continue;
                break;
            }
        }
        else
        {
            cout << "AI's move:" << endl;
            Move aiMove = findBestMove(board);
            board[aiMove.row][aiMove.col] = PLAYER_O;
        }
        if (checkWinner(board, PLAYER_X))
        {
            printBoard(board);
            cout << "Congratulations! You win!" << endl;
            break;
        }
        else if (checkWinner(board, PLAYER_O))
        {
            printBoard(board);
            cout << "AI wins! Better luck next time." << endl;
            break;
        }
        else if (isBoardFull(board))
        {
            printBoard(board);
            cout << "It's a draw!" << endl;
            break;
        }

        playerTurn = !playerTurn;
    }

    return 0;
}