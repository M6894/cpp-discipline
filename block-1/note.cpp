// C++ notes

#include <iostream>
#include <string>
#include <vector>
#include <cmath> 
#include <chrono> // Chrono - code execution time.
#include <algorithm> // Algorithm - vector sort for example.
#include <map>
#include <set>


using namespace std;
using namespace std::chrono; // Chrono

// C++ 17 for version
void PrintMap(const map<string, int>& input) {
    for (const auto& [key, data] : input) {
        cout << key << ": " << data << endl;
    }
}

// C++ Ternary Operator
string Get(int x) {
    return x > 0 ? "Yes" : (x == 0 ? "Zero" : "Negative");
}

int main()
{
    // sort with lambda expression
    vector<int> v(5, -5);
    sort(begin(v), end(v),
        // функция, сравнивающая abs(l) и abs(r) — модули чисел l и r
        [](int l, int r) {
            return abs(l) < abs(r);
        }
    );


    // For Chrono look at "Передача параметров функции по константной ссылке" в неделе 2, white belt.

    string pause;
    cin >> pause; 
    return 0;
}

/*
Font - Doom - http://patorjk.com/software/taag/#p=display&f=Doom&t=Sort
*/
