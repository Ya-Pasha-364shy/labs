#pragma once
#include <iostream>
#include <fstream>

using namespace std;

struct Node {
	int key;
	Node* left;
	Node* right;
};

class BinaryTreeClass
{
private:
	Node* node;

	// защищённый метод вставки элемента,
	// срабатывает только при вызове insert(int key)
	// чтобы правильно вставить ключ в соответствующий узел.
	void insertInTree(int key, Node* node);

public:
	// непараметризованный конструктр
	BinaryTreeClass();

	// гетер для узла
	// возвращает константое значние, так как геттер в основном
	// используется только для вывода 
	const Node* getNode();

	// метод распечатка дерева
	void print(const Node* node, int level);

	// метод удаления дерева
	void delete_tree(Node* tree);

	// вставка элемента в подходящий узел
	void insert(int key);

	// рекурсивный поиск ключа
	// с выводом тех узлов, которые алгоритм обошёл
	friend int searchRec(int key, const Node* node);

	// Итерационноый поиск ключа
	int searchIter(int key);

	// перегрузку оператора вывода заменяет 
	// метод print(const Node* node, int level)

	// friend ofstream& operator<<(ofstream fout, const BinaryTree& tree);

	~BinaryTreeClass();
};

