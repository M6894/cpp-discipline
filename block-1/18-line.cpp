
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void WorryCount(const vector<bool>& line) {
    int sum = 0;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == true) {
            sum++;
        }
    }
    cout << sum << endl;
}

int main() {
    int q = 0;
    cin >> q;

    string command;
    int i;

    vector<bool> line (0, false);
    for (int stage = 1; stage <= q; stage++) {

        cin >> command;
        if (command != "WORRY_COUNT") {
            cin >> i;
        } else {
            WorryCount(line);
        }
        
        if (command == "COME") {
            line.resize(line.size()+i);
        }
        else if (command == "WORRY" || command == "QUIET") {
            line[i] = (command == "WORRY");
        }
    }
    return 0;
}

/* MIPT and Yandex implementation - тут интересно сделан подсчет волнующихся - count из cmath. Еще интересны Worry и quiet.
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int q;
    cin >> q;
    vector<bool> is_nervous;

    for (int i = 0; i < q; ++i) {
        string operation_code;
        cin >> operation_code;

        if (operation_code == "WORRY_COUNT") {
      
        // подсчитываем количество элементов в векторе is_nervous, равных true
        cout << count(begin(is_nervous), end(is_nervous), true) << endl;
      
        } else {
            if (operation_code == "WORRY" || operation_code == "QUIET") {
        
                int person_index;
                cin >> person_index;
            
                // выражение в скобках имеет тип bool и равно true для запроса WORRY,
                // поэтому is_nervous[person_index] станет равным false или true
                // в зависимости от operation_code
                is_nervous[person_index] = (operation_code == "WORRY");
        
            } else if (operation_code == "COME") {
        
                int person_count;
                cin >> person_count;
        
                // метод resize может как уменьшать размер вектора, так и увеличивать,
                // поэтому специально рассматривать случаи с положительным
                // и отрицательным person_count не нужно
                is_nervous.resize(is_nervous.size() + person_count, false);
        
            }
        }
    }

    return 0;
}
*/

/* Task:
Люди стоят в очереди, но никогда не уходят из её начала, зато могут приходить в конец и уходить оттуда. 
Более того, иногда некоторые люди могут прекращать и начинать беспокоиться из-за того, что очередь не продвигается.

Реализуйте обработку следующих операций над очередью:

WORRY i: пометить i-го человека с начала очереди (в нумерации с 0) как беспокоящегося;
QUIET i: пометить i-го человека как успокоившегося;
COME k: добавить k спокойных человек в конец очереди;
COME -k: убрать k человек из конца очереди;
WORRY_COUNT: узнать количество беспокоящихся людей в очереди.
Изначально очередь пуста.

Формат ввода
Количество операций Q, затем описания операций.

Для каждой операции WORRY i и QUIET i гарантируется, что человек с номером i существует в очереди на момент операции.

Для каждой операции COME -k гарантируется, что k не больше текущего размера очереди.

Формат вывода
Для каждой операции WORRY_COUNT выведите одно целое число — количество беспокоящихся людей в очереди.

Пример

Ввод:
8
COME 5
WORRY 1
WORRY 4
COME -2
WORRY_COUNT
COME 3
WORRY 3
WORRY_COUNT

Вывод:
1
2
*/