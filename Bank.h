#pragma once
#include "Transactions.h"
#include "BSTree.h"
#include <string>
#include <queue>
using namespace std;
class Bank
{
public:
	Bank();
	~Bank();

	void ReadIn(string fileName);
	void ExecuteTransactions();
	void PrintOut();

private:
	queue<Transactions> transQueue;
	BSTree accountTree;
};

