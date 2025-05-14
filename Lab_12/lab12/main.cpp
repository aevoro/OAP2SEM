#include "Heap.h"
#include <iostream>
using namespace std;
heap::CMP cmpAAA(void* a1, void* a2)  //������� ���������
{
#define A1 ((AAA*)a1)
#define A2 ((AAA*)a2)
	heap::CMP
		rc = heap::EQUAL;
	if (A1->x > A2->x)
		rc = heap::GREAT;
	else
		if (A2->x > A1->x)
			rc = heap::LESS;
	return rc;
#undef A2
#undef A1 
}
//-------------------------------
int main()
{
	setlocale(LC_ALL, "rus");
	int k, choice;
	heap::Heap h1 = heap::create(30, cmpAAA);
	for (;;)
	{
		cout << "(1) ����� ���� �� �����" << endl;
		cout << "(2) �������� �������" << endl;
		cout << "(3) ������� ������������ �������" << endl;
		cout << "(4) ������� ����������� �������" << endl;
		cout << "(5) ������� i-� �������" << endl;
		cout << "(6) ���������� ����" << endl;
		cout << "(0) �����" << endl;
		cout << ">" << endl;  cin >> choice;
		system("cls");
		heap::Heap h2 = heap::create(5, cmpAAA);
		AAA* a1 = new AAA{ 1111 };
		AAA* a2 = new AAA{ 2222 };
		AAA* a3 = new AAA{ 3333 };

		switch (choice)
		{
		case 0:  exit(0);
		case 1:  h1.scan(0);
			break;
		case 2: {
			AAA* a = new AAA;
			cout << "������� ����" << endl;
			cin >> k;
			a->x = k;
			h1.insert(a);
		}
			  break;
		case 3:   h1.extractMax();
			break;
		case 4:   h1.extractMin();
			break;
		case 5:
			int i;
			cout << "������� i: ";
			cin >> i;
			h1.extractI(i);
			break;
		case 6:{
			heap::Heap h2 = heap::create(5, cmpAAA);
			for (int i = 0; i < 3; i++)
			{
				AAA* a = new AAA;
				a->x = rand() % 100;
				h2.insert(a);
			}
			cout << "������� ������ ���� ��� ����������� - " << endl;
			h2.scan(0);

			h1.unionHeap(h2);
			cout << "���� ���������� ������� ���� - " << endl;
			h1.scan(0);
			break;
		}
		default:  cout << endl << "������� �������� �������!" << endl;
		}
	} return 0;
}
