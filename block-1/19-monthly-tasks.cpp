
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int HowMuchEvents(const string& word) {
    int spaces = 0;
    for (char i : word) {
        if (i == ' ') {
            spaces++;
        }
    }
    return spaces;
}

int main() {
    int q = 0; // Количество команд
    int nextMonth = 1; // 

    string command;
    string event;
    vector<string> month(31, "");
    int day = 0; //  День на вход

    vector<string> tempVec(0, ""); // для Next
    const vector<int> daysLimit = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    cin >> q;
    for (int stage = 1; stage <= q; stage++) {

        cin >> command;
        if (command == "NEXT") {
            tempVec = month;
            tempVec.resize(daysLimit[nextMonth]);            
            if (daysLimit[nextMonth] == 28) {
                tempVec[tempVec.size()-1] += month[28] + month[29] + month[30];
            } 
            else if (daysLimit[nextMonth] < month.size()) {
                tempVec[tempVec.size()-1] += month[30];
            }
            month = tempVec;
            
            if (nextMonth < 11) {
                nextMonth++;
            } else {
                nextMonth = 0;
            }
        } else {
            cin >> day;
        }

        if (command == "ADD") {
            cin >> event;
            month[day-1] += event + " ";
        } 
        else if (command == "DUMP") {
            cout << HowMuchEvents(month[day-1]) << " " << month[day-1] << endl;;
        }
    }
    return 0;
}

/* MIPT and Yandex implementation (preferable) - после декабря идёт январь:
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// глобальные (доступные во всей программе) константы
// часто принято называть ЗАГЛАВНЫМИ_БУКВАМИ
const vector<int> MONTH_LENGTHS =
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int MONTH_COUNT = MONTH_LENGTHS.size();

int main() {
    int q;
    cin >> q;
  
    // номер текущего месяца (от 0 до 11)
    int month = 0;
  
    // внешний вектор должен иметь длину, равную количеству дней в первом месяце;
    // все внутренние векторы по умолчанию пусты, потому что дел изначально нет
    vector<vector<string>> days_concerns(MONTH_LENGTHS[month]);

    for (int i = 0; i < q; ++i) {
        string operation_code;
        cin >> operation_code;

        if (operation_code == "ADD") {

            int day;
            string concern;
            cin >> day >> concern;
            --day;  // элементы вектора нумеруются с нуля
            days_concerns[day].push_back(concern);

        } else if (operation_code == "NEXT") {

            // перед переходом к следующему месяцу запомним длину предыдущего
            // обьявляем эту переменную константной, потому что менять её не планируем
            const int old_month_length = MONTH_LENGTHS[month];
      
            // номер месяца должен увеличиться на 1, но после декабря идёт январь:
            // например, (5 + 1) % 12 = 6, но (11 + 1) % 12 = 0
            month = (month + 1) % MONTH_COUNT;
            
            const int new_month_length = MONTH_LENGTHS[month];
      
            // если новый месяц больше предыдущего, достаточно сделать resize;
            // иначе перед resize надо переместить дела с «лишних» последних дней
            if (new_month_length < old_month_length) {
        
                // далее понадобится добавлять новые дела в последний день нового месяца
                // чтобы не писать несколько раз days_concerns[new_month_length - 1],
                // создадим ссылку с более коротким названием для этого вектора
                vector<string>& last_day_concerns = days_concerns[new_month_length - 1];
        
                // перебираем все «лишние» дни в конце месяца
                for (int day = new_month_length; day < old_month_length; ++day) {
                    // копируем вектор days_concerns[day]
                    // в конец вектора last_day_concerns
                    last_day_concerns.insert(
                        end(last_day_concerns),
                        begin(days_concerns[day]), end(days_concerns[day]));
                }
            }
            days_concerns.resize(new_month_length);

        } else if (operation_code == "DUMP") {

            int day;
            cin >> day;
            --day;
            
            // выводим список дел в конкретный день в нужном формате
            cout << days_concerns[day].size() << " ";
            for (const string& concern : days_concerns[day]) {
                cout << concern << " ";
            }
            cout << endl;

        }
    }

    return 0;
}
*/



/* Task:
У каждого из нас есть ежемесячные дела, каждое из которых нужно выполнять в конкретный день каждого месяца: 
оплата счетов за электричество, абонентская плата за связь и пр. Вам нужно реализовать работу со списком 
таких дел, а именно, обработку следующих операций:

ADD i s
Добавить дело с названием s в день i.

NEXT
Закончить текущий месяц и начать новый. Если новый месяц имеет больше дней, чем текущий, добавленные 
дни изначально не будут содержать дел. Если же в новом месяце меньше дней, дела со всех удаляемых дней 
необходимо будет переместить на последний день нового месяца.

Обратите внимание, что количество команд этого типа может превышать 11.

DUMP i
Вывести все дела в день i.

Изначально текущим месяцем считается январь. Количества дней в месяцах соответствуют Григорианскому 
календарю с той лишь разницей, что в феврале всегда 28 дней.

Указание
Для дописывания всех элементов вектора v2 в конец вектора v1 удобно использовать метод insert:
v1.insert(end(v1), begin(v2), end(v2));

Формат ввода
Сначала число операций Q, затем описания операций.

Названия дел s уникальны и состоят только из латинских букв, цифр и символов подчёркивания. 
Номера дней i являются целыми числами и нумеруются от 1 до размера текущего месяца.

Формат вывода
Для каждой операции типа DUMP в отдельной строке выведите количество дел в соответствующий день, а затем их 
названия, разделяя их пробелом. Порядок вывода дел в рамках каждой операции значения не имеет.

Пример
Ввод:
12
ADD 5 Salary
ADD 31 Walk
ADD 30 WalkPreparations
NEXT
DUMP 5
DUMP 28
NEXT
DUMP 31
DUMP 30
DUMP 28
ADD 28 Payment
DUMP 28

Вывод:
1 Salary
2 WalkPreparations Walk
0
0
2 WalkPreparations Walk
3 WalkPreparations Walk Payment

*/