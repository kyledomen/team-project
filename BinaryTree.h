// Binary tree abstract base class
// Created by A. Student
// Modified by: Maksym Sagadin

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
//#include "Queue.h"
using std::cout;
using std::ofstream;

template<class ItemType>
class BinaryTree
{
protected:
    BinaryNode<ItemType>* rootPtr;        // ptr to root node
    int count;                            // number of nodes in tree

public:
    // "admin" functions
    BinaryTree() {rootPtr = 0; count = 0;}
    virtual ~BinaryTree() { destroyTree(rootPtr); }

    // common functions for all binary trees
    bool isEmpty() const    {return count == 0;}
    int size() const        {return count;}
	BinaryNode<ItemType>* getRoot() const { return rootPtr;}
    void clear()            {destroyTree(rootPtr); rootPtr = 0; count = 0;}
    void preOrder(void visit(ItemType )) const {_preorder(visit, rootPtr);}
    void inOrder(void visit(ItemType )) const  {_inorder(visit, rootPtr);}

    // overloaded for write database function
    void inOrder(void visit(ItemType, ofstream &), ofstream &f) const  {_inorder(visit, rootPtr, f);}
    void postOrder(void visit(ItemType )) const{_postorder(visit, rootPtr);}
    void printOrder(void visit(ItemType )) const {_printorder(visit, rootPtr, 0);}

    // abstract functions to be implemented by derived class
    virtual bool insert(ItemType & newData, int compare(ItemType left, ItemType right)) = 0;
    virtual bool remove(ItemType & data, int compare(ItemType left, ItemType right)) = 0;
    virtual bool getEntry(const ItemType & anEntry, ItemType &returnedItem, int compare(ItemType left, ItemType right)) const = 0;

private:
    // delete all nodes from the tree
    void destroyTree(BinaryNode<ItemType>* nodePtr);

    // internal traverse
    void _preorder(void visit(ItemType ), BinaryNode<ItemType>* nodePtr) const;
    void _inorder(void visit(ItemType ), BinaryNode<ItemType>* nodePtr) const;
    // overloaded for write database function
    void _inorder(void visit(ItemType, ofstream &file), BinaryNode<ItemType>* nodePtr, ofstream &file) const;
    void _postorder(void visit(ItemType ), BinaryNode<ItemType>* nodePtr) const;
    void _printorder(void visit(ItemType ), BinaryNode<ItemType>* nodePtr, int level) const;

};

//Destroy the entire tree
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr == NULL)
        return;

    destroyTree(nodePtr->getLeftPtr());
    destroyTree(nodePtr->getRightPtr());

    delete nodePtr;
    count = 0;
}

// Preorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType ), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        ItemType item = nodePtr->getItem();
        visit(item);
        _preorder(visit, nodePtr->getLeftPtr());
        _preorder(visit, nodePtr->getRightPtr());
    }
}

// Inorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType ), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        ItemType item = nodePtr->getItem();
        _inorder(visit, nodePtr->getLeftPtr());
        visit(item);
        _inorder(visit, nodePtr->getRightPtr());
    }
}
// Inorder Traversal (overloaded for write database function)
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType, ofstream &), BinaryNode<ItemType>* nodePtr, ofstream &file) const
{
    if (nodePtr != 0)
    {
        ItemType item = nodePtr->getItem();
        _inorder(visit, nodePtr->getLeftPtr(), file);
        visit(item, file);
        _inorder(visit, nodePtr->getRightPtr(), file);
    }
}

// Postorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType ), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		visit(item);
	}
}

//Traversal to print the tree horizontally
template<class ItemType>
void BinaryTree<ItemType>::_printorder(void visit(ItemType ), BinaryNode<ItemType>* nodePtr, int level) const
{
    if (nodePtr != 0)
    {
        ItemType item = nodePtr->getItem();
        if (item != NULL)
        {
            _printorder(visit, nodePtr->getRightPtr(), level + 1);
            for (int i = 0; i < level; i++ )
                cout << "\t";
            cout << "Level " << level << " ";
            visit(item);

            _printorder(visit, nodePtr->getLeftPtr(), level + 1);
        }
    }
}

#endif
