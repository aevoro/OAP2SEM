#include<iostream>
using namespace std;

struct Item {
    int data;
    Item* next;
};

Item* head, * tail;
int queueType; // Выбор типа очереди

bool isNull() {
    return (head == NULL);
}

void deletLast() {
    if (isNull()) {
        cout << "Очередь пуста" << endl;
    }
    else if (head == tail) {
        delete head;
        head = tail = NULL;
    }
    else {
        Item* p = head;
        while (p->next != tail) p = p->next;
        delete tail;
        tail = p;
        tail->next = NULL;
    }
}

void deletFirst() {
    if (queueType >= 3 && queueType <= 5) {
        deletLast();
        return;
    }
    if (isNull()) {
        cout << "Очередь пуста" << endl;
    }
    else {
        Item* p = head;
        head = head->next;
        delete p;
        if (head == NULL) tail = NULL;
    }
}

void getFromHead() {
    if (isNull()) {
        cout << "Очередь пуста" << endl;
    }
    else {
        cout << "Начало = " << head->data << endl;
    }
}

void insertToQueue(int x) {
    Item* p = new Item;
    p->data = x;
    p->next = NULL;

    if (isNull()) {
        head = tail = p;
        return;
    }

    switch (queueType) {
    case 1: { // LIFO
        Item* current = head;
        Item* prev = NULL;
        while (current != NULL && current->data < x) {
            prev = current;
            current = current->next;
        }
        if (prev == NULL) { 
            p->next = head;
            head = p;
        }
        else {
            prev->next = p;
            p->next = current;
        }
        if (current == NULL) {
            tail = p;
        }
        break;
    }
    case 2: { // FIFO
        Item* prev = NULL;
        Item* current = head;
        while (current != NULL && current->data > x) {
            prev = current;
            current = current->next;
        }
        if (current != NULL && current->data == x) {
            while (current->next != NULL && current->next->data == x) {
                current = current->next;
            }
            prev = current;
            current = current->next;
        }
        if (prev == NULL) {
            p->next = head;
            head = p;
        }
        else {
            prev->next = p;
            p->next = current;
        }
        if (current == NULL) {
            tail = p;
        }
        break;
    }
    case 3: { // LIFO
        Item* current = head;
        Item* prev = NULL;
        while (current != NULL && current->data <= x) {  
            prev = current;
            current = current->next;
        }
        if (prev == NULL) {
            p->next = head;
            head = p;
        }
        else {
            p->next = prev->next;
            prev->next = p;
        }
        if (p->next == NULL) {
            tail = p;
        }
        break;
    }
    case 4: { // LIFO
        Item* current = head;
        Item* prev = NULL;
        while (current != NULL && current->data > x) {
            prev = current;
            current = current->next;
        }
        if (prev == NULL) {
            p->next = head;
            head = p;
        }
        else {
            prev->next = p;
            p->next = current;
        }
        if (current == NULL) {
            tail = p;
        }
        break;
    }
    case 5: { // FIFO
        Item* prev = NULL;
        Item* current = head;
        while (current != NULL && current->data < x) {
            prev = current;
            current = current->next;
        }
        if (current != NULL && current->data == x) {
            while (current->next != NULL && current->next->data == x) {
                current = current->next;
            }
            prev = current;
            current = current->next;
        }
        if (prev == NULL) {
            p->next = head;
            head = p;
        }
        else {
            prev->next = p;
            p->next = current;
        }
        if (current == NULL) {
            tail = p;
        }
        break;
    }
    }
}

void printQueue() {
    Item* p = head;
    if (isNull()) {
        cout << "Очередь пуста" << endl;
    }
    else {
        cout << "Очередь = ";
        while (p != NULL) {
            cout << p->data << " -> ";
            p = p->next;
        }
        cout << "NULL" << endl;
    }
}

void clrQueue() {
    while (!isNull()) deletFirst();
}

int main() {
    setlocale(LC_CTYPE, "Russian");
    cout << "Выберите тип очереди (1-5): ";
    cin >> queueType;
    int choice = 1, z;
    head = NULL;
    tail = NULL;
    while (choice != 0) {
        cout << "1 - добавить элемент" << endl;
        cout << "2 - получить элемент с начала" << endl;
        cout << "3 - извлечь элемент с начала" << endl;
        cout << "4 - вывести элементы" << endl;
        cout << "5 - очистить очередь" << endl;
        cout << "0 - выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1:
            cout << "Введите элемент: ";
            cin >> z;
            insertToQueue(z);
            printQueue();
            break;
        case 2:
            getFromHead();
            break;
        case 3:
            deletFirst();
            printQueue();
            break;
        case 4:
            printQueue();
            break;
        case 5:
            clrQueue();
            break;
        }
    }
    return 0;
}