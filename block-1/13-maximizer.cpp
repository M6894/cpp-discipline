
#include <iostream>
#include <string>

using namespace std;

void UpdateIfGreater(int first, int& second) {
    if (first > second) {
        second = first;
    }
}

int main() {
    int a = 4;
    int b = 2;

    UpdateIfGreater(a, b);

    cout << b << endl;
    cin >> a; // pause
    return 0;
}

/* MIPT and Yandex implementation:
void UpdateIfGreater(int a, int& b) {
    if (a > b) {
        b = a;
    }
}
*/



/* Task:
Напишите функцию UpdateIfGreater, которая принимает 
два целочисленных аргумента: first и second. Если first 
оказался больше second, Ваша функция должна записывать 
в second значение параметра first. При этом изменение 
параметра second должно быть видно на вызывающей стороне.

Пример
int a = 4;
int b = 2;
UpdateIfGreater(a, b);
// b должно стать равно 4
*/