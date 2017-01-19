#include "stdafx.h"
#include "Transactions.h"


Transactions::Transactions()
{
	fundID1 = -1;
	fundID2 = -1;
	accID1 = -1;
	accID2 = -1;
	amount = 0;
	transType = "";
}

Transactions::Transactions(string tType)
{
	transType = tType;
	fundID1 = -1;
	fundID2 = -1;
	accID1 = -1;
	accID2 = -1;
	amount = 0;
}

Transactions::~Transactions()
{
}



string Transactions::getTransactionType() const
{
	return transType;
}

int Transactions::getFundID1() const
{
	return fundID1;
}

int Transactions::getFundID2() const
{
	return fundID2;
}

int Transactions::getAccountID1() const
{
	return accID1;
}

int Transactions::getAccountID2() const
{
	return accID2;
}

int Transactions::getAmountForTrans() const
{
	return amount;
}

string Transactions::getFirstName() const
{
	return firstName;
}

string Transactions::getLastName() const
{
	return lastName;
}

void Transactions::Deposit(Account *acc, int fundID, int amount)
{
	acc->AddToFund(amount, fundID, "D", -1, -1);
}

void Transactions::Withdraw(Account *acc, int fundID, int amount)
{
	if (acc->getBalanceOfFund(fundID) - amount >= 0)
	{
		acc->RemoveFromFund(amount, fundID, "W", -1, -1);
	}
	else  if (!checkOtherFunds(acc, fundID, amount))
	{
		acc->RecordFailedTransaction(amount, acc->getAccID(), -1, fundID, -1, "W");
		cerr << "ERROR: Not enough funds to withdraw " << amount << " from " << acc->getFullName() << " " << acc->getFundName(fundID) << endl;
	}
}

void Transactions::Transfer(Account *acc1, Account *acc2, int fund1, int fund2, int amount)
{
	if (acc1->getBalanceOfFund(fund1) - amount >= 0)
	{
		acc1->RemoveFromFund(amount, fund1, "T", acc2->getAccID(), fund2);
		acc2->AddToFund(amount, fund2, "T", acc1->getAccID(), fund1);
	}
	else if (checkOtherFunds(acc1, fund1, amount))
	{
		acc1->RemoveFromFund(amount, fund1, "T-", acc2->getAccID(), fund2);
		acc2->AddToFund(amount, fund2, "T", acc1->getAccID(), fund1);
	}
	else
	{
		acc1->RecordFailedTransaction(amount, acc1->getAccID(), acc2->getAccID(), fund1, fund2, getTransactionType());
		cerr << "ERROR: Not enough funds to transfer " << amount << " from " << acc1->getFullName() << " " << acc1->getFundName(fund1) << " to " << acc2->getFullName() << " " << acc2->getFundName(fund2) << endl;
	}
}

void Transactions::History(Account *acc)
{
	vector<string> hist;
	if (fundID1 == -1) //want to print out all balances
	{
		cout << "Transaction History for " << acc->getFullName() << " by fund." << endl;
		for (int i = 0; i < 10; i++)
		{
			hist = acc->getSingleFundHistory(i);
			if (hist.size() > 0)
			{
				cout << acc->getFundName(i) << ": $" << acc->getBalanceOfFund(i) << endl;
				for (int print = 0; print < hist.size(); print++)
				{
					cout << "  " << hist[print] << endl;
				}
			}
		}
	}
	else
	{
		cout << "Transaction History for " << acc->getFullName() << " " << acc->getFundName(fundID1) << ": $" << acc->getBalanceOfFund(fundID1) << endl;
		hist = acc->getSingleFundHistory(fundID1);
		for (int k = 0; k < hist.size(); k++)
		{
			cout << "  " << hist[k] << endl;
		}
	}

}

bool Transactions::checkOtherFunds(Account *acc, int fund, int amount)
{
	int balanceInOtherFund, balanceInThisFund, howMuchNeeded, otherFund;
	switch (fund)
	{
	case 0:
		otherFund = 1;
		break;
	case 1:
		otherFund = 0;
		break;
	case 2:
		otherFund = 3;
		break;
	case 3:
		otherFund = 2;
		break;
	default:
		return false;
	}
	balanceInOtherFund = acc->getBalanceOfFund(otherFund);
	balanceInThisFund = acc->getBalanceOfFund(fund);
	howMuchNeeded = amount - balanceInThisFund;
	if (balanceInOtherFund - howMuchNeeded >= 0)
	{
		acc->RemoveFromFund(howMuchNeeded, otherFund, "W", -1, -1);
		acc->RemoveFromFund(amount - howMuchNeeded, fund, "W", -1, -1);
		return true;
	}
	return false;
}

istream& operator>>(istream &inStream, Transactions &other)
{
	inStream >> other.transType;
	if (other.transType == "O")
	{
		string accNum;
		inStream >> other.lastName >> other.firstName >> accNum;
		if (accNum.length() == 4)
		{
			other.accID1 = atoi(accNum.c_str());
		}
		else
		{
			other.accID1 = -1;
			cerr << "ERROR: Invalid ID. Transaction refused." << endl;
		}
	}
	else if (other.transType == "D" || other.transType == "W")
	{
		string accAndFund;
		inStream >> accAndFund >> other.amount;
		if (accAndFund.length() == 5 && other.amount >= 0)
		{
			other.accID1 = atoi(accAndFund.substr(0, 4).c_str());
			other.fundID1 = atoi(accAndFund.substr(4, 1).c_str());
		}
		else
		{
			other.accID1 = -1;
			if (other.amount < 0)
			{
				cerr << "ERROR: Amount must be positive." << endl;
			}
			else
			{
				cerr << "ERROR: Invalid ID. Transaction refused." << endl;
			}
		}
	}
	else if (other.transType == "T")
	{
		string accFund1, accFund2;
		inStream >> accFund1 >> other.amount >> accFund2;
		if (accFund1.length() == 5 && accFund2.length() == 5 && other.amount >= 0)
		{
			other.accID1 = atoi(accFund1.substr(0, 4).c_str());
			other.accID2 = atoi(accFund2.substr(0, 4).c_str());
			other.fundID1 = atoi(accFund1.substr(4, 1).c_str());
			other.fundID2 = atoi(accFund2.substr(4, 1).c_str());
		}
		else
		{
			other.accID1 = -1;
			other.accID2 = -1;
			if (other.amount < 0)
			{
				cerr << "ERROR: Amount must be positive." << endl;
			}
			else
			{
				cerr << "ERROR: Invalid ID. Transaction refused." << endl;
			}
		}
	}
	else if (other.transType == "H")
	{
		string accFund;
		inStream >> accFund;
		if (accFund.length() == 4)
		{
			other.fundID1 = -1;
			other.accID1 = atoi(accFund.c_str());
		}
		else if (accFund.length() == 5)
		{
			other.fundID1 = atoi(accFund.substr(4, 1).c_str());
			other.accID1 = atoi(accFund.substr(0, 4).c_str());
		}
		else
		{
			other.accID1 = -1;
			cerr << "ERROR: Invalid ID. Transaction refused." << endl;
		}
	}
	return inStream;
}


