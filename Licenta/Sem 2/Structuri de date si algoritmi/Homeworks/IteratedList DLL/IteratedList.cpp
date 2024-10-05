#include <iostream>
#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"

using namespace std;

IteratedList::IteratedList() {
	this->current_size = 0;
	this->head = NULL;
	this->tail = NULL;
}

int IteratedList::size() const {
	return this->current_size;
}
//Theta(1)

bool IteratedList::isEmpty() const {
	return this->current_size == 0;
}
//Theta(1)

ListIterator IteratedList::first() const {
	return ListIterator(*this);
}
//Theta(1)

TElem IteratedList::getElement(ListIterator pos) const {
	if (!pos.valid())
		throw exception();
	///Average complexity  as we search from the head or from the tail based on the given 'i' - O(current_size/2) - linear
	///Best case when the position is either 0 or current_size - 1 or invalid 'i' - O(1) - constant

	// if the position is in the first half of the list then we begin from the head
	else
	{
		if (pos.current < this->current_size / 2)
		{
			DLLNode* current_element = this->head;
			for (int k = 0; k != pos.current; k++)
			{
				current_element = current_element->next;
			}
			return current_element->info;
		}
		else
		{   // if the position is in the second half of the list then we begin from the tail and we go backwards
			DLLNode* current_element = this->tail;
			for (int k = this->current_size - 1; k != pos.current; k--)
			{
				current_element = current_element->prev;
			}
			return current_element->info;
		}
	}
}

TElem IteratedList::remove(ListIterator& pos) {
    ////Best case complexity when we have to delete either the head or the tail - O(1) - constant
    ///Average case complexity we have to iterate through the elements and get to position 'i' - O(current_size) - linear

    if (!pos.valid())
    {
        throw exception();
    }
    TElem removed_element;
    if (pos.current == 0)
    {
        //Remove the head
        //Check if the head is only element
        if (this->head == this->tail)
        {
            DLLNode* current_node = this->head;
            removed_element = current_node->info;
            delete current_node;
            this->head = this->tail = NULL;
        }
        else
        {
            DLLNode* current_node = this->head;
            removed_element = current_node->info;
            this->head = current_node->next;
            delete current_node->prev;
            this->head->prev = NULL;
        }
    }
    else
        if (pos.current == this->current_size - 1)
        {
            DLLNode* current_node = this->tail;
            removed_element = current_node->info;
            this->tail = this->tail->prev;
            delete current_node->next;
            this->tail->next = NULL;
            pos.current = -1;
        }
        else
        {
            DLLNode* current_element = this->head;
            for (int k = 0; k != pos.current; k++)
            {
                current_element = current_element->next;
            }

            removed_element = current_element->info;

            current_element->prev->next = current_element->next;
            current_element->next->prev = current_element->prev;

            delete current_element;
        }
    this->current_size -= 1;
    return removed_element;
}

ListIterator IteratedList::search(TElem e) const {
    ///Average/Worst case complexity O(current_size) - linear , worst case when search for the last element
    ///Best case we search for the first element - O(1) - constant

    ListIterator it1 = this->first();
    for (int i = 0; i < this->current_size; i++)
    {
        if (it1.getCurrent() == e)
            return it1;
        it1.next();
    }
    it1.current = -1;
    return it1;
}

int IteratedList::removeAll(IteratedList& list)
{
    int count = 0;
    ListIterator it2 = list.first();
    while (it2.valid())
    {
        if ((this->search(it2.getCurrent())).valid())
        {
            TElem elem = it2.getCurrent();
            ListIterator it1 = this->search(elem);
            this->remove(it1);
            count++;
        }
        it2.next();
    }
    return count;
}
//Best case: Theta(1), worst case: Theta(list size), Total complexity: O(size)

TElem IteratedList::setElement(ListIterator pos, TElem e) {
    if (!pos.valid())
        throw exception();
    else
    {
        int i = 0;
        DLLNode* current_node = this->head;
        while (i < pos.current)
        {
            current_node = current_node->next;
            i++;
        }
        TElem info = current_node->info;
        current_node->info = e;
        return info;
    }
}
//best case: Theta(1), worst case: Theta(size), Total Complexity: O(size)

void IteratedList::addToPosition(ListIterator& pos, TElem e) {
    DLLNode* new_node = new DLLNode();
    new_node->info = e;
    if (!pos.valid())
        throw exception();
    else
    {
        int i = 0;
        DLLNode* current_node = this->head;
        while (i < pos.current)
        {
            current_node = current_node->next;
            i++;
        }
        if (i == this->current_size - 1)
        {
            current_node->next = new_node;
            new_node->prev = current_node;
            new_node->next = NULL;
            this->tail = new_node;
        }
        else
        {
            new_node->next = current_node->next;
            current_node->next->prev = new_node;
            current_node->next = new_node;
            new_node->prev = current_node;
        }
        pos.next();
        this->current_size += 1;
    }
}
//best case: Theta(1), worst case: Theta(size), Total complexity: O(size)

void IteratedList::addToEnd(TElem e) {
    DLLNode* new_node = new DLLNode();
    new_node->info = e;
    DLLNode* current_node = this->tail;
    if (current_node == NULL)
    {
        this->head = new_node;
        this->head->next = NULL;
        this->head->prev = NULL;
        this->tail = this->head;
    }
    else
    {
        current_node->next = new_node;
        new_node->prev = current_node;
        new_node->next = NULL;
        this->tail = new_node;
    }
    this->current_size += 1;
}
//Theta(1)

void IteratedList::addToBeginning(TElem e)
{
    DLLNode* new_node = new DLLNode();
    new_node->info = e;
    if (this->head == NULL)
    {
        this->head = new_node;
        this->head->next = NULL;
        this->head->prev = NULL;
        this->tail = this->head;
    }
    else
    {
        DLLNode* current_node = this->head;
        new_node->prev = NULL;
        new_node->next = current_node;
        current_node->prev = new_node;
        this->head = new_node;
    }
    this->current_size += 1;
}
//Theta(1)

IteratedList::~IteratedList() {
    DLLNode* temp;
    while (this->head != NULL) {
        temp = this->head;
        this->head = this->head->next;
        delete temp;
    }
}
//best case: Theta(1), worst case: Theta(size), Total complexity: O(size)

DLLNode::DLLNode(TElem info)
{
	this->info = info;
	this->next = NULL;
	this->prev = NULL;
}
//Theta(1)
