#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <sstream>

using namespace std;

// Реализуйте здесь
// * класс Matrix
// * оператор ввода для класса Matrix из потока istream
// * оператор вывода класса Matrix в поток ostream
// * оператор проверки на равенство двух объектов класса Matrix
// * оператор сложения двух объектов класса Matrix

class Matrix {
public:
    Matrix() {
        data.clear();
    }
    Matrix(const int& num_rows, const int& num_cols) {
        if (num_rows < 0 || num_cols < 0) {
            throw out_of_range("Negative");
        } else {
            vector<vector<int>> temp_col(num_rows); // Создаем список строк
            for (auto& row : temp_col) {
                vector<int> temp_row(num_cols);
                row = temp_row; // Создаем столбцы
            }
            data = temp_col;
        }
    }
    void Reset(const int& num_rows, const int& num_cols) {
        // Matrix temp(num_rows, num_cols);
        // data = temp.data;
        if (num_rows < 0 || num_cols < 0) {
            throw out_of_range("Negative");
        } else {
            vector<vector<int>> temp_col(num_rows); // Создаем список строк
            for (auto& row : temp_col) {
                vector<int> temp_row(num_cols);
                row = temp_row; // Создаем столбцы
            }
            data = temp_col;
        }
    }
    int At(const int& row, const int& col) const {
        // int rows = data.size() -1; 
        // int cols = data[0].size() -1;
        if (row > static_cast<int>(data.size()) -1 || col > static_cast<int>(data[0].size()) -1 || row < 0 || col < 0) {
            throw out_of_range("Out of range");
        } else {
            return data[row][col];
        }
    }
    int& At(const int& row, const int& col) {
        // int rows = data.size() -1; 
        // int cols = data[0].size() -1;
        if (row > static_cast<int>(data.size()) -1 || col > static_cast<int>(data[0].size()) -1 || row < 0 || col < 0) {
            throw out_of_range("Out of range");
        } else {
            return data[row][col];
        }
    }
    int GetNumRows() const {
        return data.size();
    }
    int GetNumColumns() const {
        return data[0].size();
    }
public:
    vector<vector<int>> data = {{}};
};

istream& operator>>(istream& input, Matrix& matrix) {
    int num_rows, num_cols;
    input >> num_rows >> num_cols;
    Matrix temp_matrix(num_rows, num_cols);
    for (auto& row : temp_matrix.data) {
        for (auto& num : row) {
            input >> num;
        }
    }
    matrix = temp_matrix;
    return input;
}

ostream& operator<<(ostream& output, const Matrix& matrix) {
    output << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
    for (const auto& row : matrix.data) {
        for (const int& num : row) {
            output << num << " ";
        }
        output << endl;
    }
    return output;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
    Matrix result;
    // if (lhs.data.empty() || rhs.data.empty()) {
    //     if (lhs.data.empty() && rhs.data.empty()) {
    //         return result;
    //     } else {
    //         throw invalid_argument("Different matrix sizes");
    //     }
    if (lhs.GetNumRows() != rhs.GetNumRows() || lhs.GetNumColumns() != rhs.GetNumColumns()) {
        throw invalid_argument("Different matrix sizes");
    } else {
        int rows_index = lhs.GetNumRows() -1;
        int cols_index = lhs.GetNumColumns() -1;
        Matrix result (lhs.GetNumRows(), lhs.GetNumColumns());
        for (int row_index = 0; row_index <= rows_index; row_index++) {
            for (int num_index = 0; num_index <= cols_index; num_index++) {
                result.data[row_index][num_index] = lhs.At(row_index, num_index) + rhs.At(row_index, num_index);
            }
        }
        return result;
    }
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.data == rhs.data) {
        return true;
    } else {
        return false;
    }
}

