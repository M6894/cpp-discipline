
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

// WORK IN PROGRESS

enum class Lang {
    DE, FR, IT
};

struct Region {
    string std_name;
    string parent_std_name;
    map<Lang, string> names;
    int64_t population;
};

bool operator==(Region& lhs, Region& rhs) {
    auto left = tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population);
    auto right = tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
    // tuple<string, string, map<Lang, string>, int64_t> one(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population);
    // tuple<string, string, map<Lang, string>, int64_t> two(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
    return left == right;
}

int FindMaxRepetitionCount(const vector<Region>& regions) {
    vector<Region> search = regions;
    int total_reps = 0;
    if (regions.empty()) {
        return total_reps;
    }
    for (int item = static_cast<int>(regions.size()); item > 0; item--) {
        auto item_copy = search[item -1];
        search.pop_back();
        // for (auto& region : search) {
            // if (item_copy == region) {
        for (int i = 0; i < static_cast<int>(search.size()); i) {
            auto compare = search[i];
            if (item_copy == compare) {
                total_reps++;
                search.erase(search.begin() + i);
                item--;
            } else {
                i++;
            }
        }
    }
    if (total_reps == 0) {
        return 1;
    } else {
        return total_reps;
    }
}

int main() {
    cout << FindMaxRepetitionCount({
        {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Russia",
            "Eurasia",
            {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
            89
        }, {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Russia",
            "Eurasia",
            {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
            89
        },
    }) << endl;
  
    cout << FindMaxRepetitionCount({
        {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Russia",
            "Eurasia",
            {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
            89
        }, {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Moscow",
            "Toulouse",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            31
        },
    }) << endl;
  
    return 0;
}

/* MIPT and Yandex implementation:

*/



/* Task:
Имеется база регионов, представленная вектором структур Region:

struct Region {
    string std_name;
    string parent_std_name;
    map<Lang, string> names;
    int64_t population;
};

Здесь Lang — идентификатор языка:

enum class Lang {
    DE, FR, IT
};

Напишите функцию FindMaxRepetitionCount, принимающую базу регионов 
и определяющую, какое максимальное количество повторов(число 
вхождений одного и того же элемента) она содержит. Две записи 
(объекты типа Region) считаются различными, если они отличаются 
хотя бы одним полем.

int FindMaxRepetitionCount(const vector<Region>& regions);

Если все записи уникальны, считайте максимальное количество повторов 
равным 1. Если записи отсутствуют, верните 0. Гарантируется, что типа 
int достаточно для хранения ответа.

Пример кода
int main() {
    cout << FindMaxRepetitionCount({
        {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Russia",
            "Eurasia",
            {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
            89
        }, {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Russia",
            "Eurasia",
            {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
            89
        },
    }) << endl;
  
    cout << FindMaxRepetitionCount({
        {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Russia",
            "Eurasia",
            {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
            89
        }, {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Moscow",
            "Toulouse",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            31
        },
    }) << endl;
  
    return 0;
}

Вывод
3
1

Пояснение
В этой задаче вам надо прислать на проверку файл с реализацией функции 
FindMaxRepetitionCount, а также дополнительных функций, если это 
необходимо. Этот файл не должен содержать типы Lang и Region. В противном 
случае вы получите ошибку компиляции.
*/