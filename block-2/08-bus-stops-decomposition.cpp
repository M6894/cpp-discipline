
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    // Реализуйте эту функцию
    if (string operation; is >> operation) {
        if (operation == "NEW_BUS") {
            q.type = QueryType::NewBus;
            is >> q.bus;
            int stops_count = 0;
            is >> stops_count;
            q.stops.resize(stops_count);
            for (string& stop : q.stops) {
                is >> stop;
            }
        } else if (operation == "BUSES_FOR_STOP") {
            q.type = QueryType::BusesForStop;
            is >> q.stop;
            return is;
        } else if (operation == "STOPS_FOR_BUS") {
            q.type = QueryType::StopsForBus;
            is >> q.bus;
        } else if (operation == "ALL_BUSES") {
            q.type = QueryType::AllBuses;
        }
    }
    return is;
}

struct BusesForStopResponse {
    // Наполните полями эту структуру
    string result;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    // Реализуйте эту функцию
    os << r.result;
    return os;
}

struct StopsForBusResponse {
    // Наполните полями эту структуру
    string result;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    // Реализуйте эту функцию
    cout << r.result;
    return os;
}

struct AllBusesResponse {
    // Наполните полями эту структуру
    string result;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    // Реализуйте эту функцию
    cout << r.result;
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        // Реализуйте этот метод
        buses_to_stops[bus] = stops;
        for (string& stop : buses_to_stops[bus]) {
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        // Реализуйте этот метод
        stringstream ss;
        if (stops_to_buses.count(stop) == 0) {
            ss << "No stop"; // << endl;
        } else {
            for (const string& bus : stops_to_buses.at(stop)) {
                ss << bus << " ";
            }
            // ss << endl;
        }
        return {ss.str()};
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        // Реализуйте этот метод
        stringstream ss;
        if (buses_to_stops.count(bus) == 0) {
            ss << "No bus"; // << endl;
        } else {
            bool first = true;
            for (const string& stop : buses_to_stops.at(bus)) {
                if (!first) {
                    ss << "\n";
                }
                first = false;
                ss << "Stop " << stop << ": ";
                if (stops_to_buses.at(stop).size() == 1) {
                    ss << "no interchange";
                } else {
                    for (const string& other_bus : stops_to_buses.at(stop)) {
                        if (bus != other_bus) {
                            ss << other_bus << " ";
                        }
                    }
                }
                // cout << endl;
            }
        }
        return {ss.str()};
    }

    AllBusesResponse GetAllBuses() const {
        // Реализуйте этот метод
        stringstream ss;
        if (buses_to_stops.empty()) {
            ss << "No buses"; // << endl;
        } else {
            bool first = true;
            for (const auto& bus_item : buses_to_stops) {
                if (!first) {
                    ss << "\n";
                }
                first = false;
                ss << "Bus " << bus_item.first << ": ";
                for (const string& stop : bus_item.second) {
                    ss << stop << " ";
                }
            }
        }
        return {ss.str()};
    }
private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}

/* MIPT and Yandex implementation:
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string typeStr;
    is >> typeStr;
    if (typeStr == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stop_count = 0;
        is >> stop_count;
        q.stops.resize(stop_count);
        for (auto& stop : q.stops) {
            is >> stop;
        }
    } else if (typeStr == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    } else if (typeStr == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    } else if (typeStr == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }

    return is;
}

struct BusesForStopResponse {
    vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.buses.empty()) {
        os << "No stop";
    } else {
        for (const auto& bus : r.buses) {
            os << bus << " ";
        }
    }
    return os;
}

struct StopsForBusResponse {
    string bus;
    vector<pair<string, vector<string>>> stops_for_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.stops_for_buses.empty()) {
        os << "No bus";
    } else {
        bool first = true;
        for (const auto& stop_and_buses : r.stops_for_buses) {
            if (!first) {
                os << endl;
            }
            first = false;
            os << "Stop " << stop_and_buses.first << ":";
            if (stop_and_buses.second.size() == 1) {
                os << " no interchange";
            } else {
                for (const auto& bus : stop_and_buses.second) {
                    if (bus != r.bus) {
                        os << " " << bus;
                    }
                }
            }
        }
    }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.buses_to_stops.empty()) {
        os << "No buses";
    } else {
        bool first = true;
        for (const auto& bus_and_stops : r.buses_to_stops) {
            if (!first) {
                os << endl;
            }
            first = false;
            os << "Bus " << bus_and_stops.first << ":";
            for (const auto& stop : bus_and_stops.second) {
                os << " " << stop;
            }
        }
    }
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops.insert(make_pair(bus, stops));
        for (const auto& stop : stops) {
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        if (stops_to_buses.count(stop) == 0) {
            return BusesForStopResponse{vector<string>()};
        } else {
            return BusesForStopResponse{stops_to_buses.at(stop)};
        }
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        vector<pair<string, vector<string>>> result;

        if (buses_to_stops.count(bus) > 0) {
            for (const auto& stop : buses_to_stops.at(bus)) {
                result.push_back(make_pair(stop, stops_to_buses.at(stop)));
            }
        }
        return StopsForBusResponse{bus, result};
    }

    AllBusesResponse GetAllBuses() const {
        return AllBusesResponse{buses_to_stops};
    }

private:
    map<string, vector<string>> buses_to_stops;
    map<string, vector<string>> stops_to_buses;
};
*/



