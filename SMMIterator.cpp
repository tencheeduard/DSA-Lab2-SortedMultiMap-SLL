#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	first();
}

void SMMIterator::first(){
	currentKey = map.head;
	if (currentKey != NULL)
		currentValue = currentKey->head;
	else
		currentValue = NULL;
}

void SMMIterator::next(){
	if (!valid())
		throw exception();

	if (currentValue->next != NULL)
		currentValue = currentValue->next;
	else {
		currentKey = currentKey->next;
		if (currentKey != NULL)
			currentValue = currentKey->head;
		else currentValue = NULL;
	}
}

bool SMMIterator::valid() const{
	return currentKey != NULL && currentValue != NULL;
}

TElem SMMIterator::getCurrent() const{
	if (!valid())
		throw exception();

	return make_pair(currentKey->key, currentValue->value);
}