int main() {
    Matrix one;
    Matrix two;
    Matrix three(2, 2);
    Matrix four;

    // stringstream s("2 2 1 1 2 2 2 2 1 1 2 2");
    stringstream s("0 0 0 0");
    s >> one >> two;

    // cin >> one >> two;
    // cout << one + two << endl;
    if (one == two) {
        cout << "Ok!" << endl;
    }
    // cout << three + four << endl;
    // cout << three + one << endl;
    cout << "Old size: " << one.data.size() << one.data[0].size() << endl;
    // three.Reset(3, 3);
    three = one + two;
    cout << "Three size: " << three.data.size() << three.data[0].size() << endl;
    
    // cout << one.At(1, 1) << endl;
    // cout << three.At(2, 3) << endl;
    // cout << three.At(0, 4) << endl;

    return 0;
}

/* MIPT and Yandex implementation:

*/



/* Task:
Предисловие
Если вы не уверены, стоит ли вам сначала пройти наш первый курс, или у вас достаточно знаний, 
чтобы начать с «Жёлтого пояса», попробуйте решить эту задачу. Если вы не понимаете её условие 
или не можете быстро решить, скорее всего, вам надо сначала пройти «Белый пояс»

Условие
В этой задаче вам надо разработать класс Matrix для представления целочисленной матрицы. Более 
подробно класс Matrix должен иметь:

конструктор по умолчанию, который создаёт матрицу с нулём строк и нулём столбцов
конструктор от двух целочисленных параметров: num_rows и num_cols, — которые задают количество 
строк и столбцов матрицы соответственно
метод Reset, принимающий два целочисленных параметра, которые задают новое количество строк и 
столбцов матрицы соответственно; метод Reset меняет размеры матрицы на заданные и обнуляет все 
её элементы
константный метод At, который принимает номер строки и номер столбца (именно в этом порядке; 
нумерация строк и столбцов начинается с нуля) и возвращает значение в соответствущей ячейке 
матрицы
неконстантный метод At с такими же параметрами, но возвращающий ссылку на значение в соответствущей 
ячейке матрицы
константные методы GetNumRows и GetNumColumns, которые возвращают количество строк и столбцов 
матрицы соответственно
Если количество строк или количество столбцов, переданное в конструктор класса Matrix или метод 
Reset, оказалось отрицательным, то должно быть выброшено стандартное исключение out_of_range.

Это же исключение должен бросать метод At, если переданная в него ячейка выходит за границы матрицы.

Кроме того для класса Matrix должны быть определены следующие операторы:

оператор ввода из потока istream; формат ввода простой — сначала задаётся количество строк и 
столбцов (именно в этом порядке), а затем все элементы матрицы: сначала элемент первой строки 
и первого столбца, затем элемент первой строки и второго столбца и так далее
оператор вывода в поток ostream; он должен выводить матрицу в том же формате, в каком её читает 
оператор ввода, — в первой строке количество строк и столбцов, во второй — элементы первой строки, 
в третьей — элементы второй строки и т.д.
оператор проверки на равенство (==): он должен возвращать true, если сравниваемые матрицы имеют 
одинаковый размер и все их соответствующие элементы равны между собой, в противном случае он должен 
возвращать false.

оператор сложения: он должен принимать две матрицы и возвращать новую матрицу, которая является их 
суммой; если переданные матрицы имеют разные размеры этот оператор должен выбрасывать стандартное 
исключение invalid_argument.
Вам дана заготовка решения, а также пример ввода и вывода. Когда вы реализуете класс Matrix, вы 
можете использовать этот пример, чтобы убедиться, что ваш код работает правильно.

Важно! Пример не проверяет выполнение всех требований, приведённых в условии.

Автор задачи — Дмитрий Минченко

Файл с заготовкой решения задачи
matrix_sum.cpp
Пример ввода
3 5
6 4 -1 9 8
12 1 2 9 -5
-4 0 12 8 6

3 5
5 1 0 -8 23
14 5 -6 6 9
8 0 5 4 1

Пример вывода
3 5
11 5 -1 1 31
26 6 -4 15 4
4 0 17 12 7

Примечание
Матрицы с нулём строк или нулём столбцов считаются пустыми. Любые две пустые матрицы равны. 
Сумма двух пустых матриц также является пустой матрицей.
*/