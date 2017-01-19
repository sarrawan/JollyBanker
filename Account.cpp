#include "stdafx.h"
#include "Account.h"


Account::Account()
{
	firstName = "";
	lastName = "";
	accID = 0;
}

Account::Account(string first, string last, int id)
{
	firstName = first;
	lastName = last;
	accID = id;

	myFunds[0] = new Funds("Money Market");
	myFunds[1] = new Funds("Prime Money Market");
	myFunds[2] = new Funds("Long-Term Bond");
	myFunds[3] = new Funds("Short-Term Bond");
	myFunds[4] = new Funds("500 Index Fund");
	myFunds[5] = new Funds("Capital Value Fund");
	myFunds[6] = new Funds("Growth Equity Fund");
	myFunds[7] = new Funds("Growth Index Fund");
	myFunds[8] = new Funds("Value Fund");
	myFunds[9] = new Funds("Value Stock Index");
}

Account::~Account()
{
	for (int i = 0; i < 10; i++)
	{
		delete myFunds[i];
		myFunds[i] = NULL;
	}
}

string Account::getFullName() const
{
	return firstName + " " + lastName;
}

string Account::getFundName(int fund) const
{
	return myFunds[fund]->getName();
}

int Account::getAccID() const
{
	return accID;
}

int Account::getBalanceOfFund(int fundID) const
{
	return myFunds[fundID]->getBalance();
}

void Account::AddToFund(int balance, int FundID, string transType, int otherID, int otherFund)
{
	myFunds[FundID]->AddBalance(balance, transType, getAccID(), FundID, otherID, otherFund);
}

void Account::RemoveFromFund(int balance, int FundID, string transType, int otherID, int otherFund)
{
	myFunds[FundID]->RemoveBalance(balance, transType, accID, FundID, otherID, otherFund);
}

vector<string> Account::getSingleFundHistory(int fundType) const
{
	return myFunds[fundType]->getFundHistory();
}

bool Account::operator==(Account &other) const
{
	return (accID == other.accID);
}

bool Account::operator<(const Account &other) const
{
	return (accID < other.accID);
}

bool Account::operator>(const Account &other) const
{
	return (accID > other.accID);
}

void Account::RecordFailedTransaction(int balance, int id1, int id2, int fund1, int fund2, string transType)
{
	if (id2 == -1)
	{
		myFunds[fund1]->RecordTransFail(balance, id1, id2, fund1, fund2, transType);
	}
	else
	{
		myFunds[fund1]->RecordTransFail(balance, id1, id2, fund1, fund2, transType);
		myFunds[fund2]->RecordTransFail(balance, id1, id2, fund1, fund2, transType);
	}
}

ostream& operator<<(ostream &outStream, const Account &other)
{
	outStream << other.getFullName() << " Account ID: " << other.getAccID() << endl;
	for (int i = 0; i < 10; i++)
	{
		outStream << "    " << other.getFundName(i) << ": $" << other.getBalanceOfFund(i) << endl;
	}
	return outStream;
}


