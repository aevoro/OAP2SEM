#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <map>

using namespace std;

struct BitDate {
	int day : 8;
	int month : 16;
	int year : 24;

	BitDate(int d = 0, int m = 0, int y = 0) : day(d), month(m), year(y) {}
};

istream& operator>>(istream& is, BitDate& bd) {
	int d, m, y;
	is >> d >> m >> y;

	if (!is) return is;

	bd.day = d;
	bd.month = m;
	bd.year = y;
	return is;
}

	ostream& operator<<(ostream & os, const BitDate & bd) {
		os << setw(2) << setfill('0') << bd.day << "."
			<< setw(2) << setfill('0') << bd.month << "."
			<< setw(4) << setfill('0') << bd.year;
		return os;
	
}
	enum class Faculty {
		ФИТ = 1,  
		ИЭФ,      
		ЛХФ,      
		ТОВ       
	} facultet;

	const map<Faculty, string> facultyNames = {
		{Faculty::ФИТ, "ФИТ"},
		{Faculty::ИЭФ, "ИЭФ"},
		{Faculty::ЛХФ, "ЛХФ"},
		{Faculty::ТОВ, "ТОВ"}
	};

	ostream& operator<<(ostream& os, const Faculty& faculty) {
		auto it = facultyNames.find(faculty);
		if (it != facultyNames.end()) {
			os << it->second;
		}
		else {
			os << "Неизвестный факультет";
		}
		return os;
	}

struct student
{
	string lastName;
	string name;
	string fathName;
	string speciality;
	string group;
	BitDate admissionDate;
	int ball;
	Faculty facultet;
} stud;



void input(student st[], int size) {
		int num;
		int yFac;
		string date;
		cout << "Введите номер записи (1-10): ";
		cin >> num;
		num--;

		if (num < 0 || num >= size) {
			cout << "Неверный номер записи!" << endl;
			return;
		}

		cout << "Введите ФИО(Через пробел): ";
		cin >> st[num].lastName >> st[num].name >> st[num].fathName;

		cout << "Введите дату поступления(ДД ММ ГГГГ): ";
		cin >> st[num].admissionDate;

		cout << "Введите название специальности: ";
		cin >> st[num].speciality;

		cout << "Введите номер группы: ";
		cin >> st[num].group;

		cout << "Выберите факультет(1 - ФИТ,2 - ИЭФ,3 - ЛХФ,4 - ТОВ): ";
		cin >> yFac;
		 st[num].facultet = static_cast<Faculty>(yFac);;

		cout << "Введите балл: ";
		cin >> st[num].ball;
}

void output(student st[], int size) {
	for (int i = 0; i < size; i++) {
		if (st[i].lastName.empty()) continue;
		cout << "Номер записи: " << i + 1 << "\n" << "ФИО студента: " << st[i].lastName << " " << st[i].name << " " << st[i].fathName << " " << "\n" <<"Дата поступления: "
			<< st[i].admissionDate << "\n" << "Название специальности: " << st[i].speciality << "\n" << "Номер группы: " << 
			st[i].group << "\n" << "Факультет: " << st[i].facultet << "\n" << "Балл: " << st[i].ball << "\n";
		cout << endl;
	}
}

void search(student st[], int size) {
	string fam;
	cout << "Введите фамилию студента: ";
	cin >> fam;
	for (int i = 0; i < size; i++) {
		if (fam == st[i].lastName) {
			cout << "Номер записи: " << i + 1 << "\n" << "ФИО студента: " << st[i].lastName << " " << st[i].name << " " << st[i].fathName << " " << "\n" << "Дата поступления: "
 				<< st[i].admissionDate << "\n" <<"Название специальности: " << st[i].speciality << "\n" << "Номер группы: " << 
				st[i].group << "\n" <<"Факультет: " << st[i].facultet << "\n" << "Балл: " << st[i].ball << "\n";
		}
	}
}

void searchMinBall(student st[], int size) {
	int minBall = 400;
	int mini = 0;
	for (int i = 0; i < size; i++) {
		if (st[i].lastName.empty()) continue;
		if (minBall > st[i].ball) {
			minBall = st[i].ball;
			mini = i;
		}
	}
	for (int i = 0; i < size; i++) {
		if (mini == i) {
			cout << "Номер записи: " << i + 1 << "\n" << "ФИО студента: " << st[i].lastName<< " " << st[i].name << " " << st[i].fathName << " " << "\n" << "Дата поступления: "
				<< st[i].admissionDate << "\n" << "Название специальности: " << st[i].speciality << "\n" << "Номер группы: " <<
				st[i].group << "\n" << "Факультет: " << st[i].facultet << "\n" << "Балл: " << st[i].ball << "\n";
		}
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	student stud[10] = {
	{"Иванов", "Иван", "Иванович" ,"ПИ", "5" ,{11, 03, 2025}, 360, Faculty::ФИТ},
		{"Сергеев", "Сергей", "Сергеевич" ,"ПИ", "5", {22, 03, 2025}, 400, Faculty::ИЭФ},
		{"Петров", "Петр", "Петрович" ,"ПИ ", "5", {28, 03, 2025}, 320, Faculty::ЛХФ}
	};
	while (true) {
		cout << "1 - Ввод\n2 - Вывод\n3 - Удаление\n4 - Поиск\n5 - Выбор по баллу\n6 - Выход\nВыбор: ";
		int swap;
		cin >> swap;
		cout << endl;
		switch (swap)
		{
		case 1:input(stud, 10);
			cout << endl;
			break;

		case 2:output(stud, 10);
			break;

		case 3: {
			cout << endl;
			output(stud, 10);
			int index;
			cout << "Введите номер студента для удаления: ";
			cin >> index;

			if (index < 1 || index > 10) {
				cout << "Неверный номер!\n";
				break;
			}

			stud[index - 1] = student{};
			cout << "Студент удален!\n";
			cout << endl;
			break;
		}
		case 4:search(stud, 10);
			cout << endl;
			break;
			
		case 5: cout << "Студент с минимальным количеством баллов:\n";
			searchMinBall(stud, 10);
			cout << endl;
			break;

		case 6:
			return 0;

		default: cout << "Неверный ввод." << endl;
			break;
		}
	}

}