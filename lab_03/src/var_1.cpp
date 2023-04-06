#include <iostream>
using namespace std;
template <typename T>

class Matrix //класс
{
private: // модификатор доступа

    int N; // кол-во столбцов
    int M; // кол-во строк
    T** matrix; // матрица

public: // модификатор доступа

    // базовый конструктор
    Matrix ()
    {
        N = 0;
        M = 0;
        matrix = nullptr;
    }

    // конструктор
    Matrix<T>(int valueN, int valueM)
    {
        N = valueN;
        M = valueM;
        
        // выделяем память
        matrix = (T**) new T * [M];
        for (int i = 0; i < M; i++)
            matrix[i] = (T*)new T[N];

        // заполняем нулями
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                matrix[i][j] = 0;
    }

    // конструктор копирования
    Matrix<T>(const Matrix<T>& A)
    {
        N = A.N;
        M = A.M;
        // выделяем память
        matrix = (T**) new T * [M];
        for (int i = 0; i < M; i++)
            matrix[i] = (T*) new T[N];

        // заполняем значениями
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                matrix[i][j] = A.matrix[i][j];
    }

    // геттер
    int GetM()
    {
        return M;
    }

    // геттер
    int GetN()
    {
        return N;
    }

    // оператор присваивания копированием
        Matrix<T>&operator = (Matrix<T> A)
    {
        if (N > 0)
        {
            // освободить память, выделенную ранее для объекта *this
            for (int i = 0; i < M; i++)
                delete[] matrix[i];
        }

        if (M > 0)
        {
            delete[] matrix;
        }

        // Копирование данных M <= _M
        M = A.M;
        N = A.N;

        // Выделить память для M опять
        matrix = (T**) new T * [M]; // количество строк, количество указателей
        for (int i = 0; i < M; i++)
            matrix[i] = (T*) new T[N];

        // заполнить значениями
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                matrix[i][j] = A.matrix[i][j];
        return *this;
    }


    // оператор ввода
    friend istream& operator >> (istream& in, Matrix<T>& A)
    {
        cout << "Enter a matrix:" << endl;
        for (int i = 0; i < A.M; i++)
        {
            for (int j = 0; j < A.N; j++)
            {
                in >> A.matrix[i][j];
            }
        }
        return in;
    }

    // оператор вывода
    friend ostream& operator << (ostream& out, Matrix<T>& A)
    {
        for (int i = 0; i < A.M; i++)
        {
            for (int j = 0; j < A.N; j++)
            {
                out << A.matrix[i][j] << " ";
            }
            out << endl;
        }
        return out;
    }
    
    // оператор +
    friend Matrix<T> operator + (Matrix<T>& A, Matrix<T>& B)
    {
        if (A.M == B.M && A.N == B.N)
        {
            Matrix<int> temp (A.N, A.M);
            for (int i = 0; i < A.M; i++)
            {
                for (int j = 0; j < A.N; j++)
                {
                    temp.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
                }
            }
            return temp;
        }
        else
        {
            Matrix<int> temp;
            return temp;
        }
    }

