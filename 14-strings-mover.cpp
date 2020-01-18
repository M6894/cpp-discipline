
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void MoveStrings(vector<string>& source, vector<string>& destination) {
    for (string i : source) {
        destination.push_back(i);
    }
    source.clear();
}

int main() {
    vector<string> source = {"a", "b", "c"};
    vector<string> destination = {"z"};
    MoveStrings(source, destination);

    for (string i : destination) {
        cout << i << endl;
    }
    // cout << source.size();
    return 0;
}

/* MIPT and Yandex implementation - (tip) вместо i использовать w в переборе слов range based for:
void MoveStrings(vector<string>& source, vector<string>& destination) {
    for (auto w : source) {
        destination.push_back(w);
    }
    source.clear();
}
*/


/* Task:
Напишите функцию MoveStrings, которая принимает два вектора 
строк, source и destination, и дописывает все строки из первого 
вектора в конец второго. После выполнения функции вектор source 
должен оказаться пустым.

Чтобы очистить содержимое вектора, надо вызвать у него метод 
clear:

vector<string> words = {"hey", "hi"};
words.clear();
// Теперь вектор words пуст

Пример
vector<string> source = {"a", "b", "c"};
vector<string> destination = {"z"};
MoveStrings(source, destination);
// source должен оказаться пустым
// destination должен содержать строки "z", "a", "b", "c" именно 
в таком порядке
*/