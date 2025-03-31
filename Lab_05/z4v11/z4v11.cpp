#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

struct Lombard {
    string lastName;
    string productName;
    int gradePrice;
    double loanAmount;
    int storagePeriod;

    struct {
        int day : 5;
        int month : 4;
        int year : 7;
    } date;

    bool isExpired(int currentDay, int currentMonth, int currentYear) const {
        int endYear = date.year + 2000;
        int endMonth = date.month;
        int endDay = date.day + storagePeriod;

        while (endDay > 31) {
            endDay -= 31;
            endMonth++;
            if (endMonth > 12) {
                endMonth = 1;
                endYear++;
            }
        }

        if (endYear < currentYear) return true;
        if (endYear == currentYear && endMonth < currentMonth) return true;
        if (endYear == currentYear && endMonth == currentMonth && endDay < currentDay) return true;
        return false;
    }
};

void printItem(Lombard items[], int size, int currentDay, int currentMonth, int currentYear) {
    for (int i = 0; i < size; i++) {
        if (items[i].lastName.empty()) continue;

        cout << "Товар #" << i + 1 << endl;
        cout << "Фамилия клиента: " << items[i].lastName << endl;
        cout << "Наименование товара: " << items[i].productName << endl;
        cout << "Оценочная стоимость: " << items[i].gradePrice << endl;
        cout << "Сумма под залог: " << items[i].loanAmount << endl;
        cout << "Дата сдачи: " << items[i].date.day << "."
            << items[i].date.month << "."
            << (items[i].date.year + 2000) << endl;
        cout << "Срок хранения: " << items[i].storagePeriod << " дней" << endl;
        cout << "Статус: "
            << (items[i].isExpired(currentDay, currentMonth, currentYear) ? "Просрочен" : "В хранении")
            << "\n-------------------------" << endl;
    }
}

void searchExpired(Lombard items[], int size, int currentDay, int currentMonth, int currentYear) {
    bool found = false;
    for (int i = 0; i < size; i++) {
        if (items[i].isExpired(currentDay, currentMonth, currentYear)) {
            if (items[i].lastName.empty()) continue;
            cout << "Товар #" << i + 1 << endl;
            cout << "Фамилия клиента: " << items[i].lastName << endl;
            cout << "Наименование товара: " << items[i].productName << endl;
            cout << "Дата окончания хранения: "
                << (items[i].date.day + items[i].storagePeriod) % 31 << "."
                << (items[i].date.month + (items[i].date.day + items[i].storagePeriod) / 31) % 12 << "."
                << (currentYear + (items[i].date.month + (items[i].date.day + items[i].storagePeriod) / 31) / 12) << endl;
                cout << "-------------------------" << endl;
                found = true;
        }
    }
    if (!found) cout << "Просроченных товаров нет!\n";
}



void searchByName(Lombard items[], int size, int currentDay, int currentMonth, int currentYear) {
    string name;
    cout << "Введите название товара: ";
    cin >> name;

    bool found = false;
    for (int i = 0; i < size; i++) {
        if (items[i].productName == name && !items[i].lastName.empty()) {
            cout << "Товар #" << i + 1 << endl;
            cout << "Фамилия клиента: " << items[i].lastName << endl;
            cout << "Оценочная стоимость: " << items[i].gradePrice << endl;
            cout << "Дата окончания хранения: "
                << (items[i].date.day + items[i].storagePeriod) % 31 << "."
                << (items[i].date.month + (items[i].date.day + items[i].storagePeriod) / 31) % 12 << "."
                << (currentYear + (items[i].date.month + (items[i].date.day + items[i].storagePeriod) / 31) / 12) << endl;
            cout << "-------------------------" << endl;
            found = true;
        }
    }
    if (!found) cout << "Товар не найден!\n";
}

void inputItem(Lombard items[], int size, int currentDay, int currentMonth, int currentYear) {

    int num;

    cout << "Введите номер товара который вы хотите добавить: "; cin >> num;

    for (int i = 0; i < size; i++) {
        {
            if (i = num - 1)
                cout << "\n=== Ввод нового товара ===" << endl;
            cout << "Фамилия клиента: ";
            cin >> items[i].lastName;
            cout << "Наименование товара: ";
            cin >> items[i].productName;
            cout << "Оценочная стоимость: ";
            cin >> items[i].gradePrice;
            cout << "Сумма под залог: ";
            cin >> items[i].loanAmount;
            cout << "Срок хранения (дней): ";
            cin >> items[i].storagePeriod;

            items[i].date.day = currentDay;
            items[i].date.month = currentMonth;
            items[i].date.year = currentYear - 2000;

            cout << "Товар успешно добавлен!" << endl;
            break;
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Lombard items[5] = {
        {"Иванов", "Часы", 10000, 5000, 30, {11, 3, 25}},
        {"Сергеев", "Телефон", 15000, 8000, 30, {13, 2, 25}},
        {"Петров", "Ноутбук", 30000, 20000, 60, {1, 1, 25}}
    };

    int currentDay, currentMonth, currentYear;
    cout << "Введите текущую дату (дд мм гг): ";
    cin >> currentDay >> currentMonth >> currentYear;
    currentYear += 2000;

    while (true) {
        cout << "\nМеню:\n"
            << "1 - Показать все товары\n"
            << "2 - Поиск просроченных\n"
            << "3 - Удалить товар\n"
            << "4 - Поиск по названию\n"
            << "5 - Добавить товар\n"
            << "6 - Выход\n"
            << "Выбор: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            printItem(items, 5, currentDay, currentMonth, currentYear);
            break;

        case 2:
            searchExpired(items, 5, currentDay, currentMonth, currentYear);
            break;

        case 3: {
            printItem(items, 5, currentDay, currentMonth, currentYear);
            int index;
            cout << "Введите номер товара для удаления: ";
            cin >> index;

            if (index < 1 || index > 5) {
                cout << "Неверный номер!\n";
                break;
            }

            items[index - 1] = Lombard{};
            cout << "Товар удален!\n";
            break;
        }

        case 4:
            searchByName(items, 5, currentDay, currentMonth, currentYear);
            break;

        case 5:
            inputItem(items, 5,currentDay, currentMonth, currentYear);
            break;

        case 6:
            return 0;

        default:
            cout << "Неверный выбор!\n";
        }
    }
}