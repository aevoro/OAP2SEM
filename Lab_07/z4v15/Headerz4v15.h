#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <unordered_map>

struct Stack
{
	int data;
	Stack* next;
};


using namespace std;

int main();
void menu();
void clearSt(Stack*& myStk);
int checkDupl(Stack*& myStk);
void addElem(Stack*& myStk);
void readFile(Stack*& myStk);
void saveInFile(Stack* myStk);
int deleteSt(Stack*& myStk);