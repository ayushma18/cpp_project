#include "../headers/emp.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <termios.h>
#include <string>
using namespace std;

void disableEcho(bool enable = true) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if (enable) {
        tty.c_lflag |= ECHO;
    } else {
        tty.c_lflag &= ~ECHO;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void admin::login(){
    while (true) {
        std::system("clear");
        string user, pass;
        char ch;
        std::cout << "\n\n\n\n\n";
        std::cout << "\t\t\t................";
        std::cout << "\n\n\t\t\t login process";
        std::cout << "\n\n\t\t\t................";
        std::cout << "\n\n\n Enter User Name: ";
        std::cin >> user;
        std::cout << "\n\n Enter password: ";
        std::fflush(stdin);
        std::cin>>pass;


        while ((ch = getchar()) != '\n') {
            pass.push_back(ch);
            std::cout << '*';
        }
        disableEcho(true);

        if (user == "a" && pass == "a") {
            std::cout << "\n\n\n\t\t\t Congratulations, login successful...";
            std::cout << "\n\n\n\t\t\t\t\t Loading";
            sleep(1);
            admin::menu();
            break;
        } else if (user != "a" && pass == "a") {
            std::cout << "\n\n\n Your user name is wrong...";
            std::cin.ignore();
            std::cin.get();
        } else if (user == "admin@gmail.com" && pass != "AP") {
            std::cout << "\n\n\n Your password is wrong...";
            std::cin.ignore();
            std::cin.get();
        } else {
            std::cout << "\n\n\n Both user name and password are wrong...";
            std::cin.ignore();
            std::cin.get();
        }
    }
}

void admin::menu() {
    while (true) {
        std::system("clear");
        int x;
        std::cout << "\n\n\t\t\t................";
        std::cout << "\n\n\t\t\t Admin Control Panel";
        std::cout << "\n\n\t\t\t................";
        std::cout << "\n\n\n 1. Insert Record";
        std::cout << "\n 2. Search Record";
        std::cout << "\n 3. Modify Record";
        std::cout << "\n 4. Delete Record";
        std::cout << "\n 5. Display Record";
        std::cout << "\n 6. Salary slip";
        std::cout << "\n 7. Check Attendance";
        std::cout << "\n 8. Search Attendance";
        std::cout << "\n 9. Group Record";
        std::cout << "\n 10. Show All Group";
        std::cout << "\n 11. Go Back";
        std::cout << "\n 12. Enter Your Choice: ";
        std::cin >> x;
        switch (x) {
            case 1:
                // insert();
                break;
            case 2:
                this->menu();
                break;
            case 3:
                exit(0);
            default:
                std::cout << "\n\n Invalid value...Please Try Again...";
                std::cin.ignore();
                std::cin.get();
        }
    }
}