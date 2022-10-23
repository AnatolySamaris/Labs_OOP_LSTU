#include <iostream>
#include <complex>
#include <random>

using namespace std;

// Класс интервал для определения интервальных чисел и операций над ними
// Объект класса интервал - пара чисел (a, b) такая, что a <= b
class Interval
{
    pair<int, int> interval;

public:

    Interval()  // Генерация случайного интервального числа при создании объекта класса
    {
        this->interval.first = -50 + rand()%(101);
        this->interval.second = this->interval.first + rand()%(50 - this->interval.first + 1);
    }

    Interval(const Interval& I) // Конструктор копирования
    {
        this->interval.first = I.interval.first;
        this->interval.second = I.interval.second;
    }

    friend ostream& operator <<(ostream& out, Interval& I) // Перегрузка оператора потокового вывода в консоль
    {
        out << '(' << I.interval.first << ", " << I.interval.second << ')';
        return out;
    }

    Interval operator +(const Interval& other) // Перегрузка оператора сложения интервальных чисел
    {
        Interval res = Interval();
        res.interval.first = this->interval.first + other.interval.first;
        res.interval.second = this->interval.second + other.interval.second;
        return res;
    }

    Interval operator -(const Interval& other) // Перегрузка оператора вычитания интервальных чисел
    {
        Interval res;
        res.interval.first = this->interval.first - other.interval.second;
        res.interval.second = this->interval.second - other.interval.first;
        return res;
    }
};


// Класс-обертка шаблонного класса комплексное число для упрощения работы
// с комплексными числами в параметризованном классе матрица.
// При создании объекта класса генерирует случайное комплексное число
class Complex
{
    complex<double> comp_num;

public:

    Complex() // Генерация случайного числа при создании объекта класса
    {
        // рандомное число на отрезке [a; b] => a + rand()%(b - a + 1);
        // Генерация случайного числа. Действительная и мнимая часть числа по модулю не больше 50
        this->comp_num = complex<double>(-50 + rand()%101, -50 + rand()%101);
    }

    Complex(const Complex& C) // Конструктор копирования
    {
        this->comp_num = C.comp_num;
    }

    Complex operator +(const Complex& C) // Перегрузка оператора сложения
    {
        Complex res;
        res.comp_num = this->comp_num + C.comp_num;
        return res;
    }

    Complex operator -(const Complex& C) // Перегрузка оператора вычитания
    {
        Complex res;
        res.comp_num = this->comp_num - C.comp_num;
        return res;
    }

    friend ostream& operator <<(ostream& out, Complex& C) // Перегрузка оператора потокового вывода на консоль
    {
        out << C.comp_num;
        return out;
    }
};


// Параметризованный класс матрица, принимает на входе
// любой класс, имеющий перегруженные операторы потокового вывода на консоль,
// сложения и вычитания
template<class T>
class Matrix
{
public:
    T m[4][4]; // Матрица фиксированного размера 4х4, содержащая объекты класса-параметра Т

    Matrix() // Заполнение матрицы объектами переданного класса-параметра Т.
    {        // В данном случае это случайные комплексные числа или случайные интервальные числа
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                m[i][j] = T();
            }
        }
    }

    Matrix(const Matrix& M) // Конструктор копирования
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                this->m[i][j] = M.m[i][j];
            }
        }
    }

    void print() // Вывод матрицы в консоль
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                cout << this->m[i][j] << ' ';
            }
            cout << endl;
        }
    }

    Matrix operator -(Matrix &M) // Перегрузка оператора вычитания
    {
        Matrix<T> res;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                res.m[i][j] = this->m[i][j] - M.m[i][j];
            }
        }
        return res;
    }

    Matrix operator +(Matrix &M) // Перегрузка оператора сложения
    {
        Matrix res;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                res.m[i][j] = this->m[i][j] + M.m[i][j];
            }
        }
        return res;
    }
};


int main()
{
    srand(time(0)); // Делаем так, чтобы всегда генерировались случайные числа

    cout << "Complex number matrices:" << endl;
    Matrix<Complex> m1;
    m1.print();
    cout << endl;

    Matrix<Complex> m2;
    m2.print();
    cout << endl;

    Matrix<Complex> m3 = m1 + m2;
    m3.print();
    cout << endl;

    Matrix<Complex> m4 = m1 - m2;
    m4.print();
    cout << endl;

    cout << "Interval number matrices:" << endl;
    Matrix<Interval> im1;
    im1.print();
    cout << endl;

    Matrix<Interval> im2;
    im2.print();
    cout << endl;

    Matrix<Interval> im3 = im1 + im2;
    im3.print();
    cout << endl;

    Matrix<Interval> im4 = im1 - im2;
    im4.print();
    cout << endl;
    return 0;
}
