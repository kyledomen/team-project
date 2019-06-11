#include <iostream>
#include <string>
#include <fstream>
#include "BinarySearchTree.h"
#include "Phone.h"

using namespace std;

void buildTree(BinarySearchTree<Phone> &tree, BinarySearchTree<Phone> &tree);
void print_menu();
void menu_choice(BinarySearchTree<Phone> &tree);
void print_menu_search();
void print_menu_list();

int main() {
    BinarySearchTree<Phone> treeP;
    BinarySearchTree<Phone> treeS;
    
    buildTree(treeP, treeS);
    
    print_menu();
    print_menu_search();
    print_menu_list();
}

/*****************************************************************************
 This function reads data about //toys from a given file and inserts them
 into a sorted Binary Search Tree.
 *****************************************************************************/
void buildTree(BinarySearchTree<Phone> &treeP, BinarySearchTree<Phone> &treeS)
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
        Phone primary(modelNo, model, brand, storage, price);
        Phone secondary(model, modelNo, brand, storage, price);

        treeP.insert(primary); //BST based on primary key
        treeS.insert(secondary); //tempsolution for second BST
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

void menu_choice(BinarySearchTree<Phone> &tree) {
    char choice = ' ';
    cout << "Choose a menu option: ";
    
    while ( choice != 'e')
    {
        cin >> choice;
        cin.ignore(5,'\n');
        
        switch (choice)
        {
            case 'd':
            case 'D':
                
                break;
            case 'b':
            case 'B':
                cout << "*~~*~~*Breadth Traversal*~~*~~*\n" << endl;
                
                break;
            case 's':
            case 'S':
               
                break;
            case 'm':
            case 'M':
                
                break;
            case 'x':
            case 'X':
               
                break;
            case 't':
            case 'T':
                
                break;
            case 'a':
            case 'A':
                
                break;
            case 'h':
            case 'H':
                
                break;
            case 'e':
            case 'E':
                cout << "\n\n\t\t *~~*~~* Good Bye *~~*~~*\n\n\n";
                return;
            default:
                cout << "You did not enter a valid choice" << endl;
                
        }
        cout << "Enter an option (H – for help): ";
    }
}


void print_menu_search() {
    cout << "    ==================="
         << "\n      SEARCH SUBMENU\n"
         << "    ===================\n"
         << "    M - Search by model number\n"
         << "    N - Search by name\n";
}

void print_menu_list() {
    cout << "    ==================="
         << "\n       LIST SUBMENU\n"
         << "    U - List the unsorted phones\n"
         << "    M - List the phones by model number\n"
         << "    N - List the phones by name\n"
         << "    I - Print as indented list\n";
}
