#include <iostream>
#include <typeinfo>
#include <limits>
#include <vector>

using namespace std;

// класс BaseException унаследован от класса exception
class base_exception: public exception {
protected:
    string text; // объяснение к исключению - общее для всех производных классов

public:
    virtual string what() = 0; // чистая виртуальная функция, которая выводит текст исключения
};

//класс, обрабатывающий исключение при вводе ошибочной размерности матрицы
class wrong_dimension final :public base_exception {
public:
//конструктор по умолчанию
    wrong_dimension() {
        text = "Ошибка. Неправильно введена размерность!";
    }

//конструктор с заданным текстом
    wrong_dimension(string _text) {
        text = _text;
    }

//переопределяем виртуальную функцию what()
    string what() {
        return text;
    }
};

class int_exception final :public base_exception {
public:
//конструктор по умолчанию
    int_exception() {
        text = "Ошибка. Тип данных не целочисленный!";
    }

//конструктор с заданным текстом
    int_exception(string _text) {
        text = _text;
    }

//переопределяем виртуальную функцию what()
    string what() {
        return text;
    }
};

//начало объявления класса
class Matrix {
//объявление свойств и методов класса в общедоступной области видимости
public:
//конструктор по умолчанию
    Matrix() {
        rows = 0;
        cols = 0;
        nums = NULL;
    }
//конструктор копирования
    Matrix(const Matrix& A) {
        rows = A.rows;
        cols = A.cols;
        nums = new int[A.rows * A.cols];
        for (int i = 0; i < A.rows * A.cols; i++) {
            nums[i] = A.nums[i];
        }
    }
//конструктор c параметрами
    Matrix(int *values, int m, int n) {
        rows = m;
        cols = n;
        nums = new int[rows * cols];
        for (int i = 0; i < rows * cols; i++) {
            nums[i] = values[i];
        }
    }
//деструктор
    ~Matrix() {
        if (nums != NULL) {
            delete nums;
        }
    }
//перегрузка оператора присваивания
    const Matrix& operator = (const Matrix& A) {
        rows = A.rows;
        cols = A.cols;
        if (nums != NULL) {
            delete nums;
        }
        nums = new int[rows * cols];
        for (int i = 0; i < rows * cols; i++) {
            nums[i] = A.nums[i];
        }
        return *this;
    }
//перегрузка оператора умножения на скаляр через дружественную функцию
    friend Matrix operator * (const Matrix& A, const int b) {
        int *tmp = new int[A.rows * A.cols];
        for (int i = 0; i < A.rows * A.cols; i++) {
            tmp[i] = A.nums[i] * b;
        }
        Matrix *C = new Matrix(tmp, A.rows, A.cols);
        return *C;
    }
//перегрузка оператора сложения через дружественную функцию
    friend Matrix operator + (const Matrix& A, const Matrix& B) {
        int *tmp = new int[A.rows * A.cols];
        for (int i = 0; i < A.rows * A.cols; i++) {
            tmp[i] = A.nums[i] + B.nums[i];
        }
        Matrix *C = new Matrix(tmp, A.rows, A.cols);
        return *C;
    }
//перегрузка оператора вычитания через дружественную функцию
    friend Matrix operator - (const Matrix& A, const Matrix& B) {
        int *tmp = new int[A.rows * A.cols];
        for (int i = 0; i < A.rows * A.cols; i++) {
            tmp[i] = A.nums[i] - B.nums[i];
        }
        Matrix *C = new Matrix(tmp, A.rows, A.cols);
        return *C;
    }
//перегрузка оператора умножения на матрицу через дружественную функцию
    friend Matrix operator *(const Matrix& A, const Matrix& B) {
        int *tmp = new int[A.rows * B.cols];
        for (int i = 0; i < A.rows * B.cols; i++) {
            tmp[i] = 0;
        }
        for (int i = 0; i < A.rows; i++) {
            for (int j = 0; j < B.cols; j++) {
                for (int c = 0; c < A.cols; c++) {
                    tmp[i * B.cols + j] += A.nums[i * A.cols + c] * B.nums[c * B.cols + j];
                }
            }
        }
        Matrix *C = new Matrix(tmp, A.rows, B.cols);
        return *C;
    }
    void print_matrix() {
        //Открытый метод, печатающий матрицу в консоль
        for (int i = 0; i < rows; i++) {
            for (int j = cols * i; j < cols * i + cols; j++) {
                cout << nums[j];
                if (j != (cols * i + cols - 1)) {
                    cout << " ";
                }
            }
            cout << "\n";
        }
    }

//объявление свойств и методов класса в закрытой области видимости
private:
    int rows; //кол-во строк в матрице
    int cols; //кол-во столбцов в матрице
    int *nums; //элементы матрицы
};

