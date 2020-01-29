
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <tuple>
#include <set>

using namespace std;

enum class Lang {
    DE, FR, IT
};

struct Region {
    string std_name;
    string parent_std_name;
    map<Lang, string> names;
    int64_t population;
};

bool operator==(const Region& lhs, const Region& rhs) {
    // tuple<string, string, map<Lang, string>, int64_t> one(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population);
    // tuple<string, string, map<Lang, string>, int64_t> two(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
    return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) == tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

bool operator<(const Region& lhs, const Region& rhs) {
    // tuple<string, string, map<Lang, string>, int64_t> one(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population);
    // tuple<string, string, map<Lang, string>, int64_t> two(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
    return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) < tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions) {
    int max_reps = 0;
    if (regions.empty()) {
        return max_reps;
    }
    set<Region> search(regions.begin(), regions.end());
    for (const auto& region : search) {
        int r = 0;
        for (const auto& compare : regions) {
            if (region == compare) {
                r++;
            }
        }
        if (r > max_reps) {
            max_reps = r;
        }
    }
    return max_reps;
}

/*
// TODO: Must be faster
int FindMaxRepetitionCount(const vector<Region>& regions) {
    // vector<Region> search = regions;
    int max_reps = 0;
    if (regions.empty()) {
        return max_reps;
    }
    for (const auto& region : regions) {
        int r = 0;
        for (const auto& compare : regions) {
            if (region == compare) {
                r++;
            }
        }
        if (r > max_reps) {
            max_reps = r;
        }
    }
    return max_reps;
}
*/
/* Max repetitions of one Region counter
int FindMaxRepetitionCount(const vector<Region>& regions) {
    vector<Region> search = regions;
    int reps = 0;
    if (regions.empty()) {
        return reps;
    }
    for (int item = static_cast<int>(regions.size()); item > 0; item--) {
        auto item_copy = search[item -1];
        search.pop_back();
        int r = 1; // Repetition counter for each element in search
        for (int i = 0; i < static_cast<int>(search.size()); i) {
            auto compare = search[i];
            if (item_copy == compare) {
                r++;
                search.erase(search.begin() + i);
                item--;
            } else {
                i++;
            }
        }
        if (r > reps) {
            reps = r;
        }
    }
    return reps;
}
*/
/* Total repetitions counting version
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
*/

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
        },
    }) << endl;
  
    return 0;
}

/* MIPT and Yandex implementation (preferred):
Внимание! Ниже опубликовано решение необязательной задачи «База регионов». 
Настоятельно рекомендуем попытаться её решить перед тем, как читать решение.

#include <map>
#include <tuple>
#include <vector>

using namespace std;

bool operator<(const Region& lhs, const Region& rhs) {
    return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
            tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions) {
    int result = 0;
    map<Region, int> repetition_count;
    for (const Region& region : regions) {
        result = max(result, ++repetition_count[region]);
    }
    return result;
}
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