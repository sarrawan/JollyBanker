#pragma once
#include "Account.h"
#include <iostream>
using namespace std;

class Transactions
{
	friend istream& operator>>(istream &inStream, Transactions &other);
public:
	Transactions();
	Transactions(string transType);
	~Transactions();

	void Deposit(Account *acc, int FundID, int amount);
	void Withdraw(Account *acc, int FundID, int amount);
	void Transfer(Account *acc1, Account *acc2, int FundID1, int FundID2, int amount);
	void History(Account *acc);

	string getFirstName() const;
	string getLastName() const;
	int getAccountID1() const;
	int getAccountID2() const;
	string getTransactionType() const;
	int getFundID1() const;
	int getFundID2() const;
	int getAmountForTrans() const;

private:
	string firstName;
	string lastName;
	int accID1;
	int accID2;
	int fundID1;
	int fundID2;
	string transType;
	int amount;

	bool checkOtherFunds(Account *acc, int fundId, int amount);

};

