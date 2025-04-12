#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>

struct Stack
{
int data;     
	Stack *next;	 
};


using namespace std;

int main();
void menu();
void clearSt(Stack*& myStk);
void deleteElemThi(Stack*& myStk);
void addElem(Stack*& myStk);
void readFile(Stack*& myStk);
void saveInFile(Stack* myStk);
int deleteSt(Stack*& myStk);