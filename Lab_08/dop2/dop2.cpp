#include <iostream>
#include <string>
#include <Windows.h>
#include <sstream>
#include <cstdlib>

using namespace std;

struct Queue{
	int maxSize;
	double* arr;
	Queue* next;
	int front;
	int rear;
	int count;
};

bool isEmpty(Queue* q) {
	return q->count == 0;
}

bool isFull(Queue* q) {
	return q->count == q->maxSize;
}


void enqueue(Queue* q, double c) {
	if (isFull(q)) {
		cerr << "Очередь переполнена!" << endl;
		return;
	}
	if (isEmpty(q)) {
		q->front = 0;
	}
	q->rear = (q->rear + 1) % q->maxSize;
	q->arr[q->rear] = c;
	q->count++;
}
void initQueue(Queue *q, int size) {
	q->maxSize = size;
	q->arr = new double[size];
	q->front = q->rear = -1;
	q->count = 0;
}

void input(Queue *q) {
	double c;
	while (!isFull(q)) {
		cout << "Введите вещественное число (осталось " << q->maxSize - q->count << "): ";
		cin >> c;
			enqueue(q, c);
	}
}

void output(Queue*q, int maxSize) {
	if (isEmpty(q)) {
		cout << "Очередь пуста.";
		return;
	}

	double max = 0;
	int numMax = 0;

	for (int i = 0; i < maxSize; i++) {
		if (max < q->arr[i]) {
			max = q->arr[i];
			numMax = i;
		}
	}
	for (int i = numMax; i >= 0; i--) {
		if (i != 0) {
			q->arr[i] = q->arr[i - 1];
		}
		else {
			q->arr[i] = max;
		}
	}
	cout << "Очередь: ";
	for (int i = 0; i < maxSize; i++) {
		cout << q->arr[i] << " ";
	}

}

int main() {
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Queue q;
	int sw;
	int maxSize;

	cout << "Введите размер очереди: ";
	cin >> maxSize;

	initQueue(&q, maxSize);

	while (true) {
		cout << "1 - Ввод\n2 - Вывод\n3 - Выход\nВыбор: ";
		cin >> sw;
		system("CLS");
		switch (sw) {
		case 1: {
			input(&q);
			cout << endl;
			break;
			}

		case 2: {
			output(&q, maxSize);
			cout << endl;
			break;
		}

		case 3: {
			cout << "Выход";
			return 0;
		}

		default: {
			cout << "Неверный ввод" << endl;
			break;
		}
		}
	}

}