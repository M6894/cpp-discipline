
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void PrintMap(const map<string, string>& capitals) {
    for (const auto& item : capitals) {
        cout << item.first << "/" << item.second << " ";
    }
    cout << endl;
}

int main() {
    int q = 0; // количество команд
    cin >> q;
    string command, country, old_capital, new_capital, old_country_name, new_country_name;
    map<string, string> capitals;

    for (int stage = 1; stage <= q; stage++) {

        cin >> command;
        if (command == "CHANGE_CAPITAL") {
            cin >> country >> new_capital;
            if (capitals[country] == "") {
                capitals[country] = new_capital;
                cout << "Introduce new country " << country << " with capital " << new_capital << endl;
            }
            else if (capitals[country] == new_capital) {
                cout << "Country " << country << " hasn't changed its capital" << endl;
            }
            else {
                old_capital = capitals[country];
                capitals[country] = new_capital;
                cout << "Country " << country << " has changed its capital from " << old_capital << " to " << new_capital << endl;
            }
        }

        if (command == "RENAME") {
            cin >> old_country_name >> new_country_name;
            if (old_country_name == new_country_name) {
                cout << "Incorrect rename, skip" << endl;
            }
            else if (capitals[new_country_name] != "") {
                cout << "Incorrect rename, skip" << endl;
            }
            else if (capitals[old_country_name] == "") {
                capitals.erase(old_country_name);
                cout << "Incorrect rename, skip" << endl;
            }
            else {
                cout << "Country " << old_country_name << " with capital " << capitals[old_country_name] 
                << " has been renamed to " << new_country_name << endl;
                capitals[new_country_name] = capitals[old_country_name];
                capitals.erase(old_country_name);
            }
            if (capitals[new_country_name] == "") { // Удаление оставшегося от проверки ключа
                capitals.erase(new_country_name);
            }
        }

        if (command == "ABOUT") {
            cin >> country;
            if (capitals[country] == "") {
                cout << "Country " << country << " doesn't exist" << endl;;
                capitals.erase(country);
            }
            else {
                cout << "Country " << country << " has capital " << capitals[country] << endl;
            }
        }

        if (command == "DUMP") {
            if (capitals.size() == 0) {
                cout << "There are no countries in the world" << endl;
            }
            else {
                PrintMap(capitals);
            }
        }
    }

    return 0;
}

/* MIPT and Yandex implementation - Лучше реализована проверка наличия ключа с помощью count:
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    int q;
    cin >> q;

    map<string, string> country_to_capital;

    for (int i = 0; i < q; ++i) {
        string operation_code;
        cin >> operation_code;

        if (operation_code == "CHANGE_CAPITAL") {

            string country, new_capital;
            cin >> country >> new_capital;
            if (country_to_capital.count(country) == 0) {
                cout << "Introduce new country " << country << " with capital " << new_capital << endl;
            } else {
                const string& old_capital = country_to_capital[country];
                if (old_capital == new_capital) {
                    cout << "Country " << country << " hasn't changed its capital" << endl;
                } else {
                    cout << "Country " << country << " has changed its capital from " << old_capital << " to " << new_capital << endl;
                }
            }
            country_to_capital[country] = new_capital;

        } else if (operation_code == "RENAME") {

            string old_country_name, new_country_name;
            cin >> old_country_name >> new_country_name;
            if (old_country_name == new_country_name || country_to_capital.count(old_country_name) == 0 || country_to_capital.count(new_country_name) == 1) {
                cout << "Incorrect rename, skip" << endl;
            } else {
                cout << "Country " << old_country_name << " with capital " << country_to_capital[old_country_name] <<
                        " has been renamed to " << new_country_name << endl;
                country_to_capital[new_country_name] = country_to_capital[old_country_name];
                country_to_capital.erase(old_country_name);
            }

        } else if (operation_code == "ABOUT") {

            string country;
            cin >> country;
            if (country_to_capital.count(country) == 0) {
                cout << "Country " << country << " doesn't exist" << endl;
            } else {
                cout << "Country " << country << " has capital " << country_to_capital[country] << endl;
            }

        } else if (operation_code == "DUMP") {

            if (country_to_capital.empty()) {
                cout << "There are no countries in the world" << endl;
            } else {
                for (const auto& country_item : country_to_capital) {
                    cout << country_item.first << "/" << country_item.second << " ";
                }
                cout << endl;
            }

        }

    }

    return 0;
}
*/



