
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

void PrintFile(const string& source_path) {
    ifstream input(source_path);
    if (input.good()) {
        cout << fixed << setprecision(3);
        double number = 0;        
        while (input >> number) {
            /*
            if (round(number * 1000.0) / 1000.0 == -0) {
                number = 0;
            } else {
                number = round(number * 1000.0) / 1000.0;
            }
            */
            cout << number << "\n";
        }
    } else {
        cout << "File opening error." << endl;
    }
}

int main() {
    const string source_path = "input.txt";
    PrintFile(source_path); 
    return 0;
}

/* MIPT and Yandex implementation:
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    ifstream input("input.txt");

    double a;

    cout << fixed << setprecision(3);

    while (input >> a) {
        cout << a << endl;
    }

    return 0;
}
*/



/* Task:
В файле input.txt записаны вещественные числа, по одному на строчку. 
На стандартный вывод напечатайте эти числа в том же порядке, по одному на строке, 
но сделайте так, чтобы у каждого из них было ровно три знака после десятичной точки 
(округление производится по стандартным правилам, т.е. 0.1234 округляется до 0.123, 
а 0.1235 до 0.124).

Пример ввода 1
5
0.34567
10.4

Пример вывода 1
5.000
0.346
10.400

Пример ввода 2
3.334
3.333
3.300

Пример вывода 2
3.334
3.333
3.300
*/