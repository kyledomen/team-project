#include <iostream>
#include <string>
#include <algorithm>
#include <locale>
#include <fstream>
#include "BinarySearchTree.h"
#include "Stack.h"
#include "Phone.h"
#include "HashTable.h"

using namespace std;

void buildStructure(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond, HashTable<Phone*>* oghash);
void deletePhone(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond, HashTable<Phone*>* oghash, Stack<Phone*>* stack);
void print_menu();
void writeOut(Phone* anItem, ofstream& f);
void writeFile(BinarySearchTree<Phone*>* treePrime);
void undo_delete(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond, HashTable<Phone*>* oghash, Stack<Phone*>* stack);
void menu_choice(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond, HashTable<Phone*>* oghash, Stack<Phone*>* stack);
void insertPhone(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond, HashTable<Phone*>* oghash);
bool dupCheck(BinarySearchTree<Phone*>* treePrime, string &input);
void print_menu_search();
void searchChoice(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond, HashTable<Phone*>* oghash);
void searchNumber(const BinarySearchTree<Phone*>* treePrime);
void searchName(const BinarySearchTree<Phone*>* treeSecond);
void print_menu_list();
void printChoice(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond, HashTable<Phone*>* oghash);
void displayIndent(Phone* anItem);
void displayP(Phone* anItem);
void displayS(Phone* anItem);
void print_model_header();
void print_name_header();
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
	buildStructure(treePrime, treeSecond, oghash);

	print_menu();
	menu_choice(treePrime, treeSecond, oghash, stack);
	return 0;
}

/*****************************************************************************
 This function reads data about //toys from a given file and inserts them
 into a sorted Binary Search Tree.
 *****************************************************************************/
void buildStructure(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond, HashTable<Phone*>* oghash)
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
		Phone* ptr = new Phone(temp);

		treePrime->insert(ptr, compareModelNo);
		treeSecond->insert(ptr, compareModel);
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

		treePrime->getEntry(target, returned, compareModelNo);

		if (input != "Q") {
			stack->push(returned);   // push the returned phone pointer in case delete is successful

			if (treePrime->remove(returned, compareModelNo) && treeSecond->remove(returned, compareModel)) {
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
		<< "L - Print out phone database\n"
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
			searchChoice(treePrime, treeSecond, oghash);
			break;

		case 'L':
			print_menu_list();
			printChoice(treePrime, treeSecond, oghash);
			break;

		case 'W':
			writeFile(treePrime);
			break;

		case 'T':
			showStatistic(oghash);
			break;

		case 'U':
			undo_delete(treePrime, treeSecond, oghash, stack); // need to clean the stack
			break;

		case 'H':
			print_menu();
			break;

		case 'Q':
			writeFile(treePrime); // need to clean the stack
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
        while (dupCheck(treePrime, modelNo) == true)
        {
            cout << "That model number already exists, please enter another...\n";
            cin >> modelNo;
        }

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
			<< "Is this correct?" << endl; //Should be reworded
		cin >> answer;
		transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
		if (answer != "NO")
		{
			treePrime->insert(ptr, compareModelNo); //BST based on primary key
			treeSecond->insert(ptr, compareModel); //BST based on secondary key
			oghash->insert(ptr);

			cout << "New Phone has been inserted." << endl;

		}

        cout << "\nWould you like to enter a new phone?:" << endl;
        cin >> answer;
        transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
	}
	cout << "\nExiting insert function.\n" << endl;

}


bool dupCheck(BinarySearchTree<Phone*>* treePrime, string &input)
{
    Phone temp, found;

    transform(input.begin(), input.end(), input.begin(), ::toupper);
    temp.setModelNo(input);
    Phone* ptr = new Phone(temp);
    Phone* ptrf = new Phone(found);

	if (treePrime->getEntry(ptr, ptrf, compareModelNo))
        return true;
    else
        return false;
}


