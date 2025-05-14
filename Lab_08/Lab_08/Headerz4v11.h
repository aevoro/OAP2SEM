#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

struct Queue{
	int maxSize, front, rear;
	char *arr;
	Queue* next;
};

void menu();
void initQueue(Queue* q, int size);
void processInput(Queue* q1, Queue* q2);
bool dequeue(Queue* q, char& c);
bool enqueue(Queue* q, char c);
void printQueue(Queue* q);