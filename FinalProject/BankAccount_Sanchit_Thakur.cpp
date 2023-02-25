#include<iostream>
#include<string>
#include<sstream>
using namespace std;
#include "BankAccount.h"
#include "HelperFunc.h"


BankAccount::BankAccount()
{
	checkFileStatus_Template();
}

void BankAccount::printDetails() const
{
	cout << "You have $" << fixed << setprecision(2) << getBalance() << " in your bank account" << endl;
}

void BankAccount::printHistory() const
{
	hf.printAllLines(BANK_HISTORY);
}

void BankAccount::addHistory(int mode, double amount)
{
	string record = "";
	string type = "";
	//Switch-case scenario
	switch (mode) {
		case 1:
			type = "Deposit";
			break;
		case 2:
			type = "Wthdrw";
			break;
		case 3:
			type = "SellStk";
			break;
		case 4:
			type = "BuyStk";
			break;
		default:
			break;
	}
	stringstream ss; 
	ss << left << "\n" << setw(16) << type << setw(16) << "$" + hf.convertToString(amount) << setw(16) <<
		hf.getDate() << setw(16) << "$" + hf.convertToString(getBalance());
	record = ss.str();
	hf.addToLastLine(BANK_HISTORY, record);
}

void BankAccount::withdrawMoney(double money)
{
	double balance = getBalance();
	if (balance - money < 0) { 
		//The account must have sufficient balance
		cout << "Insuficient funds" << endl;
	}
	else {
		stringstream ss;
		ss << fixed << setprecision(2) << balance - money*1.0;
		setBalance(ss.str()); 
		addHistory(2, money); 
		cout << "You have successfully withdraw $" << fixed << setprecision(2) << money << "." << endl;
		printDetails(); 
	}
}

void BankAccount::depositMoney(double money)
{
	if (money <= 0) { 
		//Money must be > 0
		cout << "Invalid amount of money" << endl;
		return;
	}
	else {
		stringstream ss;
		ss << fixed << setprecision(2) << getBalance() + money*1.0;
		setBalance(ss.str()); 
		addHistory(1, money); 
		cout << "You have successfully deposited $" << fixed << setprecision(2) << money << "." << endl;
		printDetails();
	}
}

void BankAccount::check_private_files()
{
	if (!hf.checkFile(BANK_HISTORY)) { 
		stringstream ss;
		ss << left << setw(16) << "Event" << setw(16) << "Amount" << setw(16) << "Date" << setw(16) << "Balance";
		string title = ss.str();
		hf.addToLastLine(BANK_HISTORY, title);
	}
}
