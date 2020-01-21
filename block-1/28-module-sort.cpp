
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

bool CheckModule(int a, int b) {
    if (a < 0) {
        a *= -1;
    }
    if (b < 0) {
        b*= -1;
    }
    return a < b;
}

void PrintVector(const vector<int>& range) {
    for (const auto& i : range) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    int q = 0;
    cin >> q;
    vector<int> range;
    int input = 0;
    for (int i = 0; i < q; i++) {
        cin >> input;
        range.push_back(input);
    }

    sort(begin(range), end(range), CheckModule);

    PrintVector(range);
    return 0;
}

/* MIPT and Yandex implementation - модуль - abs(x) из cmath. Ввод значений в вектор значений через range based for:
Чтобы отсортировать вектор целых чисел по модулю, третьим аргументом в функцию sort передадим лямбда-функцию, 
сравнивающие модули переданных чисел.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
  
    // считываем вектор
    int n;
    cin >> n;
    vector<int> v(n);
    for (int& x : v) {
        cin >> x;
    }

    // сортируем
    sort(begin(v), end(v),
        // функция, сравнивающая abs(l) и abs(r) — модули чисел l и r
        [](int l, int r) {
            return abs(l) < abs(r);
        }
    );

    // выводим отсорированный вектор
    for (int x : v) {
        cout << x << " ";
    }

    return 0;
}
*/



/* Task:
Условие
В стандартном потоке дана одна строка, состоящая из N + 1 целых чисел. Первым числом идёт само число N. Далее следуют ещё N чисел, обозначим их за массив A. Между собой числа разделены пробелом.

Отсортируйте массив А по модулю и выведите его в стандартный поток.

Ограничения
0 <= N <= 1000
-1000000 <= A[i] <= 1000000
Примеры
stdin	        stdout
2 -4 3	        3 -4
3 1 -3 2	    1 2 -3

Подсказка
функция sort дополнительно принимает третий аргумент. Изучите его подробнее по ссылке.
http://www.cplusplus.com/reference/algorithm/sort/?kw=sort
*/