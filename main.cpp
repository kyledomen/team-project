#include <iostream>
#include <string>
#include <fstream>
#include "BinarySearchTree.h"
#include "Phone.h"

using namespace std;

void buildTree(BinarySearchTree<Phone> &treePrime, BinarySearchTree<Phone> &treeSecond);
void print_menu();
void menu_choice(BinarySearchTree<Phone> &treePrime, BinarySearchTree<Phone> &treeSecond);
void insertPhone(BinarySearchTree<Phone> &treePrime, BinarySearchTree<Phone> &treeSecond);
void print_menu_search();
void searchChoice(BinarySearchTree<Phone> treePrime, BinarySearchTree<Phone> treeSecond);
void print_menu_list();

int main() {
    BinarySearchTree<Phone> treePrime, treeSecond;
    
    buildTree(treePrime, treeSecond);
    
    print_menu();

    print_menu_list();
}

/*****************************************************************************
 This function reads data about //toys from a given file and inserts them
 into a sorted Binary Search Tree.
 *****************************************************************************/
void buildTree(BinarySearchTree<Phone> &treePrime, BinarySearchTree<Phone> &treeSecond)
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

        treePrime.insert(temp, 'p'); //BST based on primary key
        treeSecond.insert(temp, 's'); //BST based on secondary key

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

void menu_choice(BinarySearchTree<Phone> &treePrime, BinarySearchTree<Phone> &treeSecond) {
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
//                printData(treePrime,treeSecond);
                break;
                
            case 'w':
            case 'W':
               //writeDatabase(treePrime,treeSecond);
                break;
            case 't':
            case 'T':
//                showStats(treePrime,treeSecond);
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

void insertPhone(BinarySearchTree<Phone> &treePrime, BinarySearchTree<Phone> &treeSecond)
{
    string answer = "No";
    while (answer == "No")
    {
        string modelNo;
        string model;
        string brand;
        int storage;
        double price;
    
        cout << "Please enter the model number." << endl;
        cin >> modelNo;
    
        cout << "Please enter the model name." << endl;
        getline(cin, model, '\n');
    
        cout << "Please enter the brand name." << endl;
        getline(cin, brand, '\n');
    
        cout << "Please enter the storage amount." << endl;
        cin >> storage;
    
        cout << "Please enter the price amount." << endl;
        cin >> price;
        
        Phone temp(modelNo, model, brand, storage, price); //Phone object created
        
        cout << "You have enter this phone: \n" << temp << endl
        << "Is this correct? (Type No or anything else)." << endl; //Should be reworded
        cin >> answer;
        if (answer != "No")
        {
            treePrime.insert(temp, 'p'); //BST based on primary key
            treeSecond.insert(temp, 's'); //BST based on secondary key
        }
    }
    
}

void print_menu_search() {
    cout << "    ==================="
         << "\n      SEARCH SUBMENU\n"
         << "    ===================\n"
         << "    M - Search by model number\n"
         << "    N - Search by name\n";
}

void searchChoice(BinarySearchTree<Phone> treePrime, BinarySearchTree<Phone> treeSecond)
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
//                searchNumber(treePrime, treeSecond);
                break;
            case 'n':
            case 'N':
//                searchName(treePrime, treeSecond);
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


void print_menu_list() {
    cout << "    ==================="
         << "\n       LIST SUBMENU\n"
         << "    U - List the unsorted phones\n"
         << "    M - List the phones by model number\n"
         << "    N - List the phones by name\n"
         << "    I - Print as indented list\n";
}
