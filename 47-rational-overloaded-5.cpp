
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

class Rational {
    // Вставьте сюда реализацию класса Rational из первой части
public:
    Rational() {
        // Реализуйте конструктор по умолчанию
        n = 0;
        d = 1;
    }

    Rational(const int& numerator, const int& denominator) {
        // Реализуйте конструктор
        n = numerator;
        d = denominator;

        // Находим наибольший общий делитель
        int first = abs(n);
        int second = abs(d);
        while (first != 0 && second != 0) {
            if (first > second) {
                first -= second;
            } else {
                second -= first;
            }
        }
        
        // Сокращаем с его использованием
        n /= (first + second);
        d /= (first + second);

        // Обрабатываем минусовые значения
        if (n < 0 && d < 0) {
            n = abs(n);
            d = abs(d);
        } else if (d < 0) {
            d = abs(d);
            n *= -1;
        }

        // Сокращаем 0/any-number до 0/1
        if (n == 0) {
            d = 1;
        }
        
        // Проверка получившихся значений
        // cout << n << "/" << d << endl; 
    }

    int Numerator() const {
        // Реализуйте этот метод
        return n;
    }

    int Denominator() const {
        // Реализуйте этот метод
        return d;
    }

private:
    // Добавьте поля
    int n;
    int d;
};

// Реализуйте для класса Rational операторы ==, + и -

// ==
bool operator==(const Rational& a, const Rational& b) {
    return a.Numerator() == b.Numerator() && a.Denominator() == b.Denominator();
}

// +
Rational operator+(const Rational& a, const Rational& b) {
    if (a.Denominator() != b.Denominator()) {
        int new_n1 = a.Numerator() * b.Denominator();
        int new_n2 = b.Numerator() * a.Denominator();
        int new_d = a.Denominator() * b.Denominator();

        return {new_n1 + new_n2, new_d};
    } else {
        return {a.Numerator() + b.Numerator(), a.Denominator()};
    }
}

// -
Rational operator-(const Rational& a, const Rational& b) {
    if (a.Denominator() != b.Denominator()) {
        int new_n1 = a.Numerator() * b.Denominator();
        int new_n2 = b.Numerator() * a.Denominator();
        int new_d = a.Denominator() * b.Denominator();

        return {new_n1 - new_n2, new_d};
    } else {
        return {a.Numerator() - b.Numerator(), a.Denominator()};
    }
}

// Вставьте сюда реализацию operator == для класса Rational из второй части
// Реализуйте для класса Rational операторы * и /
Rational operator*(const Rational& a, const Rational& b) {
    return {a.Numerator() * b.Numerator(), a.Denominator() * b.Denominator()};
}

Rational operator/(const Rational& a, const Rational& b) {
    return {a.Numerator() * b.Denominator(), a.Denominator() * b.Numerator()};
}

// Вставьте сюда реализацию operator == для класса Rational из второй части
// Реализуйте для класса Rational операторы << и >>

ostream& operator<<(ostream& output, const Rational& data) {
    output << data.Numerator() << "/" << data.Denominator();
    return output;
}

istream& operator>>(istream& input, Rational& data) {
    int n = 0;
    int d = 1;
    if (input) {
        input >> n;
        input.ignore(1);
        input >> d;
        data = {n, d};    
    }
    return input;
}

// Вставьте сюда реализацию operator == для класса Rational из второй части
// Реализуйте для класса Rational оператор(ы), необходимые для использования его
// в качестве ключа map'а и элемента set'а

bool operator<(const Rational& a, const Rational& b) {
    // Или можно так: return a.Numerator() / a.Denominator() < b.Numerator() / b.Denominator() ? true : false; 
    if (a.Denominator() != b.Denominator()) {
        int new_n1 = a.Numerator() * b.Denominator();
        int new_n2 = b.Numerator() * a.Denominator();
        int new_d = a.Denominator() * b.Denominator();

        return new_n1 < new_n2;
    } else {
        return a.Numerator() < b.Numerator();
    }
    // return a.Numerator() / a.Denominator() < b.Numerator() / b.Denominator();
}


int main() {

    const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
    if (rs.size() != 3) {
        // cout << rs.size() << endl;
        cout << "Wrong amount of items in the set" << endl;
        return 1;
    }

    vector<Rational> v;
    for (auto x : rs) {
        v.push_back(x);
    }
    if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
        cout << "Rationals comparison works incorrectly" << endl;
        return 2;
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}

/* MIPT and Yandex implementation:
#include <iostream>

using namespace std;

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
*/



/* Task:
Часть 5
Наконец, вам нужно реализовать возможность использовать объекты класса 
Rational в качестве элементов контейнера set и ключей в контейнере map. Пример:

set<Rational> rationals;
rationals.insert(Rational(1, 2));
rationals.insert(Rational(1, 3));

map<Rational, string> name;
name[Rational(1, 2)] = "одна вторая";

Шаблон программы:

rational_map.cpp
*/