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

void buildTree(BinarySearchTree<Phone*> &treePrime, BinarySearchTree<Phone*> &treeSecond, HashTable<Phone*> &oghash);
void deletePhone(BinarySearchTree<Phone*> &treePrime, BinarySearchTree<Phone*> &treeSecond, HashTable<Phone*> &oghash, Stack<Phone*> &stack);
void print_menu();
void write_file(BinarySearchTree<Phone*> &treePrime, BinarySearchTree<Phone*> &treeSecond);
void undo_delete();
void menu_choice(BinarySearchTree<Phone*> &treePrime, BinarySearchTree<Phone*> &treeSecond, HashTable<Phone*> &oghash, Stack<Phone*> &stack);
void insertPhone(BinarySearchTree<Phone*> &treePrime, BinarySearchTree<Phone*> &treeSecond);
void print_menu_search();
void searchChoice(BinarySearchTree<Phone*> treePrime, BinarySearchTree<Phone*> treeSecond);
void searchNumber(BinarySearchTree<Phone*> treePrime);
void searchName(BinarySearchTree<Phone*> treeSecond);
void print_menu_list();
void printChoice(BinarySearchTree<Phone*> treePrime, BinarySearchTree<Phone*> treeSecond);
void displayP(Phone *anItem);
void displayS(Phone *anItem);
void displayTEST(Phone* anItem); // TESTING DISPLAY FUNCTION FOR HASHTABLE ONLY
//HashTable<Phone*> rehash(HashTable<Phone*> oldhash, BinarySearchTree<Phone*> treePrime);

int main() {
    BinarySearchTree<Phone*> treePrime, treeSecond;
    Stack<Phone*> stack;
	HashTable<Phone*> oghash(10);
    buildTree(treePrime, treeSecond, oghash);
	oghash.printHashTable(displayTEST); // this is for testing if the hash table is working

    print_menu();

    menu_choice(treePrime, treeSecond, oghash, stack);



    return 0;
}
/*****************************************************************************
 This function reads data about //toys from a given file and inserts them
 into a sorted Binary Search Tree.
 *****************************************************************************/
void buildTree(BinarySearchTree<Phone*> &treePrime, BinarySearchTree<Phone*> &treeSecond, HashTable<Phone*> &oghash)
{
    ifstream infile;
    string filename = "phonedatabase.txt";
    string modelNo;
    string model;
    string brand;
    int storage;
    double price;

    infile.open(filename);
    if(!infile){
        cout << "Error!" << endl;
        exit(EXIT_FAILURE);
    }
    while (infile >> modelNo){
        infile.ignore();
        getline(infile, model, ';');
        infile.ignore();
        getline(infile, brand, ';');
        infile >> storage >> price;

        //Use constructor to pass the values to the college object.
        Phone temp(modelNo, model, brand, storage, price);
//        Phone *ptr = new Phone();
//        *ptr = temp;
        Phone *ptr = new Phone(temp);

        treePrime.insert(ptr, 'p'); //BST based on primary key
        treeSecond.insert(ptr, 's'); //BST based on secondary key
		oghash.insert(ptr);
//        if ( hash.getLoad() >= 75.00 )
//            hash.rehash


    }
    infile.close();
}

