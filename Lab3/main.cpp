#include <iostream>
#include <cmath>

using namespace std;

class VectorFunction
{
protected:
    const double null = -999999;
    double answer[2];
    double coefs[3];
    double argument = null;

public:
    virtual void calculate(double x) = 0;
    virtual void set_coefs(double a, double b, double c) = 0;
    virtual void show_coefs() = 0;

    double get_ans(int i)
    {
        return answer[i-1];
    }

    void show_result()
    {
        cout << "f1(" << argument << ") = " << answer[0] << endl;
        cout << "f2(" << argument << ") = " << answer[1] << endl;
    }
};


class FunctionOne: public VectorFunction
{
public:
    void calculate(double x) override
    {
        if (argument == null)
        {
            argument = x;
            answer[0] = this->coefs[0] * cos(this->coefs[1] * x) + this->coefs[2];
        }
        else if (x == argument)
        {
            answer[0] = this->coefs[0] * cos(this->coefs[1] * x) + this->coefs[2];
        }
        else
        {
            cout << "Argument x must be equal in every function!\nCalculating with x in the first function.\n";
            answer[0] = this->coefs[0] * cos(this->coefs[1] * argument) + this->coefs[2];
        }
    }

    void set_coefs(double a, double b, double c) override
    {
        this->coefs[0] = a;
        this->coefs[1] = b;
        this->coefs[2] = c;
    }

    void show_coefs() override
    {
        cout << this->coefs[0] << ' ' << this->coefs[1] << ' ' << this->coefs[2] << endl;
    }
};


class FunctionTwo: public VectorFunction
{
public:
    void calculate(double x) override
    {
        if (argument == null)
        {
            argument = x;
            answer[1] = this->coefs[0] * pow(x, this->coefs[1]);
        }
        else if (x == argument)
        {
            answer[1] = this->coefs[0] * pow(x, this->coefs[1]);
        }
        else
        {
            cout << "Argument x must be equal in every function!\nCalculating with x in the first function.\n";
            answer[1] = this->coefs[0] * pow(x, this->coefs[1]);
        }
    }

    void set_coefs(double a, double b, double c=0) override
    {
        this->coefs[0] = a;
        this->coefs[1] = b;
    }

    void show_coefs() final
    {
        cout << this->coefs[0] << ' ' << this->coefs[1] << endl;
    }
};

int main()
{
    FunctionOne f1 = FunctionOne();
    FunctionTwo f2 = FunctionTwo();

    f1.set_coefs(1, 2, 3);
    f2.set_coefs(10, 2);

    f1.show_coefs();
    f2.show_coefs();

    f1.calculate(5);
    f2.calculate(5);

    cout << f1.get_ans(1) << ' ' << f1.get_ans(2) << endl;

    f1.show_result();

    cout << endl;
    f1.set_coefs(3, 3, 3);
    f2.set_coefs(1, 5);

    f1.calculate(10);
    f2.calculate(5);
    f1.show_result();
    return 0;
}
