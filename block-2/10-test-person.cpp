#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <random>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

/*
class Person {
public:
    // Вы можете вставлять сюда различные реализации класса,
    // чтобы проверить, что ваши тесты пропускают корректный код
    // и ловят некорректный
    void ChangeFirstName(int year, const string& first_name) {
    }
    void ChangeLastName(int year, const string& last_name) {
    }
    string GetFullName(int year) {
    }
};
*/

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

void TestFirstName() {
    Person person;
    person.ChangeFirstName(1970, "Alex");
    person.ChangeFirstName(2020, "Stan");
    person.ChangeFirstName(1965, "Polina");
    for (const int& year : {1900, 1965, 1990}) {
        cerr << "Correct is: "<< person.GetFullName(year) << endl;
    }
    AssertEqual(person.GetFullName(1900), "Incognito", "No names test");
    AssertEqual(person.GetFullName(1965), "Polina with unknown last name", "At the year of change test");
    AssertEqual(person.GetFullName(1990), "Alex with unknown last name", "After the year of change test");
    
    for (int year : {1969, 1970}) {
        cerr << "Correct is: " << person.GetFullName(year) << endl;
    }
    AssertEqual(person.GetFullName(1969), "Polina with unknown last name", "Between changes test 1");
    AssertEqual(person.GetFullName(1970), "Alex with unknown last name", "Between changes test 2");
}

void TestLastName() {
    Person person;
    person.ChangeLastName(1970, "Alex");
    person.ChangeLastName(2020, "Stan");
    person.ChangeLastName(1965, "Polina");
    for (const int& year : {1900, 1965, 1990}) {
        cerr << "Correct is: "<< person.GetFullName(year) << endl;
    }
    AssertEqual(person.GetFullName(1900), "Incognito", "No names test");
    AssertEqual(person.GetFullName(1965), "Polina with unknown first name", "At the year of change test");
    AssertEqual(person.GetFullName(1990), "Alex with unknown first name", "After the year of change test");
    
    person.ChangeLastName(1971, "Paul");
    for (int year : {1969, 1971}) {
        cerr << "Correct is: " << person.GetFullName(year) << endl;
    }
    AssertEqual(person.GetFullName(1969), "Polina with unknown first name", "Between changes test 1");
    AssertEqual(person.GetFullName(1971), "Paul with unknown first name", "Between changes test 2");
    person.ChangeLastName(1968, "Cooper");
    for (int year : {1969, 1970}) {
        cerr << "Correct is : " << person.GetFullName(year) << endl;
    }
    AssertEqual(person.GetFullName(1969), "Cooper with unknown first name", "Last test 1");
    AssertEqual(person.GetFullName(1970), "Alex with unknown first name", "Last test 2");
}

void TestFirstAndLastName() {
    // First + 2 last
    Person person;
    person.ChangeFirstName(1970, "Alex");
    person.ChangeLastName(1970, "Smith");
    person.ChangeFirstName(2020, "Stan");
    person.ChangeFirstName(1965, "Polina");
    for (const int& year : {1900, 1965, 1990}) {
        cerr << "Correct is: "<< person.GetFullName(year) << endl;
    }
    AssertEqual(person.GetFullName(1900), "Incognito", "No names test");
    AssertEqual(person.GetFullName(1965), "Polina with unknown last name", "At the year of change test");
    AssertEqual(person.GetFullName(1990), "Alex Smith", "After the year of change test");
    
    for (int year : {1969, 1970}) {
        cerr << "Correct is: " << person.GetFullName(year) << endl;
    }
    AssertEqual(person.GetFullName(1969), "Polina with unknown last name", "Between changes test 1");
    AssertEqual(person.GetFullName(1970), "Alex Smith", "Between changes test 2");

    person.ChangeLastName(1979, "Cooper");
    AssertEqual(person.GetFullName(1979), "Alex Cooper", "Additional change of last name after asserts");
}

