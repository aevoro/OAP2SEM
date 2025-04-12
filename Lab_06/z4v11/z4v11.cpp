#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

struct list{
	string symbol;
	list* next;
};

void insert(list*& p, string value) {
	list* newP = new list;
	if (newP != NULL) {
		newP->symbol = value;
		newP->next = p;
		p = newP;
	}
}

void delElem(list *p, string value) {
	cout << "Введите удаляемый сивол: ";
	cin >> value;
		list* previous, * current, * temp;
		if (value == p->symbol)
		{
			temp = p;
			p = p->next;
			delete temp;
		}
		else {
			{
				previous = p;
				current = p->next;
				while (current != NULL && current->symbol != value)
				{
					previous = current;
					current = current->next;
				}
				if (current != NULL)
				{
					temp = current;
					previous->next = current->next;
					delete(temp);
				}
			}
		}
}

int searchElem(list*p, string value) {
	int i = 0;
	cout << "Введите символ для поиска: ";
	cin >> value;
	string last = "Таких нет";
	while (p != NULL) {
		if (value == p->symbol) {
			cout << endl << "Символ '" << value << "' предыдущий символ: '"<< last<<"'" << endl << endl;
			return 0;
		}
		else {
			last = p->symbol;
			p = p->next;
			i++;
		}
	}
	cout<< endl << "Символ не найден в списке" << endl << endl;
}

void printList(list* p) {
	if (p == NULL) {
		cout << endl << "Список пуст." << endl << endl;
	}
	else {
		cout << "Список: ";
		while (p != NULL) {
			cout << p->symbol << " ";
			p = p->next;
		}
	}
}

void printFile(list *p) {
	ofstream File("File.txt");
	while (p != nullptr) {
		File << p->symbol << endl;
		p = p->next;
	}
	cout <<endl<< "Символы записаны в файл." << endl << endl;
	File.close();
}

void readFile(list*& p) {
	ifstream File("File.txt");

	while (p != nullptr) {
		list* temp = p;
		p = p->next;
		delete temp;
	}

	string line;
	while (getline(File, line)) {
		insert(p, line); 
	}
}

void menu() {
	cout << "1 - Добавить элемент\n2 - Удалить элемент\n3 - Поиск элемента\n4 - Вывод списка\n5 - Записать в файл\n6 - Прочитать из файла\n7 - Выход\nВыбор: ";
}

int main() {
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	list * first = nullptr;
	int choise;
	string value;
	
	while (true) {
		menu();
		cin >> choise;
		switch (choise) {
		
		case 1: {
			cout << "Введите символ: ";
			cin >> value;
			insert(first, value);
			cout  << endl << "Символ добавлен" << endl << endl;
			break;
		}

		case 2: {
			delElem(first, value);
			cout << endl<< "Элемент удален" << endl << endl;
			break;
		}

		case 3: {
			searchElem(first, value);
			break;
		}

		case 4: {
			printList(first);
			cout << endl << endl;
			break;
		}

		case 5: {
			printFile(first);
			break;
		}

		case 6: {
			readFile(first);
			cout << "Сиволы прочитаны из файла." << endl << endl;
			break;
		}

		case 7: {
			return 0;
		}
		}
	}
	


}
