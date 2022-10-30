#include <iostream>
#include <random> // rand(), srand()

using namespace std;

// Класс вектор в декартовой системе N координат.
// По умолчанию имеет размерность dim = 3.
class DecartVector
{
private:
    int dim; // Размерность вектора и его точек
    double *vector; // Вектор размерности dim, вычисляемый как разность координат конечной и начальной точек.

    // Функция генерации случайного целого числа от a до b включительно. Используется только внутри класса
    static int getrand(int a, int b) { return a + rand()%(b - a + 1);}

    void fillrand() // Заполнение вектора случайными числами
    {
        for (int i = 0; i < dim; i++)
        {
            double start_point = getrand(-50, 50);
            double end_point = getrand(-50, 50);
            vector[i] = end_point - start_point;
        }
    }

public:
    DecartVector() // Конструктор по умолчанию
    {
        dim = 3;
        vector = new double[dim];
        fillrand();
    }

    DecartVector(int user_dim) // Конструктор с одним принимаемым параметром - пользовательской размерностью вектора
    {
        dim = user_dim;
        vector = new double[dim];
        fillrand();
    }

    DecartVector(const DecartVector& D) // Конструктор копирования
    {
        dim = D.dim;
        vector = D.vector;
    }

    ~DecartVector() // Деструктор. Так как размеры массивов точек и вектора динамические, надо освобождать память через деструктор
    {
            delete [] vector;
    }

    friend ostream& operator <<(ostream& out, DecartVector& D) // Перегрузка оператора потокового вывода
    {
        out << '(';
        for (int i = 0; i < D.dim - 1; i++) out << D.vector[i] << ", ";
        out << D.vector[D.dim-1] << ")";
        return out;
    }

    DecartVector operator -(const DecartVector& other) // Перегрузка оператора вычитания между двумя векторами
    {
        DecartVector res = DecartVector(dim);
        for (int i = 0; i < res.dim; i++) res.vector[i] = vector[i] - other.vector[i];
        return res;
    }

    DecartVector operator +(const DecartVector& other) // Перегрузка оператора сложения между двумя векторами
    {
        DecartVector res = DecartVector(dim);
        for (int i = 0; i < res.dim; i++) res.vector[i] = vector[i] + other.vector[i];
        return res;
    }
};


// Класс вектор в полярных координатах.
// Имеет возможность заполнения случайными значениями
// полярного радиуса и полярного угла.
class PolarVector
{
private:
    double radius; // Значение полярного радиуса вектора
    double angle; // Значение полярного угла вектора

    // Функция генерации случайного числа от a до b включительно. Используется только внутри определения класса.
    static int getrand(int from, int to) { return from + rand()%(to - from + 1);}

public:
    PolarVector() // Конструктор по умолчанию
    {
        radius = getrand(0, 25);
        angle = getrand(-180, 180);
    }

    PolarVector(const PolarVector& P) // Конструктор копирования
    {
        radius = P.radius;
        angle = P.angle;
    }

    friend ostream& operator <<(ostream& out, PolarVector& P) // Перегрузка оператора потокового вывода
    {
        out << '(' << P.radius << ", " << P.angle << ')';
        return out;
    }

    PolarVector operator -(const PolarVector& other) // Перегрузка оператора вычитания между двумя векторами
    {
        PolarVector res = PolarVector();
        double new_x = radius * cos(angle) - other.radius * cos(other.angle); // new_x = r0cosA0 - r1cosA1
        double new_y = radius * sin(angle) - other.radius * sin(other.angle); // new_y = r0sinA0 - r1sinA1
        res.radius = sqrt(pow(new_x, 2) + pow(new_y, 2)); // res.radius = sqrt(new_x^2 + new_y^2)
        res.angle = atan(new_y / new_x); // res.angle = arctg(new_y / new_x)
        return res;
    }

    PolarVector operator +(const PolarVector& other) // Перегрузка оператора сложения между двумя векторами
    {
        PolarVector res = PolarVector();
        double new_x = radius * cos(angle) + other.radius * cos(other.angle); // new_x = r0cosA0 + r1cosA1
        double new_y = radius * sin(angle) + other.radius * sin(other.angle); // new_y = r0sinA0 + r1sinA1
        res.radius = sqrt(pow(new_x, 2) + pow(new_y, 2)); // new_radius = sqrt(new_x^2 + new_y^2)
        res.angle = atan(new_y / new_x); // new_angle = arctg(new_y / new_x)
        return res;
    }
};


// Параметризованный класс матрица, принимающий на входе любой класс,
// имеющий перегруженные операторы потокового вывода, сложения и вычитания между объектами класса,
// а также метод fillrand для автоматического заполнения случайными значениями
template<class T>
class Matrix
{
private:
    T m[4][4]; // Матрица фиксированного размера 4х4, содержащая объекты класса-параметра Т

public:
    // Заполнение матрицы объектами переданного класса-параметра Т.
    // В данном случае это векторы в декартовой системе N координат или векторы в полярной системе координат
    Matrix() = default;

    Matrix(const Matrix& M) // Конструктор копирования для реализации операции присваивания
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                m[i][j] = M.m[i][j];
            }
        }
    }

    void print() // Вывод матрицы в консоль
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                cout << m[i][j] << ' ';
            }
            cout << endl;
        }
        cout << '\n';
    }

    Matrix operator -(const Matrix &M) // Перегрузка оператора вычитания
    {
        Matrix<T> res;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                res.m[i][j] = m[i][j] - M.m[i][j];
            }
        }
        return res;
    }

    Matrix operator +(const Matrix &M) // Перегрузка оператора сложения
    {
        Matrix<T> res;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                res.m[i][j] = m[i][j] + M.m[i][j];
            }
        }
        return res;
    }
};


int main()
{
    srand(time(nullptr)); // Для генерации случайных чисел

    cout << ">>> Decart vectors matrices:\n";
    cout << "m1:\n";
    Matrix<DecartVector> m1;
    m1.print();
    cout << "m2:\n";
    Matrix<DecartVector> m2;
    m2.print();
    cout << "\nm1 - m2:\n";
    Matrix<DecartVector> m3 = m1 - m2;
    m3.print();
    cout << "\nm1 + m2:\n";
    Matrix<DecartVector> m4 = m1 + m2;
    m4.print();

    cout << "\n>>> Polar vectors matrices:\n";
    cout << "p1:\n";
    Matrix<PolarVector> p1;
    p1.print();
    cout << "p2:\n";
    Matrix<PolarVector> p2;
    p2.print();
    cout << "\np1 - p2:\n";
    Matrix<PolarVector> p3 = p1 - p2;
    p3.print();
    cout << "\np1 + p2:\n";
    Matrix<PolarVector> p4 = p1 + p2;
    p4.print();
    return 0;
}
