#include "Headerz4v11.h"


int main() {
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int sw;
	Stack* myStk= new Stack;
	myStk = NULL;
	
	while (true) {
		menu();
		cin >> sw;
		cout << endl;
		switch (sw) {
		case 1: {
			saveInFile(myStk);
			break;
		}

		case 2: {
			readFile(myStk);
			break;
		}

		case 3: {
			addElem(myStk);
			break;
		}

		case 4: {
			deleteElemThi(myStk);
			break;
		}

		case 5: {
			clearSt(myStk);
			break;
		}

		case 6: {
			return 0;
		}

		case 7: {

			break;
			  }

		default: {
			cout << "Неверный ввод. Попробайте снова" << endl;
			break;
		}

		}
	}

}