#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() {
    double n, a, b, x, y, overall;
    cin >> n >> a >> b >> x >> y;
    string pause;

    if (n > b) {
        cout << n - (n * y/100) << endl;
    } else if (n > a) {
        cout << n - (n * x/100) << endl;
    } else {
        cout << n << endl;
    }
    // cin >> pause;
    return 0;
}

/* MIPT and Yandex implementation:
int main() {
    double n, a, b, x, y;
    cin >> n >> a >> b >> x >> y;
    if (n > b) {
        n *= (1 - y / 100);
    } else if (n > a) {
        n *= (1 - x / 100);
    }
    cout << n;

    return 0;
}
*/



/* Task
Написать программу вычисления стоимости покупки 
с учётом скидки. Скидка в X процентов предоставляется, 
если сумма покупки больше A рублей, в Y процентов - 
если сумма больше B рублей.

В стандартном вводе содержится пять вещественных чисел, 
разделённых пробелом: N, A, B, X, Y (A < B) - где N - 
исходная стоимость товара. Выведите стоимость покупки с 
учётом скидки.

stdin	            stdout
100 110 120 5 10	100
115 110 120 5 10	109.25
150 110 120 5 12.5	131.25
*/