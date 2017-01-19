#pragma once
#include "Account.h"

class BSTree
{
public:
	BSTree();
	~BSTree();

	bool Insert(Account *);
	bool Retrieve(const int &, Account * &);

	void Display() const;
	void Empty();
	bool isEmpty() const;

private:
	struct Node
	{
		Account *pAcct = NULL;
		Node *right = NULL;
		Node *left = NULL;
	};
	Node *root;

	bool insertRecursion(Node * &root, Account *acc);
	bool retrieveSearch(Node *current, int id, Account * &acc);
	void printInOrderTraversal(Node *current) const;
	void deleteTree(Node *current);
};

