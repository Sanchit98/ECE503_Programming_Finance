#include <stdlib.h>
#include<sstream>
using namespace std; 
#include "StockAccount.h"
#include "HelperFunc.h"

StockAccount::StockAccount()
{
	checkFileStatus_Template();
	pSS = new BubbleSort();
	pCon = new Context(pSS);

	getAllStock(); 
	srand((unsigned)time(0)); 
}

StockAccount::~StockAccount()
{
	delete pCon;
	pCon = NULL;
	updatePortfolio();
}

void StockAccount::set_portfolio(double p)
{
	portfolio = p;
	updatePortfolio(); 
}

double StockAccount::get_portfolio_from_file() const
{
	string newest = hf.getLastLine(PORTFOLIO_FILE); 
	string tok = hf.split(newest, 1);
	double p = atof(tok.c_str()) * 1.0;
	return p;
}

double StockAccount::get_portfolio()
{
	return portfolio;
}

void StockAccount::printDetails()
{
	cout << "Cash balance = $" << getBalance() << endl;
	cout << left;
	cout << setw(16) << "CompanySymbol" << setw(12) << "Number" << setw(16) << "PricePerShare" << setw(16) << "TotalValue" << endl;
	Node* currentPtr = dll.getHead()->getNext(); 
	double myBalance = 0.0;
	while (currentPtr != dll.getTail()) { 
		myBalance += currentPtr->getPrice() * currentPtr->get_num_stock(); 
		cout << setw(16) << currentPtr->get_name_stock() << setw(12) << currentPtr->get_num_stock() << setw(16) <<
			"$" + hf.convertToString(currentPtr->getPrice()) << setw(16) << 
			"$" + hf.convertToString(currentPtr->getPrice()*currentPtr->get_num_stock()) << endl;
		currentPtr = currentPtr->getNext();
	}
	if (dll.getSize() == 0) { 
		cout << "You do not have any stock yet!" << endl;
	}
	cout << "Total portfolio value: $" << myBalance + getBalance() << endl;
	set_portfolio(myBalance + getBalance());
}

void StockAccount::printHistory() const
{
	hf.printAllLines(STOCK_HISTORY); 
}

double StockAccount::findPriceByName(string name) const
{
	double random = rand() / double(RAND_MAX); 
	string result_s;
	double price;
	if (random >= 0.5) {
		result_s = hf.searchFile(RESULT_1, name);
	}
	else {
		result_s = hf.searchFile(RESULT_2, name);
	}
	if (result_s == "") {
		price = -1; 
	}
	else {
		price = atof(hf.split(result_s, 2).c_str()); 
	}
	return price*1.0;
}

void StockAccount::showStockDetails(string name)
{
	
	double price = findPriceByName(name); 
	if (price > 0) { 
		cout << left;
		cout << setw(16) << "Company Symbol" << setw(16) << "Price per share" << endl;
		string price_s = "$" + hf.convertToString(price);
		cout << setw(16) << name << setw(16) << price_s << endl;
	}
	else {
		cout << "Error: Stock not found. Cannot display the price." << endl;
	}
}

void StockAccount::getAllStock()
{
	ifstream ifs;
	ifs.open(STOCK_FILE);
	if (ifs.fail()) {
		cout << "Error: file cannot open" << endl;
	}
	else {
		string line;
		int num = 0;
		while (getline(ifs, line)) {
			if (num++ == 0)
				continue; 
			string name = hf.split(line, 1); 
			int num = atoi(hf.split(line, 3).c_str());
			Node* node = new Node(name, num); 
			//Insertion into the doubly linked list
			dll.insertNode(node);
		}
		ifs.close();
	}
}

void StockAccount::buyShares(string name, int num, double price, BankAccount& ba)
{
	
	double priceNow = findPriceByName(name); 
	if (priceNow > 0) {
		if (price < priceNow) { 
			cout << "Transaction failed: Your price is too low!" << endl;
			return;
		}
		else {
			double totalCost = num*priceNow*1.0; 
			double bal = getBalance(); 
			if (totalCost > bal) { 
				cout << "Transaction failed: Insufficient cash balance!" << endl;
			}
			else {
				Node* stock = dll.findNode(name); 
				if (stock == nullptr) {
					stock = new Node(name, num); 
					dll.insertNode(stock);
				}
				else {
					stock->set_num_stock(stock->get_num_stock() + num); 
				}
				stringstream ss;
				ss << fixed << setprecision(2) << bal - totalCost;
				setBalance(ss.str()); 
				ba.addHistory(4, totalCost); 
				addHistory(2, name, num, priceNow); 
				updateStockFile(); 
				cout << "You have purchased " << num << " shares of " << name << " at $" << 
					fixed << setprecision(2) << priceNow << " for a total of $" << priceNow*num << "." << endl;
			}
		}
	}
	else {
		cout << "Error: Stock not found" << endl;
	}
}

