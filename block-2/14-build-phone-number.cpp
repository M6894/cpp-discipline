// 14
#include "14-build-phone-number.h" // must be phone_number.h, to pass the testing system
// #include "phone_number.h"

#include <string>
#include <iostream>
#include <sstream>
#include <exception>

using namespace std;

/* Принимает строку в формате +XXX-YYY-ZZZZZZ
    Часть от '+' до первого '-' - это код страны.
    Часть между первым и вторым символами '-' - код города
    Всё, что идёт после второго символа '-' - местный номер.
    Код страны, код города и местный номер не должны быть пустыми.
    Если строка не соответствует этому формату, нужно выбросить исключение invalid_argument. 
    Проверять, что номер содержит только цифры, не нужно.
    
    Примеры:
    * +7-495-111-22-33
    * +7-495-1112233
    * +323-22-460002
    * +1-2-coursera-cpp
    * 1-2-333 - некорректный номер - не начинается на '+'
    * +7-1233 - некорректный номер - есть только код страны и города
*/
PhoneNumber::PhoneNumber(const string &international_number) {
    istringstream ss(international_number);
    if (ss) {
        char ch;
        string tmp_country_code;
        string tmp_city_code;
        string tmp_num;
        bool ok = true;
        ok = ok && ss >> ch && ch == '+';
        ok = ok && getline(ss, tmp_country_code, '-') && !tmp_country_code.empty();
        ok = ok && getline(ss, tmp_city_code, '-') && !tmp_city_code.empty();
        ok = ok && getline(ss, tmp_num) && !tmp_num.empty();
        ok = ok && (ss.eof());
        if (ok) {
            country_code_ = tmp_country_code;
            city_code_ = tmp_city_code;
            local_number_ = tmp_num;
        } else {
            throw invalid_argument("Invalid number: " + international_number);
        }
    }
}
string PhoneNumber::GetCountryCode() const {
    return country_code_;
}
string PhoneNumber::GetCityCode() const {
    return city_code_;
}
string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}
string PhoneNumber::GetInternationalNumber() const {
    return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}

/*
int main() {
    string number;
    cin >> number;
    try {
        PhoneNumber ph(number);
        cout << ph.GetInternationalNumber() << endl;
    } catch (exception& i) {
        cerr << i.what() << endl;
    }
    return 0;
}

/* MIPT and Yandex implementation (different input parsing check):
#include <stdexcept>
#include <string>
#include <sstream>
#include "phone_number.h"

using namespace std;

PhoneNumber::PhoneNumber(const string& international_number) {
    istringstream is(international_number);

    char sign = is.get();
    getline(is, country_code_, '-');
    getline(is, city_code_, '-');
    getline(is, local_number_);

    if (sign != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty()) {
        throw invalid_argument("Phone number must begin with '+' symbol and contain 3 parts separated by '-' symbol: " + international_number);
    }
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return ("+" + country_code_ + "-" + city_code_ + "-" + local_number_);
}
*/



/* Task 14:
Вам дан заголовочный файл phone_number.h, содержащий объявление класса PhoneNumber. 
При этом в комментариях описано поведение, которое ожидается от реализации этого класса.

phone_number.h

#pragma once

#include <string>

using namespace std;

class PhoneNumber {
public:
    Принимает строку в формате +XXX-YYY-ZZZZZZ
    Часть от '+' до первого '-' - это код страны.
    Часть между первым и вторым символами '-' - код города
    Всё, что идёт после второго символа '-' - местный номер.
    Код страны, код города и местный номер не должны быть пустыми.
    Если строка не соответствует этому формату, нужно выбросить исключение 
    invalid_argument. Проверять, что номер содержит только цифры, не нужно.
    
    Примеры:
    * +7-495-111-22-33
    * +7-495-1112233
    * +323-22-460002
    * +1-2-coursera-cpp
    * 1-2-333 - некорректный номер - не начинается на '+'
    * +7-1233 - некорректный номер - есть только код страны и города

    explicit PhoneNumber(const string &international_number);

    string GetCountryCode() const;
    string GetCityCode() const;
    string GetLocalNumber() const;
    string GetInternationalNumber() const;

private:
    string country_code_;
    string city_code_;
    string local_number_;
};


Пришлите cpp-файл с определениями методов класса PhoneNumber, которые реализуют 
описанное поведение.

Как будет тестироваться ваш код
Автоматическая тестирующая система добавит ваш cpp-файл в проект, содержащий другой 
cpp-файл с юнит-тестами для класса PhoneNumber, а также файл phone_number.h. Затем 
она соберёт этот проект и, если компиляция будет выполнена успешно, запустит получившийся 
исполняемый файл. Если он завершится успешно (т. е. юнит-тесты не найдут ошибок в вашей 
реализации), то ваша посылка будет засчитана.
*/