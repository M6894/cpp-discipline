
#include <iostream>
#include <string>

using namespace std;

struct Specialization {
    string data;
    explicit Specialization(const string& new_specialization) {
        data = new_specialization;
    }
};

struct Course {
    string data;
    explicit Course(const string& new_course) {
        data = new_course;
    }
};

struct Week {
    string data;
    explicit Week(const string& new_week) {
        data = new_week;
    }
};

struct LectureTitle {
    string specialization;
    string course;
    string week;
    LectureTitle(const Specialization& new_specialization, const Course& new_course, const Week& new_week) {
        specialization = new_specialization.data;
        course = new_course.data;
        week = new_week.data;
    }
};


void PrintLectureTitle(const LectureTitle& sample) {
    cout << sample.specialization << ", " << sample.course << ", " << sample.week << endl; 
}

/*
int main() {
    LectureTitle title(
        Specialization("C++"),
        Course("White belt"),
        Week("4th")
    );
    PrintLectureTitle(title);
    return 0;
}



/* MIPT and Yandex implementation (same):
struct Specialization {
    explicit Specialization(const string& new_value) {
        value = new_value;
    }
    string value;
};

struct Course {
    explicit Course(const string& new_value) {
        value = new_value;
    }
    string value;
};

struct Week {
    explicit Week(const string& new_value) {
        value = new_value;
    }
    string value;
};

struct LectureTitle {
    LectureTitle(const Specialization& new_specialization,
                const Course& new_course,
                const Week& new_week) {
        specialization = new_specialization.value;
        course = new_course.value;
        week = new_week.value;
    }
    string specialization;
    string course;
    string week;
};
*/



/* Task:
Дана структура LectureTitle:
struct LectureTitle {
    string specialization;
    string course;
    string week;
};

Допишите конструктор и структуры Specialization, Course, Week так, чтобы объект 
LectureTitle можно было создать с помощью кода

LectureTitle title(
    Specialization("C++"),
    Course("White belt"),
    Week("4th")
);

но нельзя было с помощью следующих фрагментов кода:

LectureTitle title("C++", "White belt", "4th");

LectureTitle title(string("C++"), string("White belt"), string("4th"));

LectureTitle title = {"C++", "White belt", "4th"};

LectureTitle title = {{"C++"}, {"White belt"}, {"4th"}};

LectureTitle title(
    Course("White belt"),
    Specialization("C++"),
    Week("4th")
);

LectureTitle title(
    Specialization("C++"),
    Week("4th"),
    Course("White belt")
);
*/
