#include "Headerz4v13.h"

void menu() {
    cout << "\n1 - ����\n2 - �����\n3 - ��������\n4 - ����� min/max\n5 - ������ �������\n6 - �����\n�����: ";
}
void initQueue(Queue* q, int size) {
    q->maxSize = size;
    q->arr = new int[size];
    q->front = q->rear = -1;
    q->count = 0; 
}

bool isEmpty(Queue* q) {
    return q->count == 0;
}

bool isFull(Queue* q) {
    return q->count == q->maxSize;
}

void enqueue(Queue* q, int c) {
    if (isFull(q)) {
        cerr << "������� �����������!" << endl;
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % q->maxSize;
    q->arr[q->rear] = c;
    q->count++; 
}

bool dequeue(Queue* q, int& c) {
    if (isEmpty(q)) return false;
    c = q->arr[q->front];
    q->front = (q->front + 1) % q->maxSize;
    q->count--; 
    if (q->count == 0) { 
        q->front = q->rear = -1;
    }
    return true;
}

void processInput(Queue* q) {
    int c;
    while (!isFull(q)) {
        cout << "������� ����� (�������� " << q->maxSize - q->count << "): ";
        cin >> c;
        if (c < 0) {
            enqueue(q, c);
        }
    }
}

void printQueue(Queue* q) {
    if (isEmpty(q)) {
        cout << "������� �����.";
        return;
    }
    int i = q->front;
    for (int cnt = 0; cnt < q->count; cnt++) {
        cout << q->arr[i] << " ";
        i = (i + 1) % q->maxSize;
    }
}

void findMinMax(Queue* q) {
    if (isEmpty(q)) {
        cout << "������� �����!";
        return;
    }
    int minVal = INT_MAX;
    int maxVal = INT_MIN;
    int i = q->front;
    for (int cnt = 0; cnt < q->count; cnt++) {
        if (q->arr[i] < minVal) minVal = q->arr[i];
        if (q->arr[i] > maxVal) maxVal = q->arr[i];
        i = (i + 1) % q->maxSize;
    }
    cout << "�����������: " << minVal << "\n������������: " << maxVal;
}

void deleteQueue(Queue* q) {
    delete[] q->arr;
}
