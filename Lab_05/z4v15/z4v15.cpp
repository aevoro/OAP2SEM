#include <iostream>
#include <string>
#include <Windows.h>
#include <map>
#include <iomanip>

using namespace std;

struct BitDate {
	int lastKonk;

	BitDate(int lk = 0):lastKonk(lk){}

	bool operator<(const BitDate& other) const {
		return lastKonk < other.lastKonk;
	}
};

istream& operator>>(istream& is, BitDate& bd) {
	int lk;
	is >> lk;

	if (!is) return is;

	bd.lastKonk = lk;
	return is;
}

ostream& operator<<(ostream& os, const BitDate& bd) {
	os << setw(2) << setfill('0') << bd.lastKonk;
	return os;

}
enum class Spec {
	ПИ = 1, ИСИТ, ЦД,
} speciality;

const map<Spec, string> facultyNames = {
	{Spec::ПИ, "ПИ"},
	{Spec::ИСИТ, "ИСИТ"},
	{Spec::ЦД, "ЦД"}
};

ostream& operator<<(ostream& os, const Spec& speciality) {
	auto it = facultyNames.find(speciality);
	if (it != facultyNames.end()) {
		os << it->second;
	}
	else {
		os << "Неизвестный факультет";
	}
	return os;
}

struct Usniversity
{
	string nameUn;
	string addres;
	Spec speciality;
	string payment;
	BitDate conk;
	bool operator<(const Usniversity& other) const {
		return conk < other.conk;
	}
} stud;

void input(Usniversity un[], int size) {
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

	cout << "Введите название университета: ";
	cin >> un[num].nameUn;

	cout << "Введите аддрес: ";
	cin >> un[num].addres;

	cout << "Выберите спецальность(1 - ПИ, 2 - ИСИТ, 3 - ЦД): ";
	cin >> yFac;
	un[num].speciality = static_cast<Spec>(yFac);

	cout << "Введите стоимость обучения: ";
	cin >> un[num].payment;

	cout << "Введите балл: ";
	cin >> un[num].conk;
}

void output(Usniversity un[], int size) {
	for (int i = 0; i < size; i++) {
		if (un[i].nameUn.empty()) continue;
		cout << "Номер записи: " << i + 1 << "\n" << "Название университета: " << un[i].nameUn<< "\n" << "Аддрес: "
			<< un[i].addres<< "\n" << "Название специальности: " << un[i].speciality<< "\n" << "Стоимеость обучения " <<
			un[i].payment << "\n" << "Балл: " << un[i].conk << "\n";
		cout << endl;
	}
}

void search(Usniversity un[], int size) {
	string fam;
	cout << "Введите название университета: ";
	cin >> fam;
	for (int i = 0; i < size; i++) {
		if (fam == un[i].nameUn) {
			cout << "Номер записи: " << i + 1 << "\n" << "Название университета: " << un[i].nameUn << "\n" << "Аддрес: "
				<< un[i].addres << "\n" << "Название специальности: " << un[i].speciality << "\n" << "Стоимеость обучения " <<
				un[i].payment << "\n" << "Балл: " << un[i].conk << "\n";
		}
	}
}

void searchMinBall(Usniversity un[], int size) {
	Usniversity* minUn = nullptr;
	for (int i = 0; i < size; i++) {
		if (!un[i].nameUn.empty()) {
			minUn = &un[i];
			break;
		}
	}
	if (!minUn) return; 

	for (int i = 0; i < size; i++) {
		if (!un[i].nameUn.empty() && un[i] < *minUn) {
			minUn = &un[i];
		}
	}

	cout << "Номер записи: " << (minUn - un) + 1 << "\n"
		<< "Название: " << minUn->nameUn << "\n"
		<< "Адрес: " << minUn->addres << "\n"
		<< "Специальность: " << minUn->speciality << "\n"
		<< "Стоимость обучения: " << minUn->payment << "\n"
		<< "Балл: " << minUn->conk << "\n";
}



int main() {
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Usniversity stud[10] = {
	{"БГТУ", "Минск", Spec::ЦД,"2000", 360},
		{"ГРГУ", "Гродно", Spec::ПИ,"2000", 300},
		{"БГУИР", "Минск", Spec::ПИ,"2000", 395}
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
			cout << "Введите номер университета для удаления: ";
			cin >> index;

			if (index < 1 || index > 10) {
				cout << "Неверный номер!\n";
				break;
			}

			stud[index - 1] = Usniversity{};
			cout << "Университет удален!\n";
			cout << endl;
			break;
		}
		case 4:search(stud, 10);
			cout << endl;
			break;

		case 5: cout << "Университет с минимальным количеством баллов:\n";
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
