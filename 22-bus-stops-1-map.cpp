
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void PrintMap(const map<map<int, string>, vector<string>>& input) {
    for (const auto& item : input) {
        for (const auto& key : item.first) {

        }
    }
    cout << endl;
}

vector<string> BusesForStop(map<string, vector<string>> buses, const vector<string>& buses_order, const string& stop) {
    vector<string> result;
    for (const string& bus : buses_order) {
        for (const string& each_stop : buses[bus]) {
            if (each_stop == stop) {
                result.push_back(bus);
            }
        }
    }
    return result;
}

void PrintVector(const vector<string>& input) {
    for (const string& word : input) {
        cout << word << " ";
    }
    cout << endl;
}

void PrintBusesForStop(const vector<string>& input, const string& bus) {
    vector<string> result;
    for (const string& word : input) { // Нужно исключить из вектора Bus и напечатать.
        if (word != bus) {
            cout << word << " ";
        }
    }
    cout << endl;
}

int main() {
    vector<string> buses_order;
    map<string, vector<string>> buses;
    int q = 0; // Количество операций
    string command;

    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> command;
        if (command == "NEW_BUS") {
            string bus;
            int n_stops; // Количество новых остановок
            cin >> bus >> n_stops;
            for (int num = 1; num <= n_stops; num++) {
                string stop = "";
                cin >> stop;
                buses[bus].push_back(stop);
            }
            buses_order.push_back(bus);
        }
        else if (command == "BUSES_FOR_STOP") {
            string stop = "";
            cin >> stop;
            vector<string> result = BusesForStop(buses, buses_order, stop); 

            if (result.size() == 0) {
                cout << "No stop" << endl;
            }
            else {
                PrintVector(result);
            }
        }
        else if (command == "STOPS_FOR_BUS") {
            string bus = "";
            cin >> bus;
            if (buses.count(bus) == 0) {
                cout << "No bus" << endl;
            }
            else {
                for (const string& each_stop : buses[bus]) {
                    if (BusesForStop(buses, buses_order, each_stop).size() == 1 && BusesForStop(buses, buses_order, each_stop)[0] == bus) {
                        cout << "Stop " << each_stop << ": " << "no interchange" << endl;
                    } 
                    else {
                        cout << "Stop " << each_stop << ": ";
                        PrintBusesForStop(BusesForStop(buses, buses_order, each_stop), bus);
                    }
                }
            }
        }
        else if (command == "ALL_BUSES") {
            if (buses.size() != 0) {
                for (const auto& item : buses) {
                    cout << "Bus " << item.first << ": ";
                    for (const string& stop : item.second) {
                        cout << stop << " ";
                    }
                    cout << endl;
                }
            }
            else {
                cout << "No buses" << endl;
            }    
        }
    }
    return 0;
}

/* MIPT and Yandex implementation - интересное создание вектора с помощью ссылки и создание 2х словарей. В целом такая реализация 
более объемна. Логичные структурирование кода и вызов функций.

Пожалуй, самое сложное в этой задаче — внимательно прочитать условие и аккуратно реализовать все его требования, 
выбрав при этом правильные контейнеры.

Поскольку необходимо было получать как список остановок для конкретного автобуса, так и список автобусов для конкретной 
остановки, логичнее всего было определить два словаря — buses_to_stops и stops_to_buses со строковыми ключами и 
значениями типа vector<string>.

Ответы на большинство запросов вынесем в отдельные функции: это позволит повысить читаемость кода. Заметьте, что 
при этом не всегда удаётся передавать словари по константным ссылкам: это происходит из-за того, что использование 
квадратных скобок (например, в коде stops_to_buses[stop]) теоретически может изменить словарь. В этой ситуации 
стоило бы использовать метод at вместо квадратных скобок — мы рассмотрим его в следующем курсе.

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

// ответ на запрос BUSES_FOR_STOP
void PrintBusesForStop(map<string, vector<string>>& stops_to_buses,
                       const string& stop) {
    if (stops_to_buses.count(stop) == 0) {
        cout << "No stop" << endl;
    } else {
        for (const string& bus : stops_to_buses[stop]) {
            cout << bus << " ";
        }
        cout << endl;
    }                
}

// ответ на запрос STOPS_FOR_BUS
void PrintStopsForBus(map<string, vector<string>>& buses_to_stops,
                      map<string, vector<string>>& stops_to_buses,
                      const string& bus) {
    if (buses_to_stops.count(bus) == 0) {
        cout << "No bus" << endl;
    } else {
        for (const string& stop : buses_to_stops[bus]) {
            cout << "Stop " << stop << ": ";
      
            // если через остановку проходит ровно один автобус,
            // то это наш автобус bus, следовательно, пересадки тут нет
            if (stops_to_buses[stop].size() == 1) {
                cout << "no interchange";
            } else {
                for (const string& other_bus : stops_to_buses[stop]) {
                    if (bus != other_bus) {
                        cout << other_bus << " ";
                    }
                }
            }
            cout << endl;
        }
    }             
}

// ответ на запрос ALL_BUSES
void PrintAllBuses(const map<string, vector<string>>& buses_to_stops) {
    if (buses_to_stops.empty()) {
        cout << "No buses" << endl;
    } else {
        for (const auto& bus_item : buses_to_stops) {
            cout << "Bus " << bus_item.first << ": ";
            for (const string& stop : bus_item.second) {
                cout << stop << " ";
            }
            cout << endl;
        }
    }             
}

int main() {
    int q;
    cin >> q;

    map<string, vector<string>> buses_to_stops, stops_to_buses;

    for (int i = 0; i < q; ++i) {
        string operation_code;
        cin >> operation_code;

        if (operation_code == "NEW_BUS") {

            string bus;
            cin >> bus;
            int stop_count;
            cin >> stop_count;
            
            // с помощью ссылки дадим короткое название вектору
            // со списком остановок данного автобуса;
            // ключ bus изначально отсутствовал в словаре, поэтому он автоматически
            // добавится туда с пустым вектором в качестве значения
            vector<string>& stops = buses_to_stops[bus];
            stops.resize(stop_count);
      
            for (string& stop : stops) {
                cin >> stop;
                // не забудем обновить словарь stops_to_buses
                stops_to_buses[stop].push_back(bus);
            }

        } else if (operation_code == "BUSES_FOR_STOP") {

            string stop;
            cin >> stop;
            PrintBusesForStop(stops_to_buses, stop);

        } else if (operation_code == "STOPS_FOR_BUS") {

            string bus;
            cin >> bus;
            PrintStopsForBus(buses_to_stops, stops_to_buses, bus);

        } else if (operation_code == "ALL_BUSES") {

            PrintAllBuses(buses_to_stops);

        }
    }

    return 0;
}
*/



