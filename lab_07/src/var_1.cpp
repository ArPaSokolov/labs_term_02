#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

class Stack
{
private:
	int filled;
	int maxsize;
	double* data;

public:

	Stack(int maxSize) // конструктор с указанием размера стека
	{
		maxsize = maxSize;
		try {
			data = new double[maxsize];
			filled = 0;
			cerr << "Stack created!" << endl;
		}
		catch (...) {
			maxsize = 1;
			filled = 1;
			data = new double[maxsize];
			data[0] = 0;
			cerr << "bad_alloc" << endl;
		}
	}

	int GetSize() { // получить размер
		return filled;
	}

	int GetMaxsize() { // получить макс размер
		return maxsize;
	}

	bool Empty() { // проверка на пустоту стека
		bool empty = false;
		if (filled == 0) {
			empty = true;
		}
		return empty;
	}

	void Push(double K) { // добавляем элемент сверху стека
		try {
			data[filled] = K; // добавляем элемент
			cout << "Element " << data[filled] << " was added!" << endl;
			filled += 1; // стек пополнился на один элемент
			for (int i = filled; i < maxsize; i++) {
				data[i] = 0;
				}
		}
		catch (...) {
			cerr << "overflow_error" << endl;
		}
	}

	int Pop() { // удаляем верхний элемент стека
		try {
			int pop = data[filled - 1]; // вытаскиваем верхний элемент (количество -1)
			cout << "The top element " << data[filled - 1];
			data[filled - 1] = 0; // удаляем этот элемент
			filled -= 1; // количество элементов уменьшилось на 1
			cout << " was removed." << endl;
			return pop;
		}
		catch (...) {
			cerr << "out_of_range" << endl;
		}
	}

	void Top() { // показываем верхний элемент стека
		try {
			cout << "The top element of the stack is: " << data[filled - 1] << endl; // выводим верхний элемент
		}
		catch (...) {
			cerr << "logic_error" << endl;
		}
	}

	void Info() { // вывод информации о содержании стека
		if (Empty() == false) {
			cout << "Stack is filled on " << (filled * 100 / maxsize) << "% (" <<
				filled << " elements of " << maxsize << ")" << endl;
			Top();
		}
		else {
			cout << "Stack is filled on 0%, it contains 0 elements of "
				<< maxsize << "." << endl << "The top element of the stack is: 0" << endl;
		}
	}

	void ShowStack() { // поячеечный вывод стека начиная с верхней ячейки
		int i = maxsize;
		cout << "The elements:" << endl;
		while (i > 0) {
			i--;
			cout << data[i] << endl;
		}
	}
	
	~Stack() { // деструктор
		try {
			cerr << "Destructor runs..." << endl;;
			delete[] data;
			cerr << "Destructor succeded!" << endl;
		}
		catch (...) {
			cerr << "Destructor not succeded :(";
		}
	}
};

int main()
{
	double K;
	srand(time(nullptr)); // для рандома

	Stack stack(10);

	// заполняем рандомным количеством
	int topsize = 1 + rand() % 8;
	while (stack.GetSize() < 10) {
		K = 20 + rand() % (100 - 20 + 1);
		stack.Push(K);
	}

	stack.Info();

	stack.Push(23);

	//stack.ShowStack(); 
	
	stack.Pop();

	stack.Top();

	Stack errorstack(-5);

	errorstack.Info();

	errorstack.ShowStack();

	return 0;
}