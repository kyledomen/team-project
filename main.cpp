// main test driver for BST - Homework 4
// Created by A. Student
// Modified by: Tuan Truong

#include "BinarySearchTree.h"  // BST ADT 
#include "BinaryNode.h"		   // Binary Node
#include "Toy.h"			   // Toy class to store Toy items
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

void readFile(string fileName, BinarySearchTree<Toy>* tree);
void displayWelcome();
void displayFarewell();
void displayMenu();
void displayDeveloper();
void optionManager(BinarySearchTree<Toy>* tree);
void display(Toy& anItem);
void detailedDisplay(Toy& anItem);
void displayIndentedList(void visit(Toy&), const BinaryNode<Toy>* tree, int level);
void displayIndentedList_breathFirst(void visit(Toy&), const BinarySearchTree<Toy>* tree); // accidentally created this function, read the homework wrong
void deleteLeaves(BinarySearchTree<Toy>* tree);


int main()
{
	BinarySearchTree<Toy>* tree = new BinarySearchTree<Toy>;
	displayWelcome();
	readFile("toys.txt", tree);
	displayMenu();
	optionManager(tree);
	delete tree;
	displayFarewell();
	displayDeveloper();
	return 0;
}

// welcome message
void displayWelcome()
{
	cout << "\t\t*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n"
		<< "\t\tWELCOME TO THE BINARY SEARCH TREE PROGRAM !\n"
		<< "\t\t*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n";
}

// farewell message
void displayFarewell()
{
	cout << "\t\t*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n"
		<< "\t\tTHANK YOU FOR USING THE BINARY SEARCH TREE PROGRAM!\n"
		<< "\t\t*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n";
}

//read file function to read the file and input it into the BST
void readFile(string fileName, BinarySearchTree<Toy>* tree)
{
	ifstream inFile;
	int ID;
	string name;
	int age;
	double price;

	inFile.open("toys.txt"); // did not use fileName because it doesn't work on my computer for some reason
	if (!inFile)
	{
		cout << "There is a problem opening the input file!" << endl;
		exit(EXIT_FAILURE);
	}
	else
		cout << "Reading inputs from \"" << fileName << "\" ... " << endl;
	while (inFile >> ID)
	{
		Toy item;
		inFile.ignore();
		getline(inFile, name, ';');
		inFile >> age >> price;

		item.setID(ID);
		item.setName(name);
		item.setAge(age);
		item.setPrice(price);

		bool inserted = tree->insert(item);
	}
	inFile.close();
}

//display the menu
void displayMenu()
{
	cout << "D - Tree Depth - First Traversals \n"
		<< "B - Tree Breadth - First Traversals \n"
		<< "S - Search by the primary key \n"
		<< "M - Find the smallest \n"
		<< "X - Find the largest \n"
		<< "T - Print the BST as an indented list \n"
		<< "L - Print the leaves in BST\n"
		<< "I - Print the node with one child in BST\n"
		<< "O - Delete the leaves in BST\n"
		<< "C - Count all the nodes in a given range\n"
		<< "H - Help \n"
		<< "E - Exit. \n";
}

//display the developer
void displayDeveloper()
{
	cout << endl << "\t\t*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n"
		<< "\t\tProgram developed by TUAN TRUONG \n"
		<< "\t\t*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n";
}

//menu manager to ask user for input and perform actions
void optionManager(BinarySearchTree<Toy>* tree)
{
	char input = '\0';

	while (input != 'E')
	{
		cout << "Enter an option(H - for help): ";
		cin >> input;
		if (input == 'D')
		{
			cout << "Enter your choice of traversal (1 - inorder, 2 - preorder, 3 - postorder): ";
			cin >> input;
			switch (input)
			{
			case '1':
				tree->inOrder(display);
				break;
			case '2':
				tree->preOrder(display);
				break;
			case'3':
				tree->postOrder(display);
				break;
			}
		}
		else if (input == 'B')
		{
			tree->breathFirst(display);
		}
		else if (input == 'S')
		{
			int ID;
			cout << "Enter the primary key (ID): ";
			cin >> ID;

			Toy target, returnedItem;
			target.setID(ID);
			bool searched = tree->getEntry(target, returnedItem);
			if (!searched)
				cout << "Item not found!\n";
			else
				detailedDisplay(returnedItem);
		}
		else if (input == 'M')
		{
			Toy smallestItem;
			bool smallest = tree->getSmallest(smallestItem);
			if (!smallest)
				cout << "Item not found!\n";
			else
				display(smallestItem);
		}
		else if (input == 'X')
		{
			Toy largestItem;
			bool largest = tree->getLargest(largestItem);
			if (!largest)
				cout << "Item not found!\n";
			else
				display(largestItem);
		}
		else if (input == 'H')
		{
			displayMenu();
		}
		else if (input == 'T')
		{
			displayIndentedList(display, tree->getRoot(), 1);
		}
		else if (input == 'L')
		{
			tree->printNodeWith(display, 0);
		}
		else if (input == 'I')
		{
			tree->printNodeWith(display, 1);
		}
		else if (input == 'O')
		{
			deleteLeaves(tree);
		}
		else if (input == 'C')
		{
			int depth;
			cout << "Please enter maximum depth: ";
			cin >> depth;
			int numberOfNodes = tree->numberOfNodes(depth);
			cout << "There are " << numberOfNodes << " nodes.\n";
		}
		else if (input == 'A')
		{
			displayDeveloper();
		}
		else if (input != 'E')
		{
			cout << "Wrong input! ";
		}
		cout << endl;
	}
	return;
}

// display function to pass to BST traverse functions
void display(Toy& anItem)
{
	cout << "Displaying item - " << left << setw(6) << anItem.getID()
		<< setw(30) << anItem.getName() << endl;
}

// display function with more details
void detailedDisplay(Toy& anItem)
{
	cout << "Displaying item - " << left << setw(6) << anItem.getID()
		<< setw(30) << anItem.getName()
		<< "Age: " << left << setw(10) << anItem.getAge()
		<< setprecision(5) << "$" << anItem.getPrice() << endl;
}

// print the intented lisat of the binary tree
void displayIndentedList(void visit(Toy&), const BinaryNode<Toy>* tree, int level)
{
	if (tree != 0)
	{
		Toy item = tree->getItem();
		for (int i = level; i > 1; i--)
			cout << "\t";
		cout << "Level " << level << ": ";
		visit(item);
		displayIndentedList(visit, tree->getRightPtr(), level + 1);
		displayIndentedList(visit, tree->getLeftPtr(), level + 1);
	}
}

// print the indented list of the binary tree breath-first 
void displayIndentedList_breathFirst(void visit(Toy&), const BinarySearchTree<Toy>* tree)
{
	BinaryNode<Toy>* nodePtr = tree->getRoot();
	BinaryNode<Toy>* curr = nodePtr;
	Toy item;
	Queue<BinaryNode<Toy>*>* q = new Queue<BinaryNode<Toy>*>;
	Queue<int>* treeLevel = new Queue<int>;
	if (nodePtr == 0)
		return;
	int level = 0;
	q->enqueue(nodePtr);
	treeLevel->enqueue(level);
	while (!q->isEmpty())
	{
		q->dequeue(curr);
		treeLevel->dequeue(level);
		item = curr->getItem();

		for (int i = level; i > 0; i--)
			cout << "\t";
		cout << "Level " << level + 1 << ": ";
		visit(item);

		if (curr->getLeftPtr() != 0)
		{
			q->enqueue(curr->getLeftPtr());
			treeLevel->enqueue(level + 1);
		}
		if (curr->getRightPtr() != 0)
		{
			q->enqueue(curr->getRightPtr());
			treeLevel->enqueue(level + 1);
		}
	}
}

void deleteLeaves(BinarySearchTree<Toy>* tree)
{
	Queue<BinaryNode<Toy>*>* queue = new Queue<BinaryNode<Toy>*>;

	queue = tree->gatherLeaves();
	while (!queue->isEmpty())
	{
		BinaryNode<Toy>* nodePtr;
		queue->dequeue(nodePtr);
		cout << "DELETING: ";
		Toy item = nodePtr->getItem();
		display(item);
		tree->remove(item);
	}
}
