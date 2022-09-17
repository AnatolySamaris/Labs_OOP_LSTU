#include "Matrix.h"
#include <iostream>

using namespace std;

Matrix::Matrix() // Конструктор по умолчанию
{
    size_i = 3;
    size_j = 3;
    matrix[size_i][size_j];
}

Matrix::Matrix(int s_i, int s_j, int fill_num) // Параметризованный конструктор
{
    size_i = s_i;
    size_j = s_j;
    matrix[size_i][size_j];
    for (int i = 0; i < size_i; i++)
    {
        for (int j = 0; j < size_j; j++)
        {
            matrix[i][j] = fill_num;
        }
    }
}

Matrix::Matrix(Matrix& mtrx) // Конструктор копирования
{
    size_i = mtrx.size_i;
    size_j = mtrx.size_j;
    matrix[size_i][size_j];

    for (int i = 0; i < size_i; i++)
    {
        for (int j = 0; j < size_j; j++)
        {
            matrix[i][j] = mtrx.matrix[i][j];
        }
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < size_i; i++)
    {
        delete[] matrix[i];
    }
    delete matrix;
}

void Matrix::show() // Вывод матрицы
{
    for (int i = 0; i < size_i; i++)
    {
        for (int j = 0; j < size_j; j++)
        {
            cout << matrix[i][j] << ' ';
        }
        cout << '\n';
    }
}

Matrix& Matrix::operator *(Matrix& M, const int num)
{

};
