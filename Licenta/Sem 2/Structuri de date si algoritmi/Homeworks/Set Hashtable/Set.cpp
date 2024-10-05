#include "Set.h"
#include "SetITerator.h"
#include <iostream>

using namespace std;

Set::Set() : capacity{ 10 }, length{ 0 }, first_free{ 0 }{
	this->table = new TElem[10];
	this->next_node = new TElem[10];
	for (int i = 0; i < this->capacity; i++)
	{
		this->table[i] = NULL_TELEM;
        this->next_node[i] = -1;
	}
}
/*
    BC: Theta(capacity)
    WC: Theta(capacity)
    Total complexity: O(capacity)
*/


bool Set::add(TElem elem) {
    int insert_position = this->hash(elem);
    if (this->length == this->capacity) {
        this->resize();
    }
    if (this->table[insert_position] == NULL_TELEM) {
        this->table[insert_position] = elem;
        this->next_node[insert_position] = -1;
        if (this->first_free == insert_position)
            this->updateFirstFreePosition();
    }
    else {
        int current = insert_position;
        bool found = false;
        while (this->next_node[current] != -1 && found == false) {
            if (this->table[current] == elem) {
                found = true;
            }
            current = this->next_node[current];
        }
        if (found == true)
            return false;
        if (this->table[current] == elem)
            return false;
        this->table[this->first_free] = elem;
        this->next_node[this->first_free] = -1;
        this->next_node[current] = this->first_free;
        this->updateFirstFreePosition();
    }
    this->length++;
    return true;
}
/*
    BC: Theta(1)
    WC: Theta(length)
    Total complexity: O(length)
*/


bool Set::remove(TElem elem) {
    int current = this->hash(elem);
    int prev = -1;
    int index = 0;

    while (current != -1 && this->table[current] != elem) {
        prev = current;
        current = this->next_node[current];
    }

    if (current == -1) { // we didn't find the element in the set
        return false;
    }
    else {
        bool done = false;
        do {
            int current_pos = this->next_node[current];
            int prev_pos = current;

            while (current_pos != -1 && this->hash(this->table[current_pos]) != current) {
                prev_pos = current_pos;
                current_pos = this->next_node[current_pos];
            }

            if (current_pos == -1) {
                done = true;
            }
            else {
                this->table[current] = this->table[current_pos];
                current = current_pos;
                prev = prev_pos;
            }
        } while (done == false);

        if (prev != -1) {
            this->next_node[prev] = this->next_node[current];
        }
        this->table[current] = NULL_TELEM;
        this->next_node[current] = -1;
        if (current < this->first_free) {
            this->first_free = current;
        }
    }
    this->length--;
    return true;
}
/*
    BC: Theta(capacity)
    WC: Theta(capacity)
    Total complexity: O(capacity)
*/

bool Set::search(TElem elem) const {
    int current = this->hash(elem);
    while (current != -1) {
        if (this->table[current] == elem) {
            return true;
        }
        current = this->next_node[current];
    }
    return false;
}
/*
    BC: Theta(1)
    WC: Theta(length)
    Total complexity: O(length)
*/


int Set::size() const {
    return this->length;
}
/*
    BC: Theta(1)
    WC: Theta(1)
    Total complexity: O(1)
*/


bool Set::isEmpty() const {
    if (this->length == 0)
        return true;
    else
        return false;
}
/*
    BC: Theta(1)
    WC: Theta(1)
    Total complexity: O(1)
*/


Set::~Set() {
	//TODO - Implementation
}

int Set::getRange() const
{
    if (this->size() == 0)
        return -1;
    int max_value = -1;
    int min_value = 10000;
    SetIterator it{ *this };
    while (it.valid())
    {
        if (it.getCurrent() > max_value)
            max_value = it.getCurrent();
        if (it.getCurrent() < min_value)
            min_value = it.getCurrent();
        it.next();
    }
    return max_value - min_value;
}
/*
    BC: Theta(1)
    WC: Theta(length)
    Total complexity: O(length)
*/


SetIterator Set::iterator() const {
	return SetIterator(*this);
}
/*
    BC: Theta(1)
    WC: Theta(1)
    Total complexity: O(1)
*/

int Set::hash(TElem elem) const {
    if (elem < 0)
        elem *= -1;
    return elem % this->capacity;
}
/*
    BC: Theta(1)
    WC: Theta(1)
    Total complexity: O(1)
*/

void Set::updateFirstFreePosition() {
    this->first_free++;
    while (this->first_free < this->capacity && this->table[this->first_free] != NULL_TELEM)
        this->first_free++;
}
/*
    BC: Theta(1)
    WC: Theta(length)
    Total complexity: O(length)
*/

void Set::resize() {
    TElem* old_table = new TElem[this->length];
    for (int i = 0; i < this->length; i++) {
        old_table[i] = NULL_TELEM;
    }
    int current = 0;
    for (int i = 0; i < this->capacity; i++) {
        if (this->table[i] != NULL_TELEM) {
            old_table[current++] = this->table[i];
        }
    }

    this->capacity *= 2;
    TElem* new_table = new TElem[this->capacity];
    int* new_next = new int[this->capacity];
    for (int i = 0; i < this->capacity; i++) {
        new_table[i] = NULL_TELEM;
        new_next[i] = -1;
    }
    delete[] this->table;
    delete[] this->next_node;
    this->table = new_table;
    this->next_node = new_next;

    this->first_free = 0;
    int old_length = this->length;
    this->length = 0;
    for (int i = 0; i < old_length; i++) {
        add(old_table[i]);
    }
    delete[] old_table;
}
/*
    BC: Theta(capacity)
    WC: Theta(capacity)
    Total complexity: O(capacity)
*/


