// Binary tree abstract base class
// Created by A. Student
// Modified by: Maksym Sagadin

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
//#include "Queue.h"
using std::cout;

template<class ItemType>
class BinaryTree
{
protected:
    BinaryNode<ItemType>* rootPtr;        // ptr to root node
    int count;                            // number of nodes in tree
    
public:
    // "admin" functions
    BinaryTree() {rootPtr = 0; count = 0;}
    //    BinaryTree(const BinaryTree<ItemType> & tree){ }
    virtual ~BinaryTree() { destroyTree(rootPtr); }
    //    BinaryTree & operator = (const BinaryTree & sourceTree);
    
    // common functions for all binary trees
    bool isEmpty() const    {return count == 0;}
    int size() const        {return count;}
    void clear()            {destroyTree(rootPtr); rootPtr = 0; count = 0;}
    void preOrder(void visit(ItemType &)) const {_preorder(visit, rootPtr);}
    void inOrder(void visit(ItemType )) const  {_inorder(visit, rootPtr);}
    void postOrder(void visit(ItemType &)) const{_postorder(visit, rootPtr);}
//    void breadth(void visit(ItemType &)) const{_breadth(visit);}
    void printOrder(void visit(ItemType &)) const {_printorder(visit, rootPtr, 0);}
    
    // abstract functions to be implemented by derived class
    virtual bool insert(ItemType & newData, char c) = 0;
    virtual bool remove(const ItemType & data) = 0;
    virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;
    
private:
    // delete all nodes from the tree
    void destroyTree(BinaryNode<ItemType>* nodePtr);
    
    // internal traverse
    void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _inorder(void visit(ItemType ), BinaryNode<ItemType>* nodePtr) const;
    void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    //void _breadth(void visit(ItemType &)) const;
    void _printorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, int level) const;
    
};

//Destroy the entire tree
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr == NULL)
        return;
    destroyTree(nodePtr->getLeftPtr());
    destroyTree(nodePtr->getRightPtr());
    
    //    cout << "Deleting : " << nodePtr->getItem() << endl;
    delete nodePtr;
    count = 0;
}

//Preorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        ItemType item = nodePtr->getItem();
        visit(item);
        _preorder(visit, nodePtr->getLeftPtr());
        _preorder(visit, nodePtr->getRightPtr());
    }
}

//Inorder Traversal
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

//Postorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    ItemType item = nodePtr->getItem();
    _preorder(visit, nodePtr->getLeftPtr());
    _preorder(visit, nodePtr->getRightPtr());
    visit(item);
}

////Breadth Traversal
//template<class ItemType>
//void BinaryTree<ItemType>::_breadth(void visit(ItemType &)) const
//{
//    Queue<BinaryNode<ItemType>*> queue;
//    ItemType item;
//    BinaryNode<ItemType> *currNode = this->rootPtr;
//    if (currNode != 0)
//    {
//        queue.enqueue(currNode);
//
//        while (!queue.isEmpty())
//        {
//            queue.dequeue(currNode); //pop node from queue
//            item = currNode->getItem();
//            visit (item); //to use with a display function parameter to print in main
//
//            if (currNode->getLeftPtr() != 0)
//                queue.enqueue(currNode->getLeftPtr()); //puts left node in queue
//            if (currNode->getRightPtr() != 0)
//                queue.enqueue(currNode->getRightPtr()); //puts right node in queue
//        }
//    }
//    return;
//}

//Traversal to print the tree horizontally
template<class ItemType>
void BinaryTree<ItemType>::_printorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, int level) const
{
    if (nodePtr != 0)
    {
        ItemType item = nodePtr->getItem();
        for (int i = 1; i < level; i++ )
            cout << "\t";
        cout << "Level " << level << " ";
        visit(item);
        
        _printorder(visit, nodePtr->getRightPtr(), level + 1);
        _printorder(visit, nodePtr->getLeftPtr(), level + 1);
    }
}

#endif