    // оператор +=
    Matrix<T>& operator += (const Matrix<T>& A)
    {
        if (A.M == M && A.N == N)
        {
            for (int i = 0; i < M; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    matrix[i][j] += A.matrix[i][j];
                }
            }
            return *this;
        }
        else
        {
            Matrix<T> temp;
            return temp;
        }
    }

    // оператор -
    friend Matrix<T> operator - (Matrix<T>& A, Matrix<T>& B)
    {
        if (A.M == B.M && A.N == B.N)
        {
            Matrix<int> temp(A.N, A.M);
            for (int i = 0; i < A.M; i++)
            {
                for (int j = 0; j < A.N; j++)
                {
                    temp.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
                }
            }
            return temp;   
        }
        else
        {
            Matrix<T> temp;
            return temp;
        }
    }

    // оператор *
    friend Matrix<T> operator * (Matrix<T>& A, Matrix<T>& B)
    {
        if (A.N == B.M) // (кол-во столбцов А = кол-во строк В)
        {
            Matrix<T> temp(B.N, A.M);
            for (int i = 0; i < A.M; i++) 
            {
                for (int j = 0; j < B.N; j++)
                {
                    for (int k = 0; k < A.N; k++)
                        temp.matrix[i][j] += (A.matrix[i][k] * B.matrix[k][j]);
                }
            }
            return temp;
        }
        else
        {
            Matrix<T> temp;
            return temp;
        }
    }

    // оператор *=
    Matrix<T>& operator *= (const Matrix<T>& A)
    {
        if (N != A.M) 
        {
            Matrix<T> temp;
            return temp;
        }
        else
        {
            Matrix<T> temp(M, A.N);

            for (int i = 0; i < M; i++)
            {
                for (int j = 0; j < A.N; j++)
                {
                    for (int k = 0; k < N; k++)
                    {
                        temp.matrix[i][j] += matrix[i][k] * A.matrix[k][j];
                    }
                }
            }
            *this = temp;
            return *this;
        }
    }

    // оператор ++
    Matrix<T> operator ++ (int)
    {
        for (int i = 0; i < M; i++)
        {
            matrix[i][N - 1]++;
        }
        return *this;
    }

    // определитель
    T Determinant()
    {
        if (N == M && N == 2)
        {
            T det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
            return det;
        }
        else if (N == M && N == 3)
        {
            T det = matrix[0][0] * matrix[1][1] * matrix[2][2] - matrix[0][0] * matrix[1][2]
                * matrix[2][1] - matrix[0][1] * matrix[1][0] * matrix[2][2] + matrix[0][1] * matrix[1][2]
                * matrix[2][0] - matrix[0][2] * matrix[1][1] * matrix[2][0] + matrix[0][2] * matrix[1][0]
                * matrix[2][1];
            return det;
        }
        else
        {
            cout << "Error" << endl;
            T det = 0;
            return det;
        }
    }

    void Rewrite(int valueN, int valueM)
    {
        if (N > 0)
        {
            // освободить память, выделенную ранее для объекта *this
            for (int i = 0; i < M; i++)
                delete[] matrix[i];
        }

        if (M > 0)
        {
            delete[] matrix;
        }

        N = valueN;
        M = valueM;

        // выделяем память
        matrix = (T**) new T * [M];
        for (int i = 0; i < M; i++)
            matrix[i] = (T*)new T[N];

        // заполняем нулями
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                matrix[i][j] = 0;
    }

    void EditWithDet(int ei, int ej, int edit)
    {
        cout << "Element: " << matrix[ei - 1][ej - 1];
        cout << " changed to: " << edit;
        matrix[ei - 1][ej - 1] = edit;
    }

    ~Matrix()
    {
        if (N > 0)
        {
            // освободить выделенную память для каждой строки
            for (int i = 0; i < M; i++)
                delete[] matrix[i];
        }

        if (M > 0)
            delete[] matrix;
    }
};

