
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() {
    double a, b, x, y;
    cin >> a >> b;
        
    for (int i = 1000000; i > 0; i--) {
        x = a / i;
        y = b / i;
        
        if (a == b) {
            cout << a << endl;
            break;
        } else if ((round(x) == x || round(x) == x + 1) && (round(y) == y || round(y) == y + 1)) {
            cout << i << endl;
            break;
        }
    }
    // cin >> a;
    return 0;
}

/* Task
В stdin даны два натуральных числа. Выведите 
в stdout их наибольший общий делитель.

Пример

stdin	stdout
25 27	1
12 16	4
13 13	13
Подсказка

Если вам не удаётся сдать задачу, вы можете 
воспользоваться подсказкой (attached pdf). Но 
сначала попробуйте решить её сами :)
*/



/* MIPT and Yandex implementation:
#include <iostream>

using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
  
    // пока оба числа положительны, будем их уменьшать, не меняя их НОД
    while (a > 0 && b > 0) {
    
        // возьмём большее из чисел и заменим его остатком от деления на второе
        // действительно, если a и b делятся на x, то a - b и b делятся на x
        // тогда и a % b и b делятся на x, так что можно a заменить на a % b
        if (a > b) {
            a %= b;
        } else {
            b %= a;
        }    
    }

    // если одно из чисел оказалось равно нулю, значит, на последней итерации
    // большее число разделилось на меньшее
    cout << a + b;

    return 0;
}
*/