#include "SetIterator.h"
#include <stdexcept>


SetIterator::SetIterator(const Set& s) : set{ s }, current{ 0 } {
	while (this->current < this->set.capacity && this->set.table[this->current] == -1) {
		this->current++;
	}
}
/*
	BC: Theta(1)
	WC: Theta(capacity)
	Total complexity: O(capacity)
*/


void SetIterator::first() {
	this->current = 0;
	while (this->current < this->set.capacity && this->set.table[this->current] == -1) {
		this->current++;
	}
}
/*
	BC: Theta(1)
	WC: Theta(capacity)
	Total complexity: O(capacity)
*/


void SetIterator::next() {
	if (!this->valid())
		throw std::runtime_error("");
	this->current++;
	while (this->current < this->set.capacity && this->set.table[this->current] == NULL_TELEM) {
		this->current++;
	}
}
/*
	BC: Theta(1)
	WC: Theta(capacity)
	Total complexity: O(capacity)
*/


TElem SetIterator::getCurrent()
{
	if (!this->valid())
		throw std::runtime_error("");
	return this->set.table[this->current];
}
/*
	BC: Theta(1)
	WC: Theta(1)
	Total complexity: O(1)
*/

bool SetIterator::valid() const {
	if (this->current < this->set.capacity && this->set.length > 0)
		return true;
	else
		return false;
}
/*
	BC: Theta(1)
	WC: Theta(1)
	Total complexity: O(1)
*/
