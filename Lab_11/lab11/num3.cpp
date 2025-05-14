#include <iostream>
#include <Windows.h>
#include <queue>
#include <string>
#include <vector>
using namespace std;
struct node {
	int num;
	string str;
	node* right;
	node* left;
};

void addNum(node*& tree, int num, string str) {
	if (tree == nullptr) {
		tree = new node;
		tree->num = num;
		tree->str = str;
		tree->left = nullptr;
		tree->right = nullptr;
		return;
	}

	if (num > tree->num) {
		addNum(tree->right, num, str);
	}
	else {
		addNum(tree->left, num, str);
	}
}

void deleteNum(node*& tree, int num) {
	if (tree == nullptr) {
		throw "Элемент не найден";
	}

	if (num < tree->num) {
		deleteNum(tree->left, num);
	}
	else if (num > tree->num) {
		deleteNum(tree->right, num);
	}
	else {
		if (tree->left == nullptr) {
			node* temp = tree->right;
			delete tree;
			tree = temp;
		}
		else if (tree->right == nullptr) {
			node* temp = tree->left;
			delete tree;
			tree = temp;
		}
		else {
			node* minRight = tree->right;
			while (minRight->left != nullptr) {
				minRight = minRight->left;
			}
			tree->num = minRight->num;
			deleteNum(tree->right, minRight->num);
		}
	}
}

void print(node*& tree, int level = 0, bool treeCheck = false) {
	if (tree)
	{
		print(tree->right, level + 1);
		for (int i = 0; i < level; ++i) {
			cout << "        ";
		}
		cout << tree->num << " " << tree->str << "  " << endl;
		print(tree->left, level + 1);
	}
	else if (treeCheck) {
		throw "Дерево пусто!";
	}
}

void var11(node* tree, int n) {
	if (!tree) throw "Дерево пусто!";
	if (n < 0) throw "Уровень не может быть отрицательным!";

	queue<pair<node*, int>> q;
	vector<node*> result;

	q.push(make_pair(tree, 0));

	while (!q.empty()) {
		pair<node*, int> current = q.front();
		q.pop();

		node* current_node = current.first;
		int current_level = current.second;

		if (current_level > n) break;

		if (current_level == n) {
			result.push_back(current_node);
			continue;
		}

		if (current_node->left)
			q.push(make_pair(current_node->left, current_level + 1));

		if (current_node->right)
			q.push(make_pair(current_node->right, current_level + 1));
	}

	cout << "Узлы на уровне " << n << ":\n";
	for (size_t i = 0; i < result.size(); ++i) {
		cout << "Ключ: " << result[i]->num
			<< ", Значение: " << result[i]->str << endl;
	}
	cout << "Всего узлов: " << result.size() << endl;
}

void var13(node* tree) {
	if (!tree) throw "Дерево пусто!";

	vector<int> level_sums(11, 0); 
	queue<pair<node*, int>> q;

	q.push(make_pair(tree, 0));

	while (!q.empty()) {
		auto current = q.front();
		q.pop();

		node* current_node = current.first;
		int current_level = current.second;

		if (current_level > 10) continue; 

		level_sums[current_level] += current_node->num;

		if (current_node->left)
			q.push(make_pair(current_node->left, current_level + 1));
		if (current_node->right)
			q.push(make_pair(current_node->right, current_level + 1));
	}

	cout << "Суммы по уровням:\n";
	for (size_t i = 0; i < level_sums.size(); ++i) {
		if (level_sums[i] != 0 || i == 0) 
			cout << "Уровень " << i << ": " << level_sums[i] << endl;
	}
}

int var15(node* root) {
	if (!root) throw "Дерево пусто!";

	int count = 0;
	node* current = root;

	while (current) {
		count++;
		current = current->right;
		}
	return count;
}

int main() {
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int choice = 0;
	node* Tree = nullptr;
	while (true) {
		cout << "1. Добавить" << endl;
		cout << "2. Удалить" << endl;
		cout << "3. Вывод дерева" << endl;
		cout << "4. Определить количество ветвей n-ого уровня" << endl;
		cout << "5. Сумма значений вершин" << endl;
		cout << "6. Количество узлов правой ветви" << endl;
		cout << "7. Выход" << endl;
		cout << endl;

		int choice;
		cout << "> ";
		cin >> choice;
		system("cls");
		string str;

		switch (choice)
		{
		case 1:
			int num;
			cout << "Введите ключ: ";
			cin >> num;
			cout << "Введите строку: ";
			cin >> str;
			addNum(Tree, num, str);
			break;
		case 2:
			cout << "Введите ключ: ";
			cin >> num;
			try {
				deleteNum(Tree, num);
			}
			catch (const char* e) {
				cout << e << endl;
			}
			break;
		case 3:
			try {
				print(Tree, 0, true);
				cout << endl;
			}
			catch (const char* e) {
				cout << e << endl;
			}
			break;
		case 4: {
			try {
				int target_level;
				cout << "Введите уровень: ";
				if (!(cin >> target_level)) {
					throw "Некорректный ввод уровня!";
				}
				var11(Tree, target_level);
			}
			catch (const char* e) {
				cout << "Ошибка: " << e << endl;
			}
			break;
		}
		case 5: {
			try {
				var13(Tree);
			}
			catch (const char* e) {
				cout << "Ошибка: " << e << endl;
			}
			break;
		}
		case 6: {
			try {
				int result = var15(Tree);
				cout << "Узлов в правой ветви: " << result << endl;
			}
			catch (const char* e) {
				cout << "Ошибка: " << e << endl;
			}
			break;
		}
		case 7: {
			exit(0);
			break;
		}
		default: {
			cout << "Неверный ввод!" << endl;
			break;
		}
		}
	}
}
	