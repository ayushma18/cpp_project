#include "../headers/emp.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <termios.h>
#include <string>
#include <chrono>
#include <ctime>
#include <vector>

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
        std::cin >> pass;

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
        cout << "\n\n\t\t\t Employee Control Panel";
        cout << "\n\n\t\t\t................";
        cout << "\n\n 1. View Attendance";
        cout << "\n\n 2. Check Details";
        cout << "\n\n 3. Go Back";
        cout << "\n\n 4. Check In";
        cout << "\n\n 5. View Monthly Attendance";
        cout << "\n\n 6. View Monthly Salary";
        cout << "\n\n 7. View Yearly Attendance";
        cout << "\n\n 8. View Yearly Salary";
        cout << "\n\n 9. Check Out";

        cout << "\n\n Enter Your Choice: " << endl;
        cin >> choice;
        switch (choice) {
            case 1:
                view_attendance();
                cin.ignore();
                cin.get();
                break;

            case 2:
                emp::print_details();
                cin.ignore();
                cin.get();
                break;

            case 3:
                return;

            case 4:
                emp::check_in();
                break;

            case 5:
                int month;
                cout << "Enter month (1-12): ";
                cin >> month;
                emp::view_monthly_attendance(month);
                cin.ignore();
                cin.get();
                break;

            case 6:
                cout << "Enter month (1-12): ";
                cin >> month;
                emp::view_monthly_salary(month);
                cin.ignore();
                cin.get();
                break;

            case 7:
                emp::view_yearly_attendance();
                cin.ignore();
                cin.get();
                break;

            case 8:
                emp::view_yearly_salary();
                cin.ignore();
                cin.get();
                break;
            
            case 9:
                emp::check_out();
                cin.ignore();
                cin.get();
                break;

            default:
                cout << "\n\n Invalid Value...Please Try Again...";
                cin.ignore();
                cin.get();
        }
    }
}

void emp::check_in() {
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    struct std::tm* timeinfo = std::localtime(&current_time);
    //actual
    // if (timeinfo->tm_hour == 10 && timeinfo->tm_min >= 0 && timeinfo->tm_min <= 14) {
    //     in_office = true;
    //     std::cout << "Checked In. Current time is between 10:00 AM and 10:15 AM.\n";
    // } else {
    //     std::cout << "Not Checked In. Current time is not between 10:00 AM and 10:15 AM or after 5:00 PM.\n";
    // }

    //for testing
    if (timeinfo->tm_hour < 13 ) {
        in_office = true;
        writeToFile();
        std::cout << "Checked In. Current time is between 10:00 AM and 10:15 AM.\n";
    } else {
        std::cout << "Not Checked In. Current time is not between 10:00 AM and 10:15 AM or after 5:00 PM.\n";
    }
    std::cout << "Press any key to continue \n";
    fflush(stdin);
    std::cin.ignore();
    std::cin.get();
}


void emp::check_out() {
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    struct std::tm* timeinfo = std::localtime(&current_time);
    //actual
    // if (timeinfo->tm_hour > 17 && in_office==true) {
    //     in_office = false;
    //      std::time_t t = std::time(nullptr);

    //     // Convert it to local time
    //     std::tm* localTime = std::localtime(&t);

    //     // Extract month and day
    //     int month = localTime->tm_mon + 1; // tm_mon is 0-based, so add 1
    //     int day = localTime->tm_mday;
    //     this->attendance[month - 1][day - 1] = true;
    //     std::cout << "Attendance Recorded.\n";
    // } else {
    //     std::cout << "Attendance Not Recorded\n";
    // }

    //for testing
    if (timeinfo->tm_hour > 10 && in_office==true) {

        in_office = false;
         std::time_t t = std::time(nullptr);

        // Convert it to local time
        std::tm* localTime = std::localtime(&t);
        cout << "testtt" <<endl;
        // Extract month and day
        int month = localTime->tm_mon + 1; // tm_mon is 0-based, so add 1
        int day = localTime->tm_mday;
        cout << month << day <<endl;
        cout << attendance.size() << attendance[0].size()<<endl;
        attendance[month-1][day-1] = 1;
        std::cout << "Attendance Recorded.\n";
        writeToFile();
    } else {
        std::cout << "Attendance Not Recorded\n";
    }
    std::cout << "Press any key to continue \n";
    fflush(stdin);
    std::cin.ignore();
    std::cin.get();
}

