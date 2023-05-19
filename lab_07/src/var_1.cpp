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
		catch(...){
			data = nullptr;
			cerr << "bad_alloc :(" << endl;
		}
	}

	int GetSize() { // получить размер
		return filled;
	}

	int GetMaxsize() { // получить макс размер
		return maxsize;
	}

	void Fill() { // заполняем стек рандомным количеством рандомных чисел
		int topsize = GetRandomNumber(1, 8);
		while (filled < topsize) {
			data[filled] = 20 + rand() % (100 - 20 + 1);; // добавляем элемент
			cout << "Element " << data[filled] << " was added!" << endl;
			filled += 1; // стек пополнился на один элемент
		}
		for (int i = filled; i < maxsize; i++) {
			data[i] = 0;
		}
	}

	bool Empty() { // проверка на пустоту стека
		bool empty = false;
		if (filled == 0) {
			empty = true;
		}
		return empty;
	}

	void Push() { // добавляем элемент сверху стека
		cout << "Enter new element to push: ";
		try {
			cin >> data[filled]; // добавляем элемент
			filled += 1; // стек пополнился на один элемент
		}
		catch (...) {
			cerr << "overflow_error :(" << endl;
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
			cerr << "out_of_range :(" << endl; 
		}
	}

	void Top() { // показываем верхний элемент стека
		try {
			cout << "The top element of the stack is: " << data[filled - 1] << endl; // выводим верхний элемент
		}
		catch (...) {
			cerr << "logic_error :(" << endl;
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

	int GetRandomNumber(int min, int max) // поиск рандомного числа от min до max
	{
		srand(time(NULL)); // автоматическая рандомизация
		int num = min + rand() % (max - min + 1);
		return num;
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
	Stack stack(10);

	stack.Fill();

	stack.Info();

	stack.Push();

	stack.Info();

	stack.ShowStack();

	stack.Pop();

	stack.Top();

	Stack errorstack(-5);

	return 0;
}