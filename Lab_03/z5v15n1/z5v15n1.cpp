#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cctype>

using namespace std;

bool checkword(const string& line) {
    unordered_map<string, int> wordCount;
    stringstream ss(line);
    string word;

    while (ss >> word) {
        wordCount[word]++;
        if (wordCount[word] >= 2) {
            return true;
        }
    }
    return false;
}

int findch(const string& line) {
    stringstream ss(line);
    string word;
    int maxDigits = 0, index = -1, position = 1;

    while (ss >> word) {
        int digitCount = 0;

        for (char ch : word) {
            if (isdigit(static_cast<unsigned char>(ch))) {
                digitCount++;
            }
        }

        if (digitCount > maxDigits) {
            maxDigits = digitCount;
            index = position;
        }
        position++;
    }
    return index; 
}

int main() {
    setlocale(LC_ALL, "RU");
    ifstream File1("File1.txt");
    ofstream File2("File2.txt");
    int num = 0;
    string line;
    while (getline(File1, line)) {
        num++;
        if (checkword(line)) {
            File2 << line << endl;
        }
        int wordIndex = findch(line);
        if (wordIndex != -1) {
            cout << "В строке: "<< num << " слово с наибольшим количеством цифр " << wordIndex << endl;
        }
    }

    File1.close();
    File2.close();
    return 0;
}
