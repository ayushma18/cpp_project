#include "../headers/emp.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <termios.h>
#include <string>
#include "../headers/crypto.h"
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
        std::string sr;
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
        std::cout << "\n 13. Create Employee: ";

        std::cin >> id;
        switch (x) {
             case 1:
                std::cout << "\n Enter id :";
                std::cin >> id;
                emp::insert(id);
                break;
             case 2:
                std::cout << "\n Enter id :";
                std::cin >> id;
            
                emp::search_record(id);
                std::cout << "\n\nPress any key to continue";
                std::cin.get();
                std::cin.get();
                break;
                case 3:
                std::cout << "\n Enter id :";
                std::cin >> id;
                emp::modify_record(id);
                std::cout << "\n\nRecord modified successfully.";
                std::cout << "\n\nPress any key to continue";
                std::cin.get();
                std::cin.get();
                break;
             case 4:
                exit(0);
             case 5:
                this->create_emp();
                exit(0);
             default:
                std::cout << "\n\n Invalid value...Please Try Again...";
                std::cin.ignore();
                std::cin.get();
        }
    }
}

emp admin::create_emp() {
    emp e;
    std::cout << "\n\n Enter Employee Name: ";
    std::cin >> e.name;
    std::cout << "\n\n Enter Employee ID: ";
    std::cin >> e.emp_id;
    std::cout << "\n\n Enter Employee Salary: ";
    std::cin >> e.sal;
    std::cout << "\n\n Enter Employee Group ID: ";
    std::cin >> e.group_id;
    std::cout << "\n\n Enter Employee Attendance: ";
    std::cin >> e.attendance;
    
    RSA::PrivateKey privateKey;
    RSA::PublicKey publicKey;
    GenerateKeys(privateKey, publicKey, "key/" + to_string(e.emp_id) + "private.key", "key/" + to_string(e.emp_id) + "public.key");
    e.publicKey = publicKey;
    e.writeToFile();
    return e;
}
emp emp::search_record(int id)
{
    emp e1;
    e1.set_id(id);
    e1.readFromFile();
    e1.print_details();
    return e1;
}

emp emp::insert(int id)
{
   
    {
     emp e;
     e.emp_id = id;
     std::cout << "\n\n Enter Employee Name: ";
     std::cin >> e.name;
     std::cout << "\n\n Enter Employee Salary: ";
     std::cin >> e.sal;
     std::cout << "\n\n Enter Employee Group ID: ";
     std::cin >> e.group_id;
     std::cout << "\n\n Enter Employee Attendance: ";
     std::cin >> e.attendance;

     RSA::PrivateKey privateKey;
     RSA::PublicKey publicKey;
     GenerateKeys(privateKey, publicKey, "key/" + to_string(e.emp_id) + "private.key", "key/" + to_string(e.emp_id) + "public.key");
     e.publicKey = publicKey;
     e.writeToFile();
     return e;
    }
}
emp emp::modify_record(int id) {
    emp e;
    e.set_id(id);
    e.readFromFile();

    std::cout << "\n\n Modify Employee Record";
    std::cout << "\n\n Enter New Employee Name (current: " << e.name << "): ";
    std::cin >> e.name;
    std::cout << "\n\n Enter New Employee Salary (current: " << e.sal << "): ";
    std::cin >> e.sal;
    std::cout << "\n\n Enter New Employee Group ID (current: " << e.group_id << "): ";
    std::cin >> e.group_id;
    std::cout << "\n\n Enter New Employee Attendance (current: " << e.attendance << "): ";
    std::cin >> e.attendance;

    e.writeToFile();
    return e;
}