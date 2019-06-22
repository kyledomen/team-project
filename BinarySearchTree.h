// Binary Search Tree ADT
// Created by A. Student
// Modified by: Maksym Sagadin

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include <iostream>
#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode, int compare(ItemType left, ItemType right));

    // internal remove node: locate and delete target node under nodePtr subtree
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success, int compare(ItemType left, ItemType right));

    // delete target node from tree, called by internal remove node
    BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

    // remove the leftmost node in the left subtree of nodePtr
    BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);

    // search for target node
    BinaryNode<ItemType>* findNode(const ItemType & target, int compare(ItemType left, ItemType right)) const;

public:
    // insert a node at the correct location
    bool insert( ItemType & newEntry, int compare(ItemType left, ItemType right));

    // remove a node if found
    bool remove(ItemType & anEntry, int compare(ItemType left, ItemType right));
    // find a target node
    bool getEntry(const ItemType & target, ItemType & returnedItem, int compare(ItemType left, ItemType right)) const;
    // find the smallest node
    bool getSmallest(ItemType & smallest) const;
    // find the largest node
    bool getLargest(ItemType & largest) const;

};


///////////////////////// public function definitions ///////////////////////////
//Inserting items within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::insert( ItemType & newEntry, int compare(ItemType left, ItemType right)) {
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    this->rootPtr = _insert(this->rootPtr, newNodePtr, compare);
    return true;
}
//Removing items within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::remove(ItemType & target, int compare(ItemType left, ItemType right)) {
    bool isSuccessful = false;
    this->rootPtr = _remove(this->rootPtr, target, isSuccessful, compare);
    return isSuccessful;
}
//Searches for an item within a tree by passed value and updates a passed value
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& target, ItemType & returnedItem, int compare(ItemType left, ItemType right)) const
{
    BinaryNode<ItemType> *nodePtr = NULL;

    nodePtr = findNode(target, compare);

    if (nodePtr == NULL)
        return false;
    else {
        returnedItem = nodePtr->getItem();
        return true;
    }
}

//Getting smallest node within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::getSmallest(ItemType & smallest) const
{
    BinaryNode<ItemType>* nodePtr = findSmallest(this->rootPtr);
    if (nodePtr == 0)
        return false;
    else
    {
        smallest = nodePtr->getItem();
        return true;
    }
}

//Getting largest node within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::getLargest(ItemType & largest) const
{
    BinaryNode<ItemType>* nodePtr = findLargest(this->rootPtr);
    if (nodePtr == 0)
        return false;
    else
    {
        largest = nodePtr->getItem();
        return true;
    }
}

//////////////////////////// private functions ////////////////////////////////////////////
//Implementation of the delete operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr, int compare(ItemType left, ItemType right))
{
    if (nodePtr == 0)
    {
        newNodePtr->setLeftPtr(NULL);
        newNodePtr->setRightPtr(NULL);
        return newNodePtr;
    }

    if (compare(newNodePtr->getItem(), nodePtr->getItem()) == -1)
        nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr, compare));
    else
        nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr, compare));

    return nodePtr;
}
//Implementation of the remove operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success, int compare(ItemType left, ItemType right)) {
    if (nodePtr == 0) {
        success = false;
        return 0;
    }

    if (compare(nodePtr->getItem(), target) == -1)
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success, compare));
    else if (compare(nodePtr->getItem(), target) == 1)
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success, compare));
    else {
        nodePtr = deleteNode(nodePtr);
        success = true;
    }

    return nodePtr;
}

//Implementation of the delete operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr->isLeaf())
    {
        delete nodePtr;
        nodePtr = 0;
        return nodePtr;
    }
    else if (nodePtr->getLeftPtr() == 0)
    {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else if (nodePtr->getRightPtr() == 0)
    {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else
    {
        ItemType newNodeValue;
        nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
        nodePtr->setItem(newNodeValue);
        return nodePtr;
    }
}
//Implementation to remove the left leaf
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
    if (nodePtr->getLeftPtr() == 0)
    {
        successor = nodePtr->getItem();
        return deleteNode(nodePtr);
    }
    else
    {
        nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
        return nodePtr;
    }
}

//Implementation of the search operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(const ItemType &target, int compare(ItemType left, ItemType right)) const
{
    BinaryNode<ItemType> *pCurr = this->rootPtr;
    while (pCurr != 0) {
        if (compare(pCurr->getItem(), target) == 0)
            return pCurr;

        if (compare(pCurr->getItem(), target) == 1)
            pCurr = pCurr->getLeftPtr();
        else
            pCurr = pCurr->getRightPtr();
    }
    return 0;
}

#endif