int main()
{
    int valueM;
    int valueN;
    string flag;

    // матрица А
    cout << "Enter M:" << endl;
    cin >> valueM;
    while (valueM < 0)
    {
        cout << "Incorrect value. Enter M:" << endl;
        cin >> valueM;
    }
    cout << "Enter N:" << endl;
    cin >> valueN;
    while (valueN < 0)
    {
        cout << "Incorrect value. Enter M:" << endl;
        cin >> valueN;
    }
    Matrix<int> A1(valueN, valueM);
    cin >> A1;
    cout << "- - - - - - - - - - ";

    // матрица В
    cout << endl;
    cout << "Enter M:" << endl;
    cin >> valueM;
    cout << "Enter N:" << endl;
    cin >> valueN;
    Matrix<int> B1(valueN, valueM);
    cin >> B1;
    cout << "- - - - - - - - - - " << endl;

    // матрица С
    Matrix<int> C1;

    cout << "Enter operation: ";
    cin >> flag;

    while (flag != "stop")
    {
        // ввод значений
        if (flag == "in")
        {
            // матрица А
            cout << "Enter M:" << endl;
            cin >> valueM;
            cout << "Enter N:" << endl;
            cin >> valueN;
            A1.Rewrite(valueN, valueM);
            cin >> A1;
            cout << "- - - - - - - - - - ";

            // матрица В
            cout << endl;
            cout << "Enter M:" << endl;
            cin >> valueM;
            cout << "Enter N:" << endl;
            cin >> valueN;
            B1.Rewrite(valueN, valueM);
            cin >> B1;

            cout << "- - - - - - - - - - " << endl;
            cout << "Enter operation: ";
            cin >> flag;
        }

        // вывод значений
        else if (flag == "out")
        {
            cout << "A: " << endl;
            cout << A1;
            cout << endl;
            cout << "B: " << endl;
            cout << B1;

            cout << "- - - - - - - - - - " << endl;
            cout << "Enter operation: ";
            cin >> flag;
        }

        // сложение
        else if (flag == "+")
        {
            cout << endl;
            C1 = A1 + B1;
            cout << "C = A + B: " << endl;
            cout << C1;

            cout << "- - - - - - - - - - " << endl;
            cout << "Enter operation: ";
            cin >> flag;
        }
        
        // вычитание
        else if (flag == "-")
        {
            cout << endl;
            C1 = A1 - B1;
            cout << "C = A - B: " << endl;
            cout << C1;

            cout << "- - - - - - - - - - " << endl;
            cout << "Enter operation: ";
            cin >> flag;
        }

        // определитель A
        else if (flag == "detA")
        {
            cout << A1.Determinant() << endl;

            cout << "- - - - - - - - - - " << endl;
            cout << "Enter operation: ";
            cin >> flag;
        }

        // определитель B
        else if (flag == "detB")
        {
            cout << B1.Determinant() << endl;

            cout << "- - - - - - - - - - " << endl;
            cout << "Enter operation: ";
            cin >> flag;
        }

        // +=
        else if (flag == "+=")
        {
            cout << endl;
            C1 += A1;
            cout << "C += A: " << endl;
            cout << C1;

            cout << "- - - - - - - - - - " << endl;
            cout << "Enter operation: ";
            cin >> flag;
        }

        // произведение
        else if (flag == "*")
        {
            cout << endl;
            C1 = A1 * B1;
            cout << "C = A * B: " << endl;
            cout << C1;

            cout << "- - - - - - - - - - " << endl;
            cout << "Enter operation: ";
            cin >> flag;
        }

        // произведение наоборот
        else if (flag == "**")
        {
            cout << endl;
            C1 = B1 * A1;
            cout << "C = A * B: " << endl;
            cout << C1;

            cout << "- - - - - - - - - - " << endl;
            cout << "Enter operation: ";
            cin >> flag;
        }

        // *=
        else if (flag == "*=")
        {
            cout << endl;
            C1 *= A1;
            cout << "C *= A: " << endl;
            cout << C1;

            cout << "- - - - - - - - - - " << endl;
            cout << "Enter operation: ";
            cin >> flag;
        }

        // замена в A на Det
        else if (flag == "editA")
        {
            int ei;
            int ej;
            double edit = A1.Determinant();
            cout << "Enter 'i' from " << 1 << " to " << A1.GetM() << " : ";
            cin >> ei;
            while (ei < 1 || ei > A1.GetM())
            {
                cout << "Incorrect value. Enter i:" << endl;
                cin >> ei;
            }
            cout << "Enter 'j' from " << 1 << " to " << A1.GetN() << " : ";
            cin >> ej;
            while (ej < 1 || ej > A1.GetN())
            {
                cout << "Incorrect value. Enter i:" << endl;
                cin >> ej;
            }
            A1.EditWithDet(ei, ej, edit);
            cout << endl;

            cout << "- - - - - - - - - - " << endl;
            cout << "Enter operation: ";
            cin >> flag;
        }

        // замена в B на Det
        else if (flag == "editB")
        {
            int ei;
            int ej;
            double edit = B1.Determinant();
            cout << "Enter 'i' from " << 1 << " to " << B1.GetM() << " : ";
            cin >> ei;
            while (ei < 1 || ei > B1.GetM())
            {
                cout << "Incorrect value. Enter i:" << endl;
                cin >> ei;
            }
            cout << "Enter 'j' from " << 1 << " to " << B1.GetN() << " : ";
            cin >> ej;
            while (ej < 1 || ej > B1.GetN())
            {
                cout << "Incorrect value. Enter i:" << endl;
                cin >> ej;
            }
            B1.EditWithDet(ei, ej, edit);
            cout << endl;

            cout << "- - - - - - - - - - " << endl;
            cout << "Enter operation: ";
            cin >> flag;
        }

        // ++
        else if (flag == "++")
        {
            cout << endl;
            cout << "A++:" << endl;
            int i = 0;
            while (i < 2)
            {
                cout << A1++;
                i++;
                cout << endl;
            }

            cout << "- - - - - - - - - - " << endl;
            cout << "Enter operation: ";
            cin >> flag;
        }
        
        // ошибочный ввод
        else
        {
            cout << "Operation is not correct. Enter operation: ";
            cin >> flag;
        }
    }

	return 0;
}