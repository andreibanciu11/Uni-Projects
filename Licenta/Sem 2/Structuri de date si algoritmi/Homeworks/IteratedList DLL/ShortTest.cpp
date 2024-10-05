#include "ShortTest.h"

#include <assert.h>
#include <exception>


#include "IteratedList.h"
#include "ListIterator.h"



using namespace std;

void testAll() {
	IteratedList list = IteratedList();
	assert(list.size() == 0);
	assert(list.isEmpty());

	list.addToEnd(1);
	assert(list.size() == 1);
	assert(!list.isEmpty());

	ListIterator it = list.search(1);
	assert(it.valid());
	assert(it.getCurrent() == 1);
	it.next();
	assert(!it.valid());
	it.first();
	assert(it.valid());
	assert(it.getCurrent() == 1);

	assert(list.remove(it) == 1);
	assert(list.size() == 0);
	assert(list.isEmpty());

	list.addToEnd(1);
	list.addToEnd(3);
	list.addToEnd(7);
	ListIterator it3 = list.first();
	list.addToPosition(it3, 77);
	list.addToPosition(it3, 44);
	assert(list.size() == 5);
	ListIterator it2 = list.first();
	assert(it2.getCurrent() == 1);
	it2.next();
	assert(it2.getCurrent() == 77);
	it2.next();
	assert(it2.getCurrent() == 44);
	it2.next();
	assert(it2.getCurrent() == 3);
	it2.next();
	assert(it2.getCurrent() == 7);
	it2.next();
	assert(it2.valid() == false);

	IteratedList list2 = IteratedList();
	list2.addToBeginning(4);
	list2.addToEnd(5);
	list2.addToBeginning(3);
	list2.addToEnd(6);
	list2.addToBeginning(2);
	list2.addToEnd(7);
	int i = 2;
	ListIterator it4 = list2.first();
	while (it4.valid()) {
		assert(it4.getCurrent() == i);
		i++;
		it4.next();
	}

	IteratedList list3 = IteratedList();
	list3.addToBeginning(4);
	list3.addToEnd(5);
	list3.addToBeginning(3);
	list3.addToEnd(6);
	list3.addToBeginning(2);
	list3.addToEnd(7);

	IteratedList list4 = IteratedList();
	list4.addToEnd(1);
	list4.addToEnd(2);
	list4.addToEnd(3);
	list4.addToEnd(4);
	list4.addToEnd(5);
	list4.addToEnd(6);
	list4.addToEnd(7);
	list4.addToEnd(8);
	list4.addToEnd(9);
	list4.addToEnd(10);

	assert(list4.removeAll(list3) == 6);

	ListIterator it5 = list4.first();

	assert(it5.getCurrent() == 1);
	it5.next();
	assert(it5.getCurrent() == 8);
	it5.next();
	assert(it5.getCurrent() == 9);
	it5.next();
	assert(it5.getCurrent() == 10);
}
