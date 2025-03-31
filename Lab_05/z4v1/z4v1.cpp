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

ostream& operator<<(ostream& os, const BitDate& bd) {
	os << setw(2) << setfill('0') << bd.day << "."
		<< setw(2) << setfill('0') << bd.month << "."
		<< setw(4) << setfill('0') << bd.year;
	return os;

}
enum class title {
	Разработчик = 1,
	Стажер,
	Водитель,
	Управляющий
} jobT;

const map<title, string> facultyNames = {
	{title::Разработчик, "Разработчик"},
	{title::Стажер, "Стажер"},
	{title::Водитель, "Водитель"},
	{title::Управляющий, "Управляющий"}
};

ostream& operator<<(ostream& os, const title& faculty) {
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
	string education;
	BitDate admissionDate;
	int expirience;
	title jobT;
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

	cout << "Введите образование: ";
	cin >> st[num].education;

	cout << "Выберите должность(1 - Разработчик,2 - Стажер,3 - Водитель,4 - Управляющий): ";
	cin >> yFac;
	st[num].jobT = static_cast<title>(yFac);;

	cout << "Введите стаж: ";
	cin >> st[num].expirience;
}

void output(student st[], int size) {
	for (int i = 0; i < size; i++) {
		if (st[i].lastName.empty()) continue;
		cout << "Номер записи: " << i + 1 << "\n" << "ФИО: " << st[i].lastName << " " << st[i].name << " " << st[i].fathName << " " << "\n" << "Дата поступления: "
			<< st[i].admissionDate << "\n" << "Образование: " << st[i].education<< "\n" << "Должность: " << st[i].jobT << "\n" << "Стаж: " << st[i].expirience << "\n";
		cout << endl;
	}
}

void search(student st[], int size) {
	string fam;
	cout << "Введите фамилию: ";
	cin >> fam;
	for (int i = 0; i < size; i++) {
		if (fam == st[i].lastName) {
			cout << "Номер записи: " << i + 1 << "\n" << "ФИО: " << st[i].lastName << " " << st[i].name << " " << st[i].fathName << " " << "\n" << "Дата поступления: "
				<< st[i].admissionDate << "\n" << "Образование: " << st[i].education << "\n" << "Должность: " << st[i].jobT << "\n" << "Стаж: " << st[i].expirience << "\n";
			cout << endl;
		}
	}
}

void searchMinBall(student st[], int size) {
	int minBall = 0;
	int mini = 0;
	for (int i = 0; i < size; i++) {
		if (st[i].lastName.empty()) continue;
		if (minBall < st[i].expirience) {
			minBall = st[i].expirience;
			mini = i;
		}
	}
	for (int i = 0; i < size; i++) {
		if (mini == i) {
			cout << "Номер записи: " << i + 1 << "\n" << "ФИО: " << st[i].lastName << " " << st[i].name << " " << st[i].fathName << " " << "\n" << "Дата поступления: "
				<< st[i].admissionDate << "\n" << "Образование: " << st[i].education<< "\n" << "Должность: " << st[i].jobT << "\n" << "Стаж: " << st[i].expirience << "\n";
			cout << endl;
		}
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	student stud[10] = {
	{"Иванов", "Иван", "Иванович", "Высшее",{11, 03, 2025}, 1, title::Разработчик},
		{"Петров", "Петр", "Петрович", "Среднее",{16, 03, 2025}, 1, title::Стажер},
		{"Сергеев", "Сергей", "Сергеевич", "Высшее",{1, 03, 2023}, 3, title::Управляющий}
	};
	while (true) {
		cout << "1 - Ввод\n2 - Вывод\n3 - Удаление\n4 - Поиск\n5 - Выбор по стажу\n6 - Выход\nВыбор: ";
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
			cout << "Введите номер работника для удаления: ";
			cin >> index;

			if (index < 1 || index > 10) {
				cout << "Неверный номер!\n";
				break;
			}

			stud[index - 1] = student{};
			cout << "Работник удален!\n";
			cout << endl;
			break;
		}
		case 4:search(stud, 10);
			cout << endl;
			break;

		case 5: cout << "Работник с максимальным стажем:\n";
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