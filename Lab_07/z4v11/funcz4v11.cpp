#include "Headerz4v11.h"
string filename = "File.txt";

void menu() {
	cout << "1 - Записать в файл\n2 - Прочитать из файла\n3 - Добавить элемент\n4 - Удаление элементов кратных 3\n5 - Очистка и вывод\n6 - Выход\nВыбор: ";
}
void saveInFile(Stack* myStk) {
    ofstream File(filename);
    if (!File.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }

    Stack* current = myStk;
    while (current != NULL) {
        File << current->data << " ";
        current = current->next;
    }

    File.close();
    cout << "Стек сохранен в файл." << endl << endl;
}

void readFile(Stack*& myStk) {
    ifstream File(filename);
    if (!File.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }

    while (myStk != NULL) {
        Stack* temp = myStk;
        myStk = myStk->next;
        delete temp;
    }
    myStk = NULL;

    int value;
    while (File >> value) {
        Stack* e = new Stack;
        e->data = value;
        e->next = myStk;
        myStk = e;
    }

    File.close();
    cout << "Стек загружен из файла." << endl << endl;
}

void addElem(Stack*& myStk) {
    int x;
    cout << "Введите элемент: ";
    cin >> x;
    Stack* e = new Stack;

    e->data = x;
    e->next = myStk;
    myStk = e;

    cout << "Элемент добавлен" << endl << endl;
}

void deleteElemThi(Stack*& myStk) {
    Stack* current = myStk;
    Stack* prev = NULL;
    bool deleted = false;

    while (current != NULL) {
        if (current->data % 3 == 0) {
            Stack* temp = current;
            if (prev == NULL) {
                myStk = current->next;
            }
            else {
                prev->next = current->next;
            }
            current = current->next;
            delete temp;
            deleted = true;
        }
        else {
            prev = current;
            current = current->next;
        }
    }

    if (deleted) {
        cout << "Элементы, кратные 3, удалены." << endl << endl;
    }
    else {
        cout << "Элементов, кратных 3, не найдено." << endl << endl;
    }
}

int deleteSt(Stack*& myStk) {
    if (myStk == NULL) {
        cout << "Стек пуст!" << endl;
        return -1;
    }
    else {
        Stack* e = myStk;
        int x = myStk->data;
        myStk = myStk->next;
        delete e;
        return x;
    }
}

void clearSt(Stack*& myStk) {
    if (myStk == NULL) {
        cout << "Стек пуст!" << endl;
        return;
    }

    cout << "Содержимое стека: ";
    while (myStk != NULL) {
        cout << deleteSt(myStk) << " ";
    }
    cout << endl << "Стек очищен." << endl << endl;
}
