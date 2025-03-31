#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;

struct Date {
    union {
        struct {
            int day;
            int month;
            int year;
        };
        int dateArray[3];
    };
};

struct Car {
    string name;
    string color;
    string bodyType;
    string owner;
    Date productionDate;
    Date inspectionDate;
};

void inputCar(Car& car) {
    cout << "\nВвод данных об автомобиле:\n";
    cout << "Марка: ";
    getline(cin, car.name);
    cout << "Цвет: ";
    getline(cin, car.color);
    cout << "Тип кузова: ";
    getline(cin, car.bodyType);
    cout << "Владелец: ";
    getline(cin, car.owner);

    cout << "Дата производства (ДД ММ ГГГГ): ";
    for (int i = 0; i < 3; i++) {
        cin >> car.productionDate.dateArray[i];
    }

    cout << "Дата техосмотра (ДД ММ ГГГГ): ";
    for (int i = 0; i < 3; i++) {
        cin >> car.inspectionDate.dateArray[i];
    }
    cin.ignore();
}

void printCar(const Car& car) {
    cout << "\nМарка: " << car.name
        << "\nЦвет: " << car.color
        << "\nТип кузова: " << car.bodyType
        << "\nВладелец: " << car.owner
        << "\nДата производства: "
        << car.productionDate.day << "."
        << car.productionDate.month << "."
        << car.productionDate.year
        << "\nДата техосмотра: "
        << car.inspectionDate.day << "."
        << car.inspectionDate.month << "."
        << car.inspectionDate.year
        << "\n-------------------------\n";
}

void saveToFile(const vector<Car>& cars, const string& filename) {
    ofstream file(filename);
    for (const auto& car : cars) {
        file << car.name << "\n"
            << car.color << "\n"
            << car.bodyType << "\n"
            << car.owner << "\n"
            << car.productionDate.day << " "
            << car.productionDate.month << " "
            << car.productionDate.year << "\n"
            << car.inspectionDate.day << " "
            << car.inspectionDate.month << " "
            << car.inspectionDate.year << "\n";
    }
    file.close();
}

vector<Car> loadFromFile(const string& filename) {
    vector<Car> cars;
    ifstream file(filename);
    if (!file.is_open()) return cars;

    Car temp;
    while (getline(file, temp.name) &&
        getline(file, temp.color) &&
        getline(file, temp.bodyType) &&
        getline(file, temp.owner)) {

        for (int i = 0; i < 3; i++) {
            file >> temp.productionDate.dateArray[i];
        }
        for (int i = 0; i < 3; i++) {
            file >> temp.inspectionDate.dateArray[i];
        }
        file.ignore();
        cars.push_back(temp);
    }
    file.close();
    return cars;
}

void searchByOwner(const vector<Car>& cars, const string& owner) {
    bool found = false;
    for (const auto& car : cars) {
        if (car.owner == owner) {
            printCar(car);
            found = true;
        }
    }
    if (!found) {
        cout << "Автомобили владельца " << owner << " не найдены!\n";
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<Car> cars;
    string filename = "cars.txt";

    cars = loadFromFile(filename);

    while (true) {
        cout << "\nМеню:\n"
            << "1 - Добавить автомобиль\n"
            << "2 - Показать все автомобили\n"
            << "3 - Поиск по владельцу\n"
            << "4 - Сохранить в файл\n"
            << "5 - Загрузить из файла\n"
            << "6 - Выход\n"
            << "Выбор: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            Car newCar;
            inputCar(newCar);
            cars.push_back(newCar);
            break;
        }
        case 2: {
            cout << "\nСписок автомобилей:\n";
            for (const auto& car : cars) {
                printCar(car);
            }
            break;
        }
        case 3: {
            string owner;
            cout << "Введите фамилию владельца: ";
            getline(cin, owner);
            searchByOwner(cars, owner);
            break;
        }
        case 4: {
            saveToFile(cars, filename);
            cout << "Данные сохранены в файл!\n";
            break;
        }
        case 5: {
            cars = loadFromFile(filename);
            cout << "Данные загружены из файла!\n";
            break;
        }
        case 6: {
            return 0;
        }
        default: {
            cout << "Неверный выбор!\n";
        }
        }
    }
}

