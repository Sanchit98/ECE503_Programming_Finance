#include "SortStrategy.h"

void BubbleSort::sortDoublyLinkedList(StockAccount & sa)
{
	cout << "Bubble sort selected" << endl << endl;
	Node* temp_pointer = sa.dll.head->next;
	while (temp_pointer != sa.dll.tail) {
		temp_pointer->price = sa.findPriceByName(temp_pointer->get_name_stock());
		temp_pointer = temp_pointer->next;
	}
	
	for (int i = 1; i <= sa.dll.nodeNum; i++) {
		for (int j = i; j <= sa.dll.nodeNum; j++) {
			Node* stk1 = sa.dll.findNodeByPosition(i);
			Node* stk2 = sa.dll.findNodeByPosition(j);
			double stock1 = stk1->get_num_stock() * stk1->price;
			double stock2 = stk2->get_num_stock() * stk2->price;
			if (stock1 < stock2) {
				sa.dll.swapNode(i, j);
			}
		}
	}
}

void SelectionSort::sortDoublyLinkedList(StockAccount & sa)
{
	cout << "Selection sort selected" << endl << endl;
	Node* temp_pointer = sa.dll.head->next;
	while (temp_pointer != sa.dll.tail) {
		temp_pointer->price = sa.findPriceByName(temp_pointer->get_name_stock()); 
		temp_pointer = temp_pointer->next;
	}

	for (int i = 1; i <= sa.dll.nodeNum - 1; i++) {
		int min = i;
		for (int j = i+1 ; j <= sa.dll.nodeNum; j++) {
			Node* stk1 = sa.dll.findNodeByPosition(min);
			Node* stk2 = sa.dll.findNodeByPosition(j);
			double stock1 = stk1->get_num_stock() * stk1->price;
			double stock2 = stk2->get_num_stock() * stk2->price;
			if (stock1 < stock2) {
				min = j;
			}
		}
		sa.dll.swapNode(i, min);
	}
}

Context::Context(SortStrategy* sortstrategy)
{
	this->_sortstrategy = sortstrategy;
}

Context::~Context()
{
	delete this->_sortstrategy;
}

void Context::DoSort(StockAccount& sa)
{
	this->_sortstrategy->sortDoublyLinkedList(sa);
}
