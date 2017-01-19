#include "stdafx.h"
#include "BSTree.h"


BSTree::BSTree()
{
	root = NULL;
}


BSTree::~BSTree()
{
	Empty();
}

bool BSTree::Insert(Account *acc)
{
	if (root == NULL)
	{
		root = new Node;
		root->pAcct = acc;
		return true;
	}
	else if ((*acc) < (*root->pAcct))
	{
		return insertRecursion(root->left, acc);
	}
	else
	{
		return insertRecursion(root->right, acc);
	}
}

bool BSTree::insertRecursion(Node * &current, Account *acct)
{
	if (current == NULL)
	{
		current = new Node();
		current->pAcct = acct;
		return true;
	}
	else if (*acct < *current->pAcct)
	{
		return insertRecursion(current->left, acct);
	}
	else if (*acct > *current->pAcct)
	{
		return insertRecursion(current->right, acct);
	}
	else
	{
		return false;
	}
}

bool BSTree::Retrieve(const int &id, Account *&acc)
{
	if (root == NULL)
	{
		return false;
	}
	else
	{
		return retrieveSearch(root, id, acc);
	}
}


bool BSTree::retrieveSearch(Node *current, int id, Account * &acc)
{
	if (current != NULL)
	{
		if (current->pAcct->getAccID() == id)
		{
			acc = current->pAcct;
			return true;
		}
		else if (id < current->pAcct->getAccID())
		{
			return retrieveSearch(current->left, id, acc);
		}
		else // id > current->pAcct->getAccID()
		{
			return retrieveSearch(current->right, id, acc);
		}
	}
	return false;
}

void BSTree::Display() const
{
	if (root != NULL)
	{
		printInOrderTraversal(root);

	}
}

void BSTree::printInOrderTraversal(Node *current) const
{
	if (current != NULL)
	{
		printInOrderTraversal(current->left);
		cout << (*current->pAcct) << endl;
		printInOrderTraversal(current->right);
	}
}

void BSTree::Empty()
{
	deleteTree(root);
}

void BSTree::deleteTree(Node *current)
{
	if (current == NULL)
	{
		return;
	}
	deleteTree(current->left);
	deleteTree(current->right);
	delete current->pAcct;
	current->pAcct = NULL;
	delete current;
	current = NULL;

}

bool BSTree::isEmpty() const
{
	return (root == NULL);
}