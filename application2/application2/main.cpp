#include "list.h"

struct Person
{
	char name[20];
	int age;
	Person* next;
};

void print(void* b)      
{
	Person* a = (Person*)b;
	cout << a->name << "  " << a->age << endl;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	Person a1 = { "������", 20 };
	Person a2 = { "�������", 25 };
	Person a3 = { "��������", 47 };
	Person a4 = { "�����", 46 };
	Person a5 = { "������", 41 };
	Person a6 = { "�������", 42 };
	bool rc;
	Object L1 = Create();  
	L1.Insert(&a1);
	L1.Insert(&a2);
	L1.Insert(&a3);
	L1.Insert(&a4);
	L1.Insert(&a5);
	L1.Insert(&a6);		
	L1.PrintList(print);
	Element* e = L1.Search(&a3);
	Person* aa = (Person*)e->Data;
	cout << "������ �������= " << aa->name << endl;
	rc = L1.Delete(&a2);
	if (rc == true) cout << "������ �������" << endl;
	cout << "������:" << endl;
	L1.PrintList(print);
	cout << "���������� ���������: " << L1.CountList() << endl;
	L1.DeleteList();
	cout << "������ ������" << endl;
	L1.PrintList(print);
	return 0;
}
