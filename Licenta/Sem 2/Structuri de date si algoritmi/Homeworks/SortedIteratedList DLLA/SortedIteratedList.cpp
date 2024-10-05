#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) {
	this->nodes = new DLLANode[10];
	this->cap = 10;
	for (int index = 0; index < 10; index++)
		this->nodes[index] = NULL;
	this->head = -1;
	this->tail = -1;
	this->first_free = 0;
	this->relation = r;
}
//Theta(capacity)

int SortedIteratedList::size() const {
	int node = head, count = 0;
	while (node != -1)
	{	
		node = this->nodes[node].next;
		count++;
	}
	return count;
}
//best case: Theta(1), worst case: Theta(size), Total complexity: O(size)

bool SortedIteratedList::isEmpty() const {
	if (this->head == -1)
		return true;
	else
		return false;
}
//Theta(1)

ListIterator SortedIteratedList::first() const {
	return ListIterator(*this);
}
//Theta(1)

TComp SortedIteratedList::getElement(ListIterator poz) const {
	if (poz.valid() == 0)
		throw exception();
	else
		return poz.getCurrent();
}
//Theta(1)

TComp SortedIteratedList::remove(ListIterator& poz) {
	if (poz.valid() == 0)
	{
		throw exception();
		return 0;
	}
	else
	{
		int node = this->head;
		while (this->nodes[node].info != this->getElement(poz))
			node = this->nodes[node].next;
		if (node == this->head)
		{		
			this->head = this->nodes[this->head].next;
			this->nodes[this->head].prev = -1;
		}
		else
		{
			if (node != this->tail)
			{
				this->nodes[this->nodes[node].prev].next = this->nodes[node].next;
				this->nodes[this->nodes[node].next].prev = this->nodes[node].prev;
			}
			else
			{
				this->nodes[this->nodes[node].prev].next = -1;
				this->tail = this->nodes[node].prev;
			}
		}
		poz.next();
		this->nodes[node].prev = -2;
		this->nodes[node].next = -2;
		this->first_free = node;
		//if (poz.valid() == 0)
			//throw exception();
		return this->nodes[node].info;
	}
}
//best case: Theta(1), worst case: Theta(size), Total complexity: O(size)

ListIterator SortedIteratedList::search(TComp e) const {
	ListIterator it = this->first();
	while (it.valid() && it.getCurrent() != e)
		it.next();
	return it;
}
//best case: Theta(1), worst case: Theta(size), Total complexity: O(size)

int SortedIteratedList::removeFromKtoK(int k)
{
	if (k <= 0)
		throw exception();
	else
	{
		int count = 0, nr = 0;
		ListIterator it = this->first();
		
		while (it.valid())
		{
			if ((count + 1) % k == 0)
			{
				this->remove(it);
				nr++;
			}
			else
				it.next();
			count++;
		}
		return nr;
	}
}
//best case: Theta(1), worst case: Theta(size), Total complexity: O(size)

void SortedIteratedList::add(TComp e) {
	if (this->first_free == -1)
	{
		this->cap *= 2;
		DLLANode* els = new DLLANode[this->cap];
		int node = this->head;
		while (node != -1)
		{
			els[node] = this->nodes[node];
			node = this->nodes[node].next;
		}
		delete[] this->nodes;
		this->nodes = els;
		this->first_free = this->cap / 2;
	}
	if (this->head == -1)
	{
		this->head = 0;
		this->tail = 0;
		this->nodes[0].info = e;
		this->nodes[0].prev = -1;
		this->nodes[0].next = -1;
		this->first_free = 1;
	}
	else
	{
		int node = this->head;
		while (node != -1 && this->relation(this->nodes[node].info, e))
			node = this->nodes[node].next;
		if (node == this->head)
		{
			this->nodes[first_free].info = e;
			this->nodes[first_free].prev = -1;
			this->nodes[first_free].next = this->head;
			this->nodes[this->head].prev = this->first_free;
			this->head = this->first_free;
		}
		else
		{
			if (node != -1)
			{
				this->nodes[first_free].info = e;
				this->nodes[first_free].prev = this->nodes[node].prev;
				this->nodes[first_free].next = node;
				this->nodes[node].prev = first_free;
				this->nodes[this->nodes[first_free].prev].next = first_free;
			}
			else
			{
				this->nodes[first_free].info = e;
				this->nodes[first_free].prev = this->tail;
				this->nodes[first_free].next = -1;
				this->nodes[this->tail].next = first_free;
				this->tail = this->first_free;
			}
		}
		int index = 0;
		while (this->nodes[index].prev != -2 && this->nodes[index].next != -2 && index < this->cap)
			index++;
		if (index == this->cap)
			this->first_free = -1;
		else
			this->first_free = index;
	}
}
//best case: Theta(1), worst case: Theta(size), Total complexity: O(size)

SortedIteratedList::~SortedIteratedList() {
	
}

DLLANode::DLLANode(TComp info)
{
	this->info = info;
	this->next = -2;
	this->prev = -2;
}
//Theta(1)
