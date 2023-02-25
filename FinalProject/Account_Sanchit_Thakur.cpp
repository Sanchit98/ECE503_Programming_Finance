#include "Account.h"


void Account::setBalance(string balance)
{
	//To write balance to file
	hf.writeBalanceToFile(CASH_BALANCE, balance); 
}

double Account::getBalance() const
{
	//To store the last line from the file
	string newest = hf.getLastLine(CASH_BALANCE); 
	double balance_from_file = atof(newest.c_str()) * 1.0; 
	return balance_from_file;
}

Account::Account()
{
	//To check file status first
	checkFileStatus_Template(); 
}

void Account::checkSharedFiles()
{
	if (!hf.checkFile(CASH_BALANCE)) { 
		//If CASH_BALANCE does not exist, initialize it to "10000"
		string m = "10000.00";
		hf.addToLastLine(CASH_BALANCE, m);
	}
}

void Account::checkFileStatus_Template()
{
	checkSharedFiles(); 
	checkPrivateFiles(); 
}


void Account::checkPrivateFiles()
{
	 
}