void print_menu_search() {
	cout << "    ==================="
		<< "\n      SEARCH SUBMENU\n"
		<< "    ===================\n"
		<< "    M - Search by model number\n"
		<< "    N - Search by name\n"
        << "    F - Search by model number using hash\n";
}

void searchChoice(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond, HashTable<Phone*>* oghash)
{
	char choice = ' ';

	while (choice != 'Q')
	{
        cout << "Choose a menu option (H for help | Q to exit sub menu): ";
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

        case 'F' :
            searchHash(oghash);
            break;

        case 'H':
            print_menu_search();
            break;

		case 'Q':
			cout << "\n\n\t\t Exiting Search Sub Menu\n\n\n";
			return;

		default:
			cout << "You did not enter a valid choice" << endl;
		}
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

	if (treePrime->getEntry(ptr, ptrf, compareModelNo))
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

	if (treeSecond->getEntry(ptr, ptrf, compareModel))
		cout << "\nFound Model!\n============\n" << *ptrf << endl;
	else
		cout << "Model not found!\n" << endl;
}

/******************************************************
 Prints out submenu for printing the phone database
 */
void print_menu_list() {
	cout << "    ==================="
		<< "\n       LIST SUBMENU\n"
		<< "    U - List the unsorted phones\n" //hash sequence
		<< "    M - List the phones by model number\n"
		<< "    N - List the phones by name\n"
        << "    T - Print out the hash table\n"
		<< "    I - Print as indented list\n"; // by primary key
}

/******************************************************
 Menu UI function for printing the phone database
 */
void printChoice(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond, HashTable<Phone*>* oghash)
{
	char choice = ' ';

	while (choice != 'Q')
	{
        cout << "Choose a menu option (H for help | Q to exit sub menu): ";
		cin >> choice;
		choice = toupper(choice);
		cin.ignore(5, '\n');
		cout << endl;

		switch (choice)
		{
		case 'U':
			//treePrime->postOrder(displayP);
			oghash->printHashSeq(displayTEST);
			break;

		case 'M':
			print_model_header();
			treePrime->inOrder(displayP);
			break;

		case 'N':
			print_name_header();
			treeSecond->inOrder(displayS);
			break;

        case 'T':
            oghash->printHashTable(displayTEST);
            break;

		case 'I':
			treeSecond->printOrder(displayIndent); // CHANGE TO PRIME LATER
			break;

        case 'H':
            print_menu_list();
            break;

		case 'Q':
			cout << "\n\n\t\t Exiting Printing Sub Menu\n\n\n";
			return;

		default:
			cout << "You did not enter a valid choice" << endl;
		}
	}
}

/******************************************************
 The text format for writing into the new phone data text file
 */
void writeOut(Phone* anItem, ofstream& f) {
	f << anItem->getModelNo() << " " << anItem->getModel() << "; " << anItem->getBrand()
		<< "; " << anItem->getStorage() << " " << anItem->getPrice() << endl;
}

/******************************************************
 This function searches the tree nodes to find the node
 in the tree by model name and returns it.
 */
void writeFile(BinarySearchTree<Phone*>* treePrime) {
	ofstream file("PrimeDatabase.txt");
	treePrime->inOrder(writeOut, file);
    cout << "\nFile written!\n\n";
	file.close();
}

/******************************************************
 Takes whatever that was pushed into the undo-delete stack
 and pops them back into all the structures
 */
void undo_delete(BinarySearchTree<Phone*>* treePrime, BinarySearchTree<Phone*>* treeSecond, HashTable<Phone*>* oghash, Stack<Phone*>* stack) {
	if (stack->isEmpty()) {
		cout << "\n[ERROR]: There's nothing to undo!\n\n";
		return;
	}

	Phone r;
	Phone* returned = new Phone(r);
	stack->pop(returned);
	treePrime->insert(returned, compareModelNo);
	treeSecond->insert(returned, compareModel);
	oghash->insert(returned);

	cout << "\nDelete has been reverted! Phone added back:\n" << *returned;
}

