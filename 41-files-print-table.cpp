
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

void PrintTable(const string& source_path) {
    ifstream input(source_path);
    if (input.good()) {
        int lines = 0;
        int coloumns = 0;
        input >> lines >> coloumns;
        for (int l = lines; l > 0; l--) {
            for (int c = coloumns; c > 0; c--) {
                int number = 0;
                input >> number;
                cout << setw(10) << number;
                if (c != 1) {
                    cout << " ";
                }
                input.ignore(1);
            }
            if (l != 0) {
                cout << endl;
            }
        }
    } else {
        cout << "File opening error." << endl;
    }
}

int main() {
    const string source_path = "input.txt";
    PrintTable(source_path); 
    return 0;
}

/* MIPT and Yandex implementation: аналогично, только счетчики в обратном направлении.
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    ifstream input("input.txt");
  
    int n, m;
    input >> n >> m;

    // перебираем строки
    for (int i = 0; i < n; ++i) {
        // перебираем столбцы
        for (int j = 0; j < m; ++j) {
            // считываем очередное число
            int x;
            input >> x;
            // пропускаем следующий символ
            input.ignore(1);
            // выводим число в поле ширины 10
            cout << setw(10) << x;
            // выводим пробел, если только этот столбец не последний
            if (j != m - 1) {
                cout << " ";
            }
        }
        // выводим перевод строки, если только эта строка не последняя
        if (i != n - 1) {
            cout << endl;
        }
    }  

    return 0;
}
*/



/*
В первой строке файла input.txt записаны два числа N и M. Далее в файле находится 
таблица из N строк и M столбцов, представленная в формате CSV (comma-separated values). 
Такой формат часто используется для текстового представления таблиц с данными: в файле 
несколько строк, значения из разных ячеек внутри строки отделены друг от друга запятыми. 
Ваша задача — вывести данные на экран в виде таблицы. Формат таблицы:

1) размер ячейки равен 10,

2) соседние ячейки отделены друг от друга пробелом,

3) последняя ячейка в строке НЕ оканчивается пробелом,

4) последняя строка НЕ оканчивается символом перевода строки. Гарантируется, что в 
таблице будет ровно N строк и M столбцов, значение каждой из ячеек — целое число. 

Пример ввода
2 3
1,2,3
4,5,6

Пример вывода
         1          2          3
         4          5          6

*/