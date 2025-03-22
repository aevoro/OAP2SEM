#include <iostream>
#include <string>
#include <fstream>

using namespace std;



int checkGrade(double &studentMax, double &student, double &procent) {
	procent = student / studentMax * 100;
	return procent;
}

struct student
{
	string lastName;
	string name;
	string surname;
	int exam;
	int grade[10];
};

int main() {
	setlocale(LC_ALL, "RU");
	double student = 0;
	double studentMax = 0;
	struct student st;
	double procent = 0;
	ofstream File("File.txt");
	File.is_open();

	if (!File.is_open()) { 
		cout << "Ошибка открытия файла!" << endl;
		return 1;
	}
	while (true) {
		int sw;
		cout << "1 - Записать новго студента, 2 - Выход из записи: ";
		cin >> sw;

		switch(sw){
		
		case 1: {
			cout << "Введите ФИО студента: ";
			cin >> st.lastName >> st.name >> st.surname;

			cout << "Введите количесвто экзаменов: ";
			cin >> st.exam;

			cout << "Введите оценки по экзаменам: " << endl;
			for (int i = 0; i < st.exam; i++) {
				cout << i + 1 << " экзамен: ";
				cin >> st.grade[i];
			}
			
			File << "ФИО студента " << st.lastName << " " << st.name << " " << st.surname << endl
				<< "Количество сданных экзаменов: " << st.exam << endl;
			
			File << "Оценки за экзамены: " << endl;
			
			for (int i = 0; i < st.exam; i++) {
				File << i + 1 << " экзамен: " << st.grade[i] << endl;;
			}
			bool gradeExam = false;
			for (int i = 0; i < st.exam; i++) {
				if (st.grade[i] == 4 || st.grade[i] == 5) {
					gradeExam = true;
				}
				else {
					gradeExam = false;
					break;
				}
			}
			if (gradeExam) {
				studentMax++;
				File << "Студет сдал все экзамены на 4 и 5" << endl;
			}
			break;
		}
		case 2: {
			cout << "Выход из ввода данных." << endl;
			break;

		}
		
		default: {
			cout << "Неверно введены данные." << endl;
			checkGrade(student, studentMax, procent);
			File << "Процент отношения студентов сдавших экзамен на 4 и 5 к всему количеству студентов: " << procent << endl;
			File.close();
			return 0;
		    }
		}
		student++;
	}
}