/******************************************************
 Prints the table header for when the tree is printed out
 sorted by name
 */
void print_name_header() {
	cout << setw(15) << left << "MODEL NAME" << "    |    "
		 << setw(12) << "MODEL NUMBER" << "  |  "
		 << setw(11) << "  BRAND" << "      |    "
		 << setw(4)  << "SIZE" << "  |   "
		 << setw(7)  << "PRICE" << endl;

	cout << "==============================================================================" << endl;
}

/******************************************************
 Prints the table header for when the tree is printed out
 sorted by model
 */
void print_model_header() {
	cout << setw(12) << " MODEL NUMBER" << "   |    "
		 << setw(15) << left << "MODEL NAME" << "    |    "
		 << setw(11) << "  BRAND" << "    |    "
		 << setw(4)  << "SIZE" << "  |   "
		 << setw(7)  << "PRICE" << endl;

	cout << "================================================================================" << endl;
}

/******************************************************
 Prints the format for when the tree is printed out
 as an indented tree
 */
void displayIndent(Phone* anItem) {
	cout << anItem->getModel() << endl;
}

/******************************************************
 The format for printing by the model number
 */
void displayP(Phone* anItem) {
	cout << setw(12) << right << anItem->getModelNo() << "    |    "
		 << setw(15) << left << anItem->getModel() << "    |    "
		 << setw(11) << left << anItem->getBrand() << "    |    "
		 << setw(4) << right << anItem->getStorage() << "  |  "
		 << setw(7) << right << anItem->getPrice() << endl;
	//    << anItem->getModel() << endl;

}

/******************************************************
 The format for printing by the model name
 */
void displayS(Phone* anItem) {
	cout << setw(15) << left << anItem->getModel() << "    |    "
		 << setw(10) << right << anItem->getModelNo() << "    |    "
		 << setw(11) << left << anItem->getBrand() << "    |    "
		 << setw(4) << right << anItem->getStorage() << "  |  "
		 << setw(7) << right << anItem->getPrice() << endl;
}

/******************************************************
 Readjusts and reassigns the hashtable when the load factor
 becomes too large
 */
void rehash(HashTable<Phone*>* newhash, BinarySearchTree<Phone*>* treePrime)
{
	insertfromBinary(newhash, treePrime->getRoot());
}

/******************************************************
 Traverses through the tree and inserts each phone pointer
 node back into the hashtable when rehashing
 */
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


/******************************************************
 Print the model number of the passed phone pointer
 */
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
		cout << "\nFound Model!\n" << *ptrf << endl;
	else
		cout << "Model not found!\n" << endl;

}

/***********************************************
this function prints out statistics of the hash table
************************************************/
void showStatistic(HashTable<Phone*>* hash)
{
	cout << "\nStatistic of hash table\n"
		<< "Load factor: " << hash->getLoadFactor() << endl
		<< "Number of collisions: " << hash->getCollisions() << endl
		<< "Array size: " << hash->getSize() << endl << endl;
}

/******************************************************
 Compare function that is passed to the BSTs and Hash
 to compare the model numbers of the two phone pointers
 */
int compareModelNo(Phone* left, Phone* right)
{
	if (left->getModelNo() > right->getModelNo())
		return 1;
	else if (left->getModelNo() == right->getModelNo())
		return 0;
	else
        return -1;
}

/******************************************************
 Compare function that is passed to the BSTs and Hash
 to compare the model names of the two phone pointers
 */
int compareModel(Phone* left, Phone* right)	//delete this later
{
	string leftString = left->getModel();
	string rightString = right->getModel();
	transform(leftString.begin(), leftString.end(), leftString.begin(), ::toupper);
	transform(rightString.begin(), rightString.end(), rightString.begin(), ::toupper);

	if (leftString > rightString)
		return 1;
	else if (leftString == rightString)
		return 0;
	else
		return -1;
}
