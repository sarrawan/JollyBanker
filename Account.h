#pragma once
#include "Funds.h"
#include <iostream>
#include <vector>
using namespace std;
class Account
{
	friend ostream& operator<<(ostream &outStream, const Account &other);

public:
	Account();
	Account(string first, string last, int id);
	~Account();

	string getFullName() const;
	string getFundName(int fund) const;
	int getBalanceOfFund(int fundID) const;
	int getAccID() const;

	void AddToFund(int balance, int FundID, string transType, int otherID, int otherFund);
	void RemoveFromFund(int balance, int FundID, string transType, int otherID, int otherFund);
	void RecordFailedTransaction(int balance, int id1, int id2, int fund1, int fund2, string transType);

	vector<string> getSingleFundHistory(int fundType) const;

	bool operator==(Account &other) const;
	bool operator>(const Account &other) const;
	bool operator<(const Account &other) const;

private:
	string firstName;
	string lastName;
	int accID;
	Funds *myFunds[10];
};

