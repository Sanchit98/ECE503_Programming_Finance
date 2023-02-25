#ifndef STOCKACCOUNT_H
#define STOCKACCOUNT_H
#include<iostream>
using namespace std;
#include"Account.h"
#include"BankAccount.h"
#include "SortStrategy.h"
#include"DoublyLinkedList.h"

class SortStrategy;
class Context;
class StockAccount : public Account {
	friend class BubbleSort;
	friend class SelectionSort;
public:
	StockAccount();
	~StockAccount();
	double get_portfolio_from_file() const; 
	void set_portfolio(double p); 
	double get_portfolio(); 

	void printDetails();
	void printHistory() const;

	void getAllStock(); 

	double findPriceByName(string name) const; 
	void showStockDetails(string name); 
	void sellShares(string name, int num, double price, BankAccount &ba); 
	void buyShares(string name, int num, double price, BankAccount &ba); 
	void updateStockFile(); 
	void updatePortfolio(); 
	
	void printGraph(); 

	void addHistory(int mode, string name, int num, double pricepershare); 

	SortStrategy * pSS; 
	Context * pCon;

protected:
	virtual void check_private_files(); 

private:
	DoublyLinkedList dll;
	double portfolio;
};

#endif 
