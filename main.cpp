#include "headers/emp.h"
#include <iostream>
#include <string>
#include <fstream>

void intro() {
    std::system("clear");
    std::cout << "\n\n\n\n\n\n\n";
    std::cout << "\t\t\t................";
    std::cout << "\n\t\t\t................";
    std::cout << "\n\n\t\t\t Employee Management System";
    std::cout << "\n\n\t\t\t................";
    std::cout << "\n\t\t\t................";
    std::cout << "\n\nPress any key to continue...";
    std::cin.get();
}
using namespace std;

int main() {
    intro();
    string filename="data.txt";
    std::cout << " Who are you?? \n 1. Admin \n 2. Employee \n 3. Exit \n";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        admin obj;
        obj.setFilename(filename);
        obj.login();
    } else if (choice == 2) {
        emp obj;
        obj.setFilename(filename);
        obj.login();
    } else {
        exit(0);
    }
    return 0;
}
