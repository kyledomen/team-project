#include <iostream>
#include <string>
//#include <cctype> //for toupper
#include <algorithm>
#include <locale>
#include <fstream>
#include "BinarySearchTree.h"
#include "Stack.h"
#include "Phone.h"
#include "HashTable.h"

using namespace std;

void buildTree(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond, HashTable<Phone*>* oghash);
void deletePhone(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond, HashTable<Phone*>* oghash, Stack<Phone*>* stack);
void print_menu();
void writeOut(Phone* anItem, ofstream& f);
void writeFile(BinarySearchTree<Phone*>* treePrime);
void undo_delete(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond, HashTable<Phone*>* oghash, Stack<Phone*>* stack);
void menu_choice(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond, HashTable<Phone*>* oghash, Stack<Phone*>* stack);
void insertPhone(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond, HashTable<Phone*>* oghash);
void print_menu_search();
void searchChoice(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond);
void searchNumber(const BinarySearchTree<Phone*>* treePrime);
void searchName(const BinarySearchTree<Phone*>* treeSecond);
void print_menu_list();
void printChoice(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond);
void displayP(Phone* anItem);
void displayS(Phone* anItem);
void displayTEST(Phone* anItem); // TESTING DISPLAY FUNCTION FOR HASHTABLE ONLY
void rehash(HashTable<Phone*>* newhash, BinarySearchTree<Phone*>* treePrime);
void insertfromBinary(HashTable<Phone*>* hash, BinaryNode<Phone*>* root);
void searchHash(HashTable<Phone*>* hash);
void showStatistic(HashTable<Phone*>* hash);
int compareModelNo(Phone* left, Phone* right);
int compareModel(Phone* left, Phone* right);

int main() {
	BinarySearchTree<Phone*>* treePrime = new BinarySearchTree<Phone*>;
	BinarySearchTree<Phone*>* treeSecond = new BinarySearchTree<Phone*>;
	Stack<Phone*>* stack = new Stack<Phone*>;
	HashTable<Phone*>* oghash = new HashTable<Phone*>(7);
	buildTree(treePrime, treeSecond, oghash);

	print_menu();
	menu_choice(treePrime, treeSecond, oghash, stack);
	return 0;
}

/*****************************************************************************
 This function reads data about //toys from a given file and inserts them
 into a sorted Binary Search Tree.
 *****************************************************************************/
void buildTree(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond, HashTable<Phone*>* oghash)
{
	ifstream infile;
	string filename = "phonedatabase.txt";
	string modelNo;
	string model;
	string brand;
	int storage;
	double price;

	infile.open(filename);
	if (!infile) {
		cout << "Error!" << endl;
		exit(EXIT_FAILURE);
	}
	while (infile >> modelNo) {
		infile.ignore();
		getline(infile, model, ';');
		infile.ignore();
		getline(infile, brand, ';');
		infile >> storage >> price;

		//Use constructor to pass the values to the college object.
		Phone temp(modelNo, model, brand, storage, price);
		//        Phone *ptr = new Phone();
		//        *ptr = temp;
		Phone* ptr = new Phone(temp);

		treePrime->insert(ptr, 'p'); //BST based on primary key
		treeSecond->insert(ptr, 's'); //BST based on secondary key
		oghash->insert(ptr);


	}
	infile.close();
}

void deletePhone(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond, HashTable<Phone*>* oghash, Stack<Phone*>* stack) {
	string input = "";
	cout << "\n Delete\n";
	cout << "=======\n";

	Phone t;
	Phone r;

	while (input != "Q") {
		cout << "Enter the phone's model number to be deleted (or Q to stop deleting): \n";
		getline(cin, input);
		transform(input.begin(), input.end(), input.begin(), ::toupper);
		t.setModelNo(input);

		Phone* target = new Phone(t);
		Phone* returned = new Phone(r);

		treePrime->getEntry(target, returned, 'p');

		if (input != "Q") {
			stack->push(returned);   // push the returned phone pointer in case delete is successful
			if (treePrime->remove(returned, 'p') && treeSecond->remove(returned, 's')) {
				Phone* a = new Phone;
				oghash->remove(target, a, compareModelNo);
				cout << "\nDelete successful! Phone that was deleted:" << endl;
				stack->getTop(returned);
				cout << *returned << "\n";
			}
			else {
				stack->pop(returned);    // if delete wasn't successful, then clean the top of the stack
				cout << "[ERROR]: Phone model number " << input << " was not found in the database." << endl;
			}
		}
	}

	cout << endl;
}


void print_menu() {
	cout << "========="
		<< "\n  MENU\n"
		<< "=========\n"
		<< "A - Insert a new phone\n"
		<< "D - Delete a phone\n"
		<< "S - Search by model number or name of the phone\n"
		<< "F - Search by model number using hash\n"
		<< "L - Print out phone database\n"
		<< "M - Print out the hash table\n"
		<< "W - Write phone database to file\n"
		<< "T - Show statistics\n"
		<< "U - Undo delete\n"
		<< "Q - Quit\n"
		<< "*****\n";
}
/******************************************************
 This function chooses the menu options from the user.
 */

