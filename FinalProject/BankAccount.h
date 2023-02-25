#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include"Account.h"

class BankAccount : public Account {
public:
	BankAccount();

	void printDetails() const;
	void printHistory() const;

	void depositMoney(double money); 
	void withdrawMoney(double money); 

	void addHistory(int mode, double amount); 

protected:
	virtual void check_private_files(); 

};

#endif 