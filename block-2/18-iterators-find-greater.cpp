// 18
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
    auto b = find_if(
        begin(elements), end(elements), 
        [border](const auto& el) {
            return el > border;
        }
    );
    return vector<T>(b, elements.end());
}

int main() {
    for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
        cout << x << " ";
    }
    cout << endl;
    
    string to_find = "Python";
    cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
    return 0;
}

/* MIPT and Yandex implementation:
Ключевой момент решения — поиск первого элемента, большего border. 
Позже мы научимся делать это оптимально, а пока достаточно использовать 
для этого обычный цикл while.

Как только найден итератор на первый элемент, больший border, достаточно 
создать вектор из полуинтервала, начинающегося в этом итераторе и 
заканчивающегося в конце множества — это и будут все элементы, большие 
border, в возрастающем порядке.

#include <iostream>
#include <set>
#include <vector>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
    // Начнём итерироваться по множеству
    auto it = begin(elements);
    // Цель — найти первый элемент, больший border
    // Если итератор не достиг конца и указывает не туда, двигаем
    while (it != end(elements) && *it <= border) {
  	    ++it;
    }
    // Возвращаем вектор, созданный из элементов множества, начиная с it
    return {it, end(elements)};
}
*/



/* Task:
Напишите шаблонную функцию FindGreaterElements, принимающую множество 
elements объектов типа T и ещё один объект border типа T и возвращающую 
вектор из всех элементов множества, бо́льших border, в возрастающем порядке.

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border);

Пример кода
int main() {
    for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
        cout << x << " ";
    }
    cout << endl;
    
    string to_find = "Python";
    cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
    return 0;
}

Вывод
7 8
0

*/