void menu_choice(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond, HashTable<Phone*>* oghash, Stack<Phone*>* stack) {
	char choice = ' ';

	while (choice != 'Q')
	{
		cout << "Choose a menu option (H for help | Q to exit program): ";
		cin >> choice;
		choice = toupper(choice);
		cin.ignore(5, '\n');
		while (oghash->getLoadFactor() > 0.75)
		{
			HashTable<Phone*>* newhash = new HashTable<Phone*>(oghash->getSize());
			rehash(newhash, treePrime);
			oghash = newhash;
		}
		switch (choice)
		{
		case 'A':
			insertPhone(treePrime, treeSecond, oghash);
			break;

		case 'D':
			deletePhone(treePrime, treeSecond, oghash, stack);
			break;

		case 'S':
			print_menu_search();
			searchChoice(treePrime, treeSecond);
			break;

		case 'F' :
			searchHash(oghash);
			break;

		case 'L':
			print_menu_list();
			printChoice(treePrime, treeSecond);
			break;

		case 'W':
			writeFile(treePrime);
			break;

		case 'T':
			showStatistic(oghash);
			break;

		case 'M':
			oghash->printHashTable(displayTEST);
			break;

		case 'U':
			undo_delete(treePrime, treeSecond, oghash, stack);
			break;

		case 'H':
			print_menu();
			break;

		case 'Q':
			writeFile(treePrime);
			cout << "\n\n\t\t *~~*~~* Good Bye *~~*~~*\n\n\n";
			break;

		default:
			cout << "You did not enter a valid choice" << endl;

		}
	}
}


/******************************************************
 This function inserts a new phone in the BST's
 */
void insertPhone(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond, HashTable<Phone*>* oghash)
{
	string answer = "";
	while (answer != "NO")
	{
		string modelNo;
		string model;
		string brand;
		int storage;
		double price;

		cout << "Please enter the model number:" << endl;
		cin >> modelNo;
		transform(modelNo.begin(), modelNo.end(), modelNo.begin(), ::toupper);

		cin.ignore();
		cout << "Please enter the model name:" << endl;
		getline(cin, model, '\n');

		cin.clear();
		cout << "Please enter the brand name:" << endl;
		getline(cin, brand, '\n');

		cout << "Please enter the storage amount:" << endl;
		cin >> storage;
		cin.ignore(1000, '\n');
		while (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Error! Enter storage amount: ";
			cin >> storage;
		}

		cout << "Please enter the price amount:" << endl;
		cin >> price;
		cin.ignore(1000, '\n');
		while (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Error! Enter price: ";
			cin >> price;
		}

		Phone temp(modelNo, model, brand, storage, price); //Phone object created
		Phone* ptr = new Phone(temp);

		cout << "\nYou have enter this phone: \n" << temp << endl
			<< "Is this correct? (Type No or anything else)." << endl; //Should be reworded
		cin >> answer;
		transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
		if (answer != "NO")
		{
			treePrime->insert(ptr, 'p'); //BST based on primary key
			treeSecond->insert(ptr, 's'); //BST based on secondary key
			oghash->insert(ptr);

			cout << "Exiting insert function." << endl;
			return;
		}
	}
	cout << "\nExiting insert function." << endl;

}

void print_menu_search() {
	cout << "    ==================="
		<< "\n      SEARCH SUBMENU\n"
		<< "    ===================\n"
		<< "    M - Search by model number\n"
		<< "    N - Search by name\n";
}

void searchChoice(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond)
{
	char choice = ' ';
	cout << "Choose a menu option: ";

	while (choice != 'Q')
	{
		cin >> choice;
		choice = toupper(choice);
		cin.ignore(5, '\n');

		switch (choice)
		{
		case 'M':
			searchNumber(treePrime);
			break;

		case 'N':
			searchName(treeSecond);
			break;

		case 'Q':
			cout << "\n\n\t\t *~~*~~* Good Bye *~~*~~*\n\n\n";
			return;

		default:
			cout << "You did not enter a valid choice" << endl;
		}
		print_menu_search();
		cout << "Choose a menu option or Q to exit: " << endl;
	}
}

/******************************************************
 This function searches the tree nodes to find the node
 in the tree by model number and returns it.
 */
void searchNumber(const BinarySearchTree<Phone*>* treePrime) {
	string input;
	Phone temp, found;

	cout << "Enter a model number: " << endl;
	cin >> input;
	cin.ignore(100, '\n');

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(15, '\n');
		cout << "Input Error: Enter a model number: " << endl;
		cin >> input;
	}

	transform(input.begin(), input.end(), input.begin(), ::toupper);
	temp.setModelNo(input);
	Phone* ptr = new Phone;
	ptr = &temp;
	Phone* ptrf = new Phone;
	ptrf = &found;

	if (treePrime->getEntry(ptr, ptrf, 'p'))
		cout << "\nFound Model!\n" << *ptrf << endl;
	else
		cout << "\nModel not found!\n" << endl;
}

/******************************************************
 This function searches the tree nodes to find the node
 in the tree by model name and returns it.
 */
