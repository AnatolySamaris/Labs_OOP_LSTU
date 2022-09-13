#ifndef DECISIONS_CHESSTABLE_H
#define DECISIONS_CHESSTABLE_H

#endif //DECISIONS_CHESSTABLE_H

#include <iostream>

using namespace std;

class ChessTable
{
private:
    char field[8][8];

    static int char_to_index(char letter);
    static char fill_empty(int x, int y);

public:
    ChessTable();
    void add_figure(char figure, char y, int x);
    void move(char y_old, int x_old, char y_new, int x_new);
    void help();
    void show();
    void autofill();
    void clear();
};
