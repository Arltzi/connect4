#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <limits>

using namespace std;

const int ROWS = 6;
const int COLUMNS = 7;
const char EMPTY = ' ';
const char P1 = 'X';
const char P2 = 'O';

class Board {
private:
    static Board* inst;
    static char boardState[ROWS][COLUMNS];

    Board()
    {
        ClearBoard();
    };

public:
    // make board singleton
    static Board* GetBoard()
    {
        if(inst == nullptr)
        {
            inst = new Board();
        }
        return inst;
    };

    // delete copy assignment operator
    Board& operator=(const Board&) = delete;
    // delete copy constructor
    Board(const Board&) = delete;

    // jsut fills board with empty spaces
    static void ClearBoard()
    {
        fill(&boardState[0][0], &boardState[0][0] + sizeof(boardState), EMPTY);
    };

    bool TryDrop(int col, bool p1orp2)
    {
        if(boardState[0][col] != EMPTY)
        {
            return false;
        };

        for(int row_i = 0; row_i < ROWS; row_i++)
        {
            if (row_i == ROWS || boardState[row_i + 1][col] != EMPTY)
            {
                boardState[row_i][col] = p1orp2 ? P1 : P2;
                return true;
            };
        };

        return false;
    };

    // true = player won, false = player hasnt won (not player lost!)
    bool CheckWin(bool p1orp2)
    {
        int checked = 0;
        char charToCheck = p1orp2 ? P1 : P2;

        // check horizontally
        for (int row_i = 0; row_i < ROWS; row_i++)
        {
            for (int col_i = 0; col_i < COLUMNS; col_i++)
            {
                if(boardState[row_i][col_i] == charToCheck)
                {
                    checked ++;
                    if(checked == 4)
                    {
                        return true;
                    }
                }
                else
                {
                    checked = 0;
                }
            }
            // reset consecutive counter after completing a row
            checked = 0;
        }

        // check vertically
        for (int row_i = 0; row_i < ROWS; row_i++)
        {
            for (int col_i = 0; col_i < COLUMNS; col_i++)
            {
                if(boardState[col_i][row_i] == charToCheck)
                {
                    checked ++;
                    if(checked == 4)
                    {
                        return true;
                    }
                }
                else
                {
                    checked = 0;
                }
            }
            // reset consecutive counter after completing a column
            checked = 0;
        }

        // two different approaches to check for a win
        // check diagonally (down-right)
        for (int row_i = 0; row_i < ROWS - 3; row_i++)
        {
            for (int col_i = 0; col_i < COLUMNS - 3; col_i++)
            {
                // god i love dumb checking
                if(boardState[row_i][col_i] == charToCheck
                && boardState[row_i + 1][col_i + 1] == charToCheck
                && boardState[row_i + 2][col_i + 2] == charToCheck
                && boardState[row_i + 3][col_i + 3] == charToCheck)
                {
                    return true;
                }
            }
        }

        // check diagonally (up-right)
        for (int row_i = 0; row_i < ROWS - 3; row_i++)
        {
            for (int col_i = COLUMNS; col_i > COLUMNS - 3; col_i--)
            {
                if(boardState[row_i][col_i] == charToCheck
                && boardState[row_i + 1][col_i - 1] == charToCheck
                && boardState[row_i + 2][col_i - 2] == charToCheck
                && boardState[row_i + 3][col_i - 3] == charToCheck)
                {
                    return true;
                }
            }
        }

        // no win found
        return false;
    };

    void RenderBoard()
    {
        for (int row_i = 0; row_i < ROWS; row_i++) {
            // print divider row
            for (int i = 0; i < COLUMNS; i++)
            {
                std::cout << "+--";
            }
            std::cout << "+ \n";

            for (int col_i = 0; col_i < COLUMNS; col_i++)
            {
                std::cout << '|' << boardState[row_i][col_i] << boardState[row_i][col_i];
            }
            std::cout << '|' << '\n';
        }

        for (int i = 0; i < COLUMNS; i++)
        {
            std::cout << "+--";
        }
        std::cout << "+ \n";
    };
};

// init board singleton pointer
Board* Board::inst = nullptr;
char Board::boardState[ROWS][COLUMNS] {};

int main()
{
    bool p1orp2 = true;
    int col;

    while (true) {
        system("cls");
        Board::GetBoard()->RenderBoard();

        if (p1orp2) {
            std::cout << "Player 1: pick a column (0-6): ";
        } else {
            std::cout << "Player 2: pick a column (0-6): ";
        }

        std::cin >> col;

        // stack overflow snippet "sanity check user input char c++"
        if (std::cin.fail()) {
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            continue;
        }

        if (col < 0 || col >= COLUMNS) {
            std::cout << "Invalid column. Try again." << '\n';
            continue;
        }

        if (!Board::GetBoard()->TryDrop(col, p1orp2)) {
            std::cout << "Column full. Try again." << '\n';
            continue;
        }

        if (Board::GetBoard()->CheckWin(p1orp2)) {
            system("cls");
            Board::GetBoard()->RenderBoard();
            if (p1orp2) {
                std::cout << "Player 1 (X) wins!" << '\n';
            } else {
                std::cout << "Player 2 (O) wins!" << '\n';
            }

            char playAgain;
            std::cout << "Do you want to play again? (y/n): ";
            std::cin >> playAgain;
            if (playAgain == 'y' || playAgain == 'Y') {
                Board::GetBoard()->ClearBoard();
                continue;
            } else {
                std::cout << "Thanks for playing!" << '\n';
                exit(0);
            }
            break;
        }

        p1orp2 = !p1orp2;
    }
};