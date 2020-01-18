
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void PrintFile(const string& source_path) {
    ifstream input(source_path);
    if (input) {
        string line;
        while (getline(input, line)) {
            cout << line << "\n";
        }
    }
}

void SaveFile(const string& source_path) {
    ifstream input(source_path);
    ofstream erase("output.txt");
    if (erase) {
        erase << "";
    }
    ofstream output("output.txt", ios::app);
    if (input && output) {
        string line;
        while (getline(input, line)) {
            output << line << endl;
        }
    }
}

int main() {
    const string source_path = "input.txt";
    PrintFile(source_path); 
    SaveFile(source_path);
    return 0;
}

/* MIPT and Yandex implementation:
1: Будем считывать из файлового потока по одной строке и сразу выводить их в стандартный поток вывода.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream input("input.txt");

    string line;
    while (getline(input, line)) {
        cout << line << endl;
    }

    return 0;
}

2: В отличие от предыдущего решения, вывод будет осуществляться в файловый поток.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    string line;
    while (getline(input, line)) {
        output << line << endl;
    }

    return 0;
}
*/



/* Task:
В этом задании вам предстоит написать две небольшие программы. Каждый пункт - 
отдельная задача, решение отправляйте в поле с соответствующим номером.

Часть 1
Ваша программа должна считать содержимое файла input.txt и напечатать его на 
экран без изменений. Гарантируется, что содержимое файла input.txt заканчивается переводом строки.

Пример
input.txt
Keep calm
and
learn C++

stdout
Keep calm
and
learn C++

Часть 2
Снова считайте все содержимое файла input.txt, но на этот раз выведите его в файл 
output.txt . Точно так же гарантируется, что содержимое файла input.txt заканчивается переводом строки.

Пример
input.txt
Keep calm
and
learn C++

output.txt
Keep calm
and
learn C++
*/