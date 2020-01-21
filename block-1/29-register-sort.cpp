
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>


using namespace std;

void PrintVector(const vector<string>& range) {
    for (const auto& i : range) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    int q = 0;
    cin >> q;
    vector<string> range(q);
    for (string& word : range) {
        cin >> word;
    }

    sort(begin(range), end(range), [](const string& a, const string& b) {
        string x, y;
        for (const char& letter : a) {
            x += tolower(letter);
        }
        for (const char& letter2 : b) {
            y += tolower(letter2);
        }
        return x < y;
        }
    );

    PrintVector(range);
    return 0;
}

/* MIPT and Yandex implementation:
Наиболее нетривиальная часть решения этой задачи — реализовать функцию, сравнивающую две строки без учёта регистра.

Это можно сделать, например, с помощью функции lexicographical_compare, сравнивающей два диапазона элементов 
(в нашем случае — два набора символов) с помощью данного компаратора. В компараторе для функции 
lexicographical_compare мы используем функцию tolower, возвращающую символ, приведённый к нижнему регистру.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // считываем вектор строк
    int n;
    cin >> n;
    vector<string> v(n);
    for (string& s : v) {
        cin >> s;
    }
  
    // сортируем
    sort(begin(v), end(v),
        // компаратор для сортировки — лямбда-функция, сравнивающая строки без учёта регистра
        [](const string& l, const string& r) {
            // сравниваем лексикографически...
            return lexicographical_compare(
                // ... все символы строки l ...
                begin(l), end(l),
                // ... со всеми символами строки r ...
                begin(r), end(r),
                // ..., используя в качестве компаратора сравнение отдельных символов без учёта регистра
                [](char cl, char cr) { return tolower(cl) < tolower(cr); }
            );
        }
    );
  
    // выводим отсортированный вектор
    for (const string& s : v) {
        cout << s << ' ';
    }
  
    return 0;
}
*/



/* Task:
Условие
В стандартном потоке дана одна строка, состоящая из числа N и следующих за ним N строк S. Между собой число и строки разделены пробелом.

Отсортируйте строки S в лексикографическом порядке по возрастанию, игнорируя регистр букв, и выведите их в стандартный поток вывода.

Ограничения
0 <= N <= 1000
1 <= |S| <= 15
Каждая строка S[i] может состоять из следующих символов: [0-9,a-z,A-Z]
Примеры
stdin	      stdout
2 q A	      A q
3 a C b	    a b C
*/