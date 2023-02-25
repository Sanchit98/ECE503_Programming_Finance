#ifndef ACCOUNT_H
#define ACCOUNT_H
#include"HelperFunc.h"
using namespace std;
class Account {
public:
	Account();

	double getBalance() const;
	void setBalance(string balance);
	
	virtual void printHistory() const = 0; 

	void checkFileStatus_Template(); 

	//Create an object of HelperFunc
	HelperFunc hf; 

protected:
	void checkSharedFiles(); 
	virtual void checkPrivateFiles();

};


#endif
