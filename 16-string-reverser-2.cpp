
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> Reversed(const vector<int>& v) {
    int n = v.size();  // для удобства сохраним размер вектора в переменную n
    vector<int> reversed = v;

    for (int i = 0; i < n / 2; ++i) {
        // элемент с индексом i симметричен элементу с индексом n - 1 - i
        // поменяем их местами с помощью временной переменной tmp
        int tmp = reversed[i];
        reversed[i] = reversed[n - 1 - i];
        reversed[n - 1 - i] = tmp;
    }
    return reversed;
}

int main() {
    
    vector<int> numbers = {1, 5, 3, 4, 2};
    

    for (int w : Reversed(numbers)) {
        cout << w << endl;
    }
    return 0;
}

/* MIPT and Yandex implementation - same as implemented above:
vector<int> Reversed(const vector<int>& input) {
    auto seq = input;
    for (int i = 0; i < seq.size() / 2; ++i) {
        auto tmp = seq[i];
        seq[i] = seq[seq.size() - 1 - i];
        seq[seq.size() - 1 - i] = tmp;
    }
    return seq;
}
*/



/* Task:
Реализуйте функцию vector<int> Reversed(const vector<int>& v), 
возвращающую копию вектора v, в которой числа переставлены в 
обратном порядке.

Пример
Вектор v	    Результат функции
1, 5, 3, 4, 2	2, 4, 3, 5, 1
*/
