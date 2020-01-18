
#include <iostream>
#include <string>
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
            throw invalid_argument("Invalid argument");
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
        throw domain_error("Division by zero");
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
}

int main() {
    
    Rational lhs;
    Rational rhs;
    char operation;

    try {
        cin >> lhs >> operation >> rhs;
    } catch (invalid_argument& ex) {
        cout << ex.what() << endl;
        return 0;
    }

    if (operation == '+') {
        cout << lhs + rhs << endl;
    } else if (operation == '-') {
        cout << lhs - rhs << endl;
    } else if (operation == '*') {
        cout << lhs * rhs << endl;
    } else if (operation == '/') {
        try {
            cout << lhs / rhs;
        } catch (domain_error& er) {
            cout << er.what() << endl;
        }
    }
    
    return 0;
}

/* MIPT and Yandex implementation:
Not provided. And it is ok since the implementation of this task requires ~ 3 lines of code. 

*/



/* Task:
Итак, теперь у нас с вами есть полноценный тип для представления обыкновенных дробей: класс Rational 
интегрирован в язык с помощью перегрузки операторов и не позволяет выполнять некорректные операции 
за счёт выбрасывания исключений. Давайте на основе класса Rational создадим простой калькулятор для 
обыкновенных дробей.

Вам надо написать программу, которая считывает из стандартного ввода одну строку в формате ДРОБЬ_1 
операция ДРОБЬ_2. ДРОБЬ_1 и ДРОБЬ_2 имеют формат X/Y, где X — целое, а Y — целое неотрицательное число.
операция — это один из символов '+', '-', '*', '/'.

Если ДРОБЬ_1 или ДРОБЬ_2 является некорректной обыкновенной дробью, ваша программа должна вывести в 
стандартный вывод сообщение "Invalid argument". Если считанная операция — это деление на ноль, выведите 
в стандартный вывод сообщение "Division by zero". В противном случае выведите результат операции.

Пример
stdin	    stdout
1/2 + 1/3	5/6
1/2 + 5/0	Invalid argument
4/5 / 0/8	Division by zero

*/