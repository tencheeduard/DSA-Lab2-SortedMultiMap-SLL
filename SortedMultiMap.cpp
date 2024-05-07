#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include "KeyIterator.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
	this->head = NULL;
	this->r = r;
	this->amount = 0;
}

void SortedMultiMap::add(TKey c, TValue v) {

	// Complexity:
	// 
	// O(n)
	// Average: Theta(n)
	// Worst: Theta(n)
	// Best: Theta(1) if the sortedmultimap is empty
	
	// if there's no head, set this as head
	if (head == NULL)
	{
		head = new TKeyNode();
		head->key = c;
		head->head = new TValueNode();
		head->head->value = v;
	}
	else
	{
		// start from head, iterate over all nodes until the relation returns true
		TKeyNode* keyNode = head;

		// prevKeyNode for maintaining connections when adding later
		TKeyNode* prevKeyNode = NULL;
		while (keyNode->next != NULL && r(c, keyNode->key) == false)
		{
			prevKeyNode = keyNode;
			keyNode = keyNode->next;
		}

		
		// if the while loop ended with the condition being true, position was found within the linked list
		if (r(c, keyNode->key))
		{
			// if the current key is not equal to c, then the key does not exist and it must be added
			if (keyNode->key != c)
			{

				// create the new node
				TKeyNode* newNode = new TKeyNode;
				newNode->key = c;
				newNode->head = new TValueNode();
				newNode->head->value = v;

				// if there's no previous keynode, it means it needs to be added to the head
				if (prevKeyNode == NULL)
				{
					newNode->next = head;
					head = newNode;
				}

				// otherwise add it inbetween the nodes
				else
				{
					newNode->next = prevKeyNode->next;
					prevKeyNode->next = newNode;
				}
			}
			// if it is equal to c, the key already exists, just add the value
			else
			{

				// add new node to the head
				TValueNode* newNode = new TValueNode();
				newNode->value = v;
				newNode->next = keyNode->head;
				keyNode->head = newNode;
				
				// alternatively add to the end of the values list
				/*
				// iterate through all the values
				TValueNode* node = keyNode->head;
				while (node->next != NULL)
					node = node->next;

				// add the new value
				node->next = new TValueNode();
				node->next->value = v;
				*/
			}
		}
		// if the while loop ended with the keynode being null, append it to the end of the list
		else if (keyNode->next == NULL)
			{
				keyNode->next = new TKeyNode();
				keyNode->next->key = c;
				keyNode->next->head = new TValueNode();
				keyNode->next->head->value = v;
			}
	}


	// increase amount
	amount++;
}

vector<TValue> SortedMultiMap::search(TKey c) const {
	// Complexity:
	// 
	// O(n)
	// Average: Theta(n)
	// Worst: Theta(n)
	// Best: Theta(1) if the sortedmultimap is empty

	TKeyNode* keyNode = head;
	vector<TValue> returnValue;

	// if there is no head, list is empty, so just return empty vector
	if (keyNode == NULL)
		return returnValue;


	// iterate through keys until target is found
	while (keyNode->key != c)
	{

		// if at the last node and the key is still not equal, key doesn't exist so return empty vector
		if (keyNode->next == NULL)
			return returnValue;

		keyNode = keyNode->next;
	}

	// if key is found, collect all values
	TValueNode* valueNode = keyNode->head;
	while (valueNode != NULL)
	{
		returnValue.push_back(valueNode->value);
		valueNode = valueNode->next;
	}

	// return vector
	return returnValue;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
	// Complexity:
	// 
	// O(n)
	// Average: Theta(n)
	// Worst: Theta(n)
	// Best: Theta(1) if the list is empty


	// iterate through all keynodes until key is found
	TKeyNode* prevKeyNode = NULL;
	TKeyNode* keyNode = head;
	while (keyNode != NULL && keyNode->key != c)
	{
		prevKeyNode = keyNode;
		keyNode = keyNode->next;
	}


	// if not found, can't remove anything
	if(keyNode==NULL)
		return false;

	TValueNode* valueNode = keyNode->head;
	// if the value is on the first element
	if (valueNode->value == v)
	{

		// if it's not the only one in the list, then just delete it and make the next element head.
		if (valueNode->next != NULL)
		{
			keyNode->head = valueNode->next;
			delete valueNode;
			amount--;
			return true;
		}
		
		// if it is, delete the keynode

		// if the keynode is not the head of the smm
		if (prevKeyNode != NULL)
		{
			// if there is a next element, make sure that connection remains
			if (keyNode->next != NULL)
				prevKeyNode->next = keyNode->next;
			else
				prevKeyNode->next = NULL;
		}
		// if it is head
		if(head == keyNode)
			head = keyNode->next;

		delete valueNode;
		delete keyNode;

		// reduce amount
		amount--;
		return true;
	}
	// if it's not the first element
	else
	{
		// iterate through all values
		while (valueNode->next != NULL && valueNode->next->value != v)
			valueNode = valueNode->next;

		// if at the end of the list, return false because nothing was deleted
		if (valueNode->next == NULL)
			return false;

		// else delete the node and preserve the connection
		else
		{
			// delete
			TValueNode* tmp = valueNode->next;
			valueNode->next = valueNode->next->next;
			delete tmp;

			// reduce amount
			amount--;
			return true;
		}
	}
}


int SortedMultiMap::size() const {
	return amount;
}

bool SortedMultiMap::isEmpty() const {
	return amount == 0;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

KeyIterator SortedMultiMap::keyIterator(TKey c) const
{
	// Complexity:
	// 
	// O(n)
	// Average: Theta(n)
	// Worst: Theta(n)
	// Best: Theta(n)

	// iterate through keys
	TKeyNode* keyNode = head;
	while (keyNode != NULL && keyNode->key != c)
		keyNode = keyNode->next;

	if (keyNode != NULL && keyNode->key == c)
		return KeyIterator(*keyNode);
}

SortedMultiMap::~SortedMultiMap() {
	
	// Complexity:
	// 
	// O(n)
	// Average: Theta(n)
	// Worst: Theta(n)
	// Best: Theta(n)

	// iterate through all keynodes
	TKeyNode* keyNode = head;
	TKeyNode* prevNode = NULL;
	while (keyNode != NULL)
	{
		// keep the address of the current keynode for deletion afterward
		prevNode = keyNode;

		// iterate through all valuenodes of current keynode
		TValueNode* valueNode = keyNode->head;
		TValueNode* prevValueNode = NULL;
		while (valueNode != NULL)
		{
			// keep the address of the current valuenode for deletion afterward
			prevValueNode = valueNode;

			// move on to the next with valuenode
			valueNode = valueNode->next;

			// delete the stored valuenode
			delete prevValueNode;
		}

		// move on to the next with keynode
		keyNode = keyNode->next;

		// delete the stored keynode
		delete prevNode;
	}

}
