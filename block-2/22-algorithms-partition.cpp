// 22
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

enum class Gender {
    FEMALE,
    MALE
};

struct Person {
    int age;  // возраст
    Gender gender;  // пол
    bool is_employed;  // имеет ли работу
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
    if (range_begin == range_end) {
        return 0;
    }
    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = begin(range_copy) + range_copy.size() / 2;
    nth_element(
        begin(range_copy), middle, end(range_copy),
        [](const Person& lhs, const Person& rhs) {
            return lhs.age < rhs.age;
        }
    );
    return middle->age;
}

void PrintPersonStats(const string& caption, vector<Person>& persons, vector<Person>::iterator it) {
    cout << caption << ComputeMedianAge(persons.begin(), it) << endl;
}

// Please find preferred implementation in comments below
void PrintStats(vector<Person> persons) {
    // All 
    PrintPersonStats("Median age = ", persons, persons.end());
    // Females 
    PrintPersonStats("Median age for females = ", persons, partition(persons.begin(), persons.end(), 
        [](auto& person) { return person.gender == Gender::FEMALE; }));
    // Males 
    PrintPersonStats("Median age for males = ", persons, partition(persons.begin(), persons.end(), 
        [](auto& person) { return person.gender == Gender::MALE; }));   
    // Females employed 
    PrintPersonStats("Median age for employed females = ", persons, 
        partition(persons.begin(), persons.end(), 
        [](auto& person) { return (person.gender == Gender::FEMALE && person.is_employed); }));       
    // Females unemployed 
    PrintPersonStats("Median age for unemployed females = ", persons, 
        partition(persons.begin(), persons.end(), 
        [](auto& person) { return (person.gender == Gender::FEMALE && !person.is_employed); }));
    // Males employed 
    PrintPersonStats("Median age for employed males = ", persons, 
        partition(persons.begin(), persons.end(), 
        [](auto& person) { return (person.gender == Gender::MALE && person.is_employed); }));       
    // Males unemployed 
    PrintPersonStats("Median age for unemployed males = ", persons, 
        partition(persons.begin(), persons.end(), 
        [](auto& person) { return (person.gender == Gender::MALE && !person.is_employed); }));
}

int main() {
    vector<Person> persons = {
        {31, Gender::MALE, false},
        {40, Gender::FEMALE, true},
        {24, Gender::MALE, true},
        {20, Gender::FEMALE, true},
        {80, Gender::FEMALE, false},
        {78, Gender::MALE, false},
        {10, Gender::FEMALE, false},
        {55, Gender::MALE, true},
    };
    PrintStats(persons);
    return 0;
}

/* MIPT and Yandex implementation (preferred):
void PrintStats(vector<Person> persons) {
    // Преобразуем порядок людей к следующему:
    //                  persons
    //                 /      \
    //          females        males
    //         /       \     /      \
    //      empl.  unempl. empl.   unempl.
    auto females_end = partition(
        begin(persons), end(persons), [](const Person& p) {
            return p.gender == Gender::FEMALE;
        }
    );
    auto employed_females_end = partition(
        begin(persons), females_end, [](const Person& p) {
            return p.is_employed;
        }
    );
    auto employed_males_end = partition(
        females_end, end(persons), [](const Person& p) {
            return p.is_employed;
        }
    );

    // Теперь интересующие нас группы находятся в векторе непрерывно
    cout << "Median age = "
         << ComputeMedianAge(begin(persons), end(persons))          << endl;
    cout << "Median age for females = "
         << ComputeMedianAge(begin(persons), females_end)           << endl;
    cout << "Median age for males = "
         << ComputeMedianAge(females_end, end(persons))             << endl;
    cout << "Median age for employed females = "
         << ComputeMedianAge(begin(persons),  employed_females_end) << endl;
    cout << "Median age for unemployed females = "
         << ComputeMedianAge(employed_females_end, females_end)     << endl;
    cout << "Median age for employed males = "
         << ComputeMedianAge(females_end, employed_males_end)       << endl;
    cout << "Median age for unemployed males = "
         << ComputeMedianAge(employed_males_end, end(persons))      << endl;
}
*/



/* Task:
В этой задаче вам необходимо вычислить различные демографические показатели для группы людей. 
Человек представляется структурой Person:

struct Person {
    int age;  // возраст
    Gender gender;  // пол
    bool is_employed;  // имеет ли работу
};

Тип Gender определён следующим образом:

enum class Gender {
    FEMALE,
    MALE
};

Вам необходимо написать функцию PrintStats, получающую вектор людей, вычисляющую и выводящую 
медианный возраст для каждой из следующих групп людей:

все люди;
все женщины;
все мужчины;
все занятые женщины;
все безработные женщины;
все занятые мужчины;
все безработные мужчины.
Все 7 чисел нужно вывести в строгом соответствии с форматом (см. пример).

void PrintStats(vector<Person> persons);

Принимая вектор по значению (а не по константной ссылке), вы получаете возможность модифицировать 
его копию произвольным образом и тем самым проще произвести вычисления.

Подсказка
Используйте алгоритм partition.

Вычисление медианного возраста
Для вычисления медианного возраста группы людей вы должны использовать функцию ComputeMedianAge:

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end);

Эту функцию не нужно реализовывать самостоятельно: мы реализовали её за вас и автоматически добавим 
к каждому вашему решению.

Функцию ComputeMedianAge можно вызвать и для пустого набора людей: её результат в этом случае и 
нужно считать медианным возрастом пустого набора людей.

Пример кода

// Это пример функции, его не нужно отправлять вместе с функцией PrintStats
template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
    if (range_begin == range_end) {
        return 0;
    }
    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = begin(range_copy) + range_copy.size() / 2;
    nth_element(
        begin(range_copy), middle, end(range_copy),
        [](const Person& lhs, const Person& rhs) {
            return lhs.age < rhs.age;
        }
    );
    return middle->age;
}

void PrintStats(vector<Person> persons);

int main() {
    vector<Person> persons = {
        {31, Gender::MALE, false},
        {40, Gender::FEMALE, true},
        {24, Gender::MALE, true},
        {20, Gender::FEMALE, true},
        {80, Gender::FEMALE, false},
        {78, Gender::MALE, false},
        {10, Gender::FEMALE, false},
        {55, Gender::MALE, true},
    };
    PrintStats(persons);
    return 0;
}

Вывод

Median age = 40
Median age for females = 40
Median age for males = 55
Median age for employed females = 40
Median age for unemployed females = 80
Median age for employed males = 55
Median age for unemployed males = 78

Пояснение
В этой задаче вам надо прислать на проверку файл с реализацией функции PrintStats. Этот файл не 
должен содержать определения функции ComputeMedianAge и типов Person и Gender. В противном случае 
вы получите ошибку компиляции.

Гарантируется, что типы Person и Gender объявлены в точности так же, как в коде выше.
*/