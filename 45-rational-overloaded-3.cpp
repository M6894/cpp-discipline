
#include <iostream>
using namespace std;

class Rational {
    // Вставьте сюда реализацию класса Rational из первой части
    public:
    Rational() {
        // Реализуйте конструктор по умолчанию
        // Нет необходимости в реализации конструктора по умолчанию
    }

    Rational(int numerator, int denominator) {
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
    int n = 0;
    int d = 1;
};

// Реализуйте для класса Rational операторы ==, + и -

// ==
bool operator==(const Rational& a, const Rational& b) {
    if (a.Numerator() == b.Numerator() && a.Denominator() == b.Denominator()) {
        return true;
    }
    return false;
}

// +
Rational operator+(Rational a, Rational b) {
    if (a.Denominator() != b.Denominator()) {
        int new_n1 = a.Numerator() * b.Denominator();
        int new_n2 = b.Numerator() * a.Denominator();
        int new_d = a.Denominator() * b.Denominator();

        Rational c(new_n1 + new_n2, new_d);
        return c;
    } else {
        Rational c(a.Numerator() + b.Numerator(), a.Denominator());
        return c;
    }
}

// -
Rational operator-(const Rational& a, const Rational& b) {
    if (a.Denominator() != b.Denominator()) {
        int new_n1 = a.Numerator() * b.Denominator();
        int new_n2 = b.Numerator() * a.Denominator();
        int new_d = a.Denominator() * b.Denominator();

        // Rational c(new_n1 - new_n2, new_d);
        return {new_n1 - new_n2, new_d};
    } else {
        Rational c(a.Numerator() - b.Numerator(), a.Denominator());
        return c;
    }
}

// Вставьте сюда реализацию operator == для класса Rational из второй части
// Реализуйте для класса Rational операторы * и /
Rational operator*(const Rational& a, const Rational& b) {
    Rational c(a.Numerator() * b.Numerator(), a.Denominator() * b.Denominator());
    return c;
}

Rational operator/(const Rational& a, const Rational& b) {
    Rational c(a.Numerator() * b.Denominator(), a.Denominator() * b.Numerator());
    return c;
}

int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}

/* MIPT and Yandex implementation:
Not provided.
*/



/* Task:
Аналогично предыдущей части, реализуйте операторы * и /. Например, следующий 
код должен быть валидным:

const Rational r = Rational(1, 2) * Rational(1, 3) / Rational(1, 4);
if (r == Rational(2, 3)) {
    cout << "equal";
}

Как и в предыдущем случае, гарантируется, что во всех тестах, на которых будет 
тестироваться ваша реализация, числители и знаменатели ВСЕХ дробей (как исходных, 
так и получившихся в результате соответствующих арифметических операций) будут 
укладываться в диапазон типа int.

Кроме того, гарантируется, что ни в одном из тестов, на которых будет тестироваться 
ваша реализация, не будет выполняться деление на ноль.

Шаблон программы:

rational_mult_div.cpp
*/