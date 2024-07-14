#include "../headers/emp.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <termios.h>
#include <string>
#include "../headers/crypto.h"
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;


// Function to extract numbers from a filename
int extractNumberFromFilename(const std::string& filename) {
    std::string numberStr = filename;
    // Remove the file extension (assuming ".txt" or similar)
    numberStr.erase(numberStr.find_last_of("."), std::string::npos);
    // Extract number from remaining part of the filename
    return std::stoi(numberStr);
}

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
        int x,id;
        std::string sr;
        std::string pathh = "data";

        std::cout << "\n\n\t\t\t................";
        std::cout << "\n\n\t\t\t Admin Control Panel";
        std::cout << "\n\n\t\t\t................";
        std::cout << "\n\n\n 1. Edit Record";
        std::cout << "\n 2. Search Record";
        std::cout << "\n 3. Delete Employee";
        std::cout<<"\n 4. Edit Attendance";
        std::cout << "\n 5. Display Record (All)";
        std::cout << "\n 6. Create Employee: ";

        std::cout << "\n Enter Your Choice: ";
        std::cin >> x;
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
                admin::delete_emp(id);
                break;

            case 4:
            {
                std::cout << "\n Enter id :";
                std::cin >> id;
                this->set_id(id);
                this->changeAttendance();
                this->writeToFile();
                cout << "Press any button to continue";
                std::cin.ignore();
                std::cin.get();
                break;
            }
             case 5:

                try {
                    for (const auto& entry : fs::directory_iterator(pathh)) {
                        if (fs::is_regular_file(entry.status())) {
                            std::string filename = entry.path().filename().string();
                            if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".txt") {
                                int number = extractNumberFromFilename(filename);
                                this->set_id(number);
                                this->print_details();
                                cout << "\n" <<endl;
                            }
                        }
                    }
                } catch (const fs::filesystem_error& e) {
                    std::cerr << "Filesystem error: " << e.what() << '\n';
                } catch (const std::exception& e) {
                    std::cerr << "General error: " << e.what() << '\n';
                }
                cout << "Press any button to continue";
                std::cin.ignore();
                std::cin.get();
                break;

             case 6:
                this->create_emp();
                break;

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
    e.changeAttendance();
    RSA::PrivateKey privateKey;
    RSA::PublicKey publicKey;
    GenerateKeys(privateKey, publicKey, "key/" + to_string(e.emp_id) + "private.key", "key/" + to_string(e.emp_id) + "public.key",4096);
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
     e.changeAttendance();
     RSA::PrivateKey privateKey;
     RSA::PublicKey publicKey;
     GenerateKeys(privateKey, publicKey, "key/" + to_string(e.emp_id) + "private.key", "key/" + to_string(e.emp_id) + "public.key");
     e.publicKey = publicKey;
     e.writeToFile();
     return e;
    }
}
void admin::delete_emp(int id) {
    std::string filename = "data/" + to_string(id) + ".txt";
    std::string publick = "key/"+to_string(id) +"public"+".key";
    std::string privatek = "key/"+to_string(id) +"private"+".key";


    if (remove(filename.c_str()) != 0 || remove(publick.c_str()) != 0 || remove(privatek.c_str()) != 0) {
        std::cout << "Error deleting file";
    } else {
        std::cout << "File successfully deleted";
    }
}

// emp emp::modify_record(int id) {
//     emp e;
//     e.set_id(id);
//     e.readFromFile();

//     std::cout << "\n\n Modify Employee Record";
//     std::cout << "\n\n Enter New Employee Name (current: " << e.name << "): ";
//     std::cin >> e.name;
//     std::cout << "\n\n Enter New Employee Salary (current: " << e.sal << "): ";
//     std::cin >> e.sal;
//     std::cout << "\n\n Enter New Employee Group ID (current: " << e.group_id << "): ";
//     std::cin >> e.group_id;
//     std::cout << "\n\n Enter New Employee Attendance (current: " << e.attendance << "): ";
//     std::cin >> e.attendance;

//     e.writeToFile();
//     return e;
// }