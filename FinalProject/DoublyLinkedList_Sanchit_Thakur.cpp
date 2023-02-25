#include<string>
using namespace std;
#include "StockAccount.h"
#include "DoublyLinkedList.h"
DoublyLinkedList::DoublyLinkedList()
{
	nodeNum = 0;
	//Initialize with empty head and tail node
	head = new Node("", 0);
	tail = new Node("", 0);
	head->prev = NULL;
	head->next = tail;
	tail->prev = head;
	tail->next = NULL;
}

DoublyLinkedList::~DoublyLinkedList()
{
	Node* currentPtr = head;
	while (currentPtr) {
		Node* temp_pointer = currentPtr;
		currentPtr = currentPtr->next;
		delete temp_pointer;
		temp_pointer = NULL;
	}
}

Node * DoublyLinkedList::getHead() const
{
	return head;
}

Node * DoublyLinkedList::getTail() const
{
	return tail;
}

void DoublyLinkedList::insertNode(Node * node)
{
	node->next = tail;
	node->prev = tail->prev;
	tail->prev->next = node;
	tail->prev = node;
	nodeNum++;
}

int DoublyLinkedList::getSize() const
{
	return nodeNum;
}

void DoublyLinkedList::deleteNode(string stock_name)
{
	Node * node = findNode(stock_name);
	if (node == nullptr) { 
		cout << "Stock not found!" << endl;
	}
	else { 
		node->prev->next = node->next;
		node->next->prev = node->prev;
		delete(node);
		nodeNum--;
	}
}

Node * DoublyLinkedList::findNode(string stock_name)
{
	Node * currentPtr = head->next;
	while (currentPtr != tail) { 
		if (currentPtr->stock_name == stock_name) {
			return currentPtr;
		}
		currentPtr = currentPtr->next;
	}
	return nullptr;
}

void DoublyLinkedList::swapNode(int pos1, int pos2) const
{
	Node* node1 = findNodeByPosition(pos1); 
	Node* node2 = findNodeByPosition(pos2);
	if (node1 == nullptr || node2 == nullptr) {
		cout << "This swap is invalid" << endl; 
		return;
	}
	else { 
		if (node1->next == node2) { 
			node1->next = node2->next;
			node2->prev = node1->prev;
			node1->prev->next = node2;
			node1->prev = node2;
			node2->next->prev = node1;
			node2->next = node1;
		}
		else if (node1->prev == node2) {
			node2->next = node1->next;
			node1->prev = node2->prev;
			node2->prev->next = node1;
			node2->prev = node1;
			node1->next->prev = node2;
			node1->next = node2;
		}
		else { 
			Node* temp_pointer = new Node("", 0);
			temp_pointer->next = node1->next;
			temp_pointer->prev = node1->prev;
			node1->prev->next = node2;
			node1->next->prev = node2;
			node1->prev = node2->prev;
			node1->next = node2->next;
			node2->prev->next = node1;
			node2->next->prev = node1;
			node2->prev = temp_pointer->prev;
			node2->next = temp_pointer->next;
			delete(temp_pointer);
		}
	}

}

Node * DoublyLinkedList::findNodeByPosition(int position) const
{
	if (position > getSize()) { 
		cout << "Invalid position" << endl;
		return nullptr;
	}
	else {
		int count = 1; 
		Node* temp_pointer = head->next;
		while ((count++) != position) {
			temp_pointer = temp_pointer->next;
		}
		return temp_pointer;
	}
}

void DoublyLinkedList::printList()
{
	Node* currentPtr = head->next;
	while (currentPtr != tail) {
		cout << currentPtr->stock_name << " ," << currentPtr->stock_num << endl;
		currentPtr = currentPtr->next;
	}
}
