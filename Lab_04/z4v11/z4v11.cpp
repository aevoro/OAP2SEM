#include <iostream>
#include <string>
#include <fstream>
#include <Tchar.h>
#include <Windows.h>

using namespace std;

typedef int day;
typedef int month;

struct date
{
    day dd;
    month mm;

    bool operator==(const date& other) const {
        return mm == other.mm && dd == other.dd;
    }
};

struct dannye
{
    string fam;
    string name;
    string otch;
    string street;
    string home;
    string house;
    string number;
    string work;
    string dol;
    date birthDate;
};

void printPerson(const dannye& person) {
    cout << "Ф.И.О: " << person.fam << " " << person.name << " " << person.otch << endl
        << "Дата рождения: " << person.birthDate.dd << "." << person.birthDate.mm << endl
        << "Адрес: ул. " << person.street << " д. " << person.home << " кв. " << person.house << endl
        << "Телефон: " << person.number << endl
        << "Место работы: " << person.work << endl
        << "Должность: " << person.dol << endl;
}

void saveToFile(const dannye& person) {
    ofstream file("File.txt", ios::app);
    file << person.fam << "|" << person.name << "|" << person.otch << "|"
        << person.birthDate.dd << "|" << person.birthDate.mm << "|"
        << person.street << "|" << person.home << "|" << person.house << "|"
        << person.number << "|" << person.work << "|" << person.dol << endl;
    file.close();
}

void searchInFile(const string& filename, const string& fam) {
    ifstream file(filename);
    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t pos = line.find(fam + "|");
        if (pos == 0) {
            dannye person;
            size_t start = 0;
            size_t end = line.find('|');

            person.fam = line.substr(start, end);
            start = end + 1;

            end = line.find('|', start);
            person.name = line.substr(start, end - start);
            start = end + 1;

            end = line.find('|', start);
            person.otch = line.substr(start, end - start);
            start = end + 1;

            end = line.find('|', start);
            person.birthDate.dd = stoi(line.substr(start, end - start));
            start = end + 1;

            end = line.find('|', start);
            person.birthDate.mm = stoi(line.substr(start, end - start));
            start = end + 1;

            end = line.find('|', start);
            person.street = line.substr(start, end - start);
            start = end + 1;

            end = line.find('|', start);
            person.home = line.substr(start, end - start);
            start = end + 1;

            end = line.find('|', start);
            person.house = line.substr(start, end - start);
            start = end + 1;

            end = line.find('|', start);
            person.number = line.substr(start, end - start);
            start = end + 1;

            end = line.find('|', start);
            person.work = line.substr(start, end - start);
            start = end + 1;

            person.dol = line.substr(start);

            printPerson(person);
            found = true;
            break;
        }
    }

    if (!found) cout << "Запись не найдена!" << endl;
    file.close();
}

void deleteFromFile(const string& filename, const string& fam) {
    ifstream inFile(filename);
    ofstream outFile("temp.txt");
    string line;
    bool deleted = false;

    while (getline(inFile, line)) {
        if (line.find(fam + "|") != 0) {
            outFile << line << endl;
        }
        else {
            deleted = true;
        }
    }

    inFile.close();
    outFile.close();
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (!deleted) cout << "Запись не найдена!" << endl;
}

int main(int argc, _TCHAR* argv[]) {
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    date currentDate;
    cout << "Текущая дата (дд мм): ";
    cin >> currentDate.dd >> currentDate.mm;

    while (true) {
        cout << "\n1 - Добавить\n2 - Поиск\n3 - Удалить\n4 - Выход\n Выбор: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            dannye person;
            cout << "Фамилия: "; getline(cin, person.fam);
            cout << "Имя: "; getline(cin, person.name);
            cout << "Отчество: "; getline(cin, person.otch);
            cout << "День рождения: "; cin >> person.birthDate.dd;
            cout << "Месяц рождения: "; cin >> person.birthDate.mm;
            cin.ignore();
            cout << "Улица: "; getline(cin, person.street);
            cout << "Дом: "; getline(cin, person.home);
            cout << "Квартира: "; getline(cin, person.house);
            cout << "Телефон: "; getline(cin, person.number);
            cout << "Место работы: "; getline(cin, person.work);
            cout << "Должность: "; getline(cin, person.dol);

            saveToFile(person);

            if (currentDate == person.birthDate) {
                cout << "\n!!! С днем рождения, " << person.fam << " " << person.name << " !!!\n";
            }
        }
        else if (choice == 2) {
            string fam;
            cout << "Поиск фамилии: ";
            getline(cin, fam);
            searchInFile("File.txt", fam);
        }
        else if (choice == 3) {
            string fam;
            cout << "Удалить фамилию: ";
            getline(cin, fam);
            deleteFromFile("File.txt", fam);
        }
        else if (choice == 4) {
            break;
        }
    }
    return 0;
}