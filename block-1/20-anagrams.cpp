
#include <iostream>
#include <string>
#include <map>

using namespace std;

map<char, int> BuildCharCounters(const string& word) {
    map<char, int> result;
    for (const char& w: word) {
        result[w]++;
    }

    return result;
}

int main() {
    int q; // Количество пар слов
    cin >> q;

    string wordA;
    string wordB;
    for (int stage = 1; stage <= q; stage++) {
        cin >> wordA >> wordB;
        if (BuildCharCounters(wordA) == BuildCharCounters(wordB)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}

/* MIPT and Yandex implementation (same):
#include <iostream>
#include <string>
#include <map>

using namespace std;

map<char, int> BuildCharCounters(const string& word) {
    map<char, int> counters;
    for (char c : word) {
        ++counters[c];
    }
    return counters;
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string first_word, second_word;
        cin >> first_word >> second_word;
        if (BuildCharCounters(first_word) == BuildCharCounters(second_word)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
*/



/* Task:
Слова называются анаграммами друг друга, если одно из них можно получить перестановкой букв в другом. 
Например, слово «eat» можно получить перестановкой букв слова «tea», поэтому эти слова являются анаграммами друг друга. 
Даны пары слов, проверьте для каждой из них, являются ли слова этой пары анаграммами друг друга.

Указание
Один из способов проверки того, являются ли слова анаграммами друг друга, заключается в следующем. 
Для каждого слова с помощью словаря подсчитаем, сколько раз в нём встречается каждая буква. 
Если для обоих слов эти словари равны (а это проверяется с помощью обычного оператора ==), 
то слова являются анаграммами друг друга, в противном случае не являются.

При этом построение такого словаря по слову удобно вынести в отдельную функцию BuildCharCounters.

Формат ввода
Сначала дано число пар слов N, затем в N строках содержатся пары слов, которые необходимо проверить. 
Гарантируется, что все слова состоят лишь из строчных латинских букв.

Формат вывода
Выведите N строк: для каждой введённой пары слов YES, если эти слова являются анаграммами, и NO в противном случае.

Пример
Ввод
3
eat tea
find search
master stream

Вывод:
YES
NO
YES
*/