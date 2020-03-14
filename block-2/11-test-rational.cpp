#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <limits>

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
class Rational {
public:
    // Вы можете вставлять сюда различные реализации,
    // чтобы проверить, что ваши тесты пропускают корректный код
    // и ловят некорректный

    Rational();
    Rational(int numerator, int denominator) {
    }

    int Numerator() const {
    }

    int Denominator() const {
    }
};
*/

// один из способов вычисления наибольшего общего делителя (НОД) — рекурсивный:
// вместо цикла функция будет вызывать себя же, но с другими аргументами
int GreatestCommonDivisor(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return GreatestCommonDivisor(b, a % b);
    }
}

class Rational {
public:
    Rational() {  // дробь по умолчанию — 0/1
        numerator = 0;
        denominator = 1;
    }
    Rational(int new_numerator, int new_denominator) {
        const int gcd = GreatestCommonDivisor(new_numerator, new_denominator);
        // сократим дробь, разделив числитель и знаменатель на их НОД
        numerator = new_numerator / gcd;
        denominator = new_denominator / gcd;
        // знаменатель должен быть положительным
        if (denominator < 0) {
            denominator = -denominator;
            numerator = -numerator;
        }
    }

    int Numerator() const {
        return numerator;
    }

    int Denominator() const {
        return denominator;
    }

private:
    int numerator;
    int denominator;
};

// поскольку дроби сокращены, достаточно сравнить числители и знаменатели
bool operator == (const Rational& lhs, const Rational& rhs) {
    return lhs.Numerator() == rhs.Numerator() &&
        lhs.Denominator() == rhs.Denominator();
}

// используем обычную формулу сложения дробей, основанную на приведении слагаемых к общему знаменателю
Rational operator + (const Rational& lhs, const Rational& rhs) {
    return {
        lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
        lhs.Denominator() * rhs.Denominator()
    };
}

// вычитание реализуем аналогично сложению
// дублирования кода можно было избежать, определив для класса Rational операцию унарного минуса: тогда разность lhs и rhs можно было бы вычислить           как lhs + (-rhs)
Rational operator - (const Rational& lhs, const Rational& rhs) {
    return {
        lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
        lhs.Denominator() * rhs.Denominator()
  };
}

Rational operator * (const Rational& lhs, const Rational& rhs) {
    return {
        lhs.Numerator() * rhs.Numerator(),
        lhs.Denominator() * rhs.Denominator()
    };
}

// деление равносильно умножению на обратную («перевёрнутую») дробь
Rational operator / (const Rational& lhs, const Rational& rhs) {
    return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}

istream& operator >> (istream& is, Rational& r) {
    int n, d;
    char c;
  
    if (is) {
        is >> n >> c >> d;
        if (is && c == '/') {
            r = Rational(n, d);
        }
    }
  
    return is;
}

ostream& operator << (ostream& os, const Rational& r) {
    return os << r.Numerator() << '/' << r.Denominator();
}

// чтобы сравнить lhs с rhs, сравним их разность с нулём, что равносильно сравнению с нулём числителя
bool operator < (const Rational& lhs, const Rational& rhs) {
    return (lhs - rhs).Numerator() < 0;
}

void TestConstructor() {
    AssertEqual(Rational().Numerator(), 0, "Zero numerator");
    AssertEqual(Rational().Denominator(), 1, "1 denominator");
}

void TestFractionReduction() {
    Rational test(6, 8);
    AssertEqual(test.Numerator(), 3, "6 to 3 reduction in numerator");
    AssertEqual(test.Denominator(), 4, "8 to 4 reduction in denominator");
    
    Rational test2(2147483646, 1073741823);
    AssertEqual(test2.Numerator(), 2, "Max int num");
    AssertEqual(test2.Denominator(), 1, "Half max int denom");

    Rational test3(1, 2);
    AssertEqual(test3.Numerator(), 1, "Same num");
    AssertEqual(test3.Denominator(), 2, "Same denom");

    Rational test4(8, 12);
    AssertEqual(test4.Numerator(), 2, "8/12 - 2/3 num");
    AssertEqual(test4.Denominator(), 3, "8/12 - 2/3 denom");

    Rational test5(4, -6);
    AssertEqual(test5.Numerator(), -2, "4/-6 - -2/3 num");
    AssertEqual(test5.Denominator(), 3, "4/-6 - -2/3 denom");

    AssertEqual(Rational(0, 15).Numerator(), 0, "0/15 - 0/1 num");
    AssertEqual(Rational(0, 15).Denominator(), 1, "0/15 - 0/1 denom");
}

void TestNegative() {
    Rational test(-1, 2);
    AssertEqual(test.Numerator(), -1, "negative num - negative num");
    AssertEqual(test.Denominator(), 2, "negative num - positive denom");

    Rational test2(1, -2);
    AssertEqual(test2.Numerator(), -1, "negative denom - negative num");
    AssertEqual(test2.Denominator(), 2, "negative denom - positive denom");
}