//функция для ввода размерности матрицы
int* dimension_reading() {
    static int dim[2];
    dim[0] = -1;
    dim[1] = -1;
    int m, n;
    try {
        cout << "Введите размерность матрицы (m x n) через пробел: ";
        cin >> m;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            throw wrong_dimension("Ошибка. Вводимые параметры должны быть целыми числами!");
        }
        cin >> n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            throw wrong_dimension("Ошибка. Вводимые параметры должны быть целыми числами!");
        }
        if (m * n <= 0 || m < 0 || n < 0) {
            throw wrong_dimension("Ошибка. Нулевая или отрицательная размерность!");
        }
    }
    catch (wrong_dimension e) {
        cout << e.what() << '\n';
        return dim;
    }
    dim[0] = m;
    dim[1] = n;
    return dim;
}

//функция для ввода элементов матрицы
vector <int> nums_reading(int m, int n) {
    int tmp;
    vector <int> nums;
    for (int i = 0; i < m; i++) {
        cout << "Введите элементы " << i + 1 << " строки через пробел: ";
        for (int j = n * i; j < n * i + n; j++) {
            while (true) {
                try {
                    cin >> tmp;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        throw int_exception();
                    }
                    break;
                }
                catch (int_exception e) {
                    cout << e.what() << '\n';
                }
            }
            nums.push_back(tmp);
        }
    }
    return nums;
}

int main() {
    system("chcp 65001 > nul");
    int m, n;

    cout << "Размерность матриц A и B\n";
    while (true) {
        int* ptr = dimension_reading();
        if (ptr[0] != -1) {
            m = ptr[0];
            n = ptr[1];
            break;
        }
    }

    cout << "\n";
    int values[m * n];

    cout << "\nВвод элементов матрицы A:\n";
    vector <int> tmp = nums_reading(m, n);
    for (int i = 0; i < m * n; i++) {
        values[i] = tmp[i];
    }

    //создание экземпляра класса с использованием конструктора с параметрами
    Matrix A(values, m, n);

    int b;
    while (true) {
        try {
            cout << "Введите коэфф. b: ";
            cin >> b;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                throw int_exception();
            }
            break;
        }
        catch (int_exception e) {
            cout << e.what() << '\n';
        }
    }
    cout << "\nИсходная матрица A:\n";
    A.print_matrix(); //вывод матрицы A на экран
    cout << "\nМатрица C = A * b:\n";
    //использование перегруженного оператора умножения на скаляр
    Matrix C = A * b;
    C.print_matrix(); //вывод матрицы C на экран

    cout << "\nВвод элементов матрицы B:\n";
    tmp = nums_reading(m, n);
    for (int i = 0; i < m * n; i++) {
        values[i] = tmp[i];
    }

    //создание экземпляра класса с использованием конструктора с параметрами
    Matrix B(values, m, n);

    cout << "\nИсходная матрица B:\n";
    B.print_matrix(); //вывод матрицы B на экран

    cout << "\nМатрица C = A + B:\n";
    //использование перегруженного оператора сложения
    C = A + B;
    C.print_matrix(); //вывод матрицы C на экран

    cout << "\nМатрица C = A - B:\n";
    //использование перегруженного оператора вычитания
    C = A - B;
    C.print_matrix(); //вывод матрицы C на экран

    cout << "\nРазмерность матрицы B для умножения\n";
    while (true) {
        try {
            int* ptr = dimension_reading();
            if (ptr[0] != -1) {
                if (n != ptr[0]) {
                    throw wrong_dimension("Ошибка. Кол-во столбцов матрицы A не равняется кол-ву строк матрицы B!");
                }
                m = ptr[0];
                n = ptr[1];
                break;
            }
        }
        catch (wrong_dimension e) {
            cout << e.what() << '\n';
        }

    }

    cout << "\nВвод элементов матрицы B:\n";
    tmp = nums_reading(m, n);
    for (int i = 0; i < m * n; i++) {
        values[i] = tmp[i];
    }

    //создание экземпляра класса с использованием конструктора с параметрами
    Matrix B1(values, m, n);

    cout << "\nМатрица C = A * B:\n";
    //использование перегруженного оператора умножения
    C = A * B1;
    C.print_matrix(); //вывод матрицы C на экран

    return 0;
}
