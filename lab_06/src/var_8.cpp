#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

class Figure
{
private:

protected:
	string m_name; // имя фигуры = тип
	string color; // цвет фигуры
	
public:

	Figure(const string& name) { // конструктор по параметру
		m_name = name;
		color = "none";
	}

	virtual void ShowFigure() { 
	
	}

	virtual ~Figure() {

	}
};

class Quadrat : public Figure { // подкласс

private:
	int A[2]; // координаты точки A
	int B[2]; // координаты точки B
	int C[2]; // координаты точки C
	int D[2]; // координаты точки D

public:

	Quadrat(const string& name) : Figure (name) { // конструктор по параметру
		for (int i = 0; i < 2; i++) { // обнулям координаты
			A[i] = 0;
			B[i] = 0;
			C[i] = 0;
			D[i] = 0;
		}
	}

	void SetFigure() { // ввод данных
		cout << "Type: " << m_name << endl;
		cout << "Enter color: ";
		cin >> color;
		cout << "Enter A: ";
		for (int i = 0; i < 2; i++) {
			cin >> A[i];
		}
		cout << "Enter B: ";
		for (int i = 0; i < 2; i++) {
			cin >> B[i];
		}
		cout << "Enter C: ";
		for (int i = 0; i < 2; i++) {
			cin >> C[i];
		}
		cout << "Enter D: ";
		for (int i = 0; i < 2; i++) {
			cin >> D[i];
		}
	}

	void ShowFigure() { // вывод данных
		cout << "Type: " << m_name << endl;
		cout << "Color: " << color << endl;
		cout << "A(" << A[0] << ";" << A[1] << ") ";
		cout << "B(" << B[0] << ";" << B[1] << ") ";
		cout << "C(" << C[0] << ";" << C[1] << ") ";
		cout << "D(" << D[0] << ";" << D[1] << ")" << endl;
		cout << "Square: " << GetSquare() << endl << endl;
	}

	double GetSquare() {
		double AB; // сторона
		double BC; // сторона
		double CD; // сторона
		double DA; // сторона
		double AC; // диагональ
		double BD; // диагональ
		double square; // площадь
		AB = sqrt(pow((B[0] - A[0]), 2) + pow((B[1] - A[1]), 2)); // длина стороны
		BC = sqrt(pow((C[0] - B[0]), 2) + pow((C[1] - B[1]), 2)); // длина стороны
		CD = sqrt(pow((D[0] - C[0]), 2) + pow((D[1] - C[1]), 2)); // длина стороны
		DA = sqrt(pow((A[0] - D[0]), 2) + pow((A[1] - D[1]), 2)); // длина стороны
		AC = sqrt(pow((C[0] - A[0]), 2) + pow((C[1] - A[1]), 2)); // длина диагонали
		BD = sqrt(pow((D[0] - B[0]), 2) + pow((D[1] - B[1]), 2)); // длина диагонали
		if (AB == BC && CD == DA && AB == CD && AC==BD) { // если стороны равны и равны диагонали => квадрат
			square = pow(AB, 2);
		}
		return square;
	}

	virtual ~Quadrat() {

	}
};

class Oval : public Figure {

private:
	int A[2]; // координаты точки A
	int B[2]; // координаты точки B
	int O[2]; // координаты точки O

public:
	Oval(const string& name) : Figure(name) { // конструктор по параметру
		for (int i = 0; i < 2; i++) {
			A[i] = 0;
			B[i] = 0;
			O[i] = 0;
		}
	}

	void SetFigure() { // ввод данных
		cout << "Type: " << m_name << endl;
		cout << "Enter color: ";
		cin >> color;
		cout << "Enter A: ";
		for (int i = 0; i < 2; i++) {
			cin >> A[i];
		}
		cout << "Enter B: ";
		for (int i = 0; i < 2; i++) {
			cin >> B[i];
		}
		cout << "Enter O: ";
		for (int i = 0; i < 2; i++) {
			cin >> O[i];
		}
	}

	void ShowFigure() { // вывод данных
		cout << "Type: " << m_name << endl;
		cout << "Color: " << color << endl;
		cout << "A(" << A[0] << ";" << A[1] << ") ";
		cout << "B(" << B[0] << ";" << B[1] << ") ";
		cout << "O(" << O[0] << ";" << O[1] << ")" << endl;
		cout << "Square: " << GetSquare() << endl << endl;
	}

	double GetSquare() { // ищем площадь
		double OB; // длина малой полуоси
		double OA; // длина большой полуоси
		double square; // площадь
		OA = sqrt(pow((A[0] - O[0]), 2) + pow((A[1] - O[1]), 2)); // находим длину малой полуоси
		OB = sqrt(pow((B[0] - O[0]), 2) + pow((B[1] - O[1]), 2)); // находим длину большой полуоси
		if (((A[0] - O[0]) * (B[0] - O[0]) + (A[1] - O[1]) * (B[1] - O[1])) == 0) { 
			// скалярное произведение векторов = 0 => угол между ними равен 90 градусов =>
			square = M_PI * OA * OB; // M_PI - число Пи из библиотеки <cmath>
		}
		return square;
	}

	virtual ~Oval() {

	}
};

void GetInfo(Figure& creature) { // по условию
	creature.ShowFigure();
}

int main()
{
	Quadrat quad1("Quadrat 1");
	Quadrat quad2("Quadrat 2");
	Oval oval("Oval 1");

	quad1.SetFigure();
	quad2.SetFigure();
	oval.SetFigure();


	GetInfo(quad1);

	GetInfo(oval);

	GetInfo(quad2);

	return 0;
}