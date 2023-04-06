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

	MyVectorBool() { // конструктор по умолчанию
		size = 0;
		binaryN = (bool*)calloc(size, sizeof(bool));
	}

	friend ostream& operator << (ostream& out, const MyVectorBool& V) { // оператор вывода
		cout << "Binary: ";
		bool flag = false; // флаг на встречу с единицей
		int i = 0; // счетчик
		while (i < V.size) { // цикл для вывода бинарной записи
			if (flag == false && V.binaryN[i] == 1) { // если данный элемент равен единице и единица не встречалась до этого
				flag = true; // флаг - встретили единицу
			}
			if (flag == true) { // если встретили единицу 
				out << V.binaryN[i];  // выводим элемент
			}
			i++;
		}
		if (flag == false) { // если единица так и не встретилась
			cout << 0; // выводим один нолик
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

	friend MyVectorBool& operator + (MyVectorBool& V1, MyVectorBool& V2) { // оператор сложения

		int maxSize = max(V1.size, V2.size); // находим самое длинное число
		if (V1.size < maxSize) { // выравниваем количество элементов
			bool* newBinaryN = (bool*)calloc(V1.size, sizeof(bool)); // создаем новый массив для временного хранения элементов
			for (int i = 0; i < maxSize; i--) {
				newBinaryN[i] = V1.binaryN[i]; // заполняем новый массив
			}
			V1.binaryN = (bool*)realloc(V1.binaryN, maxSize * sizeof(bool)); // выделяем память под новый элемент
			if (V1.binaryN != NULL) { // проверяем, выделилась ли память успешно
				for (int i = V1.size; i > 0; i--) {
					V1.binaryN[i] = newBinaryN[i];
					cout << V1.binaryN[i];
				}
				for (int i = V1.size; i < maxSize; i++) {
					V1.binaryN[i] = 0;
					cout << V1.binaryN[i];
				}
				cout << endl;
				free(newBinaryN); // чистим память
			}
			else { // память не выделилась
				cout << "Error 01: could not allocate memory" << endl;
			}
		}
		if (V2.size < maxSize) { // выравниваем количество элементов
			bool* newBinaryN = (bool*)calloc(V2.size, sizeof(bool)); // создаем новый массив для временного хранения элементов
			for (int i = 0; i < maxSize; i++) {
				newBinaryN[i] = V2.binaryN[i]; // заполняем новый массив
			}
			V2.binaryN = (bool*)realloc(V2.binaryN, maxSize * sizeof(bool)); // выделяем память под новый элемент
			if (V2.binaryN != NULL) { // проверяем, выделилась ли память успешно
				for (int i = V2.size; i > 0; i--) {
					V2.binaryN[i] = newBinaryN[i - 1];
					cout << V2.binaryN[i];
				}
				for (int i = V2.size; i < maxSize; i++) {
					V2.binaryN[i] = 0;
					cout << V2.binaryN[i];
				}
				cout << endl;
				free(newBinaryN); // чистим память
			}
			else { // память не выделилась
				cout << "Error 02: could not allocate memory" << endl;
			}
		}
		int carry = 0; // инициализируем перенос
		MyVectorBool temp; // создаем новый массив для хранения суммы
		temp.binaryN = (bool*)calloc(maxSize, sizeof(bool)); // выделяем память
		for (int i = maxSize; i > 0; i--) { // бежим по парам элементов
			if (V1.binaryN[i] == 0 && V2.binaryN[i] == 0 && carry == 0) {
				temp.binaryN[i] = 0;
				carry = 0;
			}
			else if (V1.binaryN[i] == 1 && V2.binaryN[i] == 0 && carry == 0) {
				temp.binaryN[i] = 1;
				carry = 0;
			}
			else if (V1.binaryN[i] == 0 && V2.binaryN[i] == 1 && carry == 0) {
				temp.binaryN[i] = 1;
				carry = 0;
			}
			else if (V1.binaryN[i] == 1 && V2.binaryN[i] == 1 && carry == 0) {
				temp.binaryN[i] = 0;
				carry = 1;
			}
			else if (V1.binaryN[i] == 1 && V2.binaryN[i] == 1 && carry == 1) {
				temp.binaryN[i] = 1;
				carry = 1;
			}
			else if (V1.binaryN[i] == 1 && V2.binaryN[i] == 0 && carry == 1) {
				temp.binaryN[i] = 0;
				carry = 1;
			}
			else if (V1.binaryN[i] == 0 && V2.binaryN[i] == 1 && carry == 1) {
				temp.binaryN[i] = 0;
				carry = 1;
			}
			else if (V1.binaryN[i] == 0 && V2.binaryN[i] == 0 && carry == 1) {
				temp.binaryN[i] = 1;
				carry = 0;
			}
			//if (carry == 1 && (i + 1) == maxSize) { // единичка осталась, а длина закончилась
			//	temp.size++;
			//	temp.binaryN = (bool*)realloc(temp.binaryN, (maxSize + 1)* sizeof(bool)); // удлиняем на один элемент
			//	temp.binaryN[maxSize] = 1;
			//}
			/*cout << temp.binaryN[i] << endl;*/
		}
		return temp;
	}

	bool operator[](int index) const { // оператор получения элемента по индексу
		return binaryN[index];
	}

	/*bool& operator[](int index) {
		return binaryN[index];
	}*/

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
};


int main() {
	int N;
	cout << "Enter a decimal number A: ";
	cin >> N; // вводим десятичное число

	MyVectorBool A(N);
	/*A.add_start(1);*/
	cout << A;

	int M;
	cout << "Enter a decimal number B: ";
	cin >> M; // вводим десятичное число

	MyVectorBool B(M);
	/*B.add_end(0);*/
	cout << B;

	//cout << "Enter index from 1 to " << B.GetSize() << " to delete: ";
	//int k;
	//cin >> k;
	//B.erase(k);
	//cout << B;

	//cout << "Enter index from 1 to " << B.GetSize() << " : ";
	//int i;
	//cin >> i;
	//cout << B[i] << endl;
	///*cout << "Enter index from 1 to " << B.GetSize() << " to change: "*/;
	///*B[i] = 1;*/
	//cout << B;

	MyVectorBool C;
	C = A + B;
	cout << C;

	return 0;
}