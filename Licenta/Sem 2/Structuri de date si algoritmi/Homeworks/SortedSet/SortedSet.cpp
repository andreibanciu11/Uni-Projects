#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) : vector(new DynamicVector{10}), capacity(10), length(0), r(r) {}
// Theta(1)


bool SortedSet::add(TComp elem) {
	int index;
	for (index = 0; index < this->length; index++)
	{
		TComp current_elem = this->vector->getElementAtIndex(index);
		if(current_elem == elem)
			return false;
	}
	if (this->length == 0)
		this->vector->add(elem);
	else
	{
		if (this->length == this->capacity)
		{
			this->vector->resize();
			this->capacity *= 2;
		}
		index = 0;
		TComp current_elem = this->vector->getElementAtIndex(index);
		while (this->r(current_elem, elem) == true && index<this->length-1)
		{
			current_elem = this->vector->getElementAtIndex(index + 1);
			index++;
		}
		if (index < this->length - 1 || (index == this->length - 1 && this->r(current_elem, elem) == false))
			this->vector->insertAfterIndex(index, elem);
		else
			this->vector->add(elem);
	}
	this->length++;
	return true;
}
// best case: Theta(1), worst case: Theta(length) => Total Complexity: O(length)


bool SortedSet::remove(TComp elem) {
	if (this->length == 0)
		return false;
	else
	{
		int index = 0;
		TComp current_elem = this->vector->getElementAtIndex(index);
		while (current_elem != elem && index < this->length-1)
		{
			current_elem = this->vector->getElementAtIndex(index + 1);
			index++;
		}
		if (index == length - 1)
		{
			if (current_elem != elem)
				return false;
			else
			{
				this->vector->deleteIndex(index);
				this->length--;
				return true;
			}
		}
		else
		{
			this->vector->deleteIndex(index);
			this->length--;
			return true;
		}
	}
}
// best case: Theta(1), worst case: Theta(length) => Total Complexity: O(length)


bool SortedSet::search(TComp elem) const {
	int index;
	for (index = 0; index < this->length; index++)
	{
		TComp current_elem = this->vector->getElementAtIndex(index);
		if (current_elem == elem)
			return true;
	}
	return false;
}
// best case: Theta(1), worst case: Theta(length) => Total Complexity: O(length)


int SortedSet::size() const {
	return this->vector->getSize();
}
// Theta(1)



bool SortedSet::isEmpty() const {
	if (this->vector->getSize() == 0)
		return true;
	else
		return false;
}
// Theta(1)

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}
// Theta(1)


SortedSet::~SortedSet() {
	
}
// Theta(1)