void TestPositive() {
    Rational test(1, 2);
    AssertEqual(test.Numerator(), 1, "positive num - positive num");
    AssertEqual(test.Denominator(), 2, "positive denom - positive denom");

    Rational test2(-1, -2);
    AssertEqual(test2.Numerator(), 1, "negative num - positive num");
    AssertEqual(test2.Denominator(), 2, "negative denom - positive denom");

    Rational test3(-2, -3);
    AssertEqual(test3.Numerator(), 2, "negative num - positive num");
    AssertEqual(test3.Denominator(), 3, "negative denom - positive denom");
}

void TestAll() {
    TestRunner runner;
    runner.RunTest(TestConstructor, "TestConstructor");
    runner.RunTest(TestFractionReduction, "TestFractionDeduction");
    runner.RunTest(TestNegative, "TestNegative");
    runner.RunTest(TestPositive, "TestPositive");
}

int main() {
    TestAll();
    // добавьте сюда свои тесты
    cerr << numeric_limits<int>::max() << endl;
    cerr << numeric_limits<int>::min() << endl;
    return 0;
}

/* MIPT and Yandex implementation:
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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

void TestPredefined() {
    AssertEqual(Rational(1, 1).Numerator(), 1, "Canonical form of 1/1 is 1/1");
    AssertEqual(Rational(1, 1).Denominator(), 1, "Canonical form of 1/1 is 1/1");
    AssertEqual(Rational(3, 5).Numerator(), 3, "Canonical form of 3/5 is 3/5");
    AssertEqual(Rational(3, 5).Denominator(), 5, "Canonical form of 3/5 is 3/5");
    AssertEqual(Rational(2147483647, 2147483647).Numerator(), 1, "Canonical form of 2147483647/2147483647 is 1/1");
    AssertEqual(Rational(2147483647, 2147483647).Denominator(), 1, "Canonical form of 2147483647/2147483647 is 1/1");
    AssertEqual(Rational(-5, 4).Numerator(), -5, "Canonical form of -5/4 is -5/4");
    AssertEqual(Rational(-5, 4).Denominator(), 4, "Canonical form of -5/4 is -5/4");
    AssertEqual(Rational(5, -4).Numerator(), -5, "Canonical form of 5/-4 is -5/4");
    AssertEqual(Rational(5, -4).Denominator(), 4, "Canonical form of 5/-4 is -5/4");
    AssertEqual(Rational(-6, -2).Numerator(), 3, "Canonical form of -6/-2 is 3/1");
    AssertEqual(Rational(-6, -2).Denominator(), 1, "Canonical form of -6/-2 is 3/1");
    AssertEqual(Rational(21, 56).Numerator(), 3, "Canonical form of 21/56 is 3/8");
    AssertEqual(Rational(21, 56).Denominator(), 8, "Canonical form of 21/56 is 3/8");
    AssertEqual(Rational(0, 100).Numerator(), 0, "Canonical form of 0/100 is 0/1");
    AssertEqual(Rational(0, 100).Denominator(), 1, "Canonical form of 0/100 is 0/1");
    AssertEqual(Rational().Numerator(), 0, "Canonical form of default constructed is 0/1");
    AssertEqual(Rational().Denominator(), 1, "Canonical form of default constructed is 0/1");
}

int main() {
    TestRunner runner;
    runner.RunTest(TestPredefined, "TestPredefined");
    return 0;
}
*/



/* Task:
Класс Rational представляет собой рациональное число и имеет следующий интерфейс

class Rational {
public:
    Rational();
    Rational(int numerator, int denominator);

    int Numerator() const;
    int Denominator() const;
};

Список требований, предъявляемых к реализации интерфейса класса Rational:

1. Конструктор по умолчанию должен создавать дробь с числителем 0 и знаменателем 1.
2. При конструировании объекта класса Rational с параметрами p и q должно выполняться 
сокращение дроби p/q.
3. Если дробь p/q отрицательная, то объект Rational(p, q) должен иметь отрицательный 
числитель и положительный знаменатель.
4. Если дробь p/q положительная, то объект Rational(p, q) должен иметь положительные 
числитель и знаменатель (обратите внимание на случай Rational(-2, -3)).
5. Если числитель дроби равен нулю, то знаменатель должен быть равен 1.

Разработайте набор юнит-тестов, которые будут проверять корректность реализации 
класса Rational. 
Тестировать случай, когда знаменатель равен нулю, не надо.

Начать работу вы можете с шаблона, который содержит наш фреймворк юнит-тестов и 
заготовку класса Rational.

test_rational.cpp
Примечание
Перед отправкой вашего файла убедитесь, что он не содержит класса Rational. В 
противном случае вы получите ошибку компиляции. Наша тестирующая система умеет 
игнорировать функции в файлах (поэтому, например, в задаче "Тесты для функции 
IsPalindrom" необязательно удалять функцию IsPalindrom), но не умеет это делать 
для классов.
*/