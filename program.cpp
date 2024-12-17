#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

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

    static void ClearBoard()
    {
        // fills board with empty spaces
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

    // bool CheckWin()
    // {

    // };

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
    int x;

    system("cls");
    Board::ClearBoard();
    Board::GetBoard()->RenderBoard();
    cin >> x;
    system("cls");
    Board::GetBoard()->TryDrop(1, true);
    Board::GetBoard()->RenderBoard();
    cin >> x;
    system("cls");
    Board::GetBoard()->TryDrop(1, false);
    Board::GetBoard()->RenderBoard();

    cin >> x;
};