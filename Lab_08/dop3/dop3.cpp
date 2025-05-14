#include <iostream>
#include <string>
#include <Windows.h>
#include <sstream>
#include <cstdlib>
#include <fstream>

using namespace std;

string f = "f.txt";
string g = "g.txt";

struct QueueNode {
	string data;
	QueueNode* next;
};

struct Queue {
	QueueNode* front = nullptr;
	QueueNode* rear = nullptr;
};

void enqueue(Queue& q, const string& value) {
	QueueNode* newNode = new QueueNode;
	newNode->data = value;
	newNode->next = nullptr;

	if (q.rear == nullptr) {
		q.front = q.rear = newNode;
	}
	else {
		q.rear->next = newNode;
		q.rear = newNode;
	}
}

bool isEmpty(Queue& q) {
	return q.front == nullptr;
}

string dequeue(Queue& q) {
	if (isEmpty(q)) {
		return "";
	}
	QueueNode* temp = q.front;
	string value = temp->data;
	q.front = q.front->next;

	if (q.front == nullptr) {
		q.rear = nullptr;
	}

	delete temp;
	return value;
}

void outFile(Queue& mainQueue) {
	ifstream FileF(f);
	if (!FileF.is_open()) {
		cout << "Ошибка открытия файла " << f << endl;
		return;
	}

	string line;
	while (getline(FileF, line)) {
		Queue charsQueue, digitsQueue;
		for (char c : line) {
			if (isdigit(c)) {
				enqueue(digitsQueue, string(1, c));
			}
			else {
				enqueue(charsQueue, string(1, c));
			}
		}

		string processedLine;
		while (!isEmpty(charsQueue)) {
			processedLine += dequeue(charsQueue);
		}
		while (!isEmpty(digitsQueue)) {
			processedLine += dequeue(digitsQueue);
		}

		enqueue(mainQueue, processedLine);
	}
}

void printQueue(Queue& q) {
	Queue temp = q;
	while (!isEmpty(temp)) {
		cout << dequeue(temp) << endl;
	}
}

void inFile(Queue &q) {
	ofstream FileG(g);
	if (!FileG.is_open()) {
		cout << "Ошибка открытия файла " << g << endl;
		return;
	}

	Queue temp;
	QueueNode* current = q.front;
	while (current != nullptr) {
		enqueue(temp, current->data);
		current = current->next;
	}

	while (!isEmpty(temp)) {
		FileG << dequeue(temp) << endl;
	}

	FileG.close();
	cout << "Данные записаны в файл " << g << endl;
}

void refreshLine(Queue *q, Queue& qstr, Queue& qnum) {
	
}

int main() {
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int sw;
	Queue mainQueue;

	while (true) {
		cout << "1 - Прочитать из файла f\n2 - Вывод в консоль\n3 - Запись в файл g\n4 - Выход\nВыбор: ";
		cin >> sw;
		system("CLS");
		switch (sw) {

		case 1: {
			outFile(mainQueue);
			break;
		}

		case 2: {
			printQueue(mainQueue);
			break;
		}

		case 3: {
			inFile(mainQueue);
			break;
		}

		case 4: {
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