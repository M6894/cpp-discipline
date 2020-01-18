
#include <iostream>
#include <string>

using namespace std;

// MIPT and Yandex implementation as a separate function added:
bool IsPalindromY(string s) {
    for (size_t i = 0; i < s.size() / 2; ++i) { // пока i меньше размера строки деленной на 2
        if (s[i] != s[s.size() - i - 1]) {      // сравнивается зеркально половина строки. Предпочтительный вариант.
            return false;
        }
    }
    return true;
}

// M6894 implementation
bool IsPalindrom(string x) {
    string check;

    for (int i = x.size()-1; i >=0; i--) {
        check += x[i];
    }
    
    if (check != x) {
        // cout << check << endl; // check iof the check variable.
        return false;
    }
    // cout << check << endl; // Check of the check variable.
    return true;
}


int main() {
    string input;
    cin >> input;

    cout << IsPalindrom(input) << endl;
    cout << IsPalindromY(input) << endl; // Ответ через функцию яндекса и МФТИ.
    
    cin >> input; // pause
    return 0;
}

/* MIPT and Yandex implementation:
bool IsPalindrom(string s) {
    for (size_t i = 0; i < s.size() / 2; ++i) {
        if (s[i] != s[s.size() - i - 1]) {
            return false;
        }
    }
    return true;
}
*/



/* Task
Напишите функцию, которая

называется IsPalindrom
возвращает bool
принимает параметр типа string и возвращает, является 
ли переданная строка палиндромом
Палиндром - это слово или фраза, которые одинаково 
читаются слева направо и справа налево. Пустая строка 
является палиндромом.

Аргумент функции	Результат
madam	            true
gentleman	        false
X                   true
*/