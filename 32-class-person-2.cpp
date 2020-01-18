
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

string GetKnownName(const int& year, map<int, string>& names) {
    for (int i = year; i >= 0; i--) {
        if (names.count(i) != 0) {
            return names[i];
        }    
    }
    return "zero";    
}

string GetFullKnownName(const int& year, map<int, string>& names) {
    string result = "";
    string brackets = "";
    string previous = "";
    for (int i = year; i >= 0; i--) {
            if (names.count(i) != 0 && result.empty()) {
                result = names[i];
                previous = names[i];
            }
            else if (names.count(i) != 0 && brackets.empty()) {
                if (names[i] != previous) {
                    brackets = " (" + names[i];
                    previous = names[i];
                }
            }
            else if (names.count(i) != 0) {
                if (names[i] != previous) {
                    brackets += ", " + names[i];
                    previous = names[i];
                }
            }
            
            if (i == 0 && !brackets.empty()) {
                brackets += ")";
            }
        }
    return result + brackets;  
}

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        first_names[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        // добавить факт изменения фамилии на last_name в год year
        last_names[year] = last_name;
    }
    string GetFullName(int year) {
        // получить имя и фамилию по состоянию на конец года year
        string known_first_name = GetKnownName(year, first_names);
        string known_last_name = GetKnownName(year, last_names);
        if (known_first_name == "zero" && known_last_name == "zero") {
            return "Incognito";
        } else if (known_first_name == "zero") {
            return known_last_name + " with unknown first name";
        } else if (known_last_name == "zero") {
            return known_first_name + " with unknown last name";
        }
        return known_first_name + " " + known_last_name;
    }
    string GetFullNameWithHistory(int year) {
        // получить все имена и фамилии по состоянию на конец года year
        string known_full_first_name = GetFullKnownName(year, first_names);
        string known_full_last_name = GetFullKnownName(year, last_names);
        if (known_full_first_name.empty() && known_full_last_name.empty()) {
            return "Incognito";
        } else if (known_full_first_name.empty()) {
            return known_full_last_name + " with unknown first name";
        } else if (known_full_last_name.empty()) {
            return known_full_first_name + " with unknown last name";
        }
        return known_full_first_name + " " + known_full_last_name;
    }
private:
    map<int, string> first_names;
    map<int, string> last_names;
};

int main() {

    Person person;
  
    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }
  
    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }
  
    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }
  
    person.ChangeFirstName(1990, "Polina");
    person.ChangeLastName(1990, "Volkova-Sergeeva");
    cout << person.GetFullNameWithHistory(1990) << endl;
  
    person.ChangeFirstName(1966, "Pauline");
    cout << person.GetFullNameWithHistory(1966) << endl;
  
    person.ChangeLastName(1960, "Sergeeva");
    for (int year : {1960, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }
  
    person.ChangeLastName(1961, "Ivanova");
    cout << person.GetFullNameWithHistory(1967) << endl;
    
    return 0;
}