void deletePhone(BinarySearchTree<Phone*> &treePrime, BinarySearchTree<Phone*> &treeSecond, HashTable<Phone*> &oghash, Stack<Phone*> &stack) {
    string target = "";
    cout << "\n Delete\n";
    cout << "=======\n";

    Phone p;
    Phone x;

    while (target != "Q") {
        cout << "Enter the phone's model number to be deleted (or Q to stop deleting): \n";
        getline(cin, target);
        p.setModelNo(target);

        Phone *ptr = new Phone(p);

        Phone *temp = new Phone(x);

        treePrime.getEntry(ptr, temp);
        cout << *temp;

        if (target != "Q") {
            if (treePrime.remove(temp, 'p') && treeSecond.remove(temp, 's')) {
                cout << "Delete successful." << endl;
            } else {
                cout << "Phone model number: " << target << " was not found in the database." << endl;
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

void menu_choice(BinarySearchTree<Phone*> &treePrime, BinarySearchTree<Phone*> &treeSecond, HashTable<Phone*> &oghash, Stack<Phone*> &stack) {
    char choice = ' ';
    cout << "Choose a menu option: ";

    while ( choice != 'Q')
    {
        cin >> choice;
        choice = toupper(choice);
        cin.ignore(5,'\n');

        switch (choice)
        {
            case 'A':
                insertPhone(treePrime, treeSecond);
                break;

            case 'D':
                deletePhone(treePrime, treeSecond, oghash, stack);
                break;

            case 'S':
                print_menu_search();
                searchChoice(treePrime, treeSecond);
                break;

            case 'L':
                print_menu_list();
                printChoice(treePrime, treeSecond);
                break;

            case 'W':
                write_file(treePrime, treeSecond);
                break;

            case 'T':
//                showStats(treePrime,treeSecond);
                break;

            case 'H':
                print_menu();
                break;

            case 'U':
                undo_delete();
                break;

            case 'Q':
                cout << "\n\n\t\t *~~*~~* Good Bye *~~*~~*\n\n\n";
                return;

            default:
                cout << "You did not enter a valid choice" << endl;

        }
        cout << "Enter an option (H – for help): ";
    }
}


//                cout << "*~~*~~*Breadth Traversal*~~*~~*\n" << endl;

/******************************************************
 This function inserts a new phone in the BST's
 */

void insertPhone(BinarySearchTree<Phone*> &treePrime, BinarySearchTree<Phone*> &treeSecond)
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

        cin.ignore();
        cout << "Please enter the model name:" << endl;
        getline(cin, model, '\n');

        cin.clear();
        cout << "Please enter the brand name:" << endl;
        getline(cin, brand, '\n');

        cout << "Please enter the storage amount:" << endl;
        cin >> storage;
        cin.ignore(1000, '\n');
        while(cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Error! Enter storage amount: ";
            cin >> storage;
        }

        cout << "Please enter the price amount:" << endl;
        cin >> price;
        cin.ignore(1000, '\n');
        while(cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Error! Enter price: ";
            cin >> price;
        }

        Phone temp(modelNo, model, brand, storage, price); //Phone object created
        Phone *ptr = new Phone(temp);

        cout << "\nYou have enter this phone: \n" << temp << endl
        << "Is this correct? (Type No or anything else)." << endl; //Should be reworded
        cin >> answer;
        transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
        if (answer != "NO")
        {
            treePrime.insert(ptr, 'p'); //BST based on primary key
            treeSecond.insert(ptr, 's'); //BST based on secondary key

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

void searchChoice(BinarySearchTree<Phone*> treePrime, BinarySearchTree<Phone*> treeSecond)
{
    char choice = ' ';
    cout << "Choose a menu option: ";

    while ( choice != 'Q')
    {
        cin >> choice;
        choice = toupper(choice);
        cin.ignore(5,'\n');

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
void searchNumber(BinarySearchTree<Phone*> treePrime)
{
    string input;
    Phone temp, found;

    cout << "Enter a model number." << endl;
    cin >> input;
    cin.ignore(100,'\n');

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(15,'\n');
        cout << "Input Error: Enter a model number" << endl;
        cin >> input;
    }

    temp.setModelNo(input);
    Phone *ptr = new Phone;
    ptr = &temp;
    Phone *ptrf = new Phone;
    ptrf = &found;

    if (treePrime.getEntry(ptr, ptrf))

        cout << "Found Model!\n" << *ptrf << endl;
    else
        cout << "Model not found!\n" << endl;
}

/******************************************************
 This function searches the tree nodes to find the node
 in the tree by model name and returns it.
 */
void searchName(BinarySearchTree<Phone*> treeSecond)
{
    string input;
    Phone temp, found;

    cout << "Enter a model name" << endl;
    getline(cin,input);

    cout << input << endl;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(10,'\n');
        cout << "Input Error: Enter a model name" << endl;
        getline(cin,input, '\n');
    }

    temp.setModel(input);
    Phone *ptr = new Phone;
    Phone *ptrf = new Phone;
    ptr = &temp;
    ptrf = &found;

    if (treeSecond.getEntry(ptr, ptrf))
        cout << "Found Model!\n" << *ptrf << endl;
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

void printChoice(BinarySearchTree<Phone*> treePrime, BinarySearchTree<Phone*> treeSecond)
{
    char choice = ' ';
    cout << "Choose a menu option: ";

    while ( choice != 'Q')
    {
        cin >> choice;
        choice = toupper(choice);
        cin.ignore(5,'\n');

        switch (choice)
        {
            case 'U':
                treePrime.postOrder(displayP);
                break;

            case 'M':
                treePrime.inOrder(displayP);
                break;

            case 'N':
                treeSecond.inOrder(displayS);
                break;

            case 'I':
                treePrime.printOrder(displayP);
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

void write_file(BinarySearchTree<Phone*> &treePrime, BinarySearchTree<Phone*> &treeSecond) {
    ifstream infilePrime;
    ifstream infile;
    ofstream filePrime ("PrimeDatabase.txt");       // creates PrimeDatabase.txt file
    ofstream fileName ("NameDatabase.txt");         // creates NameDatabase.txt file

    cout << "this is in write file" << endl;
}

void undo_delete() {
}

// displays Model Number
void displayP(Phone *anItem)
{
    cout << anItem->getModelNo() << endl;
//    << anItem->getModel() << endl;

}

// displays Model Name
void displayS(Phone *anItem)
{
    cout << anItem->getModel() << endl << endl;
}

/*
HashTable<Phone*> rehash(HashTable<Phone*> oldhash, BinarySearchTree<Phone*> treePrime)
{
	HashTable<Phone*> newHash = new HashTable<Phone*>((oldhash.getSize() * 2 + 1));

	return newHash;
}
*/

// TESTING DISPLAY FUNCTION FOR THE HASHING TABLE
void displayTEST(Phone* anItem)
{
	cout << anItem->getModelNo();
}
