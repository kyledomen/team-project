#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void print_menu();
void print_menu_search();
void print_menu_list();

int main() {
    print_menu();
    print_menu_search();
    print_menu_list();
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
