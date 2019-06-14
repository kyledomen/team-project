// Specification file for the CollegeList class
// Written By: Casey Nguyen
// IDE: Visual Studios

#ifndef S_LIST_H
#define S_LIST_H
#include "Phone.h"
#include <iostream>

using std::string;
using std::cout;
using std::endl;

template <class T>

class SList
{
private:
	struct ListNode {
		T data;
		ListNode* forw;
		//ListNode* prev;
	};
	ListNode* head;
	int count;

public:
	//Constructor
	SList()
	{
		head = new ListNode; // head points to the sentinel node
		head->forw = NULL;
		//head->prev = head;

		count = 0;
	}

	//**************************************************
	// The insertNode function inserts a node with
	// stu copied to its value member.
	// Linked list operations
	//**************************************************
	void insertNode(T dataIn)
	{
		ListNode* pNew;  // A new node
		ListNode* pCur;     // To traverse the list
		ListNode* pPre;     // The previous node

		// Allocate a new node and store num there.
		pNew = new ListNode;
		pNew -> data = dataIn;
		// Initialize pointer
		pPre = head;
		pCur = head->forw;
		//pPre = head->prev;
		// Find location: skip all nodes whose name is less than dataIn's name.
		while (pCur != NULL && pCur->data < dataIn)
		{
			pPre = pCur;
			pCur = pCur->forw;
		}

		// Insert the new node between pPre and pCur
		pPre->forw = pNew;
		pNew->forw = pCur;
		//pNew->prev = pPre;
		//pCur->prev = pNew;

		//Update the counter
		count++;
	}

	//**************************************************
	// The deleteNode function searches for a node
	// with num as its value. The node, if found, is
	// deleted from the list and from memory.
	//**************************************************
	bool deleteNode(T target)
	{
		ListNode* pCur;       // To traverse the list
		ListNode* pPre;        // To point to the previous node
		bool deleted = false;

		// Initialize pointers
		pPre = head;
		pCur = head->forw;

		// Find node containing the target: Skip all nodes whose name is less than the target
		while (pCur != NULL && pCur->data < target)
		{
			pPre = pCur;
			pCur = pCur->forw;
		}

		// If found, delete the node
		if (pCur != NULL && pCur->data == target)
		{
			pPre->forw = pCur->forw;
			//pCur->forw->prev = pPre;
			delete pCur;
			deleted = true;
			//Update counter
			count--;
		}
		return deleted;

	}

	//**************************************************
	// Search function shows if the college name is match with what the user enters
	//**************************************************
	bool searchList(T target, T& dataOut)
	{
		ListNode* pCur;
		pCur = head->forw;
		bool found = false;

		while (pCur != NULL && pCur->data < target)
			pCur = pCur->forw;

		if (pCur != NULL && pCur->data == target) {
			found = true;
			dataOut = pCur->data;
		}
		return found;
	}

	//**************************************************
	// Display function shows every college name with their rank and cost. going forward
	//**************************************************
	void traverseForward(void (*p)()) const
	{
		ListNode* pCur;  // To move through the list

		p();

		pCur = head->forw;          // Position pCur: skip the head of the list.
		while (pCur != NULL)
		{
			pCur->data.display();  //Display the value in the node.
			pCur = pCur->forw;    //Move to the next node.

		}

		cout << "==== ============================= ========= ==========" << endl;


	}

	/*
	//**************************************************
	// Display function shows every college name with their rank and cost. goign backward
	//**************************************************
	void traverseBackward(void (*p)()) const
	{
		ListNode* pCur;  // To move through the list

		p();

		pCur = head->prev;          // Position pCur: skip the head of the list.
		while (pCur != head)
		{
			pCur->data.display();  //Display the value in the node.
			pCur = pCur->prev;    //Move to the next node.

		}

		cout << "==== ============================= ========= ==========" << endl;


	};
	*/

	//Returns how many nodes there are
	int getCount() const { return count; }

	/**************************************************************************
	This function checks to see if the node is empty bys checking the count
	******************************************************************/
	bool isEmpty() const
	{
		if (getCount() == 0)
		{
			cout << "Empty list" << endl;
			return true;
		}
		else
			return false;
	}


	//Destructor
	~SList()
	{
		ListNode* pCur;   // To traverse the list
		ListNode* pNext;  // To point to the next node

		// Position nodePtr at the head of the list.
		pCur = head->forw;

		// While pCur is not at the end of the list...
		while (pCur != NULL)
		{
			// Save a pointer to the next node.
			pNext = pCur->forw;

			// Delete the current node.
			cout << "DEBUG - Destructor: Now deleting " << pCur->data.getName() << endl;
			delete pCur;

			// Position pCur at the next node.
			pCur = pNext;
		}
		cout << "DEBUG - Destructor: Now deleting the sentinel node rank " << head->data.getRank() << endl;
		delete head; // delete the sentinel node
	}

};
#endif