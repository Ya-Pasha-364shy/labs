#include "BinaryTreeClass.h"

BinaryTreeClass::BinaryTreeClass()
{
	node = NULL;
}


const Node* BinaryTreeClass::getNode() {
	return node;
}

void BinaryTreeClass::print(const Node* node, int level)
{
	if (node)
	{
		print(node->left, level + 1);

		for (int i = 0; i < level; i++)
			cout << "   ";

		cout << node->key << endl;
		print(node->right, level + 1);
	}
}

int BinaryTreeClass::searchIter(int key)
{
	const Node* my_nod = getNode();
	while ((my_nod != NULL) && (key != my_nod->key))
	{
		if (key < node->key)
			my_nod = my_nod->left;
		else
			my_nod = my_nod->right;
	}
	return key;
}

void BinaryTreeClass::insert(int key)
{
	// если главный корень 0-уровн€ есть, 
	if (((key != NULL) || (key > 0)) && (node != NULL))
	{
		// то вставл€ем значение
		insertInTree(key, node);
	}
	// если нет, то
	else
	{
		node = new Node;
		// инициализируем корневой элемент 
		node->key = key;
		// объ€вл€ем его левого ребЄнка
		node->left = NULL;
		// объ€вл€ем его правого ребЄнка
		node->right = NULL;
	}
}


void BinaryTreeClass::insertInTree(int key, Node* node)
{
	if (key < node->key)
	{
		if (node->left != NULL)
			insertInTree(key, node->left);
		else
		{
			node->left = new Node;
			node->left->key = key;
			node->left->left = NULL;
			node->left->right = NULL;
		}
	}
	else if (key >= node->key) {
		if (node->right != NULL)
			insertInTree(key, node->right);
		else
		{
			node->right = new Node;
			node->right->key = key;
			node->right->left = NULL;
			node->right->right = NULL;
		}
	}
}


void BinaryTreeClass::delete_tree(Node* tree)
{
	if (tree != NULL)
	{
		delete_tree(tree->left);
		delete_tree(tree->right);
	}
	delete tree;
}

BinaryTreeClass::~BinaryTreeClass()
{
	delete_tree(node);
}