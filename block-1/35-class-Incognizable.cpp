
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

struct Incognizable {
    int a = 0;
    int b = 0;
};

int main() {
    Incognizable a;
    Incognizable b = {};
    Incognizable c = {0};
    Incognizable d = {0, 1};

    return 0;
}

/* MIPT and Yandex implementation:
struct Incognizable {
    int x = 0;
    int y = 0;
};
*/



/* Task:
Определите тип Incognizable, для которого следующий код будет корректен:

int main() {
    Incognizable a;
    Incognizable b = {};
    Incognizable c = {0};
    Incognizable d = {0, 1};
    return 0;
}
*/