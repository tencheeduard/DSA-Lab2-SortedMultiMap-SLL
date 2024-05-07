#include <assert.h>

#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include "KeyIterator.h"
#include <exception>
#include <vector>

using namespace std;

bool relation1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedMultiMap smm = SortedMultiMap(relation1);
	assert(smm.size() == 0);
	assert(smm.isEmpty());
    smm.add(1,2);
    smm.add(1,3);
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector<TValue> v= smm.search(1);
    assert(v.size()==2);
    v= smm.search(3);
    assert(v.size()==0);
    SMMIterator it = smm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	it.next();
    }
    assert(smm.remove(1, 2) == true);
    assert(smm.remove(1, 3) == true);
    assert(smm.remove(2, 1) == false);
    assert(smm.isEmpty());


    // KEY ITERATOR TESTS
    KeyIterator kit = smm.keyIterator(1);

    assert(!kit.valid());
    try {
        kit.next();
        assert(false);
    }
    catch (exception& ex) {
        assert(true);
    }
    try {
        kit.getCurrent();
        assert(false);
    }
    catch (exception& ex) {
        assert(true);
    }

    smm.add(1, 2);
    smm.add(1, 4);
    smm.add(1, 3);
    smm.add(1, 5);

    KeyIterator kit2 = smm.keyIterator(1);

    kit2.first();
    assert(kit2.valid());
    vector<TValue> values = smm.search(1);
    int i = 0;
    while (kit2.valid())
    {
        TElem e = kit2.getCurrent();
        assert(e.second == values[i]);
        i++;
        kit2.next();
    }


}