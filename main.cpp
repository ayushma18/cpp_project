#include <iostream>
#include <fstream>
#include <unistd.h>
#include <termios.h>
#include <string>
using namespace std;

class var {
public:
    int emp_id, sal, group_id;
    string name, address;
};

class emp {
public:
    virtual void menu();
    virtual void child_menu();
    void insert();
    void display();
    void search();
    void modify();
    void del();
    void group();
    void search_group();
    void show_group();
    void check_attendance();
    void search_attendance();
    void salary_slip();
};

class child : public emp {
public:
    void login();
    void main_menu();
    void child_menu() override;
    void attendance();
} obj;

void intro() {
    system("clear");
    cout << "\n\n\n\n\n\n\n";
    cout << "\t\t\t................";
    cout << "\n\t\t\t................";
    cout << "\n\n\t\t\t Employee Management System";
    
    cout << "\n\n\t\t\t................";
    cout << "\n\t\t\t................";
    cout << "\n\nPress any key to continue...";
    cin.ignore();
    cin.get();
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

void child::login() {
    while (true) {
        system("clear");
        string user, pass;
        int admin;
        char ch;
        cout << "\n\n\n\n\n";
        cout << "\t\t\t................";
        cout << "\n\n\t\t\t login process";
        cout << "\n\n\t\t\t................";
        cout << "\n\n\n Enter User Name: ";
        cin >> user;
        cout << "\n\n Enter password: ";
        fflush(stdin);
        cin>>pass;
        disableEcho(false);
        cout << "\n Who are you ?"<< endl;
        cout << "1. Admin "<< endl;
        cout << "2. User" <<endl;
        fflush(stdin);
        cin >> admin;

        while ((ch = getchar()) != '\n') {
            pass.push_back(ch);
            cout << '*';
        }
        disableEcho(true);

        if (user == "pudasainiaayushma@gmail.com" && pass == "AP") {
            cout << "\n\n\n\t\t\t Congratulations, login successful...";
            cout << "\n\n\n\t\t\t\t\t Loading";
            sleep(1);
            if(admin==1)
                emp::menu();
            else
                child::menu();
            break;
        } else if (user != "pudasainiaayushma@gmail.com" && pass == "AP") {
            cout << "\n\n\n Your user name is wrong...";
            cin.ignore();
            cin.get();
        } else if (user == "pudasainiaayushma@gmail.com" && pass != "AP") {
            cout << "\n\n\n Your password is wrong...";
            cin.ignore();
            cin.get();
        } else {
            cout << "\n\n\n Both user name and password are wrong...";
            cin.ignore();
            cin.get();
        }
    }
}

void emp::menu() {
    while (true) {
        system("clear");
        int x;
        cout << "\n\n\t\t\t................";
        cout << "\n\n\t\t\t Admin Control Panel";
        cout << "\n\n\t\t\t................";
        cout << "\n\n\n 1. Insert Record";
        cout << "\n 2. Search Record";
        cout << "\n 3. Modify Record";
        cout << "\n 4. Delete Record";
        cout << "\n 5. Display Record";
        cout << "\n 6. Salary slip";
        cout << "\n 7. Check Attendance";
        cout << "\n 8. Search Attendance";
        cout << "\n 9. Group Record";
        cout << "\n 10. Show All Group";
        cout << "\n 11. Go Back";
        cout << "\n 12. Enter Your Choice: ";
        cin >> x;
        switch (x) {
            case 1:
                insert();
                break;
            case 2:
                obj.child_menu();
                break;
            case 3:
                exit(0);
            default:
                cout << "\n\n Invalid value...Please Try Again...";
                cin.ignore();
                cin.get();
        }
    }
}

void emp::child_menu() {}

void child::child_menu() {
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
                attendance();
                break;
            case 2:
                emp::search();
                break;
            case 3:
                main_menu();
            default:
                cout << "\n\n Invalid Value...Please Try Again...";
                cin.ignore();
                cin.get();
        }
    }
}

