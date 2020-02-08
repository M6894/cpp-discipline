
#include <iostream>
#include <string>
#include <map>
#include <exception>

using namespace std;

template<typename K, typename V>
V& GetRefStrict(map<K, V>& data, K key) {
    if (data.count(key) == 1) {
        return data.at(key);
    }
    throw runtime_error("Not found in data");
}

int main() {
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue
    return 0;
}

/* MIPT and Yandex implementation:
#include <map>
#include <stdexcept>

template<typename KeyType, typename ValueType>
ValueType& GetRefStrict(map<KeyType, ValueType>& input_map, KeyType key) {
    if (input_map.count(key) == 0) {
        throw runtime_error("no such key in dictionary");
    }
    return input_map[key];
}
*/



/* Task:
Реализуйте шаблонную функцию GetRefStrict, которая на вход принимает: 
map и значение ключа k. Если элемент по ключу k в коллекции отсутствует, 
то функция должна бросить исключение runtime_error, иначе вернуть ссылку 
на элемент в коллекции.

Пример использования функции

map<int, string> m = {{0, "value"}};
string& item = GetRefStrict(m, 0);
item = "newvalue";
cout << m[0] << endl; // выведет newvalue
*/