/* Task
Реализуйте справочник столиц стран.

На вход программе поступают следующие запросы:

CHANGE_CAPITAL country new_capital — изменение столицы страны country на new_capital, 
либо добавление такой страны с такой столицей, если раньше её не было.
RENAME old_country_name new_country_name — переименование страны из old_country_name в new_country_name.
ABOUT country — вывод столицы страны country.
DUMP — вывод столиц всех стран.
Формат ввода
В первой строке содержится количество запросов Q, в следующих Q строках — описания запросов. 
Все названия стран и столиц состоят лишь из латинских букв, цифр и символов подчёркивания.

Формат вывода
Выведите результат обработки каждого запроса:

В ответ на запрос CHANGE_CAPITAL country new_capital выведите
Introduce new country country with capital new_capital, если страны country раньше не существовало;
Country country hasn't changed its capital, если страна country до текущего момента имела столицу new_capital;
Country country has changed its capital from old_capital to new_capital, если страна country до текущего момента 
имела столицу old_capital, название которой не совпадает с названием new_capital.

В ответ на запрос RENAME old_country_name new_country_name выведите
Incorrect rename, skip, если новое название страны совпадает со старым, страна old_country_name не существует или 
страна new_country_name уже существует;
Country old_country_name with capital capital has been renamed to new_country_name, если запрос корректен и страна 
имеет столицу capital.

В ответ на запрос ABOUT country выведите
Country country doesn't exist, если страны с названием country не существует;
Country country has capital capital, если страна country существует и имеет столицу capital.

В ответ на запрос DUMP выведите
There are no countries in the world, если пока не было добавлено ни одной страны;
разделённые пробелами пары country/capital, описывающие столицы всех стран и упорядоченные по названию страны, 
если в мире уже есть хотя бы одна страна.

Пример 1
Ввод
6
CHANGE_CAPITAL RussianEmpire Petrograd
RENAME RussianEmpire RussianRepublic
ABOUT RussianRepublic
RENAME RussianRepublic USSR
CHANGE_CAPITAL USSR Moscow
DUMP

Вывод:
Introduce new country RussianEmpire with capital Petrograd
Country RussianEmpire with capital Petrograd has been renamed to RussianRepublic
Country RussianRepublic has capital Petrograd
Country RussianRepublic with capital Petrograd has been renamed to USSR
Country USSR has changed its capital from Petrograd to Moscow
USSR/Moscow

Пример 2
Ввод
24
RENAME FakeCountry FarFarAway
ABOUT FarFarAway
DUMP
CHANGE_CAPITAL TsardomOfRussia Moscow
CHANGE_CAPITAL TsardomOfRussia Moscow
CHANGE_CAPITAL ColonialBrazil Salvador
CHANGE_CAPITAL TsardomOfRussia SaintPetersburg
RENAME TsardomOfRussia RussianEmpire
CHANGE_CAPITAL RussianEmpire Moscow
CHANGE_CAPITAL RussianEmpire SaintPetersburg
CHANGE_CAPITAL ColonialBrazil RioDeJaneiro
DUMP
RENAME ColonialBrazil EmpireOfBrazil
ABOUT RussianEmpire
RENAME EmpireOfBrazil UnitedStatesOfBrazil
CHANGE_CAPITAL RussianEmpire Petrograd
RENAME RussianEmpire RussianRepublic
RENAME RussianRepublic USSR
CHANGE_CAPITAL USSR Moscow
CHANGE_CAPITAL UnitedStatesOfBrazil Brasilia
RENAME UnitedStatesOfBrazil FederativeRepublicOfBrazil
ABOUT RussianEmpire
DUMP
RENAME USSR USSR

Вывод:
Incorrect rename, skip
Country FarFarAway doesn't exist
There are no countries in the world
Introduce new country TsardomOfRussia with capital Moscow
Country TsardomOfRussia hasn't changed its capital
Introduce new country ColonialBrazil with capital Salvador
Country TsardomOfRussia has changed its capital from Moscow to SaintPetersburg
Country TsardomOfRussia with capital SaintPetersburg has been renamed to RussianEmpire
Country RussianEmpire has changed its capital from SaintPetersburg to Moscow
Country RussianEmpire has changed its capital from Moscow to SaintPetersburg
Country ColonialBrazil has changed its capital from Salvador to RioDeJaneiro
ColonialBrazil/RioDeJaneiro RussianEmpire/SaintPetersburg
Country ColonialBrazil with capital RioDeJaneiro has been renamed to EmpireOfBrazil
Country RussianEmpire has capital SaintPetersburg
Country EmpireOfBrazil with capital RioDeJaneiro has been renamed to UnitedStatesOfBrazil
Country RussianEmpire has changed its capital from SaintPetersburg to Petrograd
Country RussianEmpire with capital Petrograd has been renamed to RussianRepublic
Country RussianRepublic with capital Petrograd has been renamed to USSR
Country USSR has changed its capital from Petrograd to Moscow
Country UnitedStatesOfBrazil has changed its capital from RioDeJaneiro to Brasilia
Country UnitedStatesOfBrazil with capital Brasilia has been renamed to FederativeRepublicOfBrazil
Country RussianEmpire doesn't exist
FederativeRepublicOfBrazil/Brasilia USSR/Moscow
Incorrect rename, skip
*/