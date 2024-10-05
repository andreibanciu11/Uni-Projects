#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	this->current = 0;
}
// Theta(1)


void SortedSetIterator::first() {
	this->current = 0;
}
// Theta(1)


void SortedSetIterator::next() {
	if (this->current >= this->multime.length)
		throw exception();
	else
		this->current++;
}
// Theta(1)


TElem SortedSetIterator::getCurrent()
{
	if (this->current >= this->multime.length)
		throw exception();
	else
		return this->multime.elems[this->current];
}
// Theta(1)

bool SortedSetIterator::valid() const {
	if (this->current < this->multime.length)
		return true;
	else
		return false;
}
// Theta(1)

