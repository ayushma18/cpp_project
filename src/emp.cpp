#include "../headers/emp.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <termios.h>
#include <string>
using namespace std;

void pressAnyKey() {
    struct termios old_tio, new_tio;
    
    // Get the terminal settings for stdin
    tcgetattr(STDIN_FILENO, &old_tio);
    
    // Set the new settings for stdin
    new_tio = old_tio;
    new_tio.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    
    // Wait for a key press
    getchar();
    
    // Restore the old settings
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}

void emp::login() {
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

        if (user == "e" && pass == "e") {
            std::cout << "\n\n\n\t\t\t Congratulations, login successful...";
            std::cout << "\n\n\n\t\t\t\t\t Loading";
            sleep(1);
            emp::menu();
            break;
        } else if (user != "e" && pass == "e") {
            std::cout << "\n\n\n Your user name is wrong...";
            std::cin.ignore();
            std::cin.get();
        } else if (user == "e" && pass != "e") {
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




void emp::menu() {
    while (true) {
        int choice;
        system("clear");
        cout << "\n\n\t\t\t................";
        cout << "\n\n\t\t\t Child Control Panel";
        cout << "\n\n\t\t\t................";
        cout << "\n\n 1. Attendance";
        cout << "\n\n 2. Check Details";
        cout << "\n\n 3. Go Back";
        cout << "\n\n Enter Your Choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                // emp::check_attendance();
                break;
            case 2:
                // emp::check_details();
                break;
            case 3:
                menu();
            default:
                cout << "\n\n Invalid Value...Please Try Again...";
                cin.ignore();
                cin.get();
        }
    }
}





// void emp::check_attendance() {
//     system("clear");
//     fstream file, file1;
//     int d, m, y, a_date, a_month, a_year, t_id, emp_id, sal, group_id, count = 0;
//     string name, address;
    
//     cout << "\n\n\t\tCheck Employee Attendance";
//     file.open("emp.txt", ios::in);
//     file1.open("attendance.txt", ios::in);
    
//     if (!file || !file1) {
//         cout << "\n\n File Opening Error...";
//         cin.ignore();
//         cin.get();
//         return;
//     }
    
//     cout << "\n\n Date: ";
//     cin >> d;
//     cout << "\n Month: ";
//     cin >> m;
//     cout << "\n Year: ";
//     cin >> y;
    
//     file1.close();
//     system("clear");
//     cout << "\n\n\t\tCheck Employee Attendance";
//     cout << "\n\n Employee ID\tPresent\tAbsents";
    
//     while (file >> emp_id >> name >> sal >> address >> group_id) {
//         count = 0;
//         file1.open("attendance.txt", ios::in);
//         while (file1 >> t_id >> a_date >> a_month >> a_year) {
//             if (emp_id == t_id && d <= a_date && m == a_month && y == a_year) {
//                 count++;
//             }
//         }
//         file1.close();
//         cout << "\n " << emp_id << "\t\t" << count << "\t\t" << 30 - count;
//     }
//     file.close();
//     cin.ignore();
//     cin.get();
// }




// void admin::insert() {
//     system("clear");
//     fstream file;
//     int emp_id, sal, group_id;
//     string name, address;
    
//     cout << "\n\n\t\t\tInsert Record";
//     cout << "\n\n\n Employee ID: ";
//     cin >> emp_id;
//     cout << "\n\n Employee Name: ";
//     cin >> name;
//     cout << "\n\n Employee Salary: ";
//     cin >> sal;
//     cout << "\n\n Employee Address: ";
//     cin >> address;
//     cout << "\n\n Employee Group ID: ";
//     cin >> group_id;
    
//     file.open("emp.txt", ios::out | ios::app);
//     file << emp_id << " " << name << " " << sal << " " << address << " " << group_id << "\n";
//     file.close();
    
//     cout << "\n\n\n\t\t\tNew Record Inserted Successfully...";
//     cin.ignore();
//     cin.get();
// }

// void emp::display() {
//     system("clear");
//     fstream file;
//     int emp_id, sal, group_id;
//     string name, address;
    
//     cout << "\n\n\t\t\tDisplay Record";
//     file.open("emp.txt", ios::in);
//     if (!file) {
//         cout << "\n\n File Opening Error...";
//         cin.ignore();
//         cin.get();
//         return;
//     }
    
//     while (file >> emp_id >> name >> sal >> address >> group_id) {
//         cout << "\n\n Employee ID: " << emp_id;
//         cout << "\n Employee Name: " << name;
//         cout << "\n Employee Salary: " << sal;
//         cout << "\n Employee Address: " << address;
//         cout << "\n Employee Group ID: " << group_id;
//         cout << "\n---------------------------";
//     }
    
//     file.close();
//     cin.ignore();
//     cin.get();
// }

// void emp::search() {
//     system("clear");
//     fstream file;
//     int emp_idd, emp_id, sal, group_id, found = 0;
//     string name, address;
    
//     cout << "\n\n\t\t\tSearch Record";
//     file.open("emp.txt", ios::in);
//     if (!file) {
//         cout << "\n\n File Opening Error...";
//         cin.ignore();
//         cin.get();
//         return;
//     }
    
//     cout << "\n\n Employee ID For Search: ";
//     cin >> emp_idd;
    
//     while (file >> emp_id >> name >> sal >> address >> group_id) {
//         if (emp_idd == emp_id) {
//             system("clear");
//             cout << "\n\n\t\t\tSearch Record";
//             cout << "\n\n Employee ID: " << emp_id;
//             cout << "\n Employee Name: " << name;
//             cout << "\n Employee Salary: " << sal;
//             cout << "\n Employee Address: " << address;
//             cout << "\n Employee Group ID: " << group_id;
//             found = 1;
//         }
//     }
    
//     file.close();
//     if (!found)
//         cout << "\n\n Employee ID Cannot Be Found...";
//     cin.ignore();
//     cin.get();
// }

// void admin::modify() {
//     system("clear");
//     fstream file, file1;
//     int emp_id, sal, group_id, rest_id, found = 0;
//     string name, address, name1, address1;
    
//     cout << "\n\n\t\t\tModify Record";
//     cout << "\n\n Employee ID For Modify: ";
//     cin >> rest_id;
    
//     file.open("emp.txt", ios::in);
//     file1.open("temp.txt", ios::out);
    
//     if (!file) {
//         cout << "\n\n File Opening Error...";
//         cin.ignore();
//         cin.get();
//         return;
//     }
    
//     while (file >> emp_id >> name >> sal >> address >> group_id) {
//         if (rest_id == emp_id) {
//             cout << "\n\n New Employee Name: ";
//             cin >> name1;
//             cout << "\n New Employee Salary: ";
//             cin >> sal;
//             cout << "\n New Employee Address: ";
//             cin >> address1;
//             cout << "\n New Employee Group ID: ";
//             cin >> group_id;
//             file1 << emp_id << " " << name1 << " " << sal << " " << address1 << " " << group_id << "\n";
//             found = 1;
//         } else {
//             file1 << emp_id << " " << name << " " << sal << " " << address << " " << group_id << "\n";
//         }
//     }
    
//     file.close();
//     file1.close();
    
//     remove("emp.txt");
//     rename("temp.txt", "emp.txt");
    
//     if (found)
//         cout << "\n\n\t\t\tRecord Modified Successfully...";
//     else
//         cout << "\n\n Employee ID Cannot Be Found...";
//     cin.ignore();
//     cin.get();
// }

// void admin::del() {
//     system("clear");
//     fstream file, file1;
//     int emp_id, sal, group_id, rest_id, found = 0;
//     string name, address;
    
//     cout << "\n\n\t\t\tDelete Record";
//     cout << "\n\n Employee ID For Delete: ";
//     cin >> rest_id;
    
//     file.open("emp.txt", ios::in);
//     file1.open("temp.txt", ios::out);
    
//     if (!file) {
//         cout << "\n\n File Opening Error...";
//         cin.ignore();
//         cin.get();
//         return;
//     }
    
//     while (file >> emp_id >> name >> sal >> address >> group_id) {
//         if (rest_id != emp_id) {
//             file1 << emp_id << " " << name << " " << sal << " " << address << " " << group_id << "\n";
//         } else {
//             found = 1;
//         }
//     }
    
//     file.close();
//     file1.close();
    
//     remove("emp.txt");
//     rename("temp.txt", "emp.txt");
    
//     if (found)
//         cout << "\n\n\t\t\tRecord Deleted Successfully...";
//     else
//         cout << "\n\n Employee ID Cannot Be Found...";
//     cin.ignore();
//     cin.get();
// }

// void emp::group() {
//     cout << "Group Record\n";
//     cin.ignore();
//     cin.get();
// }

// void admin::search_group() {
//     cout << "Search Group\n";
//     cin.ignore();
//     cin.get();
// }

// void admin::show_group() {
//     cout << "Show Group\n";
//     cin.ignore();
//     cin.get();
// }

// void emp::check_attendance() {
//     system("clear");
//     fstream file, file1;
//     int d, m, y, a_date, a_month, a_year, t_id, emp_id, sal, group_id, count = 0;
//     string name, address;
    
//     cout << "\n\n\t\tCheck Employee Attendance";
//     file.open("emp.txt", ios::in);
//     file1.open("attendance.txt", ios::in);
    
//     if (!file || !file1) {
//         cout << "\n\n File Opening Error...";
//         cin.ignore();
//         cin.get();
//         return;
//     }
    
//     cout << "\n\n Date: ";
//     cin >> d;
//     cout << "\n Month: ";
//     cin >> m;
//     cout << "\n Year: ";
//     cin >> y;
    
//     file1.close();
//     system("clear");
//     cout << "\n\n\t\tCheck Employee Attendance";
//     cout << "\n\n Employee ID\tPresent\tAbsents";
    
//     while (file >> emp_id >> name >> sal >> address >> group_id) {
//         count = 0;
//         file1.open("attendance.txt", ios::in);
//         while (file1 >> t_id >> a_date >> a_month >> a_year) {
//             if (emp_id == t_id && d <= a_date && m == a_month && y == a_year) {
//                 count++;
//             }
//         }
//         file1.close();
//         cout << "\n " << emp_id << "\t\t" << count << "\t\t" << 30 - count;
//     }
//     file.close();
//     cin.ignore();
//     cin.get();
// }

// void admin::search_attendance() {
//     system("clear");
//     fstream file, file1;
//     int emp_idd, d, m, y, a_date, a_month, a_year, t_id, count = 0;
    
//     cout << "\n\n\t\tSearch Employee Attendance";
//     file.open("emp.txt", ios::in);
//     file1.open("attendance.txt", ios::in);
    
//     if (!file || !file1) {
//         cout << "\n\n File Opening Error...";
//         cin.ignore();
//         cin.get();
//         return;
//     }
    
//     cout << "\n\n Employee ID: ";
//     cin >> emp_idd;
//     cout << "\n\n Date: ";
//     cin >> d;
//     cout << "\n Month: ";
//     cin >> m;
//     cout << "\n Year: ";
//     cin >> y;
    
//     file.close();
//     system("clear");
//     cout << "\n\n\t\tCheck Employee Attendance";
    
//     while (file1 >> t_id >> a_date >> a_month >> a_year) {
//         if (emp_idd == t_id && d <= a_date && m == a_month && y == a_year) {
//             count++;
//         }
//     }
//     file1.close();
    
//     if (count > 0) {
//         cout << "\n\n Employee ID\tPresent\tAbsents";
//         cout << "\n " << emp_idd << "\t\t" << count << "\t\t" << 30 - count;
//     } else {
//         cout << "\n\n Employee ID Not Found...";
//     }
//     cin.ignore();
//     cin.get();
// }

// void emp::salary_slip() {
//     cout << "Salary Slip\n";
//     cin.ignore();
//     cin.get();
// }



