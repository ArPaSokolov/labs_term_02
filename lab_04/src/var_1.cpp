#include <iostream>
using namespace std;

class MyVectorBool {
private:

	bool* binaryN; // одномерный динамический массив для хранения бинарной записи числа
	int size = 0; // количество элементов

public:

	MyVectorBool(int N) { // конструктор
		int S = N; // десятичная запись числа
		while (S > 0) { // считаем количество знаков в числе
			S = S / 2;  // делим десятичное число на 2
			size++;
		}
		binaryN = (bool*)malloc(size * sizeof(bool)); // выделяем память под бинарную запись числа
		if (binaryN != NULL) { // проверяем, выделилась ли память успешно
			int decimalN = N; // десятичная запись числа
			int R; // остаток от деления
			int i = 1; // счетчик
			while (decimalN > 0) {
				R = decimalN % 2;  // остаток от деления на 2
				binaryN[size - i] = R; // сохраняем остаток в массив
				decimalN = decimalN / 2;  // делим десятичное число на 2
				i++;
			}
		}
		else { // память не выделилась
			cout << "Error: could not allocate memory";
		}
	}

	MyVectorBool(MyVectorBool& V) {
		size = V.size;
		binaryN = (bool*)calloc(size, sizeof(bool)); // выделяем память под бинарную запись числа
		if (binaryN != NULL) { // проверяем, выделилась ли память успешно
			for (int i = 0; i < size; i++) {
				binaryN[i] = V.binaryN[i]; // заполняем новый массив
			}
		}
		else { // память не выделилась
			cout << "Error 0: could not allocate memory" << endl;
		}
	}

	MyVectorBool() { // конструктор по умолчанию
		size = 0;
		binaryN = nullptr;
	}

	friend ostream& operator << (ostream& out, const MyVectorBool& V) { // оператор вывода
		cout << "Binary: ";
		for (int i = 0; i < V.size; i++) {
			out << V.binaryN[i];
		}
		cout << endl;
		return out;
	}

	MyVectorBool& operator = (MyVectorBool& V) { // оператор присваивания
		size = V.size;
		binaryN = (bool*)calloc(size, sizeof(bool)); // выделяем память под бинарную запись числа
		if (binaryN != NULL) { // проверяем, выделилась ли память успешно
			for (int i = 0; i < size; i++) {
				binaryN[i] = V.binaryN[i]; // заполняем новый массив
			}
			return *this;
		}
		else { // память не выделилась
			cout << "Error 1: could not allocate memory" << endl;
		}
	}

	friend MyVectorBool operator + (MyVectorBool& V1, MyVectorBool& V2)
	{
		int maxSize = max(V1.size, V2.size);
		if (V1.size < maxSize) { // выравниваем количество элементов
			for (int i = V1.size; i < maxSize; i++) {
				V1.add_start(0);
			}
		}
		else { // выравниваем количество элементов
			for (int i = V2.size; i < maxSize; i++) {
				V2.add_start(0);
			}
		}
		int carry = 0; // инициализируем перенос
		MyVectorBool temp; // создаем новый массив для хранения суммы
		temp.size = maxSize;
		temp.binaryN = (bool*)calloc(temp.size, sizeof(bool)); // выделяем память
		for (int i = (maxSize - 1); i >= 0; i--) { // бежим по парам элементов
			if (V1.binaryN[i] == 0 && V2.binaryN[i] == 0 && carry == 0) {
				temp.binaryN[i] = 0;
				carry = 0;
			}
			else if ((V1.binaryN[i] == 1 && V2.binaryN[i] == 0 && carry == 0) || 
				(V1.binaryN[i] == 0 && V2.binaryN[i] == 1 && carry == 0) ||
				(V1.binaryN[i] == 0 && V2.binaryN[i] == 0 && carry == 1)) {
				temp.binaryN[i] = 1;
				carry = 0;
			}
			else if ((V1.binaryN[i] == 1 && V2.binaryN[i] == 1 && carry == 0) ||
				(V1.binaryN[i] == 1 && V2.binaryN[i] == 0 && carry == 1) ||
				(V1.binaryN[i] == 0 && V2.binaryN[i] == 1 && carry == 1)) {
				temp.binaryN[i] = 0;
				carry = 1;
			}
			else if (V1.binaryN[i] == 1 && V2.binaryN[i] == 1 && carry == 1) {
				temp.binaryN[i] = 1;
				carry = 1;
			}
		}
		if (carry == 1) {
			temp.add_start(1);
		}
		return temp;
	}

	bool& operator[](int index) { // оператор изменения элемента по индексу
		return binaryN[index];
	}

