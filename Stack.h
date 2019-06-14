/**~*~*
   Stack template
*~**/
#ifndef STACK_ADT_H
#define STACK_ADT_H
#include <iostream>
using namespace std;

template <class T>
class Stack
{
private:
   // Structure for the stack nodes
   struct StackNode
   {
      T value;          // Value in the node
      StackNode *next;  // Pointer to next node
   };

   StackNode *top;     // Pointer to the stack top
   int count;

public:
   //Constructor
   Stack(){top = NULL; count = 0;}

   // Destructor
   ~Stack();

   // Stack operations
   bool push(T);
   bool pop(T &);
   bool isEmpty();
   int getCount();
   bool getTop(T &);
};

/**~*~*
   Destructor
*~**/
template <class T>
Stack<T>::~Stack()
{
   StackNode *currNode, *nextNode;

   // Position nodePtr at the top of the stack.
   currNode = top;

   // Traverse the list deleting each node.
   while (currNode) //while (currNode != NULL)
   {
      nextNode = currNode->next;
      delete currNode;
      currNode = nextNode;
   }
}

/**~*~*
  Member function push pushes the argument onto
  the stack.
*~**/
template <class T>
bool Stack<T>::push(T item)
{
   StackNode *newNode; // Pointer to a new node

   // Allocate a new node and store num there.
   newNode = new StackNode;
   if (!newNode)
       return false;
   newNode->value = item;

   // Update links and counter
   newNode->next = top;
   top = newNode;
   count++;

   return true;
}

/**~*~*
  Member function pop pops the value at the top
  of the stack off, and copies it into the variable
  passed as an argument.
*~**/
template <class T>
bool Stack<T>::pop(T &item)
{
   StackNode *temp; // Temporary pointer

   // empty stack
   if (count == 0)
       return false;

   // pop value off top of stack
   item = top->value;
   temp = top->next;
   delete top;
   top = temp;
   count--;

   return true;
}

/**~*~*
  Member function getcount returns size of stack
*~**/
template <class T>
int Stack<T>::getCount() {
    return count;
}

/**~*~*
  Member function getTop retrieves the top of the stack
  and copies it into the variable passed as an argument
*~**/
template <class T>
bool Stack<T>::getTop(T &item) {
    if (count == 0)
        return false;

    item = top->value;

    return true;
}

/**~*~*
  Member function isEmpty returns true if the stack
  is empty, or false otherwise.
*~**/
template <class T>
bool Stack<T>::isEmpty()
{
   return count == 0;
}
#endif
