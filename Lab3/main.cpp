#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Базовый класс вектор-функция.
// Поля functions, coefs, answer занесены в область видимости protected,
// чтобы классы-наследники могли унаследовать их.
class VectorFunction {
protected:
    // Вектор идентификаторов функций (здесь - 1 или 2), соответствующих функциям варианта 16
    vector<int> functions;
    // Вектор векторов коэффициентов соответствующих им функций. Каждый вектор - это набор коэффициентов функции под тем же индексом, что и функция в functions
    vector<vector<double>> coefs;
    // Вектор результатов функций-членов вектор-функции. Индекс результата соответствует индексу функции в functions
    vector<double> answer;

public:
    virtual void add(int id, vector<double> coefficients) = 0; // Добавление функции в вектор-функцию по идентификатору и присвоение ей коэффициентов
    virtual void calculate(double x) = 0; // Поэлементное вычисление вектор-функции от аргумента х

    vector<double> get_ans() // Возвращает результирующий вектор.
    {
        return this->answer;
    }
};

class Function: public VectorFunction // Наследование методов и свойств из класса VectorFunction
{
public:
    void add(int id, vector<double> func_coefs) override // Определение чисто виртуального метода add
    {
        if (id == 1)
        {
            vector<double> new_coefs {func_coefs[0], func_coefs[1]};
            this->functions.push_back(1); // Добавление идентификатора функции в вектор идентификаторов объекта класса Function
            this->coefs.push_back(new_coefs); // Добавление коэффициентов функции в вектор коэффициентов объекта класса Function
        }
        else // id == 2
        {
            vector<double> new_coefs {func_coefs[0], func_coefs[1], func_coefs[2]};
            this->functions.push_back(2);
            this->coefs.push_back(new_coefs);
        }
    }

    void calculate(double x) override
    {
        this->answer.clear(); // Если функция принимает аргумент не впервые, очищает прошлый результат

        for (int i = 0; i < this->functions.size(); i++) // Поэлементное вычисление вектор-функции от аргумента х по идентификаторам и коэффициентам её элементов
        {
            if (this->functions[i] == 1) this->answer.push_back(this->coefs[i][0] / x + this->coefs[i][1]);
            else this->answer.push_back(this->coefs[i][0] * log10(this->coefs[i][1] * x) + this->coefs[i][2]);
        }
    }

    void show_func() // Вывод заданных элементов вектор-функции
    {
        for (int i = 0; i < this->functions.size(); i++)
        {
            if (this->functions[i] == 1)
            {
                cout << this->coefs[i][0] << " / " << 'x' << " + " << this->coefs[i][1] << endl;
            }
            else // id == 2
            {
                cout << this->coefs[i][0] << " * lg(" << this->coefs[i][1] << " * x) + " << this->coefs[i][2] << endl;
            }
        }
    }
};

int main()
{
    Function vf = Function(); // Создание объекта класса Function

    cout << "Enter a vector-function size:";
    int size; cin >> size;

    cout << "There are two available functions:\n1. a / x + b\t 2. a * lg(b * x) + c" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << "Enter member-function id and its coefficients separated by space" << endl;
        // Ввод разделен на две части: ввод id и ввод коэффициентов, но пользователю это разделение не заметно
        int id; cin >> id;
        if (id == 1)
        {
            vector<double> coefficients(2);
            cin >> coefficients[0] >> coefficients[1];
            vf.add(1, coefficients);
        }
        else if (id == 2)
        {
            vector<double> coefficients(3);
            cin >> coefficients[0] >> coefficients[1] >> coefficients[2];
            vf.add(2, coefficients);
        }
        else
        {
            // Если пользователь допустил ошибку, добавляем еще одну итерацию для корректного ввода
            cout << "Wrong function id! Can be only 1 or 2. Try again." << endl;
            size++;
        }
    }

    cout << "\nNow your vector-function looks so:" << endl;
    vf.show_func();

    cout << "\nEnter an amount of x-values:";
    int n; cin >> n;

    // Вычисление и вывод результата вектор-функции от каждого введённого х
    for (int i = 0; i < n; i++)
    {
        cout << "Enter x-value:";
        double x; cin >> x;
        vf.calculate(x);
        cout << "For x = " << x << " result is ( ";
        for (auto j: vf.get_ans())
        {
            cout << j << " ";
        }
        cout << ")\n";
    }
    return 0;
}
