#ifndef DECISIONS_CHESSTABLE_H
#define DECISIONS_CHESSTABLE_H

#endif //DECISIONS_CHESSTABLE_H

// ChessTable - задает шахматную доску с возможностью
// добавлять фигуры вручную либо заполнять поле автоматически,
// делать ходы и атаковать фигуры противника.

class ChessTable
{
private:
    char field[8][8];
    static int char_to_index(char letter); // Перевод буквы-координаты в индекс массива
    static char fill_empty(int x, int y); // Заполняет пустое поле "+" или "-"

public:
    ChessTable(); // Конструктор класса. Заполняем поле "+" и "-"
    void add_piece(char piece, char y, int x);
    void move(char y_old, int x_old, char y_new, int x_new);
    static void help();
    void show();
    void autofill();
    void clear();
};
