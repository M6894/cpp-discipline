
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

set<string> BuildMapValuesSet(const map<int, string>& m) {
    set<string> result;
    for (const auto& item : m) {
        result.insert(item.second);
    }

    return result;
}

/* 
int main() {
    set<string> values = BuildMapValuesSet({
    {1, "odd"},
    {2, "even"},
    {3, "odd"},
    {4, "even"},
    {5, "odd"}
});

    for (const string& value : values) {
        cout << value << endl;
    }
    return 0;
}
*/



/* MIPT and Yandex implementation (same):
set<string> BuildMapValuesSet(const map<int, string>& m) {
  set<string> values;
  for (const auto& item : m) {
    values.insert(item.second);
  }
  return values;
}
*/



/* Task:
Напишите функцию BuildMapValuesSet, принимающую на вход словарь map<int, string> 
и возвращающую множество значений этого словаря:
set<string> BuildMapValuesSet(const map<int, string>& m) {
    // ...
}
Пример
Код
set<string> values = BuildMapValuesSet({
    {1, "odd"},
    {2, "even"},
    {3, "odd"},
    {4, "even"},
    {5, "odd"}
});

for (const string& value : values) {
    cout << value << endl;
}

Вывод
even
odd

Пояснение
В этой задаче на проверку вам надо прислать файл с реализацией функции BuildMapValuesSet. 
Этот файл не должен содержать функцию main. Если в нём будет функция main, вы получите ошибку компиляции.
*/
