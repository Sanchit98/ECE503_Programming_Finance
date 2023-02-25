#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

using namespace std;
#include"Node.h"
#include"StockAccount.h"
class StockAccount;
class DoublyLinkedList
{
	friend class BubbleSort;
	friend class SelectionSort;
public:
	DoublyLinkedList(); 
	~DoublyLinkedList();

	Node* getHead() const; 
	Node* getTail() const; 
		
	int getSize() const; 

	void insertNode(Node *node); 
	void deleteNode(string stockName);  
	Node* findNode(string stockName); 

	Node* findNodeByPosition(int position) const; 
	void swapNode(int pos1, int pos2) const; 

	void printList(); 

private:
	Node* head; 
	Node* tail; 
	int nodeNum;
};
#endif 