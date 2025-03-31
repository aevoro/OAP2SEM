#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>

using namespace std;

struct number {
    union {
        struct {
            int contest;
            int payment;
        };
        int num[2];
    };
};

struct info {
    string nameUn;
    string addres;
    string speciality;
    number numInfo;
};

const int MAX = 10;

void addUn(info date[], int& count) {
    if (count >= MAX) {
        cout << "Достигнут максимум записей!\n";
        return;
    }

    cout << "Университет: ";
    cin >> date[count].nameUn;
    cout << "Месторасположение: ";
    cin >> date[count].addres;
    cout << "Специальность: ";
    cin >> date[count].speciality;

    cout << "Проходной балл: ";
    cin >> date[count].numInfo.contest;
    cout << "Стоимость: ";
    cin >> date[count].numInfo.payment;

    count++;
}

void printInfo(info date[], int count) {
    for (int i = 0; i < count; i++) {
        cout << "#" << i + 1 << endl;
        cout << "Университет: " << date[i].nameUn << endl;
        cout << "Месторасположение: " << date[i].addres << endl;
        cout << "Специальность: " << date[i].speciality << endl;
        cout << "Проходной бал: " << date[i].numInfo.contest << endl;
        cout << "Стоимость: " << date[i].numInfo.payment << endl;
        cout << "-------------------------------------------------" << endl;
    }
 }

void loadFromFile(info date[], int &count) {
    ifstream f("university.txt");

    while (count < MAX&&
        getline(f, date[count].nameUn) &&
        getline(f, date[count].addres) &&
        getline(f, date[count].speciality)) {

        f >> date[count].numInfo.contest;
        f >> date[count].numInfo.payment;
        f.ignore();
        count++;
    }
    f.close();
}


void checkContest(info date[], int count) {
    int constContest = 400;
    string constUn;

    for (int i = 0; i < count; i++) {
        if (date[i].numInfo.contest < constContest) {
            constContest = date[i].numInfo.contest;
            constUn = date[i].nameUn;
        }
    }
    cout << "Университет с наименьшим проходным баллом: " << constUn << ": " << constContest << endl;
}

void inFile(info date[], int count) {
    ofstream File("university.txt");
    File.is_open();
    for (int i = 0; i < count; i++) {
        
        File  << date[i].nameUn << endl;
        File << date[i].addres << endl;
        File << date[i].speciality << endl;
        File << date[i].numInfo.contest << endl;
        File << date[i].numInfo.payment << endl;
        
    }
    File.close();
}

int main() {
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    
    int count = 0;
    info university[MAX];
    

    while (true) {
        int sw;
        cout << "1 - Вывод информации\n2 - Поиск по минимальному баллу\n3 - Записать в файл\n4 - Прочитать из файла\n5 - Добавить\n6 - Выход\nВыбор: ";
        cin >> sw;
        cout << endl;
        switch (sw) {

     case 1:  printInfo(university, count); break;
     case 2: checkContest(university, count); break;
     case 3: inFile(university, count); cout << "Данные записаны." << endl; break;
     case 4: loadFromFile(university, count); cout << "Данные прочитаны." << endl; break;
     case 5: addUn(university, count);break;
     case 6: return 0;
    }
        cout << endl;
}
}