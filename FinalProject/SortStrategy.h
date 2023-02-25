#ifndef SORTSTRATEGY_H
#define SORTSTRATEGY_H

#include"StockAccount.h"

class StockAccount;

class Context {
public:
	Context(SortStrategy*);
	~Context();
	void DoSort(StockAccount& sa); 

private:
	SortStrategy* _sortstrategy;
};
#endif 

class SortStrategy {
public:
	virtual void sortDoublyLinkedList(StockAccount& sa) = 0;
};


class SelectionSort : public SortStrategy {
	virtual void sortDoublyLinkedList(StockAccount& sa);
};

class BubbleSort : public SortStrategy {
	virtual void sortDoublyLinkedList(StockAccount& sa);
};
