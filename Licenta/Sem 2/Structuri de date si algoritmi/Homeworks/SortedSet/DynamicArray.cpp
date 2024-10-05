#include "DynamicArray.h"

DynamicVector::DynamicVector(int capacity)
{
    this->size = 0;
    this->capacity = capacity;
    this->elems = new TElem[capacity];
    for (int index = 0; index < capacity; index++)
        this->elems[index] = NULL_TELEM;
}

DynamicVector::DynamicVector(const DynamicVector& v)
{
    this->size = v.size;
    this->capacity = v.capacity;
    this->elems = new TElem[this->capacity];
    for (int i = 0; i < this->size; i++)
        this->elems[i] = v.elems[i];
}

DynamicVector::~DynamicVector()
{
    delete[] this->elems;
}

DynamicVector& DynamicVector::operator=(const DynamicVector& v)
{
    if (this == &v)
        return *this;

    this->size = v.size;
    this->capacity = v.capacity;

    delete[] this->elems;
    this->elems = new TElem[this->capacity];
    for (int i = 0; i < this->size; i++)
        this->elems[i] = v.elems[i];

    return *this;
}

void DynamicVector::add(const TElem& e)
{
    if (this->size == this->capacity)
        this->resize();
    this->elems[this->size] = e;
    this->size++;
}

int DynamicVector::deleteIndex(int Index)
{
    if (Index < 0 || Index > this->size - 1)
    {
        return -1;
    }
    for (int i = Index; i < this->size - 1; i++)
    {
        this->elems[i] = this->elems[i + 1];
    }

    this->size -= 1;

    return 0;
}

void DynamicVector::resize(double factor)
{
    this->capacity *= static_cast<int>(factor);

    TElem* els = new TElem[this->capacity];
    for (int i = 0; i < this->size; i++)
        els[i] = this->elems[i];

    delete[] this->elems;
    this->elems = els;
}

int DynamicVector::getSize() const
{
    return this->size;
}

TElem DynamicVector::getElementAtIndex(int Index) const
{

    if (Index < 0 || Index > this->size - 1)
    {
        return TElem();
    }

    return this->elems[Index];

}

int DynamicVector::updateIndex(int Index, TElem t)
{
    if (Index < 0 || Index > this->size - 1)
    {
        return -1;
    }

    this->elems[Index] = t;
    return 0;
}

int DynamicVector::insertAfterIndex(int Index, TElem t)
{
    if (Index < 0 || Index > this->size)
    {
        return -1;
    }

    for (int i = this->size - 1; i >= Index; i--)
    {
        this->elems[i + 1] = this->elems[i];
    }
    this->elems[Index] = t;
    this->size += 1;

}