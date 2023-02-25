#include "Node.h"

Node::Node(string name, int num)
	:stock_name(name), stock_num(num), price(0.0)
{
	this->prev = NULL;
	this->next = NULL;
}

int Node::get_num_stock()
{
	return stock_num;
}

void Node::set_num_stock(int num)
{
	stock_num = num;
}

string Node::get_name_stock()
{
	return stock_name;
}

Node * Node::getNext()
{
	return next;
}

double Node::getPrice()
{
	return price;
}