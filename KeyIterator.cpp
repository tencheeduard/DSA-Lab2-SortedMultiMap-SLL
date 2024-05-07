#include "KeyIterator.h"
#include "SortedMultiMap.h"

KeyIterator::KeyIterator(const TKeyNode& c) : key(c) {
	first();
}

void KeyIterator::first() {
	currentValue = key.head;
}

void KeyIterator::next() {
	if (!valid())
		throw exception();

	if (currentValue != NULL)
		currentValue = currentValue->next;
}

bool KeyIterator::valid() const {
	return currentValue != NULL;
}

TElem KeyIterator::getCurrent() const {
	if (!valid())
		throw exception();

	return make_pair(key.key, currentValue->value);
}


