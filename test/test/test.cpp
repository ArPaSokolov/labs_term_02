#include <iostream>

int main()
{
    short c = 12;
    int d = 10;
    short s = 2;

    short* pc = &c;          // получаем адрес переменной с типа short
    int* pd = &d;           // получаем адрес переменной d типа int
    short* ps = &s;         // получаем адрес переменной s типа short

    std::cout << "Variable c: address=" << pc << "\t value=" << *pc << std::endl;
    std::cout << "Variable d: address=" << pd << "\t value=" << *pd << std::endl;
    std::cout << "Variable s: address=" << ps << "\t value=" << *ps << std::endl;
}