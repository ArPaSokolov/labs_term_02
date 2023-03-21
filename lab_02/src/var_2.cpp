/*Реализуйте класс D Complex для работы с комплексными числами в формате а + bi. Он должен включать:
1. Базовый конструктор
2. Конструктор копирования
3.Оператор присваивания копированием
4.Деструктор
5.Операторы += и + *= и *
6.Оператор ++ префиксный и постфиксный (увеличение
действительной части числа на 1)
7.Операторы ввода и вывода
Продемонстрируйте работу с классом.

Лекция:
https://www.youtube.com/watch?v=BVMiGISZbMU

Пояснение для МВ
Complex& (тип возвращаемого объекта - ссылка <= возвращаем *this), 
но чтобы оно не разыменовывалось, ставим & перед operator)

Complex (тип возвращаемого объекта - значение <= возвращаем temp), 
поэтому не ставим & перед operator)

 оператор + (вне класса чтобы не привязываться к расположению z1 + double или double + z1)
 /*Complex operator + (const Complex& z1, const Complex& z2)
 {
    Complex temp = z1;
    temp += z2;
    return temp;
 }

 оператор * (вне класса чтобы не привязываться к расположению z1 * double или double * z1)
 Complex operator * (const Complex& z1, const Complex& z2)
 {
    Complex temp = z1;
    temp *= z2;
    return temp;
 }

*/

#include <iostream>
using namespace std;

class Complex //класс
{
private: // модификатор доступа
    
    double m_a; // информационное поле
    double m_b; // информационное поле

public: // модификатор доступа
   
    //базовый конструктор
    explicit Complex(double a = 0.0, double b = 0.0)  // explicit - однозначное определение
    {
        //cout << "Basic constructor" << endl;
        m_a = a;
        m_b = b;
    }

    // конструктор копирования
    Complex(const Complex& z)
    {
        //cout << "Copy constructor" << endl;
        m_a = z.m_a;
        m_b = z.m_b;
    }
    
    // оператор присваивания копированием
    Complex& operator = (Complex& z)
    {
        //cout << "Copy assigment operator" << endl;
        m_a = z.m_a;
        m_b = z.m_b;
        
        return *this;
    }
    
    // оператор +
    friend Complex operator + (const Complex& z1, const Complex& z2)
    {
        Complex temp;
        temp.m_a = z1.m_a + z2.m_a;
        temp.m_b = z1.m_b + z2.m_b;
        return temp;
    }

    // оператор +=
    Complex& operator +=  (const Complex& z)
    {
        m_a += z.m_a;
        m_b += z.m_b;
        return *this;
    }

    // оператор *
    friend Complex operator * (const Complex& z1, const Complex& z2)
    {
        Complex temp;
        temp.m_a = z1.m_a * z2.m_a - z1.m_b * z2.m_b;
        temp.m_b = z1.m_a * z2.m_b + z2.m_a * z1.m_b;
        return temp;
    }

    // оператор *=
    Complex& operator *= (const Complex& z)
    {
        double A = m_a * z.m_a - m_b * z.m_b;
        double B = m_a * z.m_b + z.m_a * m_b;
        m_a = A;
        m_b = B;
        return *this;
    }

    // оператор ++ постфиксный
    Complex operator ++ (int)
    {
        Complex temp = *this;
        this->m_a += 1;
        return temp;
    }

    // оператор ++ префиксный
    Complex& operator ++ ()
    {
        this -> m_a += 1;
        return *this;
    }

    // оператор ввода
    friend istream& operator >> (istream& in, Complex& z)
    {
        cout << "Enter" << endl;
        cout << "a: ";
        in >> z.m_a;
        cout << "b: ";
        in >> z.m_b;
        return in;
    }

    // оператор вывода
    friend ostream& operator << (ostream& out, const Complex& z)
    {
        out << z.m_a << " + " << z.m_b << "i";
        return out;
    }

    ~Complex()
    {

    }
};

int main()
{
    // ввод значений
    Complex z1, z2;
    cin >> z1;
    cin >> z2;

    // вывод значений
    cout << "z1 = " << z1 << endl;
    cout << "z2 = " << z2 << endl;

    // сумма
    Complex z3 = z1 + z2; 
    cout << "z = z1 + z2 = " << z3 << endl;

    // произведение
    Complex z4 = z1 * z2;
    cout << "z = z1 * z2 = " << z4 << endl;

    // оператор ++ префиксный
    int i = 0;
    cout << "Preincrement z1:" << endl;
    while (i < 10)
    {
        cout << ++z1 << " "; 
        ++i;
        cout << endl;
    }  
    
    // оператор ++ постфиксный
    i = 0;
    cout << "Postincrement z2:" << endl;
    while (i < 10)
    {
        cout << z2++ << " ";
        i++;
        cout << endl;
    }

    return 0;
}