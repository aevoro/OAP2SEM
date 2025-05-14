//������� ������� ��� ������� ����� (������������� � �������������) ����� � ������� ��� �����, ������ � �������� ��������� �������.
// ��� ����� ����� � ������� �������� ������ ������������� ��������. ����� ����-������� � ������������ ������� �������. 
// ������� ��� �������� ������� � ��������� �� ����������.  

#include "Headerz4v13.h"

int main() {
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int maxSize;
	int sw;

	cout << "������� ������������ ������ �������: ";
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
                cout << "������ �������: " << val;
                cout << endl;
            }
            else {
                cout << "������� �����!";
                cout << endl;
            }
            break;
        }
        case 4:
            findMinMax(&q);
            break;
        case 5:
            cout << "���������� ���������: " << q.count;
            break; 
        case 6: 
            return 0;
        }
    } while (sw != 6);
	}