/* Task:
Введение
В курсе «Белый пояс по С++» у нас была задача «Автобусные остановки — 1». 
В этой задаче вам будет дано её правильное решение, целиком содержащееся 
внутри функции main. Вам надо будет выполнить декомпозицию этого решения 
на заранее заданные блоки так, чтобы получившаяся программа так же корректно 
решала задачу. Условие задачи «Автобусные остановки — 1» приведено ниже.

Исходные файлы
Авторское решение этой задачи содержится в файле

correct.cpp
Кроме того, вам дан файл

starter.cpp
который содержит заготовки классов и функций. Не меняя функцию main, вам 
надо реализовать эти классы и функции так, чтобы получившаяся программа 
решала задачу «Автобусные остановки — 1».

Как будет тестироваться ваша программа
Автоматическая проверяющая система заменит в вашей программе функцию main 
на ту, которая дана вам в файле starter.cpp, скомпилирует получившийся 
файл и прогонит на тестах для задачи «Автобусные остановки — 1».

Условие задачи «Автобусные остановки — 1»
Реализуйте систему хранения автобусных маршрутов. Вам нужно обрабатывать 
следующие запросы:

NEW_BUS bus stop_count stop1 stop2 ... — добавить маршрут автобуса с названием 
bus и stop_count остановками с названиями stop1, stop2, ...
BUSES_FOR_STOP stop — вывести названия всех маршрутов автобуса, проходящих 
через остановку stop.
STOPS_FOR_BUS bus — вывести названия всех остановок маршрута bus со списком 
автобусов, на которые можно пересесть на каждой из остановок.
ALL_BUSES — вывести список всех маршрутов с остановками.
Формат ввода
В первой строке ввода содержится количество запросов Q, затем в Q строках 
следуют описания запросов.

Гарантируется, что все названия маршрутов и остановок состоят лишь из латинских 
букв, цифр и знаков подчёркивания.

Для каждого запроса NEW_BUS bus stop_count stop1 stop2 ... гарантируется, что 
маршрут bus отсутствует, количество остановок больше 0, а после числа stop_count 
следует именно такое количество названий остановок, причём все названия в каждом 
списке различны.

Формат вывода
Для каждого запроса, кроме NEW_BUS, выведите соответствующий ответ на него:

На запрос BUSES_FOR_STOP stop выведите через пробел список автобусов, проезжающих 
через эту остановку, в том порядке, в котором они создавались командами NEW_BUS. 
Если остановка stop не существует, выведите No stop.
На запрос STOPS_FOR_BUS bus выведите описания остановок маршрута bus в отдельных 
строках в том порядке, в котором они были заданы в соответствующей команде NEW_BUS. 
Описание каждой остановки stop должно иметь вид Stop stop: bus1 bus2 ..., где bus1 
bus2 ... — список автобусов, проезжающих через остановку stop, в порядке, в котором 
они создавались командами NEW_BUS, за исключением исходного маршрута bus. Если через 
остановку stop не проезжает ни один автобус, кроме bus, вместо списка автобусов для 
неё выведите no interchange. Если маршрут bus не существует, выведите No bus.
На запрос ALL_BUSES выведите описания всех автобусов в алфавитном порядке. Описание 
каждого маршрута bus должно иметь вид Bus bus: stop1 stop2 ..., где stop1 stop2 ... 
— список остановок автобуса bus в порядке, в котором они были заданы в 
соответствующей команде NEW_BUS. Если автобусы отсутствуют, выведите No buses.
Предупреждение
Условие задачи выше содержит много важных деталей. Если вы не уверены в том, что 
не упустили ни одной, перечитайте условие ещё раз.

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