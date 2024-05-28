#include <iostream>
#include <vector>
#include<limits>

using namespace std;


const char EMPTY = ' ';

void printBoard(const vector<vector<char>> &board)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cout << board[i][j];
            if (j < 2)
            {
                cout << " | ";
            }
        }
        cout << endl;
        if (i < 2)
        {
            cout << "---------" << endl;
        }
    }
}

bool checkWin(const vector<vector<char>> &board, char player)
{
    for (int i = 0; i < 3; ++i)
    {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
        {
            return true;
        }
    }

    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
    {
        return true;
    }

    return false;
}

bool isBoardFull(const vector<vector<char>> &board)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == ' ')
            {
                return false;
            }
        }
    }
    return true;
}

void convertMove(int move, int &row, int &col)
{
    move--;
    row = move / 3;
    col = move % 3;
}

bool isMoveValid(const vector<vector<char>> &board, int row, int col)
{
    return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == EMPTY;
}

void tictactoe()
{
    vector<vector<char>> board(3, vector<char>(3, ' '));
    char currentPlayer = 'O';

    while (true)
    {
        printBoard(board);

        int move;
        cout << "Player " << currentPlayer << ", enter your move (1-9): ";
        cin >> move;

        if (move < 1 || move > 9 || board[(move - 1) / 3][(move - 1) % 3] != ' ')
        {
            cout << "Invalid move. Try again." << endl;
            break;
        }

        int row, col;
        convertMove(move, row, col);

        board[row][col] = currentPlayer;

        if (checkWin(board, currentPlayer))
        {
            printBoard(board);
            cout << "Player " << currentPlayer << " wins!" << endl;
            break;
        }

        if (isBoardFull(board))
        {
            printBoard(board);
            cout << "It's a tie!" << endl;
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

int main()
{
    cout << "Welcome to Tic Tac Toe!" << endl;
    tictactoe();
    return 0;
}