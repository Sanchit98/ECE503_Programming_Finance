#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;
class Node {
	friend class DoublyLinkedList;
	friend class BubbleSort;
	friend class SelectionSort;
public:
	Node(string name, int num);
    //Set the number of stocks
	void set_num_stock(int num);
	//Get the number of stocks
	int get_num_stock(); 
	//Get the name of the stock
	string get_name_stock();

    //Get the price of the stocks
	double getPrice();

	Node* getNext(); 
private:
	Node *prev;
	Node *next;

	string stock_name;
	int stock_num;
	double price;
};

#endif 
