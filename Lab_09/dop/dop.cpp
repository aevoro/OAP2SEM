#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <iomanip> 

using namespace std;

struct Student {
    string fam;
    string name;
    string otch;
    int year;
    int course;
    int numGroup;
    vector<pair<string, int>> grades;
    Student* next;
    Student* prev;
};

Student* head = nullptr;
Student* tail = nullptr;

void addStudent(const Student& st) {
    Student* newStudent = new Student(st);
    newStudent->next = nullptr;

    if (!head) {
        newStudent->prev = nullptr;
        head = tail = newStudent;
    }
    else {
        newStudent->prev = tail;
        tail->next = newStudent;
        tail = newStudent;
    }
}

void printStudents() {
    Student* current = head;
    while (current) {
        cout << "Фамилия: " << current->fam << "\n"
            << "Имя: " << current->name << "\n"
            << "Отчество: " << current->otch << "\n"
            << "Год рождения: " << current->year << "\n"
            << "Курс: " << current->course << "\n"
            << "Группа: " << current->numGroup << "\n"
            << "Оценки: ";

        for (size_t i = 0; i < current->grades.size(); ++i) {
            cout << current->grades[i].first << " - "
                << current->grades[i].second;
            if (i != current->grades.size() - 1) cout << ", ";
        }

        cout << "\n----------------------------------------\n";
        current = current->next;
    }
}

    Student* findMinStudent() {
        if (!head) return nullptr; 

        Student* youngest = head;
        Student* current = head->next;

        while (current) {
            if (current->year > youngest->year) {
                youngest = current;
            }
            current = current->next;
        }
        return youngest;
    }
    Student* findMaxStudent() {
        if (!head) return nullptr;

        Student* senior = head;
        Student* current = head->next;

        while (current) {
            if (current->year < senior->year) {
                senior = current;
            }
            current = current->next;
        }
        return senior;
    }
    bool compareStudents(const Student* a, const Student* b) {
    
        if (a->course != b->course) {
            return a->course < b->course;
        }
        return a->fam < b->fam;
    }
    
    void sortStudents() {
        if (!head || !head->next) return;

        vector<Student*> vec;
        Student* curr = head;
        while (curr) {
            vec.push_back(curr);
            curr = curr->next;
        }

        sort(vec.begin(), vec.end(), compareStudents);

        head = vec[0];
        head->prev = nullptr;
        tail = vec.back();
        tail->next = nullptr;

        for (size_t i = 0; i < vec.size(); ++i) {
            if (i > 0) vec[i]->prev = vec[i - 1];
            if (i < vec.size() - 1) vec[i]->next = vec[i + 1];
        }
    }

    void calculateGroupAverages() {
        if (!head) {
            cout << "Список студентов пуст!\n";
            return;
        }

        map<int, map<string, vector<int>>> groupData;

        Student* current = head;
        while (current) {
            int group = current->numGroup;
            for (auto& subject : current->grades) {
                string name = subject.first;
                int grade = subject.second;
                groupData[group][name].push_back(grade);
            }
            current = current->next;
        }

        for (const auto& group_entry : groupData) {
            int group = group_entry.first;
            const auto& subjects = group_entry.second;

            cout << "Группа " << group << ":\n";

            for (const auto& subject_entry : subjects) {
                const string& subject = subject_entry.first;
                const vector<int>& grades = subject_entry.second;
                double sum = 0;
                for (int grade : grades) {
                    sum += grade;
                }
                double average = sum / grades.size();
                cout << "  " << subject << ": " << average << endl;
            }
            cout << "----------------------------\n";
        }
    }

    double calculateAverage(const Student* student) {
        if (student->grades.empty()) return 0.0;

        double sum = 0.0;
        for (const auto& subject : student->grades) {
            sum += subject.second;
        }
        return sum / student->grades.size();
    }

    void findTopStudentsPerGroup() {
        if (!head) {
            cout << "Список студентов пуст!\n";
            return;
        }
        map<int, pair<double, const Student*>> groupTopStudents;

        Student* current = head;
        while (current) {
            double avg = calculateAverage(current);

            if (current->grades.empty()) {
                current = current->next;
                continue;
            }

            int group = current->numGroup;

            if (groupTopStudents.find(group) == groupTopStudents.end() ||
                avg > groupTopStudents[group].first) {
                groupTopStudents[group] = { avg, current };
            }

            current = current->next;
        }

        for (const auto& group_entry : groupTopStudents) {
            int group = group_entry.first;
            double avg = group_entry.second.first;
            const Student* best = group_entry.second.second;

            cout << "Группа " << group << ":\n"
                << "  Лучший студент: " << best->fam << " "
                << best->name << " " << best->otch << "\n"
                << "  Средний балл: " << fixed << setprecision(2) << avg << "\n"
                << "  Курс: " << best->course << "\n"
                << "----------------------------------------\n";
        }
    }


