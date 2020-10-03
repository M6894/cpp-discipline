// 20
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

/* ineffective implementation
template <typename T>
void RemoveDuplicates(vector<T>& elements) {
    for (auto e = begin(elements); e != end(elements); e++) {
        // need to skip e itself at this moment.
        bool first = true;
        for (auto it = e; it != end(elements);) {
            auto duplicate = find(it, end(elements), *e);
            if (duplicate != elements.end() && !first) {
                elements.erase(duplicate);
            } 
            if (first) { // skipping e itself
                it++;
            } else {
                it = duplicate;
            }
            first = false;
        }
    }
}
*/

template <typename T>
void RemoveDuplicates(vector<T>& elements) {
    set<T> result(elements.begin(), elements.end());
    elements.assign(result.begin(), result.end());
}

int main() {
    vector<int> v1 = {6, 4, 7, 6, 4, 4, 0, 1};
    RemoveDuplicates(v1);
    for (int x : v1) {
        cout << x << " ";
    }
    cout << endl;
    
    vector<string> v2 = {"C", "C++", "C++", "C", "C++"};
    RemoveDuplicates(v2);
    for (const string& s : v2) {
        cout << s << " ";
    }
    cout << endl;

    vector<string> v3 = {"C"};
    RemoveDuplicates(v3);
    for (const string& s : v3) {
        cout << s << " ";
    }
    cout << endl;

    return 0;
}

/* MIPT and Yandex implementation:
#include <algorithm>
using namespace std;

template <typename DataType>
void RemoveDuplicates(vector<DataType>& elements) {
    sort(begin(elements), end(elements));
    elements.erase(
            unique(begin(elements), end(elements)),
            elements.end());
}
*/



/* Task:
Напишите шаблонную функцию RemoveDuplicates, принимающую по ссылке вектор elements объектов типа T 
и удаляющую из него все дубликаты элементов. Порядок оставшихся элементов может быть любым.

Гарантируется, что объекты типа T можно сравнивать с помощью операторов ==, !=, < и >.

template <typename T>
void RemoveDuplicates(vector<T>& elements);

Пример кода
int main() {
    vector<int> v1 = {6, 4, 7, 6, 4, 4, 0, 1};
    RemoveDuplicates(v1);
    for (int x : v1) {
        cout << x << " ";
    }
    cout << endl;
    
    vector<string> v2 = {"C", "C++", "C++", "C", "C++"};
    RemoveDuplicates(v2);
    for (const string& s : v2) {
        cout << s << " ";
    }
    cout << endl;
    return 0;
}

Вывод
6 4 7 0 1
C++ C

Порядок элементов может быть другим, например:
7 4 6 1 0
C C++

*/