
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

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
        string known_first_name = GetKnownFirstName(year);
        string known_last_name = GetKnownLastName(year);
        if (known_first_name == "zero" && known_last_name == "zero") {
            return "Incognito";
        } else if (known_first_name == "zero" && known_last_name != "zero") {
            return known_last_name + " with unknown first name";
        } else if (known_first_name != "zero" && known_last_name == "zero") {
            return known_first_name + " with unknown last name";
        }
        return known_first_name + " " + known_last_name;
    }
private:
    map<int, string> first_names;
    map<int, string> last_names;
    string GetKnownFirstName(const int& year) {
        for (int i = year; i >= 0; i--) {
            if (first_names.count(i) != 0) {
                return first_names[i];
            }    
        }
        return "zero";    
    }
    string GetKnownLastName(const int& year) {
        for (int i = year; i >= 0; i--) {
            if (last_names.count(i) != 0) {
                return last_names[i];
            }    
        }
        return "zero";
    }
};

int main() {
    Person person;
    
    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }
    
    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }
    
    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }
    
    return 0;
}

/* MIPT and Yandex implementation - better in some cases: 1. Функция вместо 2х методов (сокращает код в 2 раза). 
2. Проверка для вывода реализована лаконичнее.

В приватных полях класса Person сохраним два словаря:

first_names, для каждого года с изменением имени хранящий соответствующее имя.
last_names, для каждого года с изменением фамилии хранящий соответствующую фамилию.
Методы ChangeFirstName и ChangeLastName будут лишь добавлять очередную запись в соответствующий словарь.

В методе GetFulName найдём имя и фамилию, соответствующие данному году, и затем аккуратно их выведем, соблюдая все требования условия. 
Здесь нам пригодится функция FindNameByYear, принимающая на вход год и словарь «год → имя/фамилия» и возвращающая имя/фамилию, 
соответствующую данному году.

#include <map>
#include <string>

// если имя неизвестно, возвращает пустую строку
string FindNameByYear(const map<int, string>& names, int year) {
    string name;  // изначально имя неизвестно
    
    // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
    for (const auto& item : names) {
        // если очередной год не больше данного, обновляем имя
        if (item.first <= year) {
            name = item.second;
        } else {
            // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
            break;
        }
    }

    return name;
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
        // получаем имя и фамилию по состоянию на год year
        const string first_name = FindNameByYear(first_names, year);
        const string last_name = FindNameByYear(last_names, year);
        
        // если и имя, и фамилия неизвестны
        if (first_name.empty() && last_name.empty()) {
            return "Incognito";
        
        // если неизвестно только имя
        } else if (first_name.empty()) {
            return last_name + " with unknown first name";
        
        // если неизвестна только фамилия
        } else if (last_name.empty()) {
            return first_name + " with unknown last name";
        
        // если известны и имя, и фамилия
        } else {
            return first_name + " " + last_name;
        }
    }

private:
    map<int, string> first_names;
    map<int, string> last_names;
};

*/



/* Task:
Реализуйте класс для человека, поддерживающий историю изменений человеком своих фамилии и имени.

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
private:
    // приватные поля
};

Считайте, что в каждый год может произойти не более одного изменения фамилии и не более одного изменения имени. 
При этом с течением времени могут открываться всё новые факты из прошлого человека, поэтому года́ в последовательных 
вызовах методов ChangeLastName и ChangeFirstName не обязаны возрастать.

Гарантируется, что все имена и фамилии непусты.

Строка, возвращаемая методом GetFullName, должна содержать разделённые одним пробелом имя и фамилию 
человека по состоянию на конец данного года.

Если к данному году не случилось ни одного изменения фамилии и имени, верните строку "Incognito".
Если к данному году случилось изменение фамилии, но не было ни одного изменения имени, верните "last_name with unknown first name".
Если к данному году случилось изменение имени, но не было ни одного изменения фамилии, верните "first_name with unknown last name".

Пример
Код
int main() {
    Person person;
    
    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }
    
    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }
    
    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }
    
    return 0;
}

Вывод
Incognito
Polina with unknown last name
Polina Sergeeva
Polina Sergeeva
Appolinaria Sergeeva
Polina Volkova
Appolinaria Volkova
*/
