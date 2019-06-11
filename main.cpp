#include <iostream>
#include <string>
#include <fstream>
#include "BinarySearchTree.h"
#include "Phone.h"

using namespace std;

void buildTree(BinarySearchTree<Phone*> &treePrime, BinarySearchTree<Phone*> &treeSecond);
void print_menu();
void menu_choice(BinarySearchTree<Phone*> &treePrime, BinarySearchTree<Phone*> &treeSecond);
void insertPhone(BinarySearchTree<Phone*> &treePrime, BinarySearchTree<Phone*> &treeSecond);
void print_menu_search();
void searchChoice(BinarySearchTree<Phone*> treePrime, BinarySearchTree<Phone*> treeSecond);
void searchNumber(BinarySearchTree<Phone*> treePrime);
void searchName(BinarySearchTree<Phone*> treeSecond);
void print_menu_list();
void printChoice(BinarySearchTree<Phone*> treePrime, BinarySearchTree<Phone*> treeSecond);
void displayP(Phone &anItem);
void displayS(Phone &anItem);

int main() {
    BinarySearchTree<Phone*> treePrime, treeSecond;

    buildTree(treePrime, treeSecond);
    
    print_menu();
    menu_choice(treePrime, treeSecond);
    
    return 0;
}

/*****************************************************************************
 This function reads data about //toys from a given file and inserts them
 into a sorted Binary Search Tree.
 *****************************************************************************/
void buildTree(BinarySearchTree<Phone*> &treePrime, BinarySearchTree<Phone*> &treeSecond)
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
        Phone *ptr = new Phone;
        ptr = &temp;

        treePrime.insert(*ptr, 'p'); //BST based on primary key
        treeSecond.insert(*ptr, 's'); //BST based on secondary key

    }
    infile.close();
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
         << "Q - Quit\n"
         << "*****\n";
}
/******************************************************
 This function chooses the menu options from the user.
 */

void menu_choice(BinarySearchTree<Phone*> &treePrime, BinarySearchTree<Phone*> &treeSecond) {
    char choice = ' ';
    cout << "Choose a menu option: ";

    while ( choice != 'q')
    {
        cin >> choice;
        cin.ignore(5,'\n');

        switch (choice)
        {
            case 'a':
            case 'A':

                insertPhone(treePrime,treeSecond);
                break;

            case 'd':
            case 'D':
                //deletePhone(treePrime,treeSecond);
                break;
            case 's':
            case 'S':
                print_menu_search();
                searchChoice(treePrime,treeSecond);
                break;

            case 'l':
            case 'L':
                print_menu_list();
                printChoice(treePrime,treeSecond);
                break;

            case 'w':
            case 'W':
               //writeDatabase(treePrime,treeSecond);
                break;
            case 't':
            case 'T':
//                showStats(treePrime,treeSecond);
                break;

            case 'h':
            case 'H':
                print_menu();
                break;

            case 'q':
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
    while (answer != "No")
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

        cout << "Please enter the price amount:" << endl;
        cin >> price;

        Phone temp(modelNo, model, brand, storage, price); //Phone object created

        cout << "\nYou have enter this phone: \n" << temp << endl
        << "Is this correct? (Type No or anything else)." << endl; //Should be reworded
        cin >> answer;
        if (answer != "No" || answer != "no")
        {
            treePrime.insert(temp, 'p'); //BST based on primary key
            treeSecond.insert(temp, 's'); //BST based on secondary key
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

    while ( choice != 'q')
    {
        cin >> choice;
        cin.ignore(5,'\n');

        switch (choice)
        {
            case 'm':
            case 'M':
                searchNumber(treePrime);
                break;
            case 'n':
            case 'N':
                searchName(treeSecond);
                break;

            case 'q':
            case 'Q':
                cout << "\n\n\t\t *~~*~~* Good Bye *~~*~~*\n\n\n";
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

    if (treePrime.getEntry(temp, found))
        cout << "Found Model!\n" << found << endl;
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
    cin >> input;
    cin.ignore(100,'\n');

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(10,'\n');
        cout << "Input Error: Enter a model name" << endl;
        cin >> input;
    }

    temp.setModel(input);

    if (treeSecond.getEntry(temp, found))
        cout << "Found Model!\n" << found << endl;
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
    
    while ( choice != 'q' || choice != 'Q')
    {
        cin >> choice;
        cin.ignore(5,'\n');
        
        switch (choice)
        {
            case 'u':
            case 'U':
//                unsortedPhones(treePrime,treeSecond);
                break;
                
            case 'm':
            case 'M':
                treePrime.inOrder(displayP);
                break;
                
            case 'n':
            case 'N':
                treeSecond.inOrder(displayS);
                break;
                
            case 'i':
            case 'I':
                treePrime.printOrder(displayP);
                break;
                
            case 'q':
            case 'Q':
                cout << "\n\n\t\t *~~*~~* Good Bye *~~*~~*\n\n\n";
                return;
                
            default:
                cout << "You did not enter a valid choice" << endl;
        }
        cout << "Choose a menu option or Q to exit: " << endl;
    }
}

// displays Model Number
void displayP(Phone &anItem)
{
    cout << anItem.getModelNo() << endl;
}

// displays Model Name
void displayS(Phone &anItem)
{
    cout << anItem.getModel() << endl;
}
