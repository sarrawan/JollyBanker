#pragma once
#include <string>
#include <vector>
using namespace std;

class Funds
{
public:
	Funds();
	Funds(string name);
	~Funds();
	
	void AddBalance(int amount, string transaction, int accID, int fundID, int accID2, int fundID2);
	void RemoveBalance(int amount, string transaction, int accID, int fundID, int accID2, int fundID2);
	void RecordTransFail(int amount, int id1, int id2, int fund1, int fund2, string transaction);

	int getBalance() const;
	string getName() const;
	vector<string> getFundHistory() const;

private:
	string fundName;
	int fundBalance;
	vector<string> fundHistory;
};

