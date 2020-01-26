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
    Matrix(int num_rows, int num_cols) {
        Reset(num_rows, num_cols);
    }
    void Reset(int num_rows, int num_cols) {
        if (num_rows < 0 || num_cols < 0) {
            throw out_of_range("Negative");
        }
        if (num_rows == 0 || num_cols == 0) {
            num_rows = 0;           
        }
        vector<vector<int>> temp_col(num_rows); // Создаем список строк
        for (auto& row : temp_col) {
            vector<int> temp_row(num_cols);
            row = temp_row; // Создаем столбцы
        }
        data = temp_col;
    }
    int At(const int& row, const int& col) const {
        if (row > static_cast<int>(data.size()) -1 || col > static_cast<int>(data[0].size()) -1 || row < 0 || col < 0) {
            throw out_of_range("Out of range");
        } else {
            return data[row][col];
        }
    }
    int& At(const int& row, const int& col) {
        if (row > static_cast<int>(data.size()) -1 || col > static_cast<int>(data[0].size()) -1 || row < 0 || col < 0) {
            throw out_of_range("Out of range");
        } else {
            return data[row][col];
        }
    }
    int GetNumRows() const {
        return static_cast<int>(data.size());
    }
    int GetNumColumns() const {
        if (static_cast<int>(data.size()) > 0) {
            return static_cast<int>(data[0].size());
        } else {
            return 0;
        }
    }
public: // TODO: Make it private
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
    if (lhs.GetNumRows() != rhs.GetNumRows() || lhs.GetNumColumns() != rhs.GetNumColumns()) {
        throw invalid_argument("Different matrix sizes: " + to_string(lhs.GetNumRows()) + " " + to_string(lhs.GetNumColumns()) 
                                + " + " + to_string(rhs.GetNumRows()) + " " + to_string(rhs.GetNumColumns()));
    }
    int rows_index = lhs.GetNumRows() -1;
    int cols_index = lhs.GetNumColumns() -1;
    Matrix result (lhs.GetNumRows(), lhs.GetNumColumns());
    for (int row_index = 0; row_index <= rows_index; row_index++) {
        for (int num_index = 0; num_index <= cols_index; num_index++) {
            result.At(row_index, num_index) = lhs.At(row_index, num_index) + rhs.At(row_index, num_index);                
        }
    }
    return result;
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
    // stringstream s("2 2 3 3 4 4 2 2 0 0 0 0");
    // s >> one >> two;

    // Random test
    uint8_t rows = rand();
    uint8_t cols = rand();
    // if (rows < 0) {
    //     rows *= -1;
    // }
    // if (cols < 0) {
    //     cols *= -1;
    // }
    // if (rows == 0) {
    //     cols = 0;
    // }
    Matrix lhs(rows, cols);
    Matrix rhs(rows, cols);
    for (auto& row : lhs.data) {
        for (auto& num : row) {
            uint16_t new_num = rand();
            num = new_num;
        }
    }
    for (auto& row : rhs.data) {
        for (auto& num : row) {
            uint16_t new_num = rand();
            num = new_num;
        }
    }
    cout << lhs + rhs;

    // Input testing
    // string command;
    // while (getline(cin, command)) {
    //     stringstream s(command);
    //     s >> one >> two;
    //     cout << one + two << endl;
    // }

    // if (one == two) {
    //     cout << "Same matrix" << endl;
    // }

    // cout << three + four << endl;
    // cout << three + one << endl;
    
    // cout << "Old size: " << one.data.size() << one.data[0].size() << endl;
    // three = one + two;
    // cout << "Three size: " << three.data.size() << three.data[0].size() << endl;

    // cout << one.At(1, 1) << endl;
    // cout << three.At(2, 3) << endl;
    // cout << three.At(0, 4) << endl;

    return 0;
}

/* MIPT and Yandex implementation:
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <sstream>

using namespace std;

class Matrix {
private:
    int num_rows_;
    int num_columns_;

    vector<vector<int>> elements_;

public:
    Matrix() {
        num_rows_ = 0;
        num_columns_ = 0;
    }

    Matrix(int num_rows, int num_columns) {
        Reset(num_rows, num_columns);
    }

    void Reset(int num_rows, int num_columns) {
        if (num_rows < 0) {
            throw out_of_range("num_rows must be >= 0");
        }
        if (num_columns < 0) {
            throw out_of_range("num_columns must be >= 0");
        }
        if (num_rows == 0 || num_columns == 0) {
            num_rows = num_columns = 0;
        }

        num_rows_ = num_rows;
        num_columns_ = num_columns;
        elements_.assign(num_rows, vector<int>(num_columns));
    }

    int& At(int row, int column) {
        return elements_.at(row).at(column);
    }

    int At(int row, int column) const {
        return elements_.at(row).at(column);
    }

    int GetNumRows() const {
        return num_rows_;
    }

    int GetNumColumns() const {
        return num_columns_;
    }
};

bool operator==(const Matrix& one, const Matrix& two) {
    if (one.GetNumRows() != two.GetNumRows()) {
        return false;
    }

    if (one.GetNumColumns() != two.GetNumColumns()) {
        return false;
    }

    for (int row = 0; row < one.GetNumRows(); ++row) {
        for (int column = 0; column < one.GetNumColumns(); ++column) {
            if (one.At(row, column) != two.At(row, column)) {
                return false;
            }
        }
    }

    return true;
}

Matrix operator+(const Matrix& one, const Matrix& two) {
    if (one.GetNumRows() != two.GetNumRows()) {
        throw invalid_argument("Mismatched number of rows");
    }

    if (one.GetNumColumns() != two.GetNumColumns()) {
        throw invalid_argument("Mismatched number of columns");
    }

    Matrix result(one.GetNumRows(), one.GetNumColumns());
    for (int row = 0; row < result.GetNumRows(); ++row) {
        for (int column = 0; column < result.GetNumColumns(); ++column) {
            result.At(row, column) = one.At(row, column) + two.At(row, column);
        }
    }

    return result;
}

istream& operator>>(istream& in, Matrix& matrix) {
    int num_rows, num_columns;
    in >> num_rows >> num_columns;

    matrix.Reset(num_rows, num_columns);
    for (int row = 0; row < num_rows; ++row) {
        for (int column = 0; column < num_columns; ++column) {
            in >> matrix.At(row, column);
        }
    }

    return in;
}

ostream& operator<<(ostream& out, const Matrix& matrix) {
    out << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
    for (int row = 0; row < matrix.GetNumRows(); ++row) {
        for (int column = 0; column < matrix.GetNumColumns(); ++column) {
            if (column > 0) {
                out << " ";
            }
            out << matrix.At(row, column);
        }
        out << endl;
    }

    return out;
}

int main() {
    Matrix one;
    Matrix two;

    // cin >> one >> two;
    // cout << one + two << endl;

    string command;
    while (getline(cin, command)) {
        stringstream s(command);
        s >> one >> two;
        cout << one + two << endl;
    }
    
    return 0;
}
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