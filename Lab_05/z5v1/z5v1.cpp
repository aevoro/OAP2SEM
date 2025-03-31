#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>

using namespace std;

struct examInfo {
    union {
        char examName[50]; 
    };
    
    string examDate; 
};

struct teacher {
    string lastName;
    examInfo exam;
};

const int MAX = 10;

void addTeacher(teacher date[], int& count) {
    if (count >= MAX) {
        cout << "Достигнут максимум записей!\n";
        return;
    }

    cout << "Фамилия преподавателя: ";
    cin >> date[count].lastName;

        cout << "Название экзамена: ";
        cin.ignore();
        cin.getline(date[count].exam.examName, 50);

    cout << "Дата экзамена: ";
    cin >> date[count].exam.examDate;

    count++;
}

void printInfo(teacher date[], int count) {
    for (int i = 0; i < count; i++) {
        cout << "#" << i + 1 << endl;
        cout << "Фамилия преподавателя: " << date[i].lastName << endl;
       
            cout << "Название экзамена: " << date[i].exam.examName << endl;
 
        cout << "Дата экзамена: " << stoi(date[i].exam.examDate.substr(0,2)) << "." << stoi(date[i].exam.examDate.substr(2, 2)) << endl;
        cout << "-------------------------------------------------" << endl;
    }
}

void loadFromFile(teacher date[], int& count) {
    ifstream f("teachers.txt");

    while (count < MAX &&
       getline(f, date[count].lastName)){
            f.getline(date[count].exam.examName, 50);
        f >> date[count].exam.examDate;
        f.ignore();
        count++;
    }
    f.close();
}

void searchByLastName(teacher date[], int count) {
    string lastName;
    cout << "Введите фамилию преподавателя для поиска: ";
    cin >> lastName;

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (date[i].lastName == lastName) {
            cout << "Фамилия преподавателя: " << date[i].lastName << endl;
            
                cout << "Название экзамена: " << date[i].exam.examName << endl;
            cout << "Дата экзамена: " << date[i].exam.examDate << endl;
            cout << "-------------------------------------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Преподаватель с такой фамилией не найден.\n";
    }
}

void inFile(teacher date[], int count) {
    ofstream File("teachers.txt");
    if (File.is_open()) {
        for (int i = 0; i < count; i++) {
            File << date[i].lastName << endl;
            
                File << date[i].exam.examName << endl;
            File << date[i].exam.examDate << endl;
        }
        File.close();
    }
    else {
        cout << "Ошибка открытия файла для записи.\n";
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int count = 0;
    teacher teachers[MAX];

    while (true) {
        int sw;
        cout << "1 - Вывод информации\n2 - Поиск по фамилии\n3 - Записать в файл\n4 - Прочитать из файла\n5 - Добавить\n6 - Выход\nВыбор: ";
        cin >> sw;
        cout << endl;
        switch (sw) {
        case 1:  printInfo(teachers, count); break;
        case 2: searchByLastName(teachers, count); break;
        case 3: inFile(teachers, count); cout << "Данные записаны." << endl; break;
        case 4: loadFromFile(teachers, count); cout << "Данные прочитаны." << endl; break;
        case 5: addTeacher(teachers, count); break;
        case 6: return 0;
        default: cout << "Неверный выбор.\n";
        }
        cout << endl;
    }
}