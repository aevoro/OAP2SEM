//Создать 2 очереди для символов и функции для ввода, вывода и удаления элементов очереди. Ввести в очередь символы с экрана. 
//Прописные буквы преобразовать в строчные и поместить в первую очередь, строчные буквы преобразовать в прописные и поместить во вторую очередь. 

#include "Headerz4v11.h"

int main() {
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int maxSize;
	int sw;

	cout << "Введите максимальный размер очередей: ";
	cin >> maxSize;

	Queue q1;
	Queue q2;
	initQueue(&q1, maxSize);
	initQueue(&q2, maxSize);

	while (true) {
		menu();
		cin >> sw;
		system("CLS");
		switch (sw) {
		case 1: {
			processInput(&q1, &q2);  cout << endl; break; 
		}
		case 2:{
			cout << "Очередь 1 (строчные): ";
			printQueue(&q1);
			cout << "\nОчередь 2 (прописные): ";
			printQueue(&q2);
			cout << endl;
			break;
		}
		case 3: {
			char c1, c2;
			bool success1 = dequeue(&q1, c1);
			bool success2 = dequeue(&q2, c2);
			break;
		}
		case 4: {
			return 0;
		default: cout << "Неверный ввод" << endl; break;
		}
		}
	}
}