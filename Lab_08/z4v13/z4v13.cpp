//Создать очередь для массива целых (положительных и отрицательных) чисел и функции для ввода, вывода и удаления элементов очереди.
// При вводе чисел в очередь помещать только отрицательные элементы. Найти мини-мальный и максимальный элемент очереди. 
// Вывести все элементы очереди и посчитать их количество.  

#include "Headerz4v13.h"

int main() {
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int maxSize;
	int sw;

	cout << "Введите максимальный размер очереди: ";
	cin >> maxSize;

	Queue q;
	
	initQueue(&q, maxSize);
	
	while (true) {
		menu();
		cin >> sw;
		system("CLS");
		switch (sw) {
        case 1:
            processInput(&q);
            cout << endl;
            break;
        case 2:
            printQueue(&q);
            cout << endl;
            break;
        case 3: {
            int val;
            if (dequeue(&q, val)) {
                cout << "Удален элемент: " << val;
                cout << endl;
            }
            else {
                cout << "Очередь пуста!";
                cout << endl;
            }
            break;
        }
        case 4:
            findMinMax(&q);
            break;
        case 5:
            cout << "Количество элементов: " << q.count;
            break; 
        case 6: 
            return 0;
        }
    } while (sw != 6);
	}
