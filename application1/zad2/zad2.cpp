#include <iostream>
using namespace std;

struct Item {
    int data;
    Item* next;
};

Item* head = nullptr;
Item* tail = nullptr;

bool isEmpty() {
    return (head == nullptr);
}

// Удаление элемента из начала очереди
void deleteFirst() {
    if (isEmpty()) {
        cout << "Очередь пуста!" << endl;
    }
    else {
        Item* temp = head;
        head = head->next;
        if (head == nullptr) {  // Если очередь стала пустой
            tail = nullptr;
        }
        delete temp;
    }
}

// Получение элемента из начала очереди (без удаления)
void peekFront() {
    if (isEmpty()) {
        cout << "Очередь пуста!" << endl;
    }
    else {
        cout << "Первый элемент: " << head->data << endl;
    }
}

// Вставка элемента с учетом приоритета (максимум в начало, FIFO при равных)
void insertByPriority(int x) {
    Item* newNode = new Item;
    newNode->data = x;
    newNode->next = nullptr;

    if (isEmpty()) {  // Если очередь пуста
        head = tail = newNode;
    }
    else if (x > head->data) {  // Вставка в начало (максимальный приоритет)
        newNode->next = head;
        head = newNode;
    }
    else {
        Item* current = head;
        // Ищем место для вставки (по убыванию, FIFO при равных)
        while (current->next != nullptr && current->next->data >= x) {
            current = current->next;
        }
        // Вставляем после current
        newNode->next = current->next;
        current->next = newNode;
        // Если вставка в конец
        if (newNode->next == nullptr) {
            tail = newNode;
        }
    }
}

// Вывод очереди
void printQueue() {
    if (isEmpty()) {
        cout << "Очередь пуста!" << endl;
    }
    else {
        cout << "Очередь: ";
        Item* temp = head;
        while (temp != nullptr) {
            cout << temp->data;
            if (temp->next != nullptr) {
                cout << " -> ";
            }
            temp = temp->next;
        }
        cout << " -> NULL" << endl;
    }
}

// Очистка очереди
void clearQueue() {
    while (!isEmpty()) {
        deleteFirst();
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice, value;

    do {
        cout << "\n1. Добавить элемент" << endl;
        cout << "2. Просмотреть первый элемент" << endl;
        cout << "3. Удалить первый элемент" << endl;
        cout << "4. Вывести очередь" << endl;
        cout << "5. Очистить очередь" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите значение: ";
            cin >> value;
            insertByPriority(value);
            printQueue();
            break;
        case 2:
            peekFront();
            break;
        case 3:
            deleteFirst();
            printQueue();
            break;
        case 4:
            printQueue();
            break;
        case 5:
            clearQueue();
            cout << "Очередь очищена!" << endl;
            break;
        case 0:
            cout << "Выход..." << endl;
            break;
        default:
            cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);

    clearQueue();  // Очистка памяти перед выходом
    return 0;
}