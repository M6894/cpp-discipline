
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    int n = 0; // Number of blocks, 100k max
    int16_t r = 0; // Density, 100 max, somehow int8_t does not suit here
    int16_t w, h, d; // Sides, 10k max

    cin >> n >> r;
    uint64_t total_weight = 0; // sum of block_weight
    for (int i = 0; i < n; i++) {
        uint64_t block_weight = 0; // volume (w * h * d) * r;
        cin >> w >> h >> d;
        block_weight = w;
        block_weight *= h;
        block_weight *= d;
        block_weight *= r;
        total_weight += block_weight;
    }
    cout << total_weight << endl;
    return 0;
}

/* MIPT and Yandex implementation:
Главное, на что нужно было обратить внимание при решении задачи — корректный 
выбор целочисленных типов. Как следует из условия, максимально возможное 
значение массы равно 10^4 * 10^4 * 10^4 * 10^5 * 100 = 10^19, что умещается 
лишь в тип uint64_t.

#include <cstdint>
#include <iostream>

using namespace std;

int main() {
    int N, R;
    cin >> N >> R;
    uint64_t answer = 0;
    for (int i = 0; i < N; ++i) {
        int W, H, D;
        cin >> W >> H >> D;
        // Если не привести W к типу uint64_t перед умножением, 
        // произведение будет иметь тип int и случится переполнение.
        // Альтернативное решение — хранить сами W, H, D в uint64_t
        answer += static_cast<uint64_t>(W) * H * D;
    }
    answer *= R;
    cout << answer << endl;
    return 0;
}
*/



/* Task:
Вычислите суммарную массу имеющих форму прямоугольного параллелепипеда 
бетонных блоков одинаковой плотности, но разного размера.

Указание
Считайте, что размеры блоков измеряются в сантиметрах, плотность — в 
граммах на кубический сантиметр, а итоговая масса — в граммах. Таким 
образом, массу блока можно вычислять как простое произведение плотности 
на объём.

Формат ввода
В первой строке вводятся два целых положительных числа: количество блоков 
N и плотность каждого блока R. Каждая из следующих N строк содержит три 
целых положительных числа W, H, D — размеры очередного блока.

Гарантируется, что:

количество блоков N не превосходит 10^5;
плотность блоков R не превосходит 100;
размеры блоков W, H, D не превосходят 10^4.
Пример
Ввод
2 14
1 2 3
30 40 50

Вывод
840084
*/