void StockAccount::sellShares(string name, int num, double price, BankAccount &ba)
{
	Node* stock = dll.findNode(name); 
	if (stock == nullptr) { 
		cout << "Transaction failed: You do not own this stock!" << endl;
	}
	else {
		double priceNow = findPriceByName(name); 
		if (priceNow > 0) {
			if (num > stock->get_num_stock()) {
				cout << "Transaction failed: Insufficient stock shares" << endl;
				return;
			}
			else {
				if (priceNow < price) { 
					cout << "Transaction failed: Price per stock is lower than what you want to sell for" << endl;
					return;
				}
				else {
					if (stock->get_num_stock() - num == 0) {
						dll.deleteNode(name); 
					}
					else {
						stock->set_num_stock(stock->get_num_stock() - num); 
					}
					stringstream ss;
					ss << fixed << setprecision(2) << getBalance() + num*priceNow*1.0;
					setBalance(ss.str()); 
					ba.addHistory(3, num*priceNow); 
					addHistory(1, name, num, priceNow); 
					updateStockFile(); 
					cout << "You have selled " << num << " shares of " << name << " at $" << 
						fixed << setprecision(2) << priceNow << " for a total of $" << priceNow*num << "." << endl;
				}
			}
		}
		else {
			cout << "Error: Stock not found!" << endl;
		}
	}
}

void StockAccount::updateStockFile()
{
	
	hf.cleanFile(STOCK_FILE);
	string title = "CompanySymbol\tNumber\t";
	hf.addToLastLine(STOCK_FILE, title);
	Node* currentPtr = dll.getHead()->getNext();
	while (currentPtr != dll.getTail()) {
		string stock = "\n" + currentPtr->get_name_stock() + "\t\t" + hf.convert2String(currentPtr->get_num_stock());
		hf.addToLastLine(STOCK_FILE, stock);
		currentPtr = currentPtr->getNext();
	}
}

void StockAccount::updatePortfolio()
{
	
	string balance_record = "\n" + hf.convertToString(get_portfolio()) + "\t" + hf.convertTimeToString(hf.getTimeSec());
	hf.addToLastLine(PORTFOLIO_FILE, balance_record);
}

void StockAccount::addHistory(int mode, string name, int num, double pricepershare)
{
	string record = "";
	string type = "";
	
	switch (mode) {
	case 1:
		type = "Sell";
		break;
	case 2:
		type = "Buy";
		break;
	default:
		break;
	}

	stringstream ss;
	ss << left << "\n" << setw(16) << type << setw(16) << name << setw(12) << hf.convert2String(num) << 
		setw(16) << "$" + hf.convertToString(pricepershare) << setw(16) << "$" + hf.convertToString(num*pricepershare) <<
		setw(16) << hf.getTime();
	record = ss.str();
	hf.addToLastLine(STOCK_HISTORY, record);
}

void StockAccount::check_private_files()
{
	
	if (!hf.checkFile(PORTFOLIO_FILE)) {
		string balance_record = "10000.00\t" + hf.convertTimeToString(hf.getTimeSec());
		hf.addToLastLine(PORTFOLIO_FILE, balance_record);
	}
	else {
			set_portfolio(get_portfolio_from_file());
	}

	if (!hf.checkFile(STOCK_HISTORY)) {
		stringstream ss;
		ss << left << setw(16) << "Event" << setw(16) << "CompSymbol" << setw(12) << "Number" << 
			setw(16) << "PricePerShare" << setw(16) << "TotalValue" << setw(16) << "Time";
		string title = ss.str();
		hf.addToLastLine(STOCK_HISTORY, title);
	}

	if (!hf.checkFile(STOCK_FILE)) {
		string title = "CompanySymbol\tNumber\t";
		hf.addToLastLine(STOCK_FILE, title);
	}
}
