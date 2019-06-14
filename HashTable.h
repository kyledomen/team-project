// Node for a binary tree
// Created by A. Student
// Modified by: Tuan Truong
// This hash table is using linked list as a collision resolution method
#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include<string>
#include<iostream>
#include<iomanip>
#include<cmath>
#include"SList.hpp"
using namespace std;

template<class ItemType>
class HashTable
{
private:
	SList<ItemType>* data; //  an array of Linked List
	int size;  // the hash table size
	int count; // number of items in the hash table


	int dankHash(string key) const; // good hash
	int oofHash(string key) const; // bad hash

public:
	// the main functions
	HashTable(int number) { allocateMemory(number); count = 0; }
	~HashTable() { delete[] data; }
	void allocateMemory(int number);
	bool insert(const ItemType* item);
	bool search(const ItemType* target, ItemType* returnItem);
	bool remove(const ItemType* target, ItemType* returnItem);


	// getters
	int getSize() const { return size; }
	int getCount() const { return count; }
	double getLoadFactor() const;
	bool isEmpty() const { return count == 0; }

};


// check if the number is prime
bool IsPrime(int number)
{
	for (int i = 2; i < number / 2; i++)
	{
		if (number % i == 0)
		{
			return false;
		}
	}
	return true;
}

// allcate the memory for the hash table
template<class ItemType>
void HashTable<ItemType>::allocateMemory(int number)
{
	size = number * 2 + 1;
	while (!IsPrime(size))
	{
		size++;
	}
	data = new SList<ItemType> * [size];
	for (int i = 0; i < size; i++)
	{
		data[i] = 0;
	}
	count = 0;
	this->size = size;
}

// the good hashing function
template<class ItemType>
int HashTable<ItemType>::dankHash(string key) const
{
	int index = 0;
	for (int i = 0; i < key.length(); i++)
	{
		index += key[i] * key[i] * key[i];
	}
	return key % size;
}

// the bad hashing function
template<class ItemType>
int HashTable<ItemType>::oofHash(string key) const
{
	int index = 0;
	for (int i = 0; i < key.length(); i++)
	{
		index += key[i];
	}
	return key % size;
}

// insert the item into the hash table
template<class ItemType>
bool HashTable<ItemType>::insert(const ItemType* item)
{
	if (isFull())
		return false;
	int index = dankHash(item->getModelNo()); // the good hasing function
	data[index].insertNode(item);
	count++;
	return true;
}

// search for an item from the hash table
template<class ItemType>
bool HashTable<ItemType>::search(const ItemType* target, ItemType* returnItem)
{
	bool found = false;
	int index = dankHash(item->getModelNo()); // good hashing function
	if (data[index].searchList(target, returnItem))
		found = true;
	return found;
}

// remove an item from the hash table
template<class ItemType>
bool HashTable<ItemType>::remove(const ItemType* target, ItemType* returnItem)
{
	bool removed = false;
	int index = dankHash(item->getModelNo()); // good hashing function
	if (data[index].deleteNode(target, returnItem))
		removed = true;
	count++;
	return removed;
}

// get the load factor of the hash table
template<class ItemType>
double HashTable<ItemType>::getLoadFactor() const
{
	double loaded = 0;
	for (int i = 0; i < size; i++)
	{
		if (!data[i].isEmpty())
			loaded++;
	}
	return loaded / size;
}

#endif
