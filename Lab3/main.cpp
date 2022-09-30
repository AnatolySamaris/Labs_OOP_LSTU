#include <iostream>
#include <cmath>

using namespace std;

// Базовый абстрактный класс, являющийся интерфейсом для производных классов,
// определяющих различные вектор-функции (ниже - MyFunction).
class VectorFunction
{
    // Интерфейс рассчитан на вектор-функции размера 2,
    // поэтому в protected принимаются два набора коэффициентов,
    // причем первая функция имеет 3 к-та, вторая - 2.
protected:
    double coefs_one[3];
    double coefs_two[2];
    double answer[2];

public:
    virtual void set_coefs_one(double *coefs) = 0; // Задать к-ты для первой функции
    virtual void set_coefs_two(double *coefs) = 0; // Задать к-ты для второй функции
    virtual void calculate(double x) = 0; // Посчитать значение вектор-функции от аргумента х

    double get_ans(int i) // вывести i-тый (начиная с 1) элемент вектор-функции
    {
        return this->answer[i-1];
    }
};


class MyFunction: public VectorFunction // Наследование методов и свойств из класса VectorFunction
{
public:
    void set_coefs_one(double *coefs) override // Задать к-ты для первой функции. Передается массив
    {
        for (int i = 0; i < 3; i++)
        {
            this->coefs_one[i] = coefs[i];
        }
    }

    void set_coefs_two(double *coefs) override // Задать к-ты для второй функции. Передается массив
    {
        for (int i = 0; i < 2; i++)
        {
            this->coefs_two[i] = coefs[i];
        }
    }

    // Результаты вычислений записываются в результирующий вектор,
    // определенный в интерфейсе через массив длины 2.
    // При помощи унаследованного метода get_ans(int i) можно затем
    // обратиться к любому из элементов результирующего вектора.
    void calculate(double x) override
    {
        this->answer[0] = this->coefs_one[0] * cos(x * this->coefs_one[1]) + this->coefs_one[2];
        this->answer[1] = this->coefs_two[0] * pow(x, this->coefs_two[1]);
    }
};

int main()
{
    MyFunction vf = MyFunction(); // Создаем объект класса MyFunction. Создание вектор-функции

    // Определяем коэффициенты первой и второй функции созданной вектор-функции
    double coefs1[3], coefs2[2];
    cout << "Enter coefficients a, b, c for the first function:\n";
    cin >> coefs1[0] >> coefs1[1] >> coefs1[2];
    vf.set_coefs_one(coefs1);

    cout << "Enter coefficients a, b for the second function:\n";
    cin >> coefs2[0] >> coefs2[1];
    vf.set_coefs_two(coefs2);

    // Получаем массив аргументов
    int x_size;
    cout << "Enter amount of x values:\n";
    cin >> x_size;
    double x_values[x_size];
    cout << "Enter x-values. If their amount is more than 1, separate them with space:\n";
    for (int i = 0; i < x_size; i++)
    {
        cin >> x_values[i];
    }

    // Вычисляем результат для каждого аргумента и выводим в консоль поэлементно
    for (int i = 0; i < x_size; i++)
    {
        vf.calculate(x_values[i]);
        cout << "For x = " << x_values[i] << " vector-function is (" << vf.get_ans(1) << ' ' << vf.get_ans(2) << ");\n";
    }
    return 0;
}
