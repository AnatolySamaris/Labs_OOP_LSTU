#include "ChessTable.h"

int ChessTable::char_to_index(char letter)
{
    return (int)letter - 65;
}

char ChessTable::fill_empty(int x, int y)
{
    if ((x + y) % 2 == 0) return '-';
    else return '+';
}

ChessTable::ChessTable()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i + j) % 2 == 0) field[i][j] = '-';
            else field[i][j] = '+';
        }
    }

    cout << "New game has been created!\n";
    help();
    show();
}

void ChessTable::add_figure(char figure, char y, int x)
{
    field[8-x][char_to_index(y)] = figure;
    cout << "The piece " << figure << " is added to the square " << y << x << endl;
}

void ChessTable::move(char y_old, int x_old, char y_new, int x_new)
{
    if(field[8-x_old][char_to_index(y_old)] != '-' && field[8-x_old][char_to_index(y_old)] != '+')
    {
        if(field[8-x_new][char_to_index(y_new)] != '-' && field[8-x_new][char_to_index(y_new)] != '+')
        {
            char killed = field[8-x_new][char_to_index(y_new)];
            field[8-x_new][char_to_index(y_new)] = field[8-x_old][char_to_index(y_old)];
            field[8-x_old][char_to_index(y_old)] = fill_empty(8-x_old, char_to_index(y_old));
            cout << "The piece " << field[8-x_new][char_to_index(y_new)] << " beats a piece " << killed << endl;
        }
        else
        {
            field[8-x_new][char_to_index(y_new)] = field[8-x_old][char_to_index(y_old)];
            field[8-x_old][char_to_index(y_old)] = fill_empty(8-x_old, char_to_index(y_old));
            cout << "The piece " << field[8-x_new][char_to_index(y_new)] << " makes a move: " << x_old << y_old << " -> " << x_new << y_new << endl;
        }
    }
    else cout << "Selected square is empty!" << endl;
}

void ChessTable::help()
{
    cout << "\n--- HELP ---\n";
    cout << "Pieces and their signs: P/p - pawn, R/r - rook, K/k - knight, B/b - bishop, Q/q - queen, M/m - king\n";
    cout << "Pieces of two players are divided by uppercase and lowercase signs\n\n";
    cout << "AUTO - to fill the board automatically\n";
    cout << "CLEAR - to clear the board\n";
    cout << "ADD <SIGN> <CHAR_INDEX> <INT_INDEX> - to add a piece\n";
    cout << "MOVE <CHAR_INDEX_NOW> <INT_INDEX_NOW> <CHAR_INDEX_NEW> <INT_INDEX_NEW> - to make a move or to attack\n";
    cout << "SHOW - to show the board\n\n";
    cout << "HELP to show help\n";
    cout << "END to stop the game\n\n";
}

void ChessTable::show()
{
    cout << "\n  A B C D E F G H\n";
    for (int i = 0; i < 8; i++)
    {
        cout << 8-i << ' ';
        for (int j = 0; j < 8; j++)
        {
            cout << field[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

void ChessTable::autofill()
{
    for (int i = 0; i < 8; i++)
    {
        field[1][i] = 'p';
        field[6][i] = 'P';
    }
    field[0][0] = 'r';
    field[0][7] = 'r';
    field[7][0] = 'R';
    field[7][7] = 'R';

    field[0][1] = 'k';
    field[0][6] = 'k';
    field[7][1] = 'K';
    field[7][6] = 'K';

    field[0][2] = 'b';
    field[0][5] = 'b';
    field[7][2] = 'B';
    field[7][5] = 'B';

    field[0][3] = 'q';
    field[7][3] = 'Q';

    field[0][4] = 'm';
    field[7][4] = 'M';

    cout << "Autofill completed!\n";
}

void ChessTable::clear()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            field[i][j] = fill_empty(i, j);
        }
    }
    cout << "\nThe field has been cleared!\n";
}
