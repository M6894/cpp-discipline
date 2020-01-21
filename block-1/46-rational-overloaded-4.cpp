
#include <iostream>
#include <sstream>
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

        Rational c(new_n1 - new_n2, new_d);
        return c;
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


int main() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input;
        Rational r1, r2;
        input >> r1 >> r2;
        cout << "Error " << r1 << " " << r2 << endl;
        return 3;
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }

    cout << "OK" << endl;
    return 0;
}

/* MIPT and Yandex implementation:
Not provided.
*/



/* Task:
Часть 4
В этой части вам нужно реализовать операторы ввода и вывода для класса Rational. 
В результате у вас должен работать, например, такой код

Rational r;
cin >> r;
cout << r;

Шаблон программы:

rational_io.cpp
*/