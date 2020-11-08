#include "BinaryTreeClass.h"
#include <iomanip>


int searchRec(int key, const Node* node)
{
	if (key == NULL || key == node->key)
		return key;
	else if (key < node->key)
	{
		cout << node->key << " ";
		return searchRec(key, node->left);
	}
	else
	{
		cout << node->key << " ";
		return searchRec(key, node->right);
	}
}

int main()
{
	cout << "Hello !\nIt's binary tree constructor.\nTo create it successfully, follow the instructions\n\n";
	BinaryTreeClass tree;

	bool flag = true;
	while (flag)
	{
		int choise;
		cout << "Enter 0 to exit:" << endl;
		cout << "Enter 1 to enter a key:" << endl;
		cout << "Enter 2 to search an element:" << endl;
		cout << "Enter 3 to see an current binary tree:" << endl;
		cin >> choise;
		cout << endl;

		switch (choise)
		{
		case 0:
			flag = false;

			break;
		case 1:
			int my_key;
			cout << "Enter a key: ";
			cin >> my_key;

			tree.insert(my_key);
			break;
		case 2:
			int to_search;
			cout << "Enter a element for search: " << endl;
			cin >> to_search;

			cout << searchRec(to_search, tree.getNode()) << endl;
			cout << tree.searchIter(to_search) << endl;
			break;
		case 3:
			tree.print(tree.getNode(), 0);

		default:
			cout << "Enter is wrong !" << endl;
			break;
		}
	}

	//ofstream fout("binary_tree.txt");

	return 0;
}