#include <iostream>

using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    for (int i = a; i <= b; ++i) {
        if (i % 2 == 0) {
            cout << i << ' ';
        }
    }
    return 0;
}

/* MIPT and Yandex implementation:
#include <iostream>

using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    for (int i = a; i <= b; ++i) {
        if (i % 2 == 0) {
            cout << i << ' ';
        }
    }
    return 0;
}
*/



/* Task
Дано два целых числа A и B (A <= B, A >= 1, B <= 30000). Выведите через пробел 
все чётные числа от A до B (включительно).

Для проверки целого числа x на чётность используется операция взятия остатка от 
деления на 2, которая в C++ оформляется с помощью символа "%". Например,

int x;
cin >> x;
if (x % 2 == 0) {
    // x - чётное число
} else {
    // x - нечётное число
}

Пример

stdin	stdout
1 10	2 4 6 8 10
2 3	2
9 11	10
*/