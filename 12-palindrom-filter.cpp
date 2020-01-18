// Версия программы с функцией типа vector<string>.

#include <iostream>
#include <string>
#include <vector>

using namespace std;


vector<string> PalindromFilter(vector<string> words, int minLength) {
    
    vector<string> palindroms; // Новый вектор с только отобранными палиндромами
    string check; // промежуточная переменная для проверки идентичности перевернутого слова

    for (auto iWord : words) {
        for (int i = iWord.size()-1; i >=0; i--) {
            check += iWord[i];
            if (i == 0 && iWord.size() >= minLength && check == iWord) {
                palindroms.push_back(iWord);
                // cout << check << endl;
                check = "";                
            } else if (i == 0 && iWord.size()) {
                check = "";
            }
        }
    }
   return palindroms; 
}

int main() {
    vector<string> input = { /*"abacaba", "aba", */ "weew", "bro", "code", "abba" };
    int minLength = 2;
    input = PalindromFilter(input, minLength); 

    for (int i = 0; i < input.size(); i++) {
        if (i != input.size() -1) {
            cout << input[i] << ", ";
        } else {
            cout << input[i] << "\n"; 
        }
    }

    // cin >> minLength; // pause
    return 0;
}

/* MIPT and Yandex implementation - nice one, but longer:

Напишем две функции:

IsPalindrom, проверяющую, является ли строка палиндромом.
PalindromFilter, перебирающую все строки из данного вектора и проверяющую для каждой из них требуемые условия.

// определяет, является ли строка s палиндромом
bool IsPalindrom(string s) {
  
    // переберём все символы s[i] из первой половины строки
    for (size_t i = 0; i < s.size() / 2; ++i) {
        // s[s.size() - i - 1] — символ, симметричный символу s[i]
        if (s[i] != s[s.size() - i - 1]) {
            return false;  // если они не совпадают, строка точно не палиндром
        }
    }
  
    // если все пары символов совпадают, строка — палиндром
    return true;
}

vector<string> PalindromFilter(vector<string> words, int min_length) {
    vector<string> result;
    // перебираем все элементы вектора words
    for (auto s : words) {
        // если требуеые условия выполняются, добавляем s к ответу
        if (s.size() >= min_length && IsPalindrom(s)) {
            result.push_back(s);
        }
    }
    return result;
}
*/



/* Task:
Напишите функцию, которая

называется PalindromFilter
возвращает vector<string>
принимает vector<string> words и int minLength и возвращает 
все строки из вектора words, которые являются палиндромами и 
имеют длину не меньше minLength
Входной вектор содержит не более 100 строк, длина каждой строки не больше 100 символов.

Примеры
words	        minLength	результат
abacaba, aba	5	        abacaba
abacaba, aba	2	        abacaba, aba
weew, bro, code	4	        weew
*/