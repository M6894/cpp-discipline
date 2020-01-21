
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
    int q = 0;
    cin >> q;
    map<vector<string>, int> routes; // Количество различных маршрутов
    // map<int, vector<string>> buses; // Номера автобусов
    for (int i = 1; i <= q; i++) {
        int stops_count = 0;
        cin >> stops_count;
        vector<string> route; // Конкретный маршрут на вход
        for (int counter = 1; counter <= stops_count; counter++) {
            string stop;
            cin >> stop;
            route.push_back(stop);
        }
        if (routes.count(route) == 0) {
            int routes_counter = routes.size() + 1;
            routes[route] = routes_counter;
            cout << "New bus " << routes[route] << endl;
        }
        else {
            cout << "Already exists for " << routes[route] << endl;
        }
    }
    return 0;
}

/* MIPT and Yandex implementation, to note: метод создания вектора:
Эта задача призвана продемонстрировать, что одни контейнеры могут содержаться в других даже в качестве ключей. 
В данном случае стоило использовать map<vector<string>, int> — словарь, для каждого набора остановок (вектора 
строк) хранящий номер соответствующего маршрута.

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
    int q;
    cin >> q;

    map<vector<string>, int> buses;

    for (int i = 0; i < q; ++i) {
        int n;
        cin >> n;
        vector<string> stops(n);
        for (string& stop : stops) {
            cin >> stop;
        }
    
        // проверяем, не существует ли уже маршрут с таким набором остановок
        if (buses.count(stops) == 0) {
      
            // если не существует, нужно сохранить новый маршрут;
            // его номер на единицу больше текущего количества маршрутов
            const int new_number = buses.size() + 1;
            buses[stops] = new_number;
            cout << "New bus " << new_number << endl;
      
        } else {
            cout << "Already exists for " << buses[stops] << endl;
        }
    }

    return 0;
}
*/



/* Task:
В этой задаче вам нужно присваивать номера автобусным маршрутам.

А именно, для каждого маршрута, заданного набором названий остановок, нужно либо выдать 
новый номер (первому маршруту — 1, второму — 2 и т. д.), либо вернуть номер существующего 
маршрута, которому соответствует такой набор остановок.

Наборы остановок, полученные друг из друга перестановкой остановок, считаются различными (см. пример).

Указание
В C++ ключом словаря может быть не только число или строка, но и другой контейнер, например, vector.

Формат ввода
Сначала вводится количество запросов Q, затем Q описаний запросов.

Каждый запрос представляет собой положительное количество остановок N, за которым следуют разделённые 
пробелом N различных названий остановок соответствующего маршрута. Названия остановок состоят лишь из 
латинских букв и символов подчёркивания.

Формат вывода
Выведите ответ на каждый запрос в отдельной строке.

Если маршрут с данным набором остановок уже существует, в ответ на соответствующий запрос выведите 
Already exists for i, где i — номер маршрута с таким набором остановок. В противном случае нужно выделить 
введённому набору остановок новый номер i и вывести его в формате New bus i.

Пример
Ввод
4
2 Marushkino Kokoshkino
1 Kokoshkino
2 Marushkino Kokoshkino
2 Kokoshkino Marushkino

Вывод
New bus 1
New bus 2
Already exists for 1
New bus 3

Замечание
Будьте внимательны при обновлении словаря: если одновременно в одном выражении вычислять 
размер словаря и добавлять в него новый элемент, результат может отличаться от ожидаемого 
на единицу. Чтобы этого избежать, используйте временную переменную.

Например, вместо кода
map<string, int> m;
// ...
m["two"] = m.size();
// что нужно сделать раньше: вычислить size или добавить новый ключ?

стоит написать такой код:
map<string, int> m;
// ...
int new_value = m.size();
m["two"] = new_value;
// теперь всё однозначно: нужен размер до добавления элемента
*/
