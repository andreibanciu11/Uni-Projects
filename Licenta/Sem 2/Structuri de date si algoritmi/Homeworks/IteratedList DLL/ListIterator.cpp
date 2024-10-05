#include "ListIterator.h"
#include "IteratedList.h"
#include <exception>
#include <iostream>

using namespace std;

ListIterator::ListIterator(const IteratedList& list) : list(list) {
	this->current = 0;
}
//Theta(1)

void ListIterator::first() {
	this->current = 0;
}
//Theta(1)

void ListIterator::next() {
	if (!this->valid())
	{
		throw exception();
	}
	this->current += 1;
}
//Theta(1)

bool ListIterator::valid() const {
	if ((this->current > this->list.current_size - 1) || this->current < 0)
	{
		return false;
	}
	return true;
}
//Theta(1)

TElem ListIterator::getCurrent() const {
	ListIterator it1 = this->list.first();
	int i = 0;
	if (this->current == -1)
	{
		throw exception();
		return -1;
	}
	while (i < this->current)
	{
		it1.next();
		i++;
	}
	return this->list.getElement(it1);
}
//best case: Theta(1), worst case: Theta(size), Total complexity: O(1)