/* Task:
Реализуйте систему хранения автобусных маршрутов. Вам нужно обрабатывать следующие запросы:

NEW_BUS bus stop_count stop1 stop2 ... — добавить маршрут автобуса с названием bus и stop_count остановками 
с названиями stop1, stop2, ...
BUSES_FOR_STOP stop — вывести названия всех маршрутов автобуса, проходящих через остановку stop.
STOPS_FOR_BUS bus — вывести названия всех остановок маршрута bus со списком автобусов, на которые можно 
пересесть на каждой из остановок.
ALL_BUSES — вывести список всех маршрутов с остановками.
Формат ввода
В первой строке ввода содержится количество запросов Q, затем в Q строках следуют описания запросов.

Гарантируется, что все названия маршрутов и остановок состоят лишь из латинских букв, цифр и знаков подчёркивания.

Для каждого запроса NEW_BUS bus stop_count stop1 stop2 ... гарантируется, что маршрут bus отсутствует, 
количество остановок больше 0, а после числа stop_count следует именно такое количество названий остановок, 
причём все названия в каждом списке различны.

Формат вывода
Для каждого запроса, кроме NEW_BUS, выведите соответствующий ответ на него:

На запрос BUSES_FOR_STOP stop выведите через пробел список автобусов, проезжающих через эту остановку, в том порядке, 
в котором они создавались командами NEW_BUS. Если остановка stop не существует, выведите No stop.
На запрос STOPS_FOR_BUS bus выведите описания остановок маршрута bus в отдельных строках в том порядке, в котором они 
были заданы в соответствующей команде NEW_BUS. Описание каждой остановки stop должно иметь вид Stop stop: bus1 bus2 ..., 
где bus1 bus2 ... — список автобусов, проезжающих через остановку stop, в порядке, в котором они создавались командами 
NEW_BUS, за исключением исходного маршрута bus. Если через остановку stop не проезжает ни один автобус, кроме bus, 
вместо списка автобусов для неё выведите no interchange. Если маршрут bus не существует, выведите No bus.
На запрос ALL_BUSES выведите описания всех автобусов в алфавитном порядке. Описание каждого маршрута bus должно иметь 
вид Bus bus: stop1 stop2 ..., где stop1 stop2 ... — список остановок автобуса bus в порядке, в котором они были заданы 
в соответствующей команде NEW_BUS. Если автобусы отсутствуют, выведите No buses.
Предупреждение
Условие задачи выше содержит много важных деталей. Если вы не уверены в том, что не упустили ни одной, перечитайте 
условие ещё раз.

Пример
Ввод
10
ALL_BUSES
BUSES_FOR_STOP Marushkino
STOPS_FOR_BUS 32K
NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo
NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo
BUSES_FOR_STOP Vnukovo
NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo
NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo
STOPS_FOR_BUS 272
ALL_BUSES

Вывод
No buses
No stop
No bus
32 32K
Stop Vnukovo: 32 32K 950
Stop Moskovsky: no interchange
Stop Rumyantsevo: no interchange
Stop Troparyovo: 950
Bus 272: Vnukovo Moskovsky Rumyantsevo Troparyovo
Bus 32: Tolstopaltsevo Marushkino Vnukovo
Bus 32K: Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo
Bus 950: Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo
*/