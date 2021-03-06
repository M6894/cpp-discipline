
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string name;
    string surname;    
    long long day = 0;
    long long month = 0;
    long long year = 0;
};

// cin version of the function
vector<Student> GetStudentsList() {
    vector<Student> result = {};
    int lines = 0;
    cin >> lines;
    for (int i = lines; i > 0; i--) {
        Student student;
        cin >> student.name >> student.surname >> student.day >> student.month >> student.year;
        result.push_back(student);
    }
    return result;
}

void PrintRequested(vector<Student> list) {
    int n = 0; // Number of requests
    cin >> n;
    for (int i = 0; i < n; i++) {
        string command = "";
        long long student_num = 0;
        cin >> command >> student_num;
        if (command == "date" && student_num <= list.size() && student_num > 0) {
            cout << list[student_num - 1].day << "." 
                 << list[student_num - 1].month << "." 
                 << list[student_num - 1].year << endl;
        } else if (command == "name" && student_num <= list.size() && student_num > 0) {
            cout << list[student_num - 1].name << " " 
                 << list[student_num - 1].surname << "\n";
        } else {
            cout << "bad request" << endl;
        }
    }
}

/* File version of the function
vector<Student> GetStudentsList(const string& source_path) {
    vector<Student> result = {};
    ifstream input(source_path);
    if (input.good()) {
        int lines = 0;
        input >> lines;
        for (int i = lines; i > 0; i--) {
            Student student;
            input >> student.name >> student.surname >> student.day >> student.month >> student.year;
            result.push_back(student);
        }
    }
}
*/

int main() {
    string source_path = ("input.txt");
    vector<Student> list = GetStudentsList();
    // cout << list.size() << endl;
    PrintRequested(list);

    return 0;
}

/* MIPT and Yandex implementation:
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string name;
    string birthday;
};

int main() {
    int n;
    cin >> n;

    string first_name, last_name, day, month, year;
    vector<Student> students;
    for (size_t i = 0; i < n; ++i) {
        cin >> first_name >> last_name >> day >> month >> year;
        students.push_back(Student{
            first_name + " " + last_name, day + "." + month + "." + year
        });
    }

    int m;
    cin >> m;
    string query;
    int student_number;

    for (int i = 0; i < m; ++i) {
        cin >> query >> student_number;
        --student_number;
        if (query == "name" && student_number >= 0 && student_number < n) {
            cout << students[student_number].name << endl;
        } else if (query == "date" && student_number >= 0 && student_number < n) {
            cout << students[student_number].birthday << endl;
        } else {
            cout << "bad request" << endl;
        }
    }

    return 0;
}
*/



/* Task:
Определите структуру «Студент» со следующими полями: имя, фамилия, день, месяц и год рождения. 
Создайте вектор из таких структур, заполните его из входных данных и затем по запросам выведите нужные поля.

Формат ввода
Первая строка содержит одно целое число N от 0 до 10000 — число студентов.

Далее идут N строк, каждая из которых содержит две строки длиной от 1 до 15 символов — 
имя и фамилию очередного студента, и три целых числа от 0 до 1000000000 — день, месяц и год рождения.

Следующая строка содержит одно целое число M от 0 до 10000 — число запросов.

Следующие M строк содержат строку длиной от 1 до 15 символов — запрос, и целое число от 0 до 
1000000000 — номер студента (нумерация начинается с 1).

Формат вывода

Для запроса вида name K, где K от 1 до N, выведите через пробел имя и фамилию K-го студента.

Для запроса вида date K, где K от 1 до N, выведите через точку день, месяц и год рождения K-го студента.

Для остальных запросов выведите bad request.

Пример ввода
3
Ivan Ivanov 1 1 1901
Petr Petrox 2 2 1902
Alexander Sidorov 3 3 1903
3
name 1
date 3
mark 5

Пример вывода
Ivan Ivanov
3.3.1903
bad request
*/