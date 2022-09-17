#ifndef DECISIONS_MATRIX_H
#define DECISIONS_MATRIX_H

#endif //DECISIONS_MATRIX_H

// Объект класса Matrix хранит в себе целочисленную матрицу указанного размера.
// Эту матрицу можно вывести или умножить на вещественное число, причем
// в последнем случае результат запишется в новую матрицу.

class Matrix
{
private:
    int size_i;
    int size_j;
    int** matrix;

public:
    Matrix(); // Конструктор по умолчанию
    Matrix(int s_i, int s_j, int fill_num); // Параметризованный конструктор
    Matrix(Matrix& mtrx); // Конструктор копирования
    ~Matrix(); // Деструктор

    void show(); // Вывод матрицы
    friend Matrix operator *(Matrix& A, const int num);
};
