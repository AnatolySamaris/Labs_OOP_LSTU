#include <iostream>

using namespace std;

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
    Matrix() // Конструктор по умолчанию
    {
        size_i = 3;
        size_j = 3;
        matrix = new int*[size_i];
        for (int i = 0; i < size_i; i++)
        {
            matrix[i] = new int[size_j];
        }
    }

    Matrix(int s_i, int s_j) // Параметризованный конструктор
    {
        size_i = s_i;
        size_j = s_j;
        matrix = new int*[size_i];
        for (int i = 0; i < size_i; i++)
        {
            matrix[i] = new int[size_j];
        }
    }

    Matrix(const Matrix& mtrx) // Конструктор копирования
    {
        size_i = mtrx.size_i;
        size_j = mtrx.size_j;
        matrix = new int*[size_i];
        for (int i = 0; i < size_i; i++)
        {
            for (int j = 0; j < size_j; j++)
            {
                matrix[i][j] = mtrx.matrix[i][j];
            }
        }
    }

    ~Matrix() // Деструктор, освобождающий выделенную для объекта класса память
    {
        for (int i = 0; i < size_i; i++)
        {
            delete[] matrix[i];
        }
        delete [] matrix;
    }

    void fill() // Заполняет матрицу числами от 1 до j (число столбцов)
    {
        for (int i = 0; i < size_i; i++)
        {
            for (int j = 0; j < size_j; j++)
            {
                matrix[i][j] = j + 1;
            }
        }
    }

    int get(int i, int j) // Возвращает значение [i][j]-элемента
    {
        return matrix[i][j];
    }

    void set(int val, int i, int j) // Устанавливает в [i][j]-элементу значение val
    {
        matrix[i][j] = val;
    }

    friend ostream& operator <<(ostream& out, Matrix& M) // Перегрузка оператора для вывода матрицы
    {
        for (int i = 0; i < M.size_i; i++)
        {
            for (int j = 0; j < M.size_j; j++)
            {
                out << M.get(i, j) << ' ';
            }
            out << '\n';
        }
        return out;
    }

    Matrix operator *(int num) // Перегрузка оператора для умножения матрицы на число
    {
        for (int i = 0; i < this->size_i; i++)
        {
            for (int j = 0; j < this->size_j; j++)
            {
                this->set(num, i, j);
            }
        }
        return *this;
    }
};


int main() {
    Matrix A = Matrix();
    A.fill();
    cout << "Matrix A:\n" << A << '\n';

    Matrix B = Matrix(3, 4);
    B.fill();
    cout << "Matrix B:\n" << B << '\n';

    Matrix C = A * 5;
    cout << "Matrix C = A * 5:\n" << C << '\n';
}
