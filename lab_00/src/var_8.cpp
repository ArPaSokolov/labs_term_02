/*
Написать класс
Методы Set, Get + любой доп
2 информационных поля
2 конструктора + деструктор
константы, указатели, ссылки
*/

#include <iostream>
#include <cmath>
using namespace std;

class Rect // класс
{
private: // модификатор доступа
	int *A; // поле
	int *B; // поле
	const float pi = 3.1415926535; // поле
public: // модификатор доступа
	Rect(int *valueA, int *valueB) // constructor 1
	{
		A = valueA;
		B = valueB;
	}
	Rect() // constructor 2
	{
		A = new int;
		B = new int;
	}
	
	void SetSides(int sideOne, int sideTwo) // (метод) задаем значение
	{
		A = &sideOne;
		B = &sideTwo;
	}

	int GetA() // (метод) получаем значение
	{
		return *A;
	}

	int GetB() // (метод) получаем значение
	{
		return *B;
	}

	int Square() // (метод) находим площадь
	{
		int valueS = (*A) * (*B);
		return valueS;
	}
	double circleLength()
	{
		double d = pow(*A, 2) + pow(*B, 2);
		double length = pi * sqrt(d);
		return length;
	}

	void Show() // (метод) выводим все данные
	{
		cout << "A is: " << *A << "  |  A adress is: " << A << endl;
		cout << "B is: " << *B << "  |  B adress is: " << B << endl;
		cout << "PI is: " << pi << endl;
	}

	~Rect() // destructor
	{
		delete A;
		delete B;
	}

};
int main()
{
	cout << "Enter 2 sides:" << endl;
	int valueA;
	int valueB;
	cin >> valueA;
	cin >> valueB;

	Rect AB (&valueA, &valueB); //обЪект
	
	cout << "Square is: " << AB.Square() << endl;
	cout << "Circle length is: " << AB.circleLength() << endl;
	cout << "" << endl;
	
	AB.Show();

	return 0;
}