#include "Headerz4v15.h"
string filename = "File.txt";

void menu() {
    cout << "1 - Записать в файл\n2 - Прочитать из файла\n3 - Добавить элемент\n4 - Удаление элемента стека\n5 - Очистка и вывод\n6 - Выход\nВыбор: ";
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

int checkDupl(Stack*& myStk) {
    if (myStk == nullptr) {
        cout << "Стек пуст!" << endl << endl;
        return 0;
    }

    vector<int> elements;
    Stack* current = myStk;
    while (current != nullptr) {
        elements.push_back(current->data);
        current = current->next;
    }

    unordered_map<int, int> freq;
    int target = -1;

    for (int i = elements.size() - 1; i >= 0; i--) {
        freq[elements[i]]++;
        if (freq[elements[i]] > 1) {
            target = elements[i];
        }
    }

    if (target == -1) {
        cout << "Дубликаты не найдены!" << endl << endl;
        return 0;
    }

    bool isRemoved = false;
    vector<int> newElements;
    for (int elem : elements) {
        if (!isRemoved && elem == target) {
            isRemoved = true;
            continue;
        }
        newElements.push_back(elem);
    }

    while (myStk != nullptr) {
        Stack* temp = myStk;
        myStk = myStk->next;
        delete temp;
    }

    for (auto it = newElements.rbegin(); it != newElements.rend(); ++it) {
        Stack* e = new Stack;
        e->data = *it;
        e->next = myStk;
        myStk = e;
    }

    cout << "Первый повторяющийся элемент '" << target << "' удален" << endl << endl;
    return 0;
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
