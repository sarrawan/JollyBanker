#include "stdafx.h"
#include "Bank.h"
#include <fstream>
#include <iostream>
using namespace std;

Bank::Bank()
{
}

void Bank::ReadIn(string file)
{
	if (!file.empty())
	{
		ifstream inFile(file);
		if (inFile.is_open())
		{
			while (!inFile.eof())
			{
				Transactions tempTrans;
				inFile >> tempTrans;
				transQueue.push(tempTrans);
			}
			inFile.close();
		}
	}
}


void Bank::ExecuteTransactions()
{
	while (!transQueue.empty())
	{
		Transactions tempTrans = transQueue.front();
		Account *tempAcc;
		if (tempTrans.getAccountID1() != -1)
		{
			if (tempTrans.getTransactionType() == "O" && accountTree.Retrieve(tempTrans.getAccountID1(), tempAcc) == false)
			{
				accountTree.Insert(new Account(tempTrans.getFirstName(), tempTrans.getLastName(), tempTrans.getAccountID1()));
			}
			else if (accountTree.Retrieve(tempTrans.getAccountID1(), tempAcc) == true)
			{
				if (tempTrans.getTransactionType() == "O")
				{
					cerr << "ERROR: Account " << tempTrans.getAccountID1() << " is already open. Transaction refused." << endl;
				}
				else if (tempTrans.getTransactionType() == "D")
				{
					tempTrans.Deposit(tempAcc, tempTrans.getFundID1(), tempTrans.getAmountForTrans());
				}
				else if (tempTrans.getTransactionType() == "W")
				{
					tempTrans.Withdraw(tempAcc, tempTrans.getFundID1(), tempTrans.getAmountForTrans());
				}
				else if (tempTrans.getTransactionType() == "T")
				{
					Account *otherAcc;
					if (accountTree.Retrieve(tempTrans.getAccountID2(), otherAcc) && tempTrans.getAccountID2() != -1)
					{
						tempTrans.Transfer(tempAcc, otherAcc, tempTrans.getFundID1(), tempTrans.getFundID2(), tempTrans.getAmountForTrans());
					}
					else
					{
						cerr << "ERROR: Account " << tempTrans.getAccountID2() << " not found. Transferal refused." << endl;
					}
				}
				else if (tempTrans.getTransactionType() == "H")
				{
					tempTrans.History(tempAcc);
				}
			}
			else
			{
				cerr << "ERROR: Account " << tempTrans.getAccountID1() << " not found. Transaction refused" << endl;
			}
		}
		transQueue.pop();
	}
}

void Bank::PrintOut()
{
	cout << "\nProcessing Done. Final Balances" << endl;
	accountTree.Display();
}

Bank::~Bank()
{
}
