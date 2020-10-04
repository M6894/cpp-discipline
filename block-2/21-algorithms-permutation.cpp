// 21
#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

ostream& operator<<(ostream& output, const vector<uint16_t>& vec) {
    for (auto& v : vec) {
        cout << v << ' ';
    }
    return output;
}

int main() {
    uint16_t num = 0;
    cin >> num;
    vector<uint16_t> range(num);
    iota(range.rbegin(), range.rend(), 1);
    do {
        cout << range << endl;
    } while(prev_permutation(range.begin(), range.end()));

    return 0;
}

/* MIPT and Yandex implementation:
Основная идея — использовать алгоритм prev_permutation для итеративного построения предыдущей 
перестановки по заданной. Его удобно обернуть в цикл do while.

Кроме того, для инициализации первой перестановки используем алгоритмы iota (заполняющий диапазон 
числами от 1 до n) и reverse.

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    int range_length;
    cin >> range_length;
    vector<int> permutation(range_length);
    
    // iota    -> http://ru.cppreference.com/w/cpp/algorithm/iota
    // Заполняет диапазон последовательно возрастающими значениями
    // Обратные итераторы позволяют заполнить его, двигаясь от конца к началу
    iota(permutation.rbegin(), permutation.rend(), 1); 
    
    // prev_permutation ->
    //         http://ru.cppreference.com/w/cpp/algorithm/prev_permutation
    // Преобразует диапазон в предыдущую (лексикографически) перестановку,
    // если она существует, и возвращает true,
    // иначе (если не существует) - в последнюю (наибольшую) и возвращает false
    do {
        for (int num : permutation) {
            cout << num << ' ';
        }
        cout << endl;
    } while (prev_permutation(permutation.begin(), permutation.end()));

    return 0;
}
*/



/* Task:
Дано целое положительное число N, не превышающее 9. Выведите все перестановки чисел от 1 до N в 
обратном лексикографическом порядке (см. пример).

Пример
Ввод
3

Вывод
3 2 1
3 1 2
2 3 1
2 1 3
1 3 2
1 2 3

Подсказка
Библиотека <algorithm> содержит готовые функции, позволяющие решить эту задачу.
*/