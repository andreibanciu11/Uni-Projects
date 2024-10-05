#pragma once
#define NULL_TELEM 0
typedef int TElem;

class DynamicVector
{
private:
    TElem* elems;
    int size;
    int capacity;

public:
    // default constructor for a DynamicVector
    DynamicVector(int capacity = 10);

    // copy constructor for a DynamicVector
    DynamicVector(const DynamicVector& v);
    ~DynamicVector();

    // assignment operator for a DynamicVector
    DynamicVector& operator=(const DynamicVector& v);

    // Adds an element to the current DynamicVector.
    void add(const TElem& e);

    // Deletes the element situated at the given Index
    int deleteIndex(int Index);
    int updateIndex(int Index, TElem t);
    int insertAfterIndex(int Index, TElem t);
    int getSize() const;
    TElem getElementAtIndex(int Index) const;

    // Resizes the current DynamicVector, multiplying its capacity by a given factor (real number).
    void resize(double factor = 2);
};