void emp::insert() {
    system("clear");
    fstream file;
    int emp_id, sal, group_id;
    string name, address;
    
    cout << "\n\n\t\t\tInsert Record";
    cout << "\n\n\n Employee ID: ";
    cin >> emp_id;
    cout << "\n\n Employee Name: ";
    cin >> name;
    cout << "\n\n Employee Salary: ";
    cin >> sal;
    cout << "\n\n Employee Address: ";
    cin >> address;
    cout << "\n\n Employee Group ID: ";
    cin >> group_id;
    
    file.open("emp.txt", ios::out | ios::app);
    file << emp_id << " " << name << " " << sal << " " << address << " " << group_id << "\n";
    file.close();
    
    cout << "\n\n\n\t\t\tNew Record Inserted Successfully...";
    cin.ignore();
    cin.get();
}

void emp::display() {
    system("clear");
    fstream file;
    int emp_id, sal, group_id;
    string name, address;
    
    cout << "\n\n\t\t\tDisplay Record";
    file.open("emp.txt", ios::in);
    if (!file) {
        cout << "\n\n File Opening Error...";
        cin.ignore();
        cin.get();
        return;
    }
    
    while (file >> emp_id >> name >> sal >> address >> group_id) {
        cout << "\n\n Employee ID: " << emp_id;
        cout << "\n Employee Name: " << name;
        cout << "\n Employee Salary: " << sal;
        cout << "\n Employee Address: " << address;
        cout << "\n Employee Group ID: " << group_id;
        cout << "\n---------------------------";
    }
    
    file.close();
    cin.ignore();
    cin.get();
}

void emp::search() {
    system("clear");
    fstream file;
    int emp_idd, emp_id, sal, group_id, found = 0;
    string name, address;
    
    cout << "\n\n\t\t\tSearch Record";
    file.open("emp.txt", ios::in);
    if (!file) {
        cout << "\n\n File Opening Error...";
        cin.ignore();
        cin.get();
        return;
    }
    
    cout << "\n\n Employee ID For Search: ";
    cin >> emp_idd;
    
    while (file >> emp_id >> name >> sal >> address >> group_id) {
        if (emp_idd == emp_id) {
            system("clear");
            cout << "\n\n\t\t\tSearch Record";
            cout << "\n\n Employee ID: " << emp_id;
            cout << "\n Employee Name: " << name;
            cout << "\n Employee Salary: " << sal;
            cout << "\n Employee Address: " << address;
            cout << "\n Employee Group ID: " << group_id;
            found = 1;
        }
    }
    
    file.close();
    if (!found)
        cout << "\n\n Employee ID Cannot Be Found...";
    cin.ignore();
    cin.get();
}

void emp::modify() {
    system("clear");
    fstream file, file1;
    int emp_id, sal, group_id, rest_id, found = 0;
    string name, address, name1, address1;
    
    cout << "\n\n\t\t\tModify Record";
    cout << "\n\n Employee ID For Modify: ";
    cin >> rest_id;
    
    file.open("emp.txt", ios::in);
    file1.open("temp.txt", ios::out);
    
    if (!file) {
        cout << "\n\n File Opening Error...";
        cin.ignore();
        cin.get();
        return;
    }
    
    while (file >> emp_id >> name >> sal >> address >> group_id) {
        if (rest_id == emp_id) {
            cout << "\n\n New Employee Name: ";
            cin >> name1;
            cout << "\n New Employee Salary: ";
            cin >> sal;
            cout << "\n New Employee Address: ";
            cin >> address1;
            cout << "\n New Employee Group ID: ";
            cin >> group_id;
            file1 << emp_id << " " << name1 << " " << sal << " " << address1 << " " << group_id << "\n";
            found = 1;
        } else {
            file1 << emp_id << " " << name << " " << sal << " " << address << " " << group_id << "\n";
        }
    }
    
    file.close();
    file1.close();
    
    remove("emp.txt");
    rename("temp.txt", "emp.txt");
    
    if (found)
        cout << "\n\n\t\t\tRecord Modified Successfully...";
    else
        cout << "\n\n Employee ID Cannot Be Found...";
    cin.ignore();
    cin.get();
}

