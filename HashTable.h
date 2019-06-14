// Node for a binary tree
// Created by A. Student
// Modified by: Maksym Sagadin
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
	int size;
	int count;


	int dankHash(string key) const; // good hash
	int oofHash(string key) const; // bad hash

public:
	// the main functions
	HashTable(int number) { allocateMemory(number); }
	void allocateMemory(int number);
	bool insert(const ItemType* item);
	bool search(const ItemType* item, ItemType* returnItem);



	// getters
	int getSize() const { return size; }
	int getCount() const { return count; }
	bool isFull() const { return count == size; }
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

	int index = dankHash(item->getData()); // the good hasing function;
	data[index].insertNode(item);
	return true;
}

// search for an item from the hash table
template<class ItemType>
bool search(const ItemType* item, ItemType* returnItem)
{
	bool found = false;
	
}



#endif
