// #include "13-sum-reverse-sort.h" // must be named "sum_reverse_sort.h" to pass the testing system
#include "sum_reverse_sort.h"
// #include "13-sum-reverse-sort-tests.h"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int Sum(int x, int y) { return x + y; }

string Reverse(string s) { 
    reverse(begin(s), end(s)); 
    return s;
}

void Sort(vector<int>& nums) { 
    // sort(nums.begin(), nums.end());
    sort(begin(nums), end(nums));
}

/*
int main() {
    TestAll();
    return 0;
}
*/

/* MIPT and Yandex implementation:
#include "sum_reverse_sort.h"

#include <algorithm>
using namespace std;

int Sum(int x, int y) {
    return x + y;
}

string Reverse(string s) {
    reverse(s.begin(), s.end());
    return s;
}

void Sort(vector<int>& nums) {
    sort(nums.begin(), nums.end());
}
*/



/* Task:
Вам дан заголовочный файл sum_reverse_sort.h, содержащий объявления трёх функций

sum_reverse_sort.h
#pragma once
#include <string>
#include <vector>

using namespace std;

int Sum(int x, int y);
string Reverse(string s);
void Sort(vector<int>& nums);

Вам надо прислать cpp-файл, содержащий определения этих функций.

Как будет тестироваться ваш код
Автоматическая тестирующая система добавит ваш cpp-файл в проект, 
содержащий другой cpp-файл с юнит-тестами для всех трёх функций, а также файл 
sum_reverse_sort.h. Затем она соберёт этот проект и, если компиляция будет выполнена 
успешно, запустит получившийся исполняемый файл. Если он завершится успешно (т. е. 
юнит-тесты не найдут ошибок в вашей реализации), то ваша посылка будет засчитана.
*/