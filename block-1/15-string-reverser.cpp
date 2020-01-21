
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void Reverse(vector<int>& v) {
    vector<int> reversed;
    for (int w = v.size()-1; w >=0; w--) {
        reversed.push_back(v[w]);
    }
    v = reversed;
}

int main() {
    
    vector<int> numbers = {1, 5, 3, 4, 2};
    Reverse(numbers);

    for (int w : numbers) {
        cout << w << endl;
    }
    return 0;
}

/* MIPT and Yandex implementation - preferred implementation:
В этой задаче достаточно было перебрать все элементы первой половины вектора и поменять их местами с симметричными им.

void Reverse(vector<int>& v) {
  int n = v.size();  // для удобства сохраним размер вектора в переменную n
  for (int i = 0; i < n / 2; ++i) {
    // элемент с индексом i симметричен элементу с индексом n - 1 - i
    // поменяем их местами с помощью временной переменной tmp
    int tmp = v[i];
    v[i] = v[n - 1 - i];
    v[n - 1 - i] = tmp;
  }
}
*/



/* Task:
Реализуйте функцию void Reverse(vector<int>& v), которая 
переставляет элементы вектора в обратном порядке.

Пример
vector<int> numbers = {1, 5, 3, 4, 2};
Reverse(numbers);
// numbers должен оказаться равен {2, 4, 3, 5, 1}
*/
