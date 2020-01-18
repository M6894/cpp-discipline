
#include <iostream>

using namespace std;

int Factorial(int x) {
    
    int result = 1;
    // if не нужен, т.к. в for i сравнивается с 1.
    if (x >= 0) { 
        for (int i = 1; i <= x; i++) {
            result *= i;
        }
    }
    return result;
}

int main() {
    int input = 0;
    cin >> input;
    cout << Factorial(input) << endl;

    // cin >> input;
    return 0;
}

/* MIPT and Yandex implementation - (preferred implementation)

Самый простой способ решить задачу — написать цикл, вычисляющий 
произведение чисел от 2 до x, предварительно сравнив x с единицей:

int Factorial(int x) {
    int result = 1;
    for (int i = 2; i <= x; ++i) {
        result *= i;
    }
    return result;
}

Существует способ написать более лаконичный код по этой задаче — заметить, 
что для положительных x Factorial(x) = x * Factorial(x - 1), и использовать 
рекурсию, то есть вызывать из функции Factorial себя же, но с на единицу 
меньшим аргументом:

int Factorial(int x) {
    if (x <= 1) {
        return 1;
    } else {
        return x * Factorial(x - 1);  // вычисляем факториал от x-1 и умножаем на x
    }
}

TODO:
Запустить второй вариант в Дебаггере (done).
*/



/* Task
Напишите функцию, которая

называется Factorial
возвращает int
принимает int и возвращает факториал своего аргумента. 
Гарантируется, что аргумент функции по модулю не 
превышает 10. Для отрицательных аргументов функция 
должна возвращать 1.
Аргумент функции	Результат
1	                    1
-2	                    1
4	                    24
*/