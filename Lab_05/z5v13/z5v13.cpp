#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;

struct Number {
    union {
        struct {
            int popul;
            int square;
        };
        int num[2];
    };
};

struct Country {
    string name;
    string capital;
    string president;
    Number stats;
};
const int MAX_COUNTRIES = 10;
const string FILENAME = "countries.txt";

void addCountry(Country countries[], int& count) {
    if (count >= MAX_COUNTRIES) {
        cout << "Достигнут максимум записей!\n";
        return;
    }

    cout << "Название страны: ";
    cin >> countries[count].name;
    cout << "Столица: ";
    cin >> countries[count].capital;
    cout << "Президент: ";
    cin >> countries[count].president;

    cout << "Население и площадь (через пробел): ";
    cin >> countries[count].stats.num[0] >> countries[count].stats.num[1];

    count++;
}

void printCountries(Country countries[], int count) {
    for (int i = 0; i < count; i++) {
        cout << "\nСтрана #" << i + 1 << endl;
        cout << "Название: " << countries[i].name << endl
            << "Столица: " << countries[i].capital << endl
            << "Президент: " << countries[i].president << endl
            << "Население: " << countries[i].stats.popul << " чел." << endl
            << "Площадь: " << countries[i].stats.square << " км²" << endl;
    }
}

void searchByCapital(Country countries[], int count) {
    string capital;
    cout << "Введите столицу: ";
    cin >> capital;

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (countries[i].capital == capital) {
            printCountries(&countries[i], 1);
            found = true;
        }
    }
    if (!found) cout << "Не найдено!\n";
}

void saveToFile(Country countries[], int count) {
    ofstream f(FILENAME);
    for (int i = 0; i < count; i++) {
        f << countries[i].name << "\n"
            << countries[i].capital << "\n"
            << countries[i].president << "\n"
            << countries[i].stats.num[0] << " "
            << countries[i].stats.num[1] << "\n";
    }
    f.close();
}

void loadFromFile(Country countries[], int& count) {
    ifstream f(FILENAME);
    count = 0;

    while (count < MAX_COUNTRIES &&
        getline(f, countries[count].name) &&
        getline(f, countries[count].capital) &&
        getline(f, countries[count].president)) {

        f >> countries[count].stats.num[0]
            >> countries[count].stats.num[1];
        f.ignore();
        count++;
    }
    f.close();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

   
    Country countries[MAX_COUNTRIES];
    int count = 0;
    int choice;

    while(true){
        cout << "\n1 - Добавить страну\n"
            << "2 - Показать все\n"
            << "3 - Поиск по столице\n"
            << "4 - Сохранить в файл\n"
            << "5 - Загрузить из файла\n"
            << "6 - Выход\n"
            << "Выбор: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: addCountry(countries, count); break;
        case 2: printCountries(countries, count); break;
        case 3: searchByCapital(countries, count); break;
        case 4: saveToFile(countries, count); break;
        case 5: loadFromFile(countries, count); break;
        case 6: return 0;
        default: cout << "Неверный выбор!\n";
        }
    }
}