
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main() {
    // Input
    int n = 0;
    cin >> n;
    vector<int> temps(n);
    int64_t temps_sum = 0;
    for (int& t : temps) {
        cin >> t;
        temps_sum += t;
    }
    
    // Random test
    // for (int& t : temps) {
    //     t = rand();
    //     temps_sum += t;
    // }
    
    // Average counting
    int average = temps_sum / n;
    
    // Hot days counting
    vector<int> hot_days;
    for (int day = 0; day < n; day++) {
        if (temps[day] > average) {
            hot_days.push_back(day);
        }
    }
    
    // Output
    cout << hot_days.size() << endl;
    for (const int& day : hot_days) {
        cout << day << " ";
    }
    cout << endl;

    return 0;
}

/* MIPT and Yandex implementation (same):
При решении задачи необходимо было обратить внимание на два момента:

Сумма температур может достигать 10^14, поэтому должна храниться в типе int64_t.
Сумма температур может быть отрицательной, поэтому не должна делиться на беззнаковое 
число при вычислении среднего арифметического.

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> temperatures(n);
    int64_t sum = 0;
    for (int& temperature : temperatures) {
        cin >> temperature;
        sum += temperature;
    }

    int average = sum / n;

    vector<int> above_average_indices;
    for (int i = 0; i < n; ++i) {
        if (temperatures[i] > average) {
            above_average_indices.push_back(i);
        }
    }

    cout << above_average_indices.size() << endl;
    for (int i : above_average_indices) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
*/



/* Task:
Решите задачу «Средняя температура» в других ограничениях на входные данные.

Даны значения температуры, наблюдавшиеся в течение N подряд идущих дней. 
Найдите номера дней (в нумерации с нуля) со значением температуры выше 
среднего арифметического за все N дней.

Гарантируется, что среднее арифметическое значений температуры является 
целым числом.

Формат ввода
Вводится число N, затем N целых чисел — значения температуры в 0-й, 1-й, 
... (N−1)-й день. Гарантируется, что N не превышает миллиона (10^6), а 
значения температуры, измеряющиеся в миллионных долях градусов по Цельсию, 
лежат в диапазоне от −10^8 до 10^8. Проверять соблюдение этих ограничений 
не нужно: вы можете ориентироваться на них при выборе наиболее подходящих 
типов для переменных.

Формат вывода
Первое число K — количество дней, значение температуры в которых выше 
среднего арифметического. Затем K целых чисел — номера этих дней.

Пример
Ввод
5
5 4 1 -2 7

Вывод
3
0 1 4
*/