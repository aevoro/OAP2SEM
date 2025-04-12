#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

struct list {
    int symbol;
    list* next;
};

void insert(list*& p, int value) {
    list* newP = new list;
    newP->symbol = value;
    newP->next = p;
    p = newP;
}

void delElem(list*& p) {
    if (p == nullptr) {
        cout << "Список пуст!" << endl;
        return;
    }

    int value;
    cout << "Введите удаляемое число: ";
    cin >> value;

    if (p->symbol == value) {
        list* temp = p;
        p = p->next;
        delete temp;
        return;
    }

    list* current = p;
    while (current->next != nullptr) {
        if (current->next->symbol == value) {
            list* temp = current->next;
            current->next = current->next->next;
            delete temp;
            return;
        }
        current = current->next;
    }

    cout << "Элемент не найден!" << endl;
}

void searchElem(list* p) {
    int sumValue = 0;
    while (p != NULL) {
        if (p->symbol < -9 && p->symbol > -100) {
            sumValue += p->symbol;
        }
        p = p->next;
    }
    if (sumValue != 0) {
        cout << "Сумма отрицательных двухзначных элементов: " << sumValue << endl;
    }
    else {
        cout << "Таких элементов нет" << endl;
    }
}

void printList(list* p) {
    if (p == NULL) {
        cout << endl << "Список пуст." << endl << endl;
    }
    else {
        cout << "Список: ";
        while (p != NULL) {
            cout << p->symbol << " ";
            p = p->next;
        }
        cout << endl;
    }
}

void printFile(list* p) {
    ofstream File("File.txt");
    while (p != nullptr) {
        File << p->symbol << endl;
        p = p->next;
    }
    cout << endl << "Данные записаны в файл." << endl << endl;
    File.close();
}

void readFile(list*& p) {
    ifstream File("File.txt");
    if (!File.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }

    while (p != nullptr) {
        list* temp = p;
        p = p->next;
        delete temp;
    }

    list** tail = &p;
    string line;
    while (getline(File, line)) {
        *tail = new list{ stoi(line), nullptr };
        tail = &((*tail)->next);
    }

    File.close();
    cout << "Данные успешно загружены" << endl;
}

void menu() {
    cout << "1 - Добавить элемент\n2 - Удалить элемент\n3 - Cумма отрицательных двухзначных элементов\n4 - Вывод списка\n5 - Записать в файл\n6 - Прочитать из файла\n7 - Выход\nВыбор: ";
}

int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    list* first = nullptr;
    int choise;
    int value;

    while (true) {
        menu();
        cin >> choise;
        switch (choise) {
        case 1: {
            cout << "Введите число: ";
            cin >> value;
            insert(first, value);
            cout << endl << "Число добавлено" << endl << endl;
            break;
        }
        case 2: {
            delElem(first);
            break;
        }
        case 3: {
            searchElem(first);
            break;
        }
        case 4: {
            printList(first);
            break;
        }
        case 5: {
            printFile(first);
            break;
        }
        case 6: {
            readFile(first);
            break;
        }
        case 7: {
            while (first != nullptr) {
                list* temp = first;
                first = first->next;
                delete temp;
            }
            return 0;
        }
        }
    }
}