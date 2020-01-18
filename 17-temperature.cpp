
#include <iostream>
// #include <string>
#include <vector>

using namespace std;

// Vector input from user with number of items reuest
vector<int> EnterVector() {
    vector<int> input;
    int itemsNums = 0;
    cin >> itemsNums;
    int tmp;

    for (int i = 0; i < itemsNums; i++) {
        cin >> tmp;
        input.push_back(tmp);
    }
    return input;
}

// Higher than average calculation. Generates vector with indexes of input vector items that higher than average of whole vector.
vector<int> IsAboveAverage(const vector<int>& v) {
    int sum = 0;
    for (auto i : v) {
        sum += i;
    }

    vector<int> output;
    for (int i =0; i < v.size(); i++) {
        if (v[i] > sum / v.size()) {
            output.push_back(i);
        }
    }
    cout << output.size() << endl;;
    return output;
}

// Vector printing with constant link
void PrintVector(const vector<int>& v) {
    for (auto i : v) {
        cout << i << " ";
    }
}

int main() {
    PrintVector(IsAboveAverage(EnterVector()));

    return 0;
}

/* MIPT and Yandex implementation - what is useful: alternative vector filling.
int main() {
    int n;
    cin >> n;
    vector<int> temperatures(n);
    int sum = 0;
    for (int& temperature : temperatures) {
        cin >> temperature;
        sum += temperature;
    }

    int average = sum / n;
    vector<int> result_indices;
    for (int i = 0; i < n; ++i) {
        if (temperatures[i] > average) {
            result_indices.push_back(i);
        }
    }

    cout << result_indices.size() << endl;
    for (int result_index : result_indices) {
        cout << result_index << " ";
    }
    cout << endl;

    return 0;
}
*/



/* Task:
Даны значения температуры, наблюдавшиеся в течение N подряд идущих дней. 
Найдите номера дней (в нумерации с нуля) со значением температуры выше среднего арифметического за все N дней.

Гарантируется, что среднее арифметическое значений температуры является целым числом.

Формат ввода
Вводится число N, затем N неотрицательных целых чисел — 
значения температуры в 0-й, 1-й, ... (N−1)-й день.

Формат вывода
Первое число K — количество дней, значение температуры в которых выше среднего арифметического. 
Затем K целых чисел — номера этих дней.

Пример
Ввод:
5
7 6 3 0 9

Вывод:
3
0 1 4
*/