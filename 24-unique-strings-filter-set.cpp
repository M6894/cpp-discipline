
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

int main() {
    int q = 0;
    cin >> q;
    set<string> unique_words;
    for (int i = 1; i <= q; i++) {
        string word;
        cin >> word;
        unique_words.insert(word);
    }
    cout << unique_words.size() << endl;
    return 0;
}

/* MIPT and Yandex implementation (same):
#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {
    int n;
    cin >> n;
    set<string> strings;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        strings.insert(s);
    }
    cout << strings.size() << endl;

    return 0;
}
*/



/* Task:
Дан набор строк. Найдите количество уникальных строк в этом наборе.

Формат ввода
Сначала вводится количество строк N, затем — сами N строк, разделённые пробелом. 
Все строки состоят лишь из латинских букв, цифр и символов подчёркивания.

Формат вывода
Выведите единственное целое число — количество уникальных строк в данном наборе.

Пример
Ввод
6
first
second
first
third
second
second

Вывод
3
*/