void TestAll() {
    TestRunner runner;
    runner.RunTest(TestFirstName, "TestFirstName");
    runner.RunTest(TestLastName, "TestLastName");
    runner.RunTest(TestFirstAndLastName, "TestFirstAndLastName");
}

int main() {
    // добавьте сюда свои тесты
    TestAll();
    return 0;
}

/* MIPT and Yandex implementation (same):
#include <iostream>
#include <map>
#include <ostream>
#include <random>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream &operator<<(ostream &os, const vector<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream &operator<<(ostream &os, const set<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << "{";
    bool first = true;
    for (const auto &kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template <class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string &hint) { AssertEqual(b, true, hint); }

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string &test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception &e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

void TestPredefinedLastNameFirst() {
    Person person;

    person.ChangeLastName(1965, "Sergeeva");
    person.ChangeFirstName(1967, "Polina");

    AssertEqual(person.GetFullName(1964), "Incognito");
    AssertEqual(person.GetFullName(1966), "Sergeeva with unknown first name");
    AssertEqual(person.GetFullName(1968), "Polina Sergeeva");
}

void TestPredefined() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");

    AssertEqual(person.GetFullName(1964), "Incognito");
    AssertEqual(person.GetFullName(1966), "Polina with unknown last name");
    AssertEqual(person.GetFullName(1968), "Polina Sergeeva");

    person.ChangeFirstName(1969, "Appolinaria");
    AssertEqual(person.GetFullName(1968), "Polina Sergeeva");
    AssertEqual(person.GetFullName(1969), "Appolinaria Sergeeva");
    AssertEqual(person.GetFullName(1970), "Appolinaria Sergeeva");

    person.ChangeLastName(1968, "Volkova");
    AssertEqual(person.GetFullName(1967), "Polina Sergeeva");
    AssertEqual(person.GetFullName(1968), "Polina Volkova");
    AssertEqual(person.GetFullName(1969), "Appolinaria Volkova");

}

int main() {
    TestRunner runner;
    runner.RunTest(TestPredefined, "TestPredefined");
    runner.RunTest(TestPredefinedLastNameFirst, "TestPredefinedLastNameFirst");
    return 0;
}
*/



/* Task:
Задача
В первом курсе «Белый пояс по С++» у нас была задача «Имена и фамилии — 1». 
В ней надо было разработать класс Person, поддерживающий историю изменений 
человеком своих фамилии и имени. В данной задаче вам надо разработать 
юнит-тесты на реализацию класса Person. При разработке тестов учитывайте 
ограничения, которые накладывает на класс Person условие задачи «Имена и 
фамилии — 1».

Начать работу вы можете с шаблона, который содержит наш фреймворк 
юнит-тестов и заготовку класса.

test_person.cpp

Условие задачи «Имена и фамилии — 1»
Реализуйте класс для человека, поддерживающий историю изменений человеком 
своих фамилии и имени.

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

Считайте, что в каждый год может произойти не более одного изменения фамилии 
и не более одного изменения имени. При этом с течением времени могут открываться 
всё новые факты из прошлого человека, поэтому года́ в последовательных вызовах 
методов ChangeLastName и ChangeFirstName не обязаны возрастать.

Гарантируется, что все имена и фамилии непусты.

Строка, возвращаемая методом GetFullName, должна содержать разделённые одним 
пробелом имя и фамилию человека по состоянию на конец данного года.

Если к данному году не случилось ни одного изменения фамилии и имени, верните 
строку "Incognito".
Если к данному году случилось изменение фамилии, но не было ни одного изменения 
имени, верните "last_name with unknown first name".
Если к данному году случилось изменение имени, но не было ни одного изменения 
фамилии, верните "first_name with unknown last name".

Примечание
Перед отправкой вашего файла убедитесь, что он не содержит класса Person. 
В противном случае вы получите ошибку компиляции. Наша тестирующая система 
умеет игнорировать функции в файлах (поэтому, например, в задаче "Тесты для 
функции IsPalindrom" необязательно удалять функцию IsPalindrom), но не умеет 
это делать для классов.
*/