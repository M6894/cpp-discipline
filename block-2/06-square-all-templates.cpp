
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <utility>

using namespace std;

template<typename Key, typename Value> map<Key, Value> operator*(map<Key, Value> data);
template<typename T> vector<T> operator*(vector<T> lhs, vector<T> rhs);
template<typename Left, typename Right> pair<Left, Right> operator*(pair<Left, Right> lhs, pair<Left, Right> rhs);
template<typename Anything> Anything Sqr(Anything data);

template<typename Key, typename Value> 
map<Key, Value> operator*(map<Key, Value> lhs, map<Key, Value> rhs) {
    map<Key, Value> result(begin(lhs), end(lhs));
    for (auto& r : result) {
        r.second = lhs[r.first] * rhs[r.first];
    }
    return result;
} 

template<typename T> 
vector<T> operator*(vector<T> lhs, vector<T> rhs) {
    vector<T> result;
    for (auto i = 0; i < lhs.size(); i++) {
        result.push_back(lhs[i] * rhs[i]); 
    }
    return result;
}

template<typename Left, typename Right> 
pair<Left, Right> operator*(pair<Left, Right> lhs, pair<Left, Right> rhs) {
    return make_pair(lhs.first * rhs.first, lhs.second * rhs.second);
}

template<typename Anything>
Anything Sqr(Anything data) {
    return data * data;
}

int main() {
    // Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    vector<vector<int>> a = {{1,2}, {2,4}};
    cout << "vector of vectors:";
    for (auto b : Sqr(a)) {
        for (auto c : b) {
            cout << ' ' << c;
        }
    }
    cout << endl;

    map<int, int> m = {{1, 2}, {2, 4}};
    cout << "map:";
    for (auto x : Sqr(m)) {
        cout << ' ' << x.second;
    }
    cout << endl;

    pair p = {1,2};

    map<int, pair<int, int>> map_of_pairs = {
        {4, {2, 2}},
        {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
    return 0;
}

/* MIPT and Yandex implementation (preferred):
Реализуем функцию Sqr для чисел, словарей, векторов и пар.

// Объявим функции без тела,
// чтобы их можно было использовать в произвольном порядке

// Для простых типов
template<typename T>
T Sqr(T value);

// Для вектора
template<typename T>
vector<T> Sqr(const vector<T>& value);

// Для словаря
template<typename K, typename V>
map<K, V> Sqr(const map<K, V>& value);

// Для пары
template<typename K, typename V>
pair<K, V> Sqr(const pair<K, V>& value);

// Теперь реализуем их в соответствии с заданием
template<typename T>
T Sqr(T value) {
    return value * value;
}

template<typename T>
vector<T> Sqr(const vector<T>& value) {
    vector<T> result;
    for (const T& x : value) {
        // Здесь важно, что вместо x * x вызывается функция Sqr:
        // это позволяет возводить в квадрат составные объекты
        result.push_back(Sqr(x));
    }

    return result;
}

template<typename K, typename V>
map<K, V> Sqr(const map<K, V>& value) {
    map<K, V> result;
    for (const auto& element : value) {
        result[element.first] = Sqr(element.second);
    }
    return result;
}

template<typename K, typename V>
pair<K, V> Sqr(const pair<K, V>& value) {
    return {Sqr(value.first), Sqr(value.second)};
}
*/



/* Task:
Реализуйте шаблонную функцию Sqr, которая работает не только для чисел, 
но и для контейнеров. Функция должна возвращать копию исходного контейнера, 
модифицировав его следующим образом:

для vector элементы нужно возвести в квадрат;
для map в квадрат нужно возвести только значения, но не ключи;
для pair в квадрат нужно возвести каждый элемент пары.
// Пример вызова функции
vector<int> v = {1, 2, 3};
cout << "vector:";
for (int x : Sqr(v)) {
    cout << ' ' << x;
}
cout << endl;

map<int, pair<int, int>> map_of_pairs = {
    {4, {2, 2}},
    {7, {4, 3}}
};
cout << "map of pairs:" << endl;
for (const auto& x : Sqr(map_of_pairs)) {
    cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
}

Код выше должен вывести
vector: 1 4 9
map of pairs:
4 4 4
7 16 9

Функция должна корректно работать не только для контейнеров, состоящих из чисел, 
но и для составных объектов, например, векторов словарей пар чисел.

Для успешной сдачи решения необходимо сделать предварительное объявление 
шаблонных функций перед всеми шаблонными функциями.

Пример предварительного объявления шаблонной функции

// Предварительное объявление шаблонных функций
template<typename T> T FuncA(T x);
template<typename T> void FuncB(T x);

// Объявляем шаблонные функции
template <typename T>
T FuncA(T x) {  }

template <typename T>
void FuncB(T x) {  }

Зачем это нужно и как это работает вы узнаете далее из наших курсов.
*/