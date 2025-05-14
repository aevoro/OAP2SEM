#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <sstream>
#include <cstdlib>

using namespace std;

struct Queue {
	int maxSize, front, rear;
	int* arr;
	Queue* next;
	int count;
};

void menu();
void initQueue(Queue* q, int size);
bool isEmpty(Queue* q);
bool isFull(Queue* q);
void enqueue(Queue* q, int c);
bool dequeue(Queue* q, int& c);
void processInput(Queue* q);
void printQueue(Queue* q);
void findMinMax(Queue* q);
