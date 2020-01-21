
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

class SortedStrings {
public:
    void AddString(const string& s) {
        // добавить строку s в набор
        list.push_back(s);
    }
    vector<string> GetSortedStrings() {
        // получить набор из всех добавленных строк в отсортированном порядке
        sort(begin(list), end(list));
        return list;
    }
private:
    // приватные поля
    vector<string> list;
};

void PrintSortedStrings(SortedStrings& strings) {
    for (const string& s : strings.GetSortedStrings()) {
        cout << s << " ";
    }
    cout << endl;
}

int main() {
    SortedStrings strings;
  
    strings.AddString("first");
    strings.AddString("third");
    strings.AddString("second");
    PrintSortedStrings(strings);

    strings.AddString("second");
    PrintSortedStrings(strings);

    return 0;
}

/* MIPT and Yandex implementation (same):
class SortedStrings {
public:
    void AddString(const string& s) {
        data.push_back(s);
    }
    vector<string> GetSortedStrings() {
        sort(begin(data), end(data));
        return data;
    }
private:
    vector<string> data;
};

*/



/* Task:
Реализуйте класс, поддерживающий набор строк в отсортированном порядке. 
Класс должен содержать два публичных метода:

class SortedStrings {
public:
    void AddString(const string& s) {
        // добавить строку s в набор
    }
    vector<string> GetSortedStrings() {
        // получить набор из всех добавленных строк в отсортированном порядке
    }
private:
    // приватные поля
};

Пример
Код
void PrintSortedStrings(SortedStrings& strings) {
    for (const string& s : strings.GetSortedStrings()) {
        cout << s << " ";
    }
    cout << endl;
}

int main() {
    SortedStrings strings;
  
    strings.AddString("first");
    strings.AddString("third");
    strings.AddString("second");
    PrintSortedStrings(strings);
    
    strings.AddString("second");
    PrintSortedStrings(strings);
    
    return 0;
}

Вывод
first second third
first second second third
*/