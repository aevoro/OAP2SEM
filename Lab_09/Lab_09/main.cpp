#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;
const unsigned int NAME_SIZE = 30;
const unsigned int CITY_SIZE = 20;

struct Address
{
	char name[NAME_SIZE];
	char city[CITY_SIZE];
	Address* next;
	Address* prev;
};

int menu(void)
{
	char s[80];  int c;
	cout << endl;
	cout << "1. Ввод имени" << endl;
	cout << "2. Удаление имени" << endl;
	cout << "3. Вывод на экран" << endl;
	cout << "4. Поиск" << endl;
	cout << "5. Замена выбранного элемента" << endl;
	cout << "6. Добавление в начало списка всех элементов некоторого списка L" << endl;
	cout << "7. Функция добавления в конец списка всех элементов некоторого списка L" << endl;
	cout << "8. Выход" << endl;
	cout << endl;
	do
	{
		cout << "Ваш выбор: ";
		cin.sync();
		gets_s(s);
		cout << endl;
		c = atoi(s);
	} while (c < 0 || c > 8);
	return c;
}

void insert(Address* e, Address** phead, Address** plast) 
{
	Address* p = *plast;
	if (*plast == NULL)
	{
		e->next = NULL;
		e->prev = NULL;
		*plast = e;
		*phead = e;
		return;
	}
	else
	{
		p->next = e;
		e->next = NULL;
		e->prev = p;
		*plast = e;
	}
}

Address* setElement()    
{
	Address* temp = new  Address();
	if (!temp)
	{
		cerr << "Ошибка выделения памяти памяти";
		return NULL;
	}
	cout << "Введите имя: ";
	cin.getline(temp->name, NAME_SIZE - 1, '\n');
	cin.ignore(cin.rdbuf()->in_avail());
	cin.clear();
	cout << "Введите город: ";
	cin.getline(temp->city, CITY_SIZE - 1, '\n');
	cin.ignore(cin.rdbuf()->in_avail());
	cin.clear();
	temp->next = NULL;
	temp->prev = NULL;
	return temp;
}

void outputList(Address** phead, Address** plast)     
{
	Address* t = *phead;
	while (t)
	{
		cout << t->name << ' ' << t->city << endl;
		t = t->next;
	}
	cout << "" << endl;
}

void find(char name[NAME_SIZE], Address** phead)    
{
	Address* t = *phead;
	while (t)
	{
		if (!strcmp(name, t->name)) break;
		t = t->next;
	}
	if (!t)
		cerr << "Имя не найдено" << endl;
	else
		cout << t->name << ' ' << t->city << endl;
}

void delet(char name[NAME_SIZE], Address** phead, Address** plast)  
{
	struct Address* t = *phead;
	while (t)
	{
		if (!strcmp(name, t->name))  break;
		t = t->next;
	}
	if (!t)
		cerr << "Имя не найдено" << endl;
	else
	{
		if (*phead == t)
		{
			*phead = t->next;
			if (*phead)
				(*phead)->prev = NULL;
			else
				*plast = NULL;
		}
		else
		{
			t->prev->next = t->next;
			if (t != *plast)
				t->next->prev = t->prev;
			else
				*plast = t->prev;
		}
		delete t;
		cout << "Элемент удален" << endl;
	}
}

int main(void)
{
	Address* head = NULL;
	Address* last = NULL;
	setlocale(LC_CTYPE, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	while (true)
	{
		switch (menu())
		{
		case 1:  insert(setElement(), &head, &last);
			break;
		case 2: {
			char dname[NAME_SIZE];
			cout << "Введите имя: ";
			cin.getline(dname, NAME_SIZE - 1, '\n');
			cin.ignore(cin.rdbuf()->in_avail());
			cin.sync();
			delet(dname, &head, &last);
		}
			  break;
		case 3:  outputList(&head, &last);
			break;
		case 4: {
			char fname[NAME_SIZE];
			cout << "Введите имя: ";
			cin.getline(fname, NAME_SIZE - 1, '\n');
			cin.ignore(cin.rdbuf()->in_avail());
			cin.sync();
			find(fname, &head);
		}
			  break;
		case 5: {
			int index;
			cout << "Введите индекс элемента для замены: ";
			cin >> index;
			cin.ignore();

			cout << "Введите новые данные:" << endl;
			Address* x = setElement();
			if (!x) break;

			Address* current = head;
			int count = 0;
			bool found = false;
			while (current) {
				if (count == index) {
					strcpy_s(current->name, x->name);
					strcpy_s(current->city, x->city);
					found = true;
					break;
				}
				current = current->next;
				count++;
			}
			if (!found) {
				cerr << "Элемент не найден." << endl;
			}
			delete x; 
			break;
		}
		case 6: {
			Address* head_L = NULL;
			Address* last_L = NULL;
			char choice;
			do {
				Address* elem = setElement();
				if (elem) {
					insert(elem, &head_L, &last_L);
				}
				else {
					cerr << "Ошибка ввода элемента." << endl;
					break;
				}
				cout << "Продолжить ввод? (y/n): ";
				cin >> choice;
				cin.ignore();
			} while (choice == 'y' || choice == 'Y');

			if (head_L) {
				
				if (head) {
					head_L->prev = NULL;
					last_L->next = head;
					head->prev = last_L;
					head = head_L;
				}
				else {
					head = head_L;
					last = last_L;
				}
			}
			break;
		}
		case 7: {
			Address* head_L = NULL;
			Address* last_L = NULL;
			char choice;
			do {
				Address* elem = setElement();
				if (elem) {
					insert(elem, &head_L, &last_L);
				}
				else {
					cerr << "Ошибка ввода элемента." << endl;
					break;
				}
				cout << "Продолжить ввод? (y/n): ";
				cin >> choice;
				cin.ignore();
			} while (choice == 'y' || choice == 'Y');

			if (head_L) {
				if (last) {
					last->next = head_L;
					head_L->prev = last;
					last = last_L;
				}
				else {
					head = head_L;
					last = last_L;
				}
			}
			break;
		}
		case 8:  exit(0);
		default: exit(1);
		}
	}
	return 0;
}
void writeToFile(Address** phead)       
{
	struct Address* t = *phead;
	FILE* fp;
	errno_t err = fopen_s(&fp, "mlist", "wb");
	if (err)
	{
		cerr << "Файл не открывается" << endl;
		exit(1);
	}
	cout << "Сохранение в файл" << endl;
	while (t)
	{
		fwrite(t, sizeof(struct Address), 1, fp);
		t = t->next;
	}
	fclose(fp);
}

void readFromFile(Address** phead, Address** plast)          
{
	struct Address* t;
	FILE* fp;
	errno_t err = fopen_s(&fp, "mlist", "rb");
	if (err)
	{
		cerr << "Файл не открывается" << endl;
		exit(1);
	}
	while (*phead)
	{
		*plast = (*phead)->next;
		delete* phead;
		*phead = *plast;
	}
	*phead = *plast = NULL;
	cout << "Загрузка из файла" << endl;
	while (!feof(fp))
	{
		t = new Address();
		if (!t)
		{
			cerr << "Ошибка выделения памяти" << endl;
			return;
		}
		if (1 != fread(t, sizeof(struct Address), 1, fp)) break;
		insert(t, phead, plast);
	}
	fclose(fp);
}

