#include "ChessTable.h"
#include <iostream>

using namespace std;

int ChessTable::char_to_index(char letter)
{
    return (int)letter - 65; // Используем код буквы в ASCII и вычитаем код буквы "А". Тогда А -> 0, B -> 1...
}

char ChessTable::fill_empty(int x, int y)
{
    if ((x + y) % 2 == 0) return '-'; // Сумма координат четная => клетка "белая", иначе - "черная"
    else return '+';
}

ChessTable::ChessTable() // Заполняем поле "+" и "-" по указанному в fill_empty правилу
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i + j) % 2 == 0) field[i][j] = '-';
            else field[i][j] = '+';
        }
    }

    // Для удобства пользователя сразу выводим помощь и показываем поле
    cout << "New game has been created!\n";
    help();
    show();
}

// Добавляет фигуру. Параметры: буква-код фигуры, буква-координата, цифра-координата
void ChessTable::add_piece(char piece, char y, int x)
{
    field[8-x][char_to_index(y)] = piece;
    cout << "The piece " << piece << " is added to the square " << y << x << endl;
}

// Ход фигурой со "старых" координат на "новые". Если на "новой" клетке противник - бьет его.
void ChessTable::move(char y_old, int x_old, char y_new, int x_new)
{
    if(field[8-x_old][char_to_index(y_old)] != '-' && field[8-x_old][char_to_index(y_old)] != '+') // Если "старая" клетка занята...
    {
        if(field[8-x_new][char_to_index(y_new)] != '-' && field[8-x_new][char_to_index(y_new)] != '+') // Если "новая" клетка занята...
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
    cout << ".autofill() - to fill the board automatically\n";
    cout << ".clear() - to clear the board\n";
    cout << ".add_piece(SIGN, CHAR_INDEX, INT_INDEX) - to add a piece\n";
    cout << ".move(CHAR_INDEX_NOW, INT_INDEX_NOW, CHAR_INDEX_NEW, INT_INDEX_NEW) - to make a move or to attack\n";
    cout << ".show() - to show the board\n\n";
    cout << ".help() - to show help\n";
}

void ChessTable::show() // Выводит игровое поле на данный момент
{
    cout << "\n | A B C D E F G H |\n---------------------\n";
    for (int i = 0; i < 8; i++)
    {
        cout << 8-i << "| ";
        for (int j = 0; j < 8; j++)
        {
            cout << field[i][j] << ' ';
        }
        cout << '|' << 8-i << '\n';
    }
    cout << "---------------------\n | A B C D E F G H |\n\n";
}

void ChessTable::autofill() // Автозаполнение поля для игры в шахматы
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

void ChessTable::clear() // Очистить игровое поле от всех фигур
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
