// 17
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int>& numbers) {
    auto it = find_if(begin(numbers), end(numbers), [](const int& num) {return num < 0;});

    while (it != begin(numbers)) {
        it--;
        cout << *it << " ";
    }
}

int main() {
    PrintVectorPart({});
    cout << endl;
    PrintVectorPart({6, 1, 8, -5, 4});
    cout << endl;
    PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
    cout << endl;
    PrintVectorPart({6, 1, 8, 5, 4});
    cout << endl;
    return 0;
}

/* MIPT and Yandex implementation:
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void PrintVectorPart(const vector<int>& numbers) {
    auto negative_it = find_if(
        numbers.begin(), numbers.end(),
        [](int number) {
            return number < 0;
        }
    );

    for (auto it = negative_it; it != numbers.begin(); ) {
        cout << *(--it) << " ";
    }
}
*/



/* Task:
Напишите функцию PrintVectorPart, принимающую вектор целых чисел numbers, 
выполняющую поиск первого отрицательного числа в нём и выводящую в стандартный 
вывод все числа, расположенные левее найденного, в обратном порядке. Если вектор 
не содержит отрицательных чисел, выведите все числа в обратном порядке.

void PrintVectorPart(const vector<int>& numbers);

Пример кода

int main() {
    PrintVectorPart({6, 1, 8, -5, 4});
    cout << endl;
    PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
    cout << endl;
    PrintVectorPart({6, 1, 8, 5, 4});
    cout << endl;
    return 0;
}

Вывод
8 1 6

4 5 8 1 6

*/