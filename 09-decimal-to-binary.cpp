
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main () {
    int a = 0;
    int rem; // остаток от целочисленного деления.
    vector<int> b; // binary

    cin >> a;
    rem = a;

    while (a > 0) {
        rem = a % 2;
        a /= 2;
        b.push_back(rem);
    }

    for (int i = b.size()-1; i >= 0; i--) {
        cout << b[i];
    }

    cin >> a; // pause
    return 0;
}

/*
На вход дано целое положительное число N. 
Выведите его в двоичной системе счисления 
без ведущих нулей.

Пример

stdin	stdout
5	    101
32	    100000
1	    1

Подсказка
число N можно считывать в переменную типа int
в этой задаче вам может пригодиться контейнер vector; 
напоминаем, что добавление значения x в конец вектора 
v делается так: v.push_back(x);
*/



/* Task 2 (updated)
На вход дано целое положительное число N. Выведите его в двоичной системе 
счисления без ведущих нулей.

Пример

stdin	stdout
5	    101
32	    100000
1	    1
Подсказка
число N можно считывать в переменную типа int;
алгоритм перевода из десятичной системы счисления в двоичную, может быть найден, 
например, здесь: 
https://www.yaklass.ru/p/informatika/10-klass/informatciia-i-informatcionnye-protcessy-11955/predstavlenie-chislovoi-informatcii-v-kompiutere-11901/re-62e8903e-ba93-478a-85b5-ae45af40c658
в этой задаче вам может пригодиться контейнер vector; напоминаем, что добавление 
значения x в конец вектора v делается так: v.push_back(x);
*/



/* MIPT and Yandex implementation:
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    vector<int> bits;

    cin >> n;
    while (n > 0) {
        bits.push_back(n % 2);
        n /= 2;
    }

    for (int i = bits.size() - 1; i >= 0; --i) {
        cout << bits[i];
    }
    return 0;
}
*/