void menu() {
    cout << "(1) Сортировка\n"
        << "(2) Средний балл\n"
        << "(3) Поиск возраста\n"
        << "(4) Лучший студент\n"
        << "(5) Вывести список\n"
        << "(6) Выход\n>";
}

int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    addStudent({
        "Иванов", "Иван", "Иванович", 2007, 1, 10,
        {{"ОАиП", 9}, {"АиСД", 9}, {"КПО", 9}},
        nullptr, nullptr
        });

    addStudent({
        "Сидорова", "Мария", "Алексеевна", 2006, 2, 7,
        {{"ОАиП", 10}, {"АИСД", 8}, {"КПО", 9}},
        nullptr, nullptr
        });

    addStudent({
        "Максимова", "Мария", "Алексеевна", 2005, 2, 7,
        {{"ОАиП", 5}, {"АИСД", 2}, {"КПО", 1}},
        nullptr, nullptr
        });

    addStudent({
        "Петров", "Пётр", "Сергеевич", 2006, 1, 10,
        {{"ОАиП", 4}, {"АиСД", 5}, {"КПО", 7}},
        nullptr, nullptr
        });

    addStudent({
        "Валерова", "Александра", "Александровна", 2005, 3, 7,
        {{"ОАиП", 6}, {"АИСД", 8}, {"КПО", 9}},
        nullptr, nullptr
        });
    addStudent({
        "Александрова", "Александра", "Александровна", 2004, 3, 7,
        {{"ОАиП", 4}, {"АИСД", 1}, {"КПО", 6}},
        nullptr, nullptr
        });

    

    int choice;
    while (true) {
        system("CLS");
        menu();
        cin >> choice;
        switch (choice) {
        case 1:
            sortStudents();
            break;
        case 2:
            calculateGroupAverages();
            break;
            
        case 3: {
            system("CLS");
            Student * youngest = findMinStudent();
            if (youngest) {
                cout << "Самый молодой студент:\n";
                cout << "Фамилия: " << youngest->fam << "\n"
                    << "Имя: " << youngest->name << "\n"
                    << "Отчество: " << youngest->otch << "\n"
                    << "Год рождения: " << youngest->year << "\n"
                    << "Курс: " << youngest->course << "\n"
                    << "Группа: " << youngest->numGroup << "\n"
                    << "Оценки: ";

                for (size_t i = 0; i < youngest->grades.size(); ++i) {
                    cout << youngest->grades[i].first << " - "
                        << youngest->grades[i].second;
                    if (i != youngest->grades.size() - 1) cout << ", ";
                }
                cout << "\n----------------------------------------\n";
            }
            else {
                cout << "Список студентов пуст!\n";
            }
            
            Student* senior = findMaxStudent();
            if (senior) {
                cout << "Самый старший студент:\n";
                cout << "Фамилия: " << senior->fam << "\n"
                    << "Имя: " << senior->name << "\n"
                    << "Отчество: " << senior->otch << "\n"
                    << "Год рождения: " << senior->year << "\n"
                    << "Курс: " << senior->course << "\n"
                    << "Группа: " << senior->numGroup << "\n"
                    << "Оценки: ";

                for (size_t i = 0; i < senior->grades.size(); ++i) {
                    cout << senior->grades[i].first << " - "
                        << senior->grades[i].second;
                    if (i != senior->grades.size() - 1) cout << ", ";
                }
                cout << "\n----------------------------------------\n";
            }
            else {
                cout << "Список студентов пуст!\n";
            }
            break;
            }
        case 4:
            findTopStudentsPerGroup();
            break;
        case 5:
            printStudents();
            break;
        case 6:
            return 0;
        default:
            cout << "Неверный выбор!" << endl;
        }
        system("pause");
    }
}