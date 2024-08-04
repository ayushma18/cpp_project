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
        cout << "\n\n 3. Check In";
        cout << "\n\n 4. Check Out";
        cout << "\n\n 5. View Monthly Attendance";
        cout << "\n\n 6. View Yearly Attendance";
        cout << "\n\n 7. View Monthly Salary";
        cout << "\n\n 8. View Yearly Salary";
        cout << "\n\n 9. Go Back";

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

            case 7:
                cout << "Enter month (1-12): ";
                cin >> month;
                emp::view_monthly_salary(month);
                cin.ignore();
                cin.get();
                break;

            case 6:
                emp::view_yearly_attendance();
                cin.ignore();
                cin.get();
                break;

            case 8:
                emp::view_yearly_salary();
                cin.ignore();
                cin.get();
                break;
            
            case 4:
                emp::check_out();
                cin.ignore();
                cin.get();
                break;
            case 9 :
            

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
    if (timeinfo->tm_hour == 10 && timeinfo->tm_min >= 0 && timeinfo->tm_min <= 14) {
        in_office = true;
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
    if (timeinfo->tm_hour > 17 && in_office==true) {
        in_office = false;
         std::time_t t = std::time(nullptr);

        // Convert it to local time
        std::tm* localTime = std::localtime(&t);

        // Extract month and day
        int month = localTime->tm_mon + 1; // tm_mon is 0-based, so add 1
        int day = localTime->tm_mday;
        this->attendance[month - 1][day - 1] = true;
        std::cout << "Attendance Recorded.\n";
    } else {
        std::cout << "Attendance Not Recorded\n";
    }

    //for testing
    // if (timeinfo->tm_hour > 10 && in_office==true) {

    //     in_office = false;
    //      std::time_t t = std::time(nullptr);

    //     // Convert it to local time
    //     std::tm* localTime = std::localtime(&t);
    //     cout << "testtt" <<endl;
    //     // Extract month and day
    //     int month = localTime->tm_mon + 1; // tm_mon is 0-based, so add 1
    //     int day = localTime->tm_mday;
    //     cout << month << day <<endl;
    //     cout << attendance.size() << attendance[0].size()<<endl;
    //     attendance[month-1][day-1] = 1;
    //     std::cout << "Attendance Recorded.\n";
    //     writeToFile();
    // } else {
    //     std::cout << "Attendance Not Recorded\n";
    // }


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
        std::cout << "Salary for " << monthNames[monthIndex] << ": Rs." << monthlySalary << std::endl;
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
            std::cout << monthNames[monthIndex] << ": Rs." << monthlySalary << std::endl;
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