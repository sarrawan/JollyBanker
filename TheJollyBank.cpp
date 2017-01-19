// TheJollyBank.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Bank.h"

int main()
{
	Bank b;
	b.ReadIn("BankTransIn.txt");
	b.ExecuteTransactions();
	b.PrintOut();
    return 0;
}