void emp::view_monthly_attendance(int month) {
// Check if the month is within the valid range
    if (month < 1 || month > 12) {
        std::cout << "Invalid month. Please enter a month between 1 and 12." << std::endl;
        return;
    }

    // Adjust for 0-based index
    month -= 1;
    size_t monthSize = static_cast<size_t>(month);
    // Check if there is attendance data for the given month
    if (monthSize >= attendance.size() || attendance[monthSize].empty()) {
        std::cout << "No attendance data available for month " << month + 1 << "." << std::endl;
        return;
    }

    // Display attendance for the specified month
    std::cout << "Attendance for month " << month + 1 << ":" << std::endl;
    for (size_t day = 0; day < attendance[month].size(); ++day) {
        std::cout << "Day " << day + 1 << ": " << (attendance[month][day] ? "Present" : "Absent") << std::endl;
    }
}

void emp::view_yearly_attendance() {
    // Check if there is attendance data
    if (attendance.empty()) {
        std::cout << "No attendance data available for the year." << std::endl;
        return;
    }

    // Define month names for better readability
    const std::vector<std::string> monthNames = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    // Display attendance for each month
    for (size_t month = 0; month < attendance.size(); ++month) {
        if (!attendance[month].empty()) {
            std::cout << "Attendance for " << monthNames[month] << ":" << std::endl;
            for (size_t day = 0; day < attendance[month].size(); ++day) {
                std::cout << "  Day " << day + 1 << ": " << (attendance[month][day] ? "Present" : "Absent") << std::endl;
            }
        } else {
            std::cout << "No attendance data available for " << monthNames[month] << "." << std::endl;
        }
    }
}

void emp::view_monthly_salary(int month) {
        static const std::string monthNames[] = {
            "January", "February", "March", "April", "May", "June", 
            "July", "August", "September", "October", "November", "December"
        };

        // Check if the month is within the valid range
        if (month < 1 || month > 12) {
            std::cout << "Invalid month. Please enter a month between 1 and 12." << std::endl;
            return;
        }

        // Adjust for 0-based index
        size_t monthIndex = static_cast<size_t>(month - 1);

        // Check if there is attendance data for the given month
        if (monthIndex >= attendance.size() || attendance[monthIndex].empty()) {
            std::cout << monthNames[monthIndex] << ": No attendance data available." << std::endl;
            return;
        }

        // Calculate the total number of present days for the specified month
        size_t presentDays = 0;
        for (size_t day = 0; day < attendance[monthIndex].size(); ++day) {
            if (attendance[monthIndex][day]) {
                presentDays++;
            }
        }

        // Calculate the salary for the specified month based on present days
        double monthlySalary = presentDays * sal;

        // Display salary for the specified month
        std::cout << "Salary for " << monthNames[monthIndex] << ": $" << monthlySalary << std::endl;
    }

    void emp::view_yearly_salary() {
        static const std::string monthNames[] = {
            "January", "February", "March", "April", "May", "June", 
            "July", "August", "September", "October", "November", "December"
        };

        std::cout << "Yearly Salary Breakdown:" << std::endl;

        for (int month = 1; month <= 12; ++month) {
            // Adjust for 0-based index
            size_t monthIndex = static_cast<size_t>(month - 1);

            // Check if there is attendance data for the given month
            if (monthIndex >= attendance.size() || attendance[monthIndex].empty()) {
                std::cout << monthNames[monthIndex] << ": No attendance data available." << std::endl;
                continue;
            }

            // Calculate the total number of present days for the specified month
            size_t presentDays = 0;
            for (size_t day = 0; day < attendance[monthIndex].size(); ++day) {
                if (attendance[monthIndex][day]) {
                    presentDays++;
                }
            }

            // Calculate the salary for the specified month based on present days
            double monthlySalary = presentDays * sal;

            // Display salary for the specified month
            std::cout << monthNames[monthIndex] << ": $" << monthlySalary << std::endl;
        }
    }

void emp::disableEcho(bool enable) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if (!enable)
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    (void)tcsetattr(STDIN_FILENO, TCSANOW, &tty);
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



