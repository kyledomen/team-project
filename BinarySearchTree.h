// Binary Search Tree ADT
// Created by A. Student
// Modified by: Maksym Sagadin

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode, char c);
    
    // internal remove node: locate and delete target node under nodePtr subtree
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr,  ItemType target, bool & success);
    
    // delete target node from tree, called by internal remove node
    BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
    
    // remove the leftmost node in the left subtree of nodePtr
    BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
    
    // search for target node
    BinaryNode<ItemType>* findNode(ItemType & target, char c) const;
    
    // find the smallest node
    BinaryNode<ItemType>* findSmallest(BinaryNode<ItemType>* nodePtr) const;
    
    // find the largest node
    BinaryNode<ItemType>* findLargest(BinaryNode<ItemType>* nodePtr) const;
    
public:
    // insert a node at the correct location
    bool insert( ItemType & newEntry, char c);
    // remove a node if found
    bool remove( ItemType & anEntry);
    // find a target node
    bool getEntry(ItemType & target, ItemType & returnedItem, char c) const;
    // find the smallest node
    bool getSmallest(ItemType & smallest) const;
    // find the largest node
    bool getLargest(ItemType & largest) const;
    
};


///////////////////////// public function definitions ///////////////////////////
//Inserting items within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::insert( ItemType & newEntry, char c)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    this->rootPtr = _insert(this->rootPtr, newNodePtr, c);
    return true;
}


//Removing items within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::remove( ItemType & target)
{
    bool isSuccessful = false;
    this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
    return isSuccessful;
}

//Finding entries within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(ItemType & target, ItemType & returnedItem, char c) const
{
    BinaryNode<ItemType>* nodePtr = findNode(target, c);
    if (nodePtr == 0)
        return false;
    else
    {
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

//Getting smallest node within a tree
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

//Implementation of the insert operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr, char c)
{
    if (nodePtr == 0)
    {
        newNodePtr->setLeftPtr(NULL);
        newNodePtr->setRightPtr(NULL);
        return newNodePtr;
    }
    if (c == 'p')
    {
        if ( *(newNodePtr->getItem()) < *(nodePtr->getItem()) )
            nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr, c));
        else
            nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr, c));
    }
    else if (c == 's')
    {
//        if (newNodePtr->getItem()->getModel() < nodePtr->getItem()->getModel())
        if ( *(nodePtr->getItem()) > *(newNodePtr->getItem()) )
            nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr, c));
        else
            nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr, c));
    }
    
    return nodePtr;
}

//Implementation of the remove operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target,
                                                          bool & success)

{
    if (nodePtr == 0)
    {
        success = false;
        return 0;
    }
    if (nodePtr->getItem() > target)
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
    else if (nodePtr->getItem() < target)
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
    else
    {
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

//Implementation for the search operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(ItemType & target, char c) const
{
    BinaryNode<ItemType> *pCurr = this->rootPtr;
    while (pCurr != 0)
    {
        if (*(pCurr->getItem()) == *target)
            return pCurr;
        if (c == 's')
        {
            if (*target < *(pCurr->getItem()))
            {
                pCurr = pCurr->getRightPtr();
            }
            else
            {
                pCurr = pCurr->getLeftPtr();
            }
        }
        else if (c == 'p')
        {
            if (*(pCurr->getItem()) < *target )
            {
                pCurr = pCurr->getRightPtr();
            }
            else
            {
                pCurr = pCurr->getLeftPtr();
            }
        }
    }
    return 0;
}

//Implementation for the find smallest node operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findSmallest(BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        if (nodePtr->getLeftPtr() == 0)
            return nodePtr;
        else
            return findSmallest(nodePtr->getLeftPtr());
    }
    return 0;
}

//Implementation for the find largest node operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findLargest(BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        if (nodePtr->getRightPtr() == 0)
            return nodePtr;
        else
            return findLargest(nodePtr->getRightPtr());
    }
    return 0;
}

#endif
