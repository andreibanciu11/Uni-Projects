#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r, int max_capacity)
{
	this->elems = new TElem[max_capacity];
	for (int index = 0; index < max_capacity; index++)
		this->elems[index] = NULL_TELEM;
	this->capacity = max_capacity;
	this->length = 0;
	this->r = r;
}
// Theta(capacity)


bool SortedSet::add(TComp elem) {
	int index;
	for (index = 0; index < this->length; index++)
	{
		TComp current_elem = this->elems[index];
		if (current_elem == elem)
			return false;
	}
	if (this->isFull() == 0)
	{
		if (this->length == 0)
			this->elems[0] = elem;
		else
		{
			if (this->length == this->capacity)
			{
				this->capacity *= 2;
				TElem* els = new TElem[this->capacity];
				for (int i = 0; i < this->length; i++)
					els[i] = this->elems[i];
				delete[] this->elems;
				this->elems = els;
			}
			index = 0;
			TComp current_elem = this->elems[index];
			while (this->r(current_elem, elem) == true && index < this->length - 1)
			{
				current_elem = this->elems[index + 1];
				index++;
			}
			if (index < this->length - 1 || (index == this->length - 1 && this->r(current_elem, elem) == false))
			{
				for (int i = this->length - 1; i >= index; i--)
				{
					this->elems[i + 1] = this->elems[i];
				}
				this->elems[index] = elem;
			}
			else
				this->elems[this->length] = elem;
		}
		this->length++;
		return true;
	}
	else
		return false;
}
// best case: Theta(1), worst case: Theta(length) => Total Complexity: O(length)


bool SortedSet::remove(TComp elem) {
	if (this->length == 0)
		return false;
	else
	{
		int index = 0;
		TComp current_elem = this->elems[index];
		while (current_elem != elem && index < this->length - 1)
		{
			current_elem = this->elems[index+1];
			index++;
		}
		if (index == length - 1)
		{
			if (current_elem != elem)
				return false;
			else
			{
				for (int i = index; i < this->length - 1; i++)
				{
					this->elems[i] = this->elems[i + 1];
				}
				this->length--;
				return true;
			}
		}
		else
		{
			for (int i = index; i < this->length - 1; i++)
			{
				this->elems[i] = this->elems[i + 1];
			}
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
		TComp current_elem = this->elems[index];
		if (current_elem == elem)
			return true;
	}
	return false;
}
// best case: Theta(1), worst case: Theta(length) => Total Complexity: O(length)


int SortedSet::size() const {
	return this->length;
}
// Theta(1)



bool SortedSet::isEmpty() const {
	if (this->length == 0)
		return true;
	else
		return false;
}
// Theta(1)

bool SortedSet::isFull() const
{
	if(this->length == this->capacity)
		return 1;
	else
		return 0;
}
// Theta(1)

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}
// Theta(1)


SortedSet::~SortedSet() {

}
// Theta(1)