	void add_start(bool k) { // добавление элемента в начало
		bool* newBinaryN = (bool*)calloc(size, sizeof(bool)); // создаем новый массив для временного хранения элементов
		for (int i = 0; i < size; i++) {
			newBinaryN[i] = binaryN[i]; // заполняем новый массив
		}
		size++; // удлиняем массив на один эллемент
		binaryN = (bool*)realloc(binaryN, size * sizeof(bool)); // выделяем память под новый элемент
		if (binaryN != NULL) { // проверяем, выделилась ли память успешно
			for (int i = size; i > 0; i--) { // сдвигаем все элементы вправо на одну позицию
				binaryN[i] = newBinaryN[i - 1];
			}
			binaryN[0] = k; // добавляем новый элемент в начало массива
			free(newBinaryN); // чистим память
		}
		else { // память не выделилась
			size--; // возвращаем прежнюю длину
			cout << "Error 2: could not allocate memory" << endl;
		}
	}

	void add_end(bool k) { // добавление элемента в конец
		bool* newBinaryN = (bool*)calloc(size, sizeof(bool)); // создаем новый массив для временного хранения элементов
		for (int i = 0; i < size; i++) {
			newBinaryN[i] = binaryN[i]; // заполняем новый массив
		}
		size++; // удлиняем массив на один эллемент
		binaryN = (bool*)realloc(binaryN, size * sizeof(bool)); // выделяем память под новый элемент
		if (binaryN != NULL) { // проверяем, выделилась ли память успешно
			for (int i = 0; i < size; i++) {
				binaryN[i] = newBinaryN[i]; // заполняем новый массив
			}
			binaryN[size - 1] = k; // добавляем новый элемент в начало массива
			free(newBinaryN); // чистим память
		}
		else { // память не выделилась
			size--; // возвращаем прежнюю длину
			cout << "Error 3: could not allocate memory" << endl;
		}
	}

	void erase(int k) { // удаление элемента по индексу
		bool* newBinaryN = (bool*)calloc(size, sizeof(bool)); // создаем новый массив для временного хранения элементов
		for (int i = 0; i < size; i++) {
			newBinaryN[i] = binaryN[i]; // заполняем новый массив
		}
		size--; // уменьшаем массив на один элемент
		binaryN = (bool*)realloc(binaryN, size * sizeof(bool)); // выделяем память на один элемнт меньше
		if (binaryN != NULL) { // проверяем, выделилась ли память успешно
			int j = 0;
			for (int i = 0; i < size; i++) { // заполняем новый массив
				if (i == (k - 1)) { // встретили индекс, по которому нужно удалить элемент
					j++; // пропускаем этот индекс в массиве с временным хранением элементов
					binaryN[i] = newBinaryN[j]; // теперь j всегда на 1 больше чем i
				}
				else { // это не индекс по которому нужно удалить элемент
					binaryN[i] = newBinaryN[j];
				}
				j++;
			}
			free(newBinaryN); // чистим память
		}
		else { // память не выделилась
			size++; // возвращаем прежнюю длину
			cout << "Error 4: could not allocate memory" << endl;
		}
	}

	int GetSize() { // геттер длины массива
		return size;
	}

	~MyVectorBool() { // деструктор
		free(binaryN);
	}

	//----------------------------------------------------------- доп задание ------------------------------------------------
	friend MyVectorBool operator / (MyVectorBool& V1, MyVectorBool& V2) { // перемешать элементы двух массивов начиная с конца
		int sumSize = V1.size + V2.size; // находим общую длину
		MyVectorBool temp; // новый вектор для хранения
		temp.size = sumSize;
		temp.binaryN = (bool*)calloc(temp.size, sizeof(bool)); // выделяем память
		if (V1.size > V2.size) { // случай когда первое число больше чем второе
			int rest = V1.size - V2.size; // разница в длине
			for (int i = 0; i < (rest - 1) || i < (V1.size - 1); i++) {
				temp.binaryN[i] = V1.binaryN[i];
			}
			int j = rest;
			int i = 0;
			int m = rest;
			while (m <= (temp.size - 1) && j <= (V1.size - 1)) { // закидываем элементы из первого через 1
				temp.binaryN[m] = V1.binaryN[j];
				m += 2;
				j++;
			}
			m = rest + 1;
			while (m <= (temp.size - 1) && i <= (V2.size - 1)) { // закидываем элементы из второго через 1
				temp.binaryN[m] = V2.binaryN[i];
				m += 2;
				i++;
			}
		}
		return temp;
	}
	//----------------------------------------------------------- доп задание ------------------------------------------------
};


int main() {
	int N;
	cout << "Enter a decimal number A: ";
	cin >> N; // вводим десятичное число

	MyVectorBool A(N);/*
	A.add_start(0);*/
	cout << A;

	int M;
	cout << "Enter a decimal number B: ";
	cin >> M; // вводим десятичное число

	MyVectorBool B(M);/*
	B.add_end(0)*/;
	cout << B;

	MyVectorBool C;
	C = A + B;
	cout << "A + B" << endl;
	cout << C;

	// доп задание
	C = A / B;
	cout << C;

	/*cout << "Enter index from 1 to " << B.GetSize() << " to delete: ";
	int k;
	cin >> k;
	B.erase(k);
	cout << B;

	cout << "Enter index from 1 to " << B.GetSize() << " to change: ";
	int i;
	bool k;
	cin >> i;
	cout << "Change to: ";
	cin >> k;
	B[i-1] = k;
	cout << B;*/


	return 0;
}