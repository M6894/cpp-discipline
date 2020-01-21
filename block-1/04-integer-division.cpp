#include <iostream>
#include <string>

using namespace std;

int main() {
    int a, b;
    string pause;
    cin >> a >> b;
    if (b == 0) {
        cout << "Impossible" << endl;
    } else {
        cout << a / b << endl;
    }
    
    // cin >> pause;
    return 0;
}

/* MIPT and Yandex implementation:
int main() {
    int a, b;
    cin >> a >> b;

    if (b == 0) {
        cout << "Impossible" << endl;
    } else {
        cout << a / b << endl;
    }

    return 0;
}
*/


/* Task
Дано два целых числа A и B в диапазоне от 0 до 1 000 000 включительно. Напишите программу, 
которая вычисляет целую часть частного от деления A на B.

Если B = 0, выведите "Impossible".

Пример

stdin	stdout
10 2	5
3 5	    0
11 0	Impossible
*/