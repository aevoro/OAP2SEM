#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
bool checkline(const string& line) {
   
    stringstream ss(line);
    string word;
    int wordcol = 0;
    while (ss >> word) {
        wordcol++;
        if (wordcol > 1) return false;
    }
    return wordcol == 1;
}
int main() {
	setlocale(LC_ALL, "RU");
	ifstream FileA; 
	ofstream FileB;
	string line1;
	FileA.open("FileA.txt");
    FileB.open("FileB.txt");
    string line;
    while (getline(FileA, line)) {
        if (checkline(line)) {
            FileB << line << endl;
        }
    }
   
    ifstream FileBread("FileB.txt");
    cout << "Слова перенесены" << endl;
    int shortword = 0   ;
    size_t minlength = SIZE_MAX;
    while (getline(FileBread, line)) {
        stringstream ss(line);
        string word;
        while (ss >> word) {
            for (int i = 0; i < size(word); i++) {
                if (word == "\n") {
                    break;
                }
                else {
                    shortword++;
                }
            }
        }
    }
    if (shortword!=0) {
    FileB << "Количество символов: " << shortword << endl;
}
 else {
     cout << "В файле FILE2 нет слов." << endl;
    }

    FileBread.close();
    FileA.close();
    FileB.close();
} 