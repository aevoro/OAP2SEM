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

// �������� �������� �� ������ �������
void deleteFirst() {
    if (isEmpty()) {
        cout << "������� �����!" << endl;
    }
    else {
        Item* temp = head;
        head = head->next;
        if (head == nullptr) {  // ���� ������� ����� ������
            tail = nullptr;
        }
        delete temp;
    }
}

// ��������� �������� �� ������ ������� (��� ��������)
void peekFront() {
    if (isEmpty()) {
        cout << "������� �����!" << endl;
    }
    else {
        cout << "������ �������: " << head->data << endl;
    }
}

// ������� �������� � ������ ���������� (�������� � ������, FIFO ��� ������)
void insertByPriority(int x) {
    Item* newNode = new Item;
    newNode->data = x;
    newNode->next = nullptr;

    if (isEmpty()) {  // ���� ������� �����
        head = tail = newNode;
    }
    else if (x > head->data) {  // ������� � ������ (������������ ���������)
        newNode->next = head;
        head = newNode;
    }
    else {
        Item* current = head;
        // ���� ����� ��� ������� (�� ��������, FIFO ��� ������)
        while (current->next != nullptr && current->next->data >= x) {
            current = current->next;
        }
        // ��������� ����� current
        newNode->next = current->next;
        current->next = newNode;
        // ���� ������� � �����
        if (newNode->next == nullptr) {
            tail = newNode;
        }
    }
}

// ����� �������
void printQueue() {
    if (isEmpty()) {
        cout << "������� �����!" << endl;
    }
    else {
        cout << "�������: ";
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

// ������� �������
void clearQueue() {
    while (!isEmpty()) {
        deleteFirst();
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice, value;

    do {
        cout << "\n1. �������� �������" << endl;
        cout << "2. ����������� ������ �������" << endl;
        cout << "3. ������� ������ �������" << endl;
        cout << "4. ������� �������" << endl;
        cout << "5. �������� �������" << endl;
        cout << "0. �����" << endl;
        cout << "�������� ��������: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "������� ��������: ";
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
            cout << "������� �������!" << endl;
            break;
        case 0:
            cout << "�����..." << endl;
            break;
        default:
            cout << "�������� �����!" << endl;
        }
    } while (choice != 0);

    clearQueue();  // ������� ������ ����� �������
    return 0;
}