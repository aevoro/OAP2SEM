#include "Headerz4v1.h"
string filename = "File.txt";

void menu() {
    cout << "1 - Записать в файл\n2 - Прочитать из файла\n3 - Добавить элемент\n4 - Раазделение стека\n5 - Очистка и вывод\n6 - Выход\nВыбор: ";
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
void Push(Stack*& top, int data) {
    Stack* newNode = new Stack;
    newNode->data = data;
    newNode->next = top;
    top = newNode;
}

int refreshStack(Stack*& myStk) {
    if (myStk == nullptr) {
        cout << "Стек пуст!" << endl << endl;
        return 0;
    }

    Stack* Positive = nullptr;
    Stack* Negative = nullptr;

    while (myStk != nullptr) {
        int x = deleteSt(myStk);
        if (x >= 0) {
            Push(Positive, x);
        }
        else {
            Push(Negative, x);
        }
    }

    cout << "Содержимое положительного стека: ";

    while (Positive != nullptr) {
        int x = deleteSt(Positive);
        cout << x << " ";
    }
    cout <<endl << "Содержимое отрицательного стека: ";
    while (Negative != nullptr) {
        int x = deleteSt(Negative);
        cout << x << " ";
    }

    cout << endl << endl;
    return 1;
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
