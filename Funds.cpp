#include "stdafx.h"
#include "Funds.h"


Funds::Funds()
{
	fundName = "";
	fundBalance = 0;
}

Funds::Funds(string name)
{
	fundName = name;
	fundBalance = 0;
}

Funds::~Funds()
{
}

void Funds::AddBalance(int amount, string transaction, int accID, int fundID, int accID2, int fundID2)
{
	fundBalance += amount;
	if (accID2 == -1 && fundID2 == -1)
	{
		fundHistory.push_back(transaction + " " + to_string(accID) + to_string(fundID) + " " + to_string(amount));
	}
	else
	{
		fundHistory.push_back(transaction + " " + to_string(accID2) + to_string(fundID2) + " " + to_string(amount) + " " + to_string(accID) + to_string(fundID));
	}
}

void Funds::RemoveBalance(int amount, string transaction, int accID, int fundID, int accID2, int fundID2)
{
	if (transaction.length() == 2)
	{
		fundHistory.push_back(transaction.substr(0, 1) + " " + to_string(accID) + to_string(fundID) + " " + to_string(amount) + " " + to_string(accID2) + to_string(fundID2));
	}
	else
	{
		fundBalance -= amount;
		if (accID2 == -1 && fundID2 == -1)
		{
			fundHistory.push_back(transaction + " " + to_string(accID) + to_string(fundID) + " " + to_string(amount));
		}
		else
		{
			fundHistory.push_back(transaction + " " + to_string(accID) + to_string(fundID) + " " + to_string(amount) + " " + to_string(accID2) + to_string(fundID2));
		}
	}
}

void Funds::RecordTransFail(int amount, int id1, int id2, int fund1, int fund2, string transaction)
{
	if (id2 == -1)
	{
		fundHistory.push_back(transaction + " " + to_string(id1) + to_string(fund1) + " " + to_string(amount) + " (Failed)");
	}
	else
	{
		fundHistory.push_back(transaction + " " + to_string(id1) + to_string(fund1) + " " + to_string(amount) + " " + to_string(id2) + to_string(fund2) + " (Failed)");
	}
}

int Funds::getBalance() const
{
	return fundBalance;
}

string Funds::getName() const
{
	return fundName;
}

vector<string> Funds::getFundHistory() const
{
	return fundHistory;
}
