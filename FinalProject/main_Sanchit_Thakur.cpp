#include <iostream>
#include <string>
using namespace std;

#include "HelperFunc.h"
#include "BankAccount.h"
#include "StockAccount.h"
#include "DoublyLinkedList.h"

void ManageStockAccount(); 
void ManageBankAccout(); 
void Setting(); 
void Exit(); 
template <class T> 
T getPositive(); 

BankAccount ba; 
StockAccount sa; 

int main(int argc, char * argv[]) {
	int choice = 0;
	while (choice != 4) { 
		cout << endl << "Welcome to the Account Management System!" << endl;
		cout << "Please select an account to access:" << endl;
		cout << "1. Stock Portfolio Account" << endl;
		cout << "2. Bank Account" << endl;
		cout << "3. Settings (Design Pattern: Strategy)" << endl;
		cout << "4. Exit" << endl;
		cout << endl << "Option: ";
		cin >> choice; 
		cin.clear();
		cin.ignore(1024, '\n');

		switch (choice) 
		{
		case 1:
			ManageStockAccount();
			break;
		case 2:
			ManageBankAccout();
			break;
		case 3:
			Setting();
			break;
		case 4:
			Exit();
			break;
		default:
			cout << "Please enter the right choice!" << endl;
			break;
		}
	}

	system("pause");
	return 0;
}

void ManageStockAccount(int argc, char * argv[])
{
	int choice = 0;
	while (choice != 7) {
		cout << endl << "Stock Portfolio Account!" << endl;
		cout << "Please select an option :" << endl;
		cout << "1. Display the price for a stock symbol" << endl;
		cout << "2. Display the current portfolio" << endl;
		cout << "3. Buy shares" << endl;
		cout << "4. Sell shares" << endl;
		cout << "5. View a graph for the portfolio value" << endl;
		cout << "6. View transaction history" << endl;
		cout << "7. Return to previous menu" << endl;
		cout << endl << "Option: ";
		cin >> choice;
		cin.clear();
		cin.ignore(1024, '\n');
        string r_command;
		string filename;
		string rscript;
		string path_filename;
		string name; 
		int num; 
		double price; 

		switch (choice)
		{
		case 1:
			cout << "Please enter the stock symbol: " << endl;
			getline(cin, name); 
			sa.showStockDetails(name); 
			break;
		case 2:
			sa.pCon->DoSort(sa); 
			sa.printDetails();
			break;
		case 3:
			cout << "Please enter the stock symbol you wish to purchase: " << endl;
			getline(cin, name); 
			cout << "Please enter the number of shares: " << endl;
			num = getPositive<int>(); 
			cout << "Please enter the maximum amount you are willing to pay per share: " << endl << "$";
			price = getPositive<double>(); 
			sa.buyShares(name, num, price, ba); 
			break;
		case 4:
			cout << "Please enter the stock symbol you wish to sell: " << endl;
			getline(cin, name); 
			cout << "Please enter the number of shares: " << endl;
			num = getPositive<int>(); 
			cout << "Please enter the minimum amount you are willing to sell per share: " << endl << "$";
			price = getPositive<double>(); 
			sa.sellShares(name, num, price, ba); 
			break;
		case 5:
			r_command = argv[0]; 
			cin.get();
			filename = "/temp.R"; 
			rscript = "RScript \\";
			path_filename = r_command + filename;
			cout<<path_filename;
			system(path_filename.c_str());
			//sa.printGraph(); //print the graph by matlab
			break;
		case 6:
			sa.printHistory(); 
			break;
		case 7:
			break; 
		default:
			cout << "Please enter the right choice!" << endl;
			break;
		}
	}
}

void ManageBankAccout()
{
	int choice = 0;
	double money;
	while (choice != 5) { 
		cout << endl << "Stock Portfolio Account" << endl;
		cout << "Please select an option :" << endl;
		cout << "1. View account balance" << endl;
		cout << "2. Deposit money" << endl;
		cout << "3. Withdraw money" << endl;
		cout << "4. Print out history" << endl;
		cout << "5. Return to previous menu" << endl;
		cout << endl << "Option: ";
		cin >> choice;
		cin.clear();
		cin.ignore(1024, '\n');

		switch (choice)
		{
		case 1:
			ba.printDetails(); 
			break;
		case 2:
			cout << "Please enter the amount you want to deposit:" << endl << "$";
			money = getPositive<double>(); 
			ba.depositMoney(money); 
			sa.set_portfolio(sa.get_portfolio() + money); 
			break;
		case 3:
			cout << "Please enter the amount you want to withdraw:" << endl << "$";
			money = getPositive<double>(); 
			ba.withdrawMoney(money); 
			sa.set_portfolio(sa.get_portfolio() - money); 
			break;
		case 4:
			ba.printHistory(); 
			break;
		case 5:
			break;
		default:
			cout << "Please enter the right choice!" << endl;
			break;
		}
	}
}

void Setting()
{
	int choice = 0;
	while (choice != 3) {
		cout << endl << "Settings (Design Pattern: Strategy)" << endl;
		cout << "Please select an option :" << endl;
		cout << "1. Bubble Sort (default)" << endl;
		cout << "2. Selection Sort" << endl;
		cout << "3. Return to previous menu" << endl;
		cout << endl << "Option: ";
		cin >> choice;
		cin.clear();
		cin.ignore(1024, '\n');

		switch (choice)
		{
		case 1:
		//Bubble sorting
			sa.pSS = new BubbleSort();
			cout << "You have change the sort method to bubble sort." << endl;
			break;
		case 2:
		//Selection sorting
			sa.pSS = new SelectionSort();
			cout << "You have change the sort method to selection sort." << endl;
			break;
		case 3:
			break; 
		default:
			cout << "Please enter the right choice!" << endl;
			break;
		}

		sa.pCon = new Context(sa.pSS);

	}
}

template <class T> T getPositive() 
{
	T m;
	cin >> m;
	cin.clear();
	cin.ignore(1024, '\n');
	while (m <= 0) { 
		cout << "Error: Please enter a positive number!" << endl;
		cin >> m;
		cin.clear();
		cin.ignore(1024, '\n');
	}
	return m;
}

void Exit()
{
	sa.updatePortfolio(); 
}