void searchName(const BinarySearchTree<Phone*>* treeSecond) {
	string input;
	Phone temp, found;

	cout << "Enter a model name" << endl;
	getline(cin, input);

	//cout << input << endl;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(10, '\n');
		cout << "Input Error: Enter a model name" << endl;
		getline(cin, input, '\n');
	}

	temp.setModel(input);
	Phone* ptr = new Phone;
	Phone* ptrf = new Phone;
	ptr = &temp;
	ptrf = &found;

	if (treeSecond->getEntry(ptr, ptrf, 's'))
		cout << "\nFound Model!\n============\n" << *ptrf << endl;
	else
		cout << "Model not found!\n" << endl;
}


void print_menu_list() {
	cout << "    ==================="
		<< "\n       LIST SUBMENU\n"
		<< "    U - List the unsorted phones\n" //hash sequence
		<< "    M - List the phones by model number\n"
		<< "    N - List the phones by name\n"
		<< "    I - Print as indented list\n"; // by primary key
}

void printChoice(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond)
{
	char choice = ' ';
	cout << "Choose a menu option: ";

	while (choice != 'Q')
	{
		cin >> choice;
		choice = toupper(choice);
		cin.ignore(5, '\n');

		switch (choice)
		{
		case 'U':
			treePrime->postOrder(displayP);
			break;

		case 'M':
			treePrime->inOrder(displayP);
			break;

		case 'N':
			treeSecond->inOrder(displayS);
			break;

		case 'I':
			treePrime->printOrder(displayP);
			break;

		case 'Q':
			cout << "\n\n\t\t *~~*~~* Good Bye *~~*~~*\n\n\n";
			return;

		default:
			cout << "You did not enter a valid choice" << endl;
		}
		print_menu_list();
		cout << "Choose a menu option or Q to exit: " << endl;
	}
}

void writeOut(Phone* anItem, ofstream& f) {
	f << anItem->getModelNo() << " " << anItem->getModel() << "; " << anItem->getBrand()
		<< "; " << anItem->getStorage() << " " << anItem->getPrice() << endl;
}

void writeFile(BinarySearchTree<Phone*>* treePrime) {
	ofstream file("PrimeDatabase.txt");
	treePrime->inOrder(writeOut, file);
	file.close();
}

void undo_delete(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond, HashTable<Phone*>* oghash, Stack<Phone*>* stack) {
	if (stack->isEmpty()) {
		cout << "\n[ERROR]: There's nothing to undo!\n\n";
		return;
	}

	Phone r;
	Phone* returned = new Phone(r);
	stack->pop(returned);
	treePrime->insert(returned, 'p');
	treeSecond->insert(returned, 's');
	oghash->insert(returned);

	cout << "\nDelete has been reverted! Phone added back:\n" << *returned;
}

// displays Model Number
void displayP(Phone* anItem) {
	cout << anItem->getModelNo() << endl;
	//    << anItem->getModel() << endl;

}

// displays Model Name
void displayS(Phone* anItem) {
	cout << anItem->getModel() << endl;
}


void rehash(HashTable<Phone*>* newhash, BinarySearchTree<Phone*>* treePrime)
{
	insertfromBinary(newhash, treePrime->getRoot());
}

void insertfromBinary(HashTable<Phone*>* hash, BinaryNode<Phone*>* root)
{
	if (root != NULL)
	{
		Phone* phone = root->getItem();
		hash->insert(phone);
		insertfromBinary(hash, root->getLeftPtr());
		insertfromBinary(hash, root->getRightPtr());
	}
}


// TESTING DISPLAY FUNCTION FOR THE HASHING TABLE
void displayTEST(Phone* anItem) {
	cout << anItem->getModelNo();
}

/***********************************************
this function allows you to search by model name
************************************************/
void searchHash(HashTable<Phone*>* hash) {
	string input;
	Phone temp, found;
	cout << "Enter model number: " << endl;
	cin >> input;
	cin.ignore(100, '\n');
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(15, '\n');
		cout << "Input Error: Enter a model number" << endl;
		cin >> input;
	}

	transform(input.begin(), input.end(), input.begin(), ::toupper);
	temp.setModelNo(input);
	Phone* ptr = new Phone(temp);
	Phone* ptrf = new Phone(found);


	if (hash->search(ptr, ptrf, compareModelNo))
		cout << "Found Model!\n" << *ptrf << endl;
	else
		cout << "Model not found!\n" << endl;

}

/***********************************************
this function prints out statistics
************************************************/
void showStatistic(HashTable<Phone*>* hash)
{
	cout << "Statistic of hash table\n"
		<< "Load factor: " << hash->getLoadFactor() << endl
		<< "Number of collisions: " << hash->getCollisions() << endl
		<< "Array size: " << hash->getSize() << endl;

}


int compareModelNo(Phone* left, Phone* right)
{
	if (left->getModelNo() > right->getModelNo())
		return 1;
	else if (left->getModelNo() == right->getModelNo())
		return 0;
	else
        return -1;
}
int compareModel(Phone* left, Phone* right)
{
	if (left->getModel() > right->getModel())
		return 1;
	else if (left->getModel() == right->getModel())
		return 0;
	else
		return -1;
}
