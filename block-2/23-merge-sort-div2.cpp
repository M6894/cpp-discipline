// 23*div2
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
/*
// Div 2 version enhanced
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {

    // Size check
    if (distance(range_begin, range_end) < 2) {
        return;
    }
    // Vector initiation
    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    // Vector cut
    auto middle = begin(elements) + elements.size() / 2;
    // Recursion
    MergeSort(elements.begin(), middle);
    MergeSort(middle, elements.end());
    // Merge
    merge(elements.begin(), middle, middle, elements.end(), range_begin);
}
*/

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {

    // Size check
    // if (distance(range_begin, range_end) < 2) {
    if (range_end - range_begin < 2) {
        return;
    }
    // Vector initiation
    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    // Vector cut
    auto middle = begin(elements) + elements.size() / 2;
    // Recursion
    MergeSort(elements.begin(), middle);
    MergeSort(middle, elements.end());
    // Merge
    merge(elements.begin(), middle, middle, elements.end(), range_begin);
}

int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1}; // div 2
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}

/* MIPT and Yandex implementation:
// В этой задаче достаточно аккуратно реализовать предложенный алгоритм, не ошибившись при 
// использовании итераторов.

// Часть 1. Разбиение на 2 части

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    // 1. Если диапазон содержит меньше 2 элементов, выходим из функции
    int range_length = range_end - range_begin;
    if (range_length < 2) {
        return;
    }
    
    // 2. Создаем вектор, содержащий все элементы текущего диапазона
    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    
    // 3. Разбиваем вектор на две равные части
    auto mid = elements.begin() + range_length / 2;
    
    // 4. Вызываем функцию MergeSort от каждой половины вектора
    MergeSort(elements.begin(), mid);
    MergeSort(mid, elements.end());
    
    // 5. С помощью алгоритма merge сливаем отсортированные половины
    // в исходный диапазон
    // merge -> http://ru.cppreference.com/w/cpp/algorithm/merge
    merge(elements.begin(), mid, mid, elements.end(), range_begin);
}
*/



/* Task:
Напишите шаблонную функцию MergeSort, принимающую два итератора шаблонного типа RandomIt и 
сортирующую заданный ими диапазон с помощью сортировки слиянием. Гарантируется, что:

итераторы типа RandomIt аналогичны по функциональности итераторам вектора и строки, то есть их 
можно сравнивать с помощью операторов <, <=, > и >=, а также вычитать и складывать с числами;
сортируемые объекты можно сравнивать с помощью оператора <.

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end);

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end);
Часть 1. Реализация с разбиением на 2 части
Алгоритм
Классический алгоритм сортировки слиянием выглядит следующим образом:

Если диапазон содержит меньше 2 элементов, выйти из функции.
Создать вектор, содержащий все элементы текущего диапазона.
Разбить вектор на две равные части. (В этой задаче гарантируется, что длина передаваемого диапазона 
является степенью двойки, так что вектор всегда можно разбить на две равные части.)
Вызвать функцию MergeSort от каждой половины вектора.
С помощью алгоритма std::merge слить отсортированные половины, записав полученный отсортированный 
диапазон вместо исходного.
Вы должны реализовать именно этот алгоритм и никакой другой: тестирующая система будет проверять, 
что вы выполняете с элементами именно эти действия.

Подсказка
Чтобы создать вектор, содержащий все элементы текущего диапазона (п. 2 алгоритма), необходимо уметь 
по типу итератора узнавать тип элементов, на которые он указывает. Если итератор RandomIt 
принадлежит стандартному контейнеру (вектору, строке, множеству, словарю...), нижележащий тип можно 
получить с помощью выражения typename RandomIt::value_type. Таким образом, гарантируется, что 
создать вектор в п. 2 можно следующим образом:

vector<typename RandomIt::value_type> elements(range_begin, range_end);

Пример кода
int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}

Вывод
0 1 4 4 4 6 6 7

Часть 2. Реализация с разбиением на 3 части
Реализуйте сортировку слиянием, разбивая диапазон на 3 равные части, а не на 2. Гарантируется, что 
длина исходного диапазона является степенью 3.

Соответственно, пункты 3–5 алгоритма нужно заменить следующими:

Разбить вектор на 3 равные части.
Вызвать функцию MergeSort от каждой части вектора.
Слить первые две трети вектора с помощью алгоритма merge, сохранив результат во временный вектор с 
помощью back_inserter.
Слить временный вектор из предыдущего пункта с последней третью вектора из п. 2, записав полученный 
отсортированный диапазон вместо исходного.

Пример кода
int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}

Вывод
0 1 4 4 4 5 6 6 7
*/