
#include <iostream>
#include <string>

using namespace std;

int main() {
    string a, b, c;
    cin >> a >> b >> c;
  
    if (a <= b && a <= c) {
        cout << a;
    } else if (b <= a && b <= c) {
        cout << b;
    } else {
        cout << c;
    }
    return 0;
}

/* MIPT and Yandex implementation:
int main() {
    string a, b, c;
    cin >> a >> b >> c;
  
    if (a <= b && a <= c) {
        cout << a;
    } else if (b <= a && b <= c) {
        cout << b;
    } else {
        cout << c;
    }
    return 0;
}
*/



/* M6894 first implementation
int main ()
{
    string a, b, c, pause;
    cin >> a >> b >> c;
    if (a < b)
    {
        if (a < c)
        {
            cout << a << endl;
        }
        else 
        {
            cout << c << endl;
        }
    }
    else 
    {
        if (b < c)
        {
            cout << b << endl;
        }
        else 
        {
            cout << c << endl;
        }
    }
    // cin >> pause;
    return 0;
}
*/



/* Task
В стандартном потоке даны три строки, разделённые пробелом. Каждая строка состоит из строчных 
латинских букв и имеет длину не более 30 символов. Выведите в стандартный вывод лексикографически 
минимальную из них.

Примеры
stdin	                stdout
milk milkshake month	milk
c a b	                a
fire fog wood	        fire
*/