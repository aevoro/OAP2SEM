#include "Headerz4v11.h"

void menu() {
	cout << "1 - Ввод\n2 - Вывод\n3 - Удаление\n4 - Выход\nВыбор: ";
}

void initQueue(Queue* q, int size) {
	q->maxSize = size;
	q->arr = new char[size];
	q->front = q->rear = -1;
}

bool isEmpty(Queue* q) {
	return q->front == -1;
}

bool isFull(Queue* q) {
	return q->rear == q->maxSize - 1;
}

bool enqueue(Queue* q, char c) {
	if (isFull(q)) return false;
	if (isEmpty(q)) q->front = 0;
	q->rear++;
	q->arr[q->rear] = c;
	return true;
}

bool dequeue(Queue* q, char& c) {
	if (isEmpty(q)) return false;
	c = q->arr[q->front];
	if (q->front == q->rear) q->front = q->rear = -1;
	else q->front++;
	return true;
}

void processInput(Queue* q1, Queue* q2) {
	string input;
	cout << "Введите строку: ";
	cin.ignore();
	getline(cin, input);

	for (char c : input) {
		if (isupper(c)) {
			char lower = tolower(c);
			if (!enqueue(q1, lower)) {
				cout << "Очередь 1 переполнена.";
			}
		}
		else if (islower(c)) {
			char upper = toupper(c);
			if (!enqueue(q2, upper)) {
				cout << "Очередь 2 переполнена.";
			}
		}
	}
}

void printQueue(Queue* q) {
	if (isEmpty(q)) {
		cout << "Очередь пуста.";
		return;
	}
	for (int i = q->front; i <= q->rear; i++) {
		cout << q->arr[i] << " ";
	}
}