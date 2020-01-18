
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>

using namespace std;

int main() {
    map<set<string>, set<string>> synonyms; // исходя из решения МФТИ и Яндекса, можно было 
                                            // сделать только один словарь map<string, set<string>>;
    map<string, int> words_count;

    int q = 0;
    cin >> q;
    
    for (int i = 0; i < q; ++i) {
        string command;
        cin >> command;
        if (command == "ADD") {
            string word1, word2;
            cin >> word1 >> word2;
            set<string> temp = {word1, word2};
            if (synonyms.count(temp) == 0) {
                synonyms[temp] = temp;
                words_count[word1]++;
                words_count[word2]++;
            }
        }
        else if (command == "CHECK") {
            string word1, word2;
            cin >> word1 >> word2;
            set<string> check_set = {word1, word2};
            if (synonyms.count(check_set) != 0) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
        else if (command == "COUNT") {
            string check_word;
            cin >> check_word;
            cout << words_count[check_word] << endl;
        }
    }
    return 0;
}

/* MIPT and Yandex implementation (preferable):
Чтобы быстро проверять, является ли одно слово синонимом другого, можно было использовать словарь 
множеств — map<string, set<string>>: для каждого слова будем хранить множество его синонимов.

#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

int main() {
    int q;
    cin >> q;

    map<string, set<string>> synonyms;

    for (int i = 0; i < q; ++i) {
        string operation_code;
        cin >> operation_code;

        if (operation_code == "ADD") {

            string first_word, second_word;
            cin >> first_word >> second_word;
            
            // второе слово добавляем в список синонимов первого...
            synonyms[first_word].insert(second_word);
            // и наоборот
            synonyms[second_word].insert(first_word);

        } else if (operation_code == "COUNT") {

            string word;
            cin >> word;
            cout << synonyms[word].size() << endl;

        } else if (operation_code == "CHECK") {

            string first_word, second_word;
            cin >> first_word >> second_word;
      
            // ищём второе слово во множестве синонимов первого
            // (можно было сделать и наоборот)
            if (synonyms[first_word].count(second_word) == 1) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }

        }
    }

    return 0;
}
*/



/* Task:
Два слова называются синонимами друг друга, если они имеют похожие значения. 
Реализуйте следующие операции над словарём синонимов:

ADD word1 word2 — добавить в словарь пару синонимов (word1, word2).
COUNT word — узнать количество синонимов слова word.
CHECK word1 word2 — проверить, являются ли слова word1 и word2 синонимами. 
Слова word1 и word2 считаются синонимами, если среди запросов ADD был хотя бы 
один запрос ADD word1 word2 или ADD word2 word1.

Формат ввода
Сначала вводится количество запросов Q, затем Q строк с описаниями запросов. 
Гарантируется, что в каждом запросе CHECK и ADD слова word1 и word2 различны. 
Все слова состоят лишь из латинских букв, цифр и символов подчёркивания.

Формат вывода
Для каждого запроса в соответствующей строке выведите ответ на него:

В ответ на запрос COUNT word выведите единственное целое число — количество 
синонимов слова word.
В ответ на запрос CHECK word1 word2 выведите строку YES, если word1 и word2 
являются синонимами, и NO в противном случае.
Пример
Ввод
8
ADD program code
COUNT cipher
ADD code cipher
COUNT code
COUNT program
CHECK code program
CHECK program cipher
CHECK cpp java

Вывод
0
2
1
YES
NO
NO
*/