void emp::del() {
    system("clear");
    fstream file, file1;
    int emp_id, sal, group_id, rest_id, found = 0;
    string name, address;
    
    cout << "\n\n\t\t\tDelete Record";
    cout << "\n\n Employee ID For Delete: ";
    cin >> rest_id;
    
    file.open("emp.txt", ios::in);
    file1.open("temp.txt", ios::out);
    
    if (!file) {
        cout << "\n\n File Opening Error...";
        cin.ignore();
        cin.get();
        return;
    }
    
    while (file >> emp_id >> name >> sal >> address >> group_id) {
        if (rest_id != emp_id) {
            file1 << emp_id << " " << name << " " << sal << " " << address << " " << group_id << "\n";
        } else {
            found = 1;
        }
    }
    
    file.close();
    file1.close();
    
    remove("emp.txt");
    rename("temp.txt", "emp.txt");
    
    if (found)
        cout << "\n\n\t\t\tRecord Deleted Successfully...";
    else
        cout << "\n\n Employee ID Cannot Be Found...";
    cin.ignore();
    cin.get();
}

void emp::group() {
    cout << "Group Record\n";
    cin.ignore();
    cin.get();
}

void emp::search_group() {
    cout << "Search Group\n";
    cin.ignore();
    cin.get();
}

void emp::show_group() {
    cout << "Show Group\n";
    cin.ignore();
    cin.get();
}

void emp::check_attendance() {
    system("clear");
    fstream file, file1;
    int d, m, y, a_date, a_month, a_year, t_id, emp_id, sal, group_id, count = 0;
    string name, address;
    
    cout << "\n\n\t\tCheck Employee Attendance";
    file.open("emp.txt", ios::in);
    file1.open("attendance.txt", ios::in);
    
    if (!file || !file1) {
        cout << "\n\n File Opening Error...";
        cin.ignore();
        cin.get();
        return;
    }
    
    cout << "\n\n Date: ";
    cin >> d;
    cout << "\n Month: ";
    cin >> m;
    cout << "\n Year: ";
    cin >> y;
    
    file1.close();
    system("clear");
    cout << "\n\n\t\tCheck Employee Attendance";
    cout << "\n\n Employee ID\tPresent\tAbsents";
    
    while (file >> emp_id >> name >> sal >> address >> group_id) {
        count = 0;
        file1.open("attendance.txt", ios::in);
        while (file1 >> t_id >> a_date >> a_month >> a_year) {
            if (emp_id == t_id && d <= a_date && m == a_month && y == a_year) {
                count++;
            }
        }
        file1.close();
        cout << "\n " << emp_id << "\t\t" << count << "\t\t" << 30 - count;
    }
    file.close();
    cin.ignore();
    cin.get();
}

void emp::search_attendance() {
    system("clear");
    fstream file, file1;
    int emp_idd, d, m, y, a_date, a_month, a_year, t_id, count = 0;
    
    cout << "\n\n\t\tSearch Employee Attendance";
    file.open("emp.txt", ios::in);
    file1.open("attendance.txt", ios::in);
    
    if (!file || !file1) {
        cout << "\n\n File Opening Error...";
        cin.ignore();
        cin.get();
        return;
    }
    
    cout << "\n\n Employee ID: ";
    cin >> emp_idd;
    cout << "\n\n Date: ";
    cin >> d;
    cout << "\n Month: ";
    cin >> m;
    cout << "\n Year: ";
    cin >> y;
    
    file.close();
    system("clear");
    cout << "\n\n\t\tCheck Employee Attendance";
    
    while (file1 >> t_id >> a_date >> a_month >> a_year) {
        if (emp_idd == t_id && d <= a_date && m == a_month && y == a_year) {
            count++;
        }
    }
    file1.close();
    
    if (count > 0) {
        cout << "\n\n Employee ID\tPresent\tAbsents";
        cout << "\n " << emp_idd << "\t\t" << count << "\t\t" << 30 - count;
    } else {
        cout << "\n\n Employee ID Not Found...";
    }
    cin.ignore();
    cin.get();
}

void emp::salary_slip() {
    cout << "Salary Slip\n";
    cin.ignore();
    cin.get();
}

void child::main_menu() {
    cout << "Main Menu\n";
    cin.ignore();
    cin.get();
}

void child::attendance() {
    cout << "Attendance\n";
    cin.ignore();
    cin.get();
}

int main() {
    intro();
    obj.login();
    return 0;
}
