#ifndef HELPERFUNC_H
#define HELPERFUNC_H
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#define CASH_BALANCE "data\\cash_balance.txt"

#define BANK_HISTORY "data\\bank_transaction_history.txt"

#define PORTFOLIO_FILE "data\\stock_portfolio.txt"
#define STOCK_FILE "data\\stock_details.txt"
#define STOCK_HISTORY "data\\stock_transaction_history.txt"

#define RESULT_1 "data\\Result_1.txt"
#define RESULT_2 "data\\Result_2.txt"

class HelperFunc {
public:
	HelperFunc();
	string convertToString(double d) const; 
	string convert2String(double d) const; 
	string convertTimeToString(long d) const; 

	bool checkFile(char* file) const; 
	void cleanFile(char* file); 
	string searchFile(char* file, string key) const;

	string getDate() const; 
	string getTime() const; 
	time_t getTimeSec() const; 

	int getLineNum(char* file) const; 
	void printAllLines(char* file) const; 

	void writeBalanceToFile(char* file, string s); 
	void addToLastLine(char* file, string str); 
	string getLastLine(char* file) const; 

	string split(string str, int num) const;

};

#endif 
