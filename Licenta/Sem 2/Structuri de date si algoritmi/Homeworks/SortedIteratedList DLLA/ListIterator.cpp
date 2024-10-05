#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list) {
	this->current = list.head;
}

void ListIterator::first() {
	this->current = this->list.head;
}
//Theta(1)

void ListIterator::next() {
	if (this->valid())
		this->current = this->list.nodes[current].next;
	else
		throw exception();
}
//Theta(1)

bool ListIterator::valid() const {
	if (this->current != -1)
		return true;
	else
		return false;
}
//Theta(1)

TComp ListIterator::getCurrent() const {
	return this->list.nodes[current].info;
}
//Theta(1)