/* MIPT and Yandex implementation:
Отличие от предыдущей задачи состоит лишь в необходимости добавить метод GetFullNameWithHistory. 
Но для того, чтобы избежать дублирования кода в методах GetFullName и GetFullNameWithHistory, 
решение предыдущей задачи придётся значительно переработать.

Напишем следующие вспомогательные функции:

Функцию FindNamesHistory, возвращающую по году и словарю «год → имя (фамилия)» всю историю изменений 
имени (фамилии) к этому году в виде вектора строк.
Функцию BuildJoinedName, по истории изменений имени (фамилии) возвращающую эту историю в виде единой 
строки: сначала последнее имя, затем в круглых скобках через запятую все предыдущие имена.
Функцию BuildFullName, по имени и фамилии (возможно, неизвестным, то есть пустым) возвращающую полное 
имя в требуемом формате. В прошлой задаче этот код находился непосредственно в методе GetFullName, 
теперь же он понадобился и в методе GetFullNameWithHistory — потому мы и выделили его в отдельную функцию.
Кроме того, напишем короткие вспомогательные приватные методы FindFirstNamesHistory и FindLastNamesHistory, 
с помощью функции FindNamesHistory возвращающие по данному году историю изменений имени или фамилии.

В методах GetFullName и GetFullNameWithHistory останется лишь аккуратно вызвать описанные выше функции и методы.

#include <algorithm>
#include <map>
#include <vector>

using namespace std;

vector<string> FindNamesHistory(const map<int, string>& names_by_year, int year) {
    vector<string> names;
    // перебираем всю историю в хронологическом порядке
    for (const auto& item : names_by_year) {
        // если очередное имя не относится к будущему и отличается от предыдущего,
        if (item.first <= year && (names.empty() || names.back() != item.second)) {
            // добавляем его в историю
            names.push_back(item.second);
        }
    }
    return names;
}

string BuildJoinedName(vector<string> names) {
    // нет истории — имя неизвестно
    if (names.empty()) {
        return "";
    }
    // меняем прямой хронологический порядок на обратный
    reverse(begin(names), end(names));
    
    // начинаем строить полное имя с самого последнего
    string joined_name = names[0];
  
    // перебираем все последующие имена
    for (int i = 1; i < names.size(); ++i) {
        if (i == 1) {
            // если это первое «историческое» имя, отделяем его от последнего скобкой
            joined_name += " (";
        } else {
            // если это не первое имя, отделяем от предыдущего запятой
            joined_name += ", ";
        }
        // и добавляем очередное имя
        joined_name += names[i];
    }
  
    // если в истории было больше одного имени, мы открывали скобку — закроем её
    if (names.size() > 1) {
        joined_name += ")";
    }
    // имя со всей историей готово
    return joined_name;
}

// см. решение предыдущей задачи
string BuildFullName(const string& first_name, const string& last_name) {
    if (first_name.empty() && last_name.empty()) {
        return "Incognito";
    } else if (first_name.empty()) {
        return last_name + " with unknown first name";
    } else if (last_name.empty()) {
        return first_name + " with unknown last name";
    } else {
        return first_name + " " + last_name;
    }
}

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        first_names[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        last_names[year] = last_name;
    }
  
    string GetFullName(int year) {
        // найдём историю изменений имени и фамилии
        // в данном случае это излишне, так как нам достаточно узнать последние имя и фамилию, но почему бы не использовать готовые функции?
        const vector<string> first_names_history = FindFirstNamesHistory(year);
        const vector<string> last_names_history = FindLastNamesHistory(year);
    
        // подготовим данные для функции BuildFullName: возьмём последние имя и фамилию или оставим их пустыми, если они неизвестны
        string first_name;
        string last_name;
        if (!first_names_history.empty()) {
            first_name = first_names_history.back();
        }
        if (!last_names_history.empty()) {
            last_name = last_names_history.back();
        }
        return BuildFullName(first_name, last_name);
    }
  
    string GetFullNameWithHistory(int year) {
        // получим полное имя со всей историей
        const string first_name = BuildJoinedName(FindFirstNamesHistory(year));
        // получим полную фамилию со всей историей
        const string last_name = BuildJoinedName(FindLastNamesHistory(year));
        // объединим их с помощью готовой функции
        return BuildFullName(first_name, last_name);
    }

private:
    vector<string> FindFirstNamesHistory(int year) {
        return FindNamesHistory(first_names, year);
    }
    vector<string> FindLastNamesHistory(int year) {
        return FindNamesHistory(last_names, year);
    }

    map<int, string> first_names;
    map<int, string> last_names;
};

*/



/* Task:
Дополните класс из предыдущей задачи «Имена и фамилии — 1» методом GetFullNameWithHistory:
class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        // добавить факт изменения имени на first_name в год year
    }
    void ChangeLastName(int year, const string& last_name) {
        // добавить факт изменения фамилии на last_name в год year
    }
    string GetFullName(int year) {
        // получить имя и фамилию по состоянию на конец года year
    }
    string GetFullNameWithHistory(int year) {
        // получить все имена и фамилии по состоянию на конец года year
    }
private:
    // приватные поля
};

В отличие от метода GetFullName, метод GetFullNameWithHistory должен вернуть не только последние имя и 
фамилию к концу данного года, но ещё и все предыдущие имена и фамилии в обратном хронологическом порядке. 
Если текущие факты говорят о том, что человек два раза подряд изменил фамилию или имя на одно и то же, 
второе изменение при формировании истории нужно игнорировать.

Для лучшего понимания формата см. примеры.

Пример 1
Код

int main() {
    Person person;

    person.ChangeFirstName(1900, "Eugene");
    person.ChangeLastName(1900, "Sokolov");
    person.ChangeLastName(1910, "Sokolov");
    person.ChangeFirstName(1920, "Evgeny");
    person.ChangeLastName(1930, "Sokolov");
    cout << person.GetFullNameWithHistory(1940) << endl;
  
  return 0;
}

Вывод
Evgeny (Eugene) Sokolov

Пример 2
Код
int main() {
    Person person;
  
    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }
  
    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }
  
    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }
  
    person.ChangeFirstName(1990, "Polina");
    person.ChangeLastName(1990, "Volkova-Sergeeva");
    cout << person.GetFullNameWithHistory(1990) << endl;
  
    person.ChangeFirstName(1966, "Pauline");
    cout << person.GetFullNameWithHistory(1966) << endl;
  
    person.ChangeLastName(1960, "Sergeeva");
    for (int year : {1960, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }
  
    person.ChangeLastName(1961, "Ivanova");
    cout << person.GetFullNameWithHistory(1967) << endl;
    
    return 0;
}

Вывод
Incognito
Polina with unknown last name
Polina Sergeeva
Polina Sergeeva
Appolinaria (Polina) Sergeeva
Polina Volkova (Sergeeva)
Appolinaria (Polina) Volkova (Sergeeva)
Polina (Appolinaria, Polina) Volkova-Sergeeva (Volkova, Sergeeva)
Pauline (Polina) with unknown last name
Sergeeva with unknown first name
Pauline (Polina) Sergeeva
Pauline (Polina) Sergeeva (Ivanova, Sergeeva)
*/
