
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        // if (person_tasks.count(person) == 1) {
            return person_tasks.at(person);
        // }
    }
    
    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person) {
        person_tasks[person][TaskStatus::NEW]++;
    }
    
    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
        TasksInfo updated;
        TasksInfo untouched;
        if (person_tasks.count(person) == 0) {
            return make_pair(updated, untouched); // DEBUG (pair - tuple)
        } else {
            auto tasks = person_tasks[person];
            // Приравниваем task_count к количеству невыполненных задач
            int incomplete_tasks_count = 0;
            for (const auto& t : tasks) {
                incomplete_tasks_count += t.second;
            }
            if (task_count > incomplete_tasks_count) {
                task_count = incomplete_tasks_count;
            }
            // TODO: Create zero numbers to iterate
            // Perform tasks
            int move_count = 0;
            for (const auto& [task, number] : person_tasks[person]) {
                if (task_count >= number && task_count != 0) { // debug (0 number) // seems ok
                    if (move_count == 0) {
                        move_count += number;
                        task_count -= number;
                        tasks.erase(task);
                    } else {
                        int temp_move_count = number;
                        tasks[task] = move_count;
                        updated[task] = move_count;
                        move_count = temp_move_count;
                    }
                } else if (task_count != 0) {
                    tasks[task] -= task_count;
                    untouched[task] = tasks[task];
                    int temp_move_count = task_count;
                    task_count = 0;
                    if (move_count == 0) {
                        move_count = temp_move_count;
                    } else {
                        tasks[task] += move_count;
                        updated[task] = move_count;
                        move_count = temp_move_count;
                    }
                } else { // Only update untouched or add move_count and update updated
                    if (number == 0) {
                        tasks.erase(task);
                    } else {
                        if (move_count == 0) {
                            untouched[task] = number;
                        } else {
                            untouched[task] = number;
                            updated[task] = move_count;
                            tasks[task] += move_count;
                        }
                    }
                }
            }
            person_tasks[person] = tasks;
            return make_pair(updated, untouched);
        }
    }
private:
    map<string, TasksInfo> person_tasks;
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
        ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
        ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
        ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    TasksInfo updated_tasks, untouched_tasks;
    
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
    
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
    return 0;
}


/* MIPT and Yandex implementation:

*/



/* Task:
Реализуйте класс TeamTasks, позволяющий хранить статистику по статусам 
задач команды разработчиков:

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const;
    
    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person);
    
    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
        const string& person, int task_count);
};

Метод PerformPersonTasks должен реализовывать следующий алгоритм:

Рассмотрим все не выполненные задачи разработчика person.
Упорядочим их по статусам: сначала все задачи в статусе NEW, затем все 
задачи в статусе IN_PROGRESS и, наконец, задачи в статусе TESTING.
Рассмотрим первые task_count задач и переведём каждую из них в следующий 
статус в соответствии с естественным порядком: NEW → IN_PROGRESS → TESTING → DONE.
Вернём кортеж из двух элементов: информацию о статусах обновившихся задач 
(включая те, которые оказались в статусе DONE) и информацию о статусах остальных 
не выполненных задач.
В случае отсутствия разработчика с именем person метод PerformPersonTasks должени 
вернуть кортеж из двух пустых TasksInfo

Гарантируется, что task_count является положительным числом. Если task_count превышает 
текущее количество невыполненных задач разработчика, достаточно считать, что task_count 
равен количеству невыполненных задач: дважды обновлять статус какой-либо задачи в этом 
случае не нужно.

Кроме того, гарантируется, что метод GetPersonTasksInfo не будет вызван для 
разработчика, не имеющего задач.

Пример работы метода PerformPersonTasks
Предположим, что у конкретного разработчика имеется 10 задач со следующими статусами:

NEW — 3
IN_PROGRESS — 2
TESTING — 4
DONE — 1
Поступает команда PerformPersonTasks с параметром task_count = 4, что означает 
обновление статуса для 3 задач c NEW до IN_PROGRESS и для 1 задачи с IN_PROGRESS 
до TESTING. Таким образом, новые статусы задач будут следующими:

IN_PROGRESS — 3 обновлённых, 1 старая
TESTING — 1 обновлённая, 4 старых
DONE — 1 старая
В этом случае необходимо вернуть кортеж из 2 словарей:

Обновлённые задачи: IN_PROGRESS — 3, TESTING — 1.
Не обновлённые задачи, исключая выполненные: IN_PROGRESS — 1, TESTING — 4.
Словари не должны содержать лишних элементов, то есть статусов, которым соответствует 
ноль задач.

Примечание
Обновление словаря одновременно с итерированием по нему может привести к непредсказуемым 
последствиям. При возникновении такой необходимости рекомендуется сначала в отдельном 
временном словаре собрать информацию об обновлениях, а затем применить их к основному 
словарю.

Пример кода
// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
        ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
        ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
        ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    
    TasksInfo updated_tasks, untouched_tasks;
    
    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
    
    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}

Вывод
Ilia's tasks: 1 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Ivan's tasks: 3 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Updated Ivan's tasks: 0 new tasks, 2 tasks in progress, 0 tasks are being tested, 0 tasks are done
Untouched Ivan's tasks: 1 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Updated Ivan's tasks: 0 new tasks, 1 tasks in progress, 1 tasks are being tested, 0 tasks are done
Untouched Ivan's tasks: 0 new tasks, 1 tasks in progress, 0 tasks are being tested, 0 tasks are done

Пояснение
В этой задаче вам надо прислать на проверку файл с реализацией класса TeamTasks. 
Этот файл не должен содержать определения типов TaskStatus и TasksInfo. 
В противном случае вы получите ошибку компиляции.

Гарантируется, что типы TaskStatus и TasksInfo объявлены в точности так же, как в коде выше.
*/