
#include <iostream>
#include <exception>
using namespace std;

class Rational {
    // Вставьте сюда реализацию класса Rational
public:
    Rational() {
        // Реализуйте конструктор по умолчанию
        n = 0;
        d = 1;
    }

    Rational(const int& numerator, const int& denominator) {
        // Реализуйте конструктор
        
        // Zero division check
        if (denominator == 0) {
            throw invalid_argument("zero denominator");
        }

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
    if (b == Rational(0, 1)) {
        throw domain_error("zero division");
    }
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

// Вставьте сюда реализацию operator / для класса Rational

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}

/* MIPT and Yandex implementation:
#include <iostream>
#include <exception>

using namespace std;

int GreatestCommonDivisor(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return GreatestCommonDivisor(b, a % b);
    }
}

class Rational {
public:
    Rational() {
        numerator = 0;
        denominator = 1;
    }
    Rational(int new_numerator, int new_denominator) {
        if (new_denominator == 0) {
            // бросаем исключение в случае нулевого знаменателя
        throw invalid_argument("");
        }
        const int gcd = GreatestCommonDivisor(new_numerator, new_denominator);
        numerator = new_numerator / gcd;
        denominator = new_denominator / gcd;
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

Rational operator * (const Rational& lhs, const Rational& rhs) {
    return {
        lhs.Numerator() * rhs.Numerator(),
        lhs.Denominator() * rhs.Denominator()
    };
}

Rational operator / (const Rational& lhs, const Rational& rhs) {
    // проверяем делитель на 0 (что равносильно проверке на 0 его числителя)
    if (rhs.Numerator() == 0) {
        throw domain_error("");
    }
    return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}
*/



/* Task:
Вспомним класс Rational, который мы реализовали в задачах, посвящённых перегрузке операторов. 
Там специально говорилось, что в тестах объекты класса Rational никогда не создаются с нулевым
знаменателем и никогда не выполняется деление на ноль. Настало время избавиться от этого ограничения 
и научиться обрабатывать нулевой знаменатель и деление на ноль. В этой задаче вам предстоит это сделать. 

Поменяйте реализацию конструктора класса Rational так, чтобы он выбрасывал исключение invalid_argument, 
если знаменатель равен нулю. Кроме того, переделайте реализацию оператора деления для класса Rational 
так, чтобы он выбрасывал исключение domain_error, если делитель равен нулю. 

Напомним, что вам надо реализовать интерфейс

class Rational {
public:
    Rational();
    Rational(int numerator, int denominator);

    int Numerator() const;
    int Denominator() const;
};

и оператор деления для класса Rational

Rational operator / (const Rational& lhs, const Rational& rhs);

Так же, как и в задачах на перегрузку операторов, вам будет предложен файл с заготовкой кода. 
Функция main в этом файле содержит ряд юнит-тестов, которые позволят вам проверить свою реализацию. 
При проверке вашего решения оно будет тестироваться на более полном наборе тестов, так что успешное 
прохождение всех юнит-тестов не гарантирует, что ваша реализация будет зачтена.

Шаблон программы:

rational_throw.cpp
*/