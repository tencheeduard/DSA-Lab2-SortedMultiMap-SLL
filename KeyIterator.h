#pragma once

#include "SortedMultiMap.h"

class KeyIterator {
	friend class SortedMultiMap;
private:
	const TKeyNode& key;

	KeyIterator(const TKeyNode& key);

	TValueNode* currentValue;

public:
	void first();
	void next();
	bool valid() const;
	TElem getCurrent